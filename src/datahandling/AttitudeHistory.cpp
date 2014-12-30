//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file History.cpp
*  \brief Encapsulation of History memento object.
*  \author $Author: nilspace $
*  \version $Revision: 1.10 $
*  \date    $Date: 2003/05/27 17:35:52 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "AttitudeHistory.h"
namespace O_SESSAME {

AttitudeHistory::AttitudeHistory()
{
    ResetHistory();
    m_AttitudeHistory.reserve(HISTORY_RESERVE_SIZE);
    m_AttitudeInterpolations.reserve(HISTORY_RESERVE_SIZE);
}

AttitudeHistory::~AttitudeHistory()
{

}

void AttitudeHistory::AppendHistory(const double &_appendTime, const Rotation &_appendRotation, const Vector &_appendAngVel)
{
    AppendHistory(ssfTime(_appendTime), AttitudeState(_appendRotation, _appendAngVel));
}

void AttitudeHistory::AppendHistory(const ssfTime &_appendTime, const Rotation &_appendRotation, const Vector &_appendAngVel)
{
    History::AppendHistory(_appendTime);
    m_AttitudeHistory.push_back(AttitudeState(_appendRotation, _appendAngVel));
    return;
}
    
void AttitudeHistory::AppendHistory(const double &_appendTime, const AttitudeState &_appendAttitudeState)
{
    AppendHistory(ssfTime(_appendTime), _appendAttitudeState);
}

void AttitudeHistory::AppendHistory(const ssfTime &_appendTime, const AttitudeState &_appendAttitudeState)
{
    History::AppendHistory(_appendTime);
    m_AttitudeHistory.push_back(_appendAttitudeState);
    return;
}

/*! \todo figure out how to append a large chunk of one vector<> to another */
void AttitudeHistory::AppendHistory(const vector<ssfTime> &_appendTime, const vector<AttitudeState> &_appendAttitudeState)
{
    vector<AttitudeState>::const_iterator iter = _appendAttitudeState.begin();
    // History::AppendHistory returns the distance from the end over any overlapping states.
    vector<ssfTime>::difference_type retDistance = History::AppendHistory(_appendTime);
    
    // If there is an overlap, delete the attitude states following the overlap point.
    if(retDistance != 0)
        m_AttitudeHistory.erase(m_AttitudeHistory.end()-retDistance, m_AttitudeHistory.end());

    for(iter = _appendAttitudeState.begin(); iter != _appendAttitudeState.end(); ++iter)
        m_AttitudeHistory.push_back(*iter);

    return;
}

/*! \todo Determine if the multiple AppendHistory's can be combined in some smart way. */
void AttitudeHistory::AppendHistory(const vector<ssfTime> &_appendTime, const vector<Rotation> &_appendRotation, const vector<Vector> &_appendAngVel)
{
    vector<ssfTime>::const_iterator iterTime;
    vector<Rotation>::const_iterator iterRot;
        iterRot = _appendRotation.begin();
    vector<Vector>::const_iterator iterVec;
        iterVec = _appendAngVel.begin();
        
    for(iterTime = _appendTime.begin(); iterTime != _appendTime.end(); ++iterTime)
    {
        AppendHistory(*iterTime, *iterRot, *iterVec);
        ++iterRot;
        ++iterVec;
    }
    return;
}

void AttitudeHistory::ResetHistory()
{
    vector<AttitudeState> newAttitude(0);
    m_AttitudeHistory.swap(newAttitude);
    History::ResetHistory();
    return;
}


Matrix AttitudeHistory::GetHistory(const RotationType &_rotType)
{
    // initialize the output matrix based on the size of the desired output rotation, the angular velocity 
    //	output, and an element for time. The number of rows is equal to the number of time elements.
    int RotVectorSize = (m_AttitudeHistory.back()).GetRotation().GetRotation(_rotType).getIndexBound();
    int AngVelVectorSize = (m_AttitudeHistory.back()).GetAngularVelocity().getIndexBound();
    Matrix returnMatrix(m_TimeHistory.size(), 1 + RotVectorSize + AngVelVectorSize);
    
    for(int ii = 0; ii < m_TimeHistory.size(); ii++)
    {
        returnMatrix(MatrixIndexBase + ii, MatrixIndexBase) = m_TimeHistory[ii].GetSeconds();
        returnMatrix(MatrixIndexBase + ii, _(MatrixIndexBase+1,MatrixIndexBase + RotVectorSize)) = ~m_AttitudeHistory[ii].GetRotation().GetRotation(_rotType);
        returnMatrix(MatrixIndexBase + ii, _(MatrixIndexBase + 1 + RotVectorSize, MatrixIndexBase + RotVectorSize + AngVelVectorSize)) = ~(m_AttitudeHistory[ii].GetAngularVelocity()(_));
    }
    return returnMatrix;
}

AttitudeState AttitudeHistory::GetState(const ssfTime& _requestedTime)
{
    Rotation tempRot;
    Vector tempAngVel(3);
    GetState(_requestedTime, tempRot, tempAngVel);
    return AttitudeState(tempRot, tempAngVel);
}
void AttitudeHistory::GetState(const ssfTime& _requestedTime, Rotation& _returnRotation, Vector& _returnAngVelVector)
{
    int RotVectorSize = QUATERNION_SIZE;
    int AngVelVectorSize = (m_AttitudeHistory.back()).GetAngularVelocity().getIndexBound();
 
    // History::GetState returns the index of the nearest state.
    vector<ssfTime>::difference_type nearestTimeIndex = History::GetState(_requestedTime);
 
    int numDataPoints = 0;
    if(m_OriginalInterpolator)
        numDataPoints = m_OriginalInterpolator->GetNumberDataPoints();
    else /*! \todo implement better error handling strategy */
        return;
    Vector timeVector(numDataPoints);
    Matrix dataMatrix(numDataPoints, RotVectorSize+AngVelVectorSize);
    Vector tempVector(RotVectorSize+AngVelVectorSize);
    
    // See if there is data at the requested time.
    if(m_TimeHistory[nearestTimeIndex] != _requestedTime)
    {
        // Determine if there is currently an interpolation through the requested point.
        //	if there isn't, create one, then evaluate the interpolation at the requested data point.
        while(m_AttitudeInterpolations.capacity() < nearestTimeIndex)
        {
            m_AttitudeInterpolations.reserve(m_AttitudeHistory.capacity() + HISTORY_RESERVE_SIZE);
        }
        // Check to see if the data is initialized to hold an interpolation
        if(!m_AttitudeInterpolations[nearestTimeIndex])
        {            
            // fill in the 'missing' interpolations
            for(int kk = m_AttitudeInterpolations.size(); kk < nearestTimeIndex; ++kk)
                    m_AttitudeInterpolations.push_back(m_OriginalInterpolator->NewPointer());

            m_AttitudeInterpolations.push_back(m_OriginalInterpolator->NewPointer());
        }
        // Calculate the interpolation parameters if necessary
        if(!m_AttitudeInterpolations[nearestTimeIndex]->GetValid())
        {
            for(int ii = 1; ii <= numDataPoints; ++ii) 
            {
                timeVector(ii) = m_TimeHistory[nearestTimeIndex - (numDataPoints/2-1) + ii].GetSeconds();
                dataMatrix(ii,_(1,RotVectorSize)) = ~m_AttitudeHistory[nearestTimeIndex - (numDataPoints/2-1) + ii].GetRotation().GetRotation(Quaternion_Type);
                dataMatrix(ii,_(RotVectorSize+1,RotVectorSize+AngVelVectorSize)) = ~m_AttitudeHistory[nearestTimeIndex - (numDataPoints/2-1) + ii].GetAngularVelocity();
            }

            m_AttitudeInterpolations[nearestTimeIndex]->Interpolate(timeVector, dataMatrix); 
        }

        tempVector = m_AttitudeInterpolations[nearestTimeIndex]->Evaluate(_requestedTime.GetSeconds());
        _returnRotation.Set(Quaternion(~tempVector(_(1,4))));
        _returnAngVelVector(_)  = tempVector(_(5,7));
    }
    else
    { // there happens to be meshpoint data at the requested time, return it.
        _returnRotation = m_AttitudeHistory[nearestTimeIndex].GetRotation();
        _returnAngVelVector =  m_AttitudeHistory[nearestTimeIndex].GetAngularVelocity();
    }

    return;
}

} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: AttitudeHistory.cpp,v $
*	Revision 1.10  2003/05/27 17:35:52  nilspace
*	Updated to prevent errors.
*	
*	Revision 1.9  2003/05/20 17:50:01  nilspace
*	Updated comments.
*	
*	Revision 1.8  2003/05/13 18:45:35  nilspace
*	Added interpolation functionality.
*	
*	Revision 1.7  2003/05/01 18:24:36  nilspace
*	Prevented overlapping Appends by removing the old states and times.
*	
*	Revision 1.6  2003/04/29 20:57:46  nilspace
*	Updated to work with Propagator.
*	
*	Revision 1.5  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.4  2003/04/25 17:14:59  nilspace
*	Added OrbitHistory & made sure it builds.
*	Moved Appending time to History.cpp.
*	
*	Revision 1.3  2003/04/23 17:00:46  nilspace
*	Changed to work with AttitudeState and not Rotation and AngVel seperately.
*	Time is now stored as ssfTime.
*	
*	Revision 1.1  2003/03/27 20:29:19  nilspace
*	Initial Submission.
*
******************************************************************************/

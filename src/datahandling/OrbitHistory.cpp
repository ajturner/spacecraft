//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitHistory.cpp
*  \brief Encapsulation of Orbit History memento object.
*  \author $Author: nilspace $
*  \version $Revision: 1.7 $
*  \date    $Date: 2003/05/22 21:01:31 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "OrbitHistory.h"
namespace O_SESSAME {

OrbitHistory::OrbitHistory()
{
    ResetHistory();
    m_OrbitHistory.reserve(HISTORY_RESERVE_SIZE);
    m_OrbitInterpolations.reserve(HISTORY_RESERVE_SIZE);
}
    
void OrbitHistory::AppendHistory(const double &_appendTime, const OrbitState &_appendOrbitState)
{
    AppendHistory(ssfTime(_appendTime), _appendOrbitState);
}

void OrbitHistory::AppendHistory(const ssfTime &_appendTime, const OrbitState &_appendOrbitState)
{
    History::AppendHistory(_appendTime);
    m_OrbitHistory.push_back(_appendOrbitState);
    return;
}

void OrbitHistory::AppendHistory(const vector<ssfTime> &_appendTime, const vector<OrbitState> &_appendOrbitState)
{
    vector<OrbitState>::const_iterator iter;
    // History::AppendHistory returns the distance from the end over any overlapping states.
    vector<ssfTime>::difference_type retDistance = History::AppendHistory(_appendTime);
    
    // If there is an overlap, delete the orbit states following the overlap point.
    if(retDistance != 0)
        m_OrbitHistory.erase(m_OrbitHistory.end()-retDistance, m_OrbitHistory.end());
        
    // Append the new states to the orbit history.
    for(iter = _appendOrbitState.begin(); iter != _appendOrbitState.end(); ++iter)
        m_OrbitHistory.push_back(*iter);

    return;
}

void OrbitHistory::ResetHistory()
{
    vector<OrbitState> newOrbit(0);
    m_OrbitHistory.swap(newOrbit);
    History::ResetHistory();
    return;
}


Matrix OrbitHistory::GetHistory()
{
    /*! \todo Grab the history depending on the desired state return type (elements, position, velocity, etc.) */
    // initialize the output matrix based on the size of the desired output state, 
    // and an element for time. The number of rows is equal to the number of time elements.
    int OrbitVectorSize = (m_OrbitHistory.back()).GetState().getIndexBound();
    Matrix returnMatrix(m_TimeHistory.size(), 1 + OrbitVectorSize);
    
    for(int ii = 0; ii < m_TimeHistory.size(); ii++)
    {
        returnMatrix(MatrixIndexBase + ii, MatrixIndexBase) = m_TimeHistory[ii].GetSeconds();
        returnMatrix(MatrixIndexBase + ii, _(MatrixIndexBase+1,MatrixIndexBase + OrbitVectorSize)) = ~m_OrbitHistory[ii].GetState();
    }
    return returnMatrix;
}
OrbitState OrbitHistory::GetState(const ssfTime& _requestedTime)
{
    OrbitState tempOrbState;
    GetState(_requestedTime, tempOrbState);
    return tempOrbState;
}
void OrbitHistory::GetState(const ssfTime& _requestedTime, OrbitState& _returnOrbitState)
{
    // History::GetState returns the index of the nearest state.
    vector<ssfTime>::difference_type nearestTimeIndex = History::GetState(_requestedTime);
 
    int numDataPoints = 0;
    if(m_OriginalInterpolator)
        numDataPoints = m_OriginalInterpolator->GetNumberDataPoints();
    else /*! \todo implement better error handling strategy */
        return;
    Vector timeVector(numDataPoints);
    Matrix dataMatrix(numDataPoints, NUM_POSVEL_ELEMENTS);
    Vector tempVector(NUM_POSVEL_ELEMENTS);
    
    // See if there is data at the requested time.
    if(m_TimeHistory[nearestTimeIndex] != _requestedTime)
    {
        // Determine if there is currently an interpolation through the requested point.
        //	if there isn't, create one, then evaluate the interpolation at the requested data point.
        while(m_OrbitInterpolations.capacity() < nearestTimeIndex)
        {
            m_OrbitInterpolations.reserve(m_OrbitHistory.capacity() + HISTORY_RESERVE_SIZE);
        }
        // Check to see if the data is initialized to hold an interpolation
        if(!m_OrbitInterpolations[nearestTimeIndex])
        {            
            // fill in the 'missing' interpolations
            for(int kk = m_OrbitInterpolations.size(); kk < nearestTimeIndex; ++kk)
                    m_OrbitInterpolations.push_back(m_OriginalInterpolator->NewPointer());

            m_OrbitInterpolations.push_back(m_OriginalInterpolator->NewPointer());
        }
        // Calculate the interpolation parameters if necessary
        if(!m_OrbitInterpolations[nearestTimeIndex]->GetValid())
        {
            for(int ii = 1; ii <= numDataPoints; ++ii) 
            {
                timeVector(ii) = m_TimeHistory[nearestTimeIndex - (numDataPoints/2-1) + ii].GetSeconds();
                dataMatrix(ii,_) = ~m_OrbitHistory[nearestTimeIndex - (numDataPoints/2-1) + ii].GetStateRepresentation()->GetPositionVelocity();
            }

            m_OrbitInterpolations[nearestTimeIndex]->Interpolate(timeVector, dataMatrix); 
        }

        tempVector = m_OrbitInterpolations[nearestTimeIndex]->Evaluate(_requestedTime.GetSeconds());
        _returnOrbitState.SetStateRepresentation(new PositionVelocity);
        _returnOrbitState.GetStateRepresentation()->SetPositionVelocity(tempVector);
            
        // Set the returned orbit frame to the same as the history's stored orbit states.
        _returnOrbitState.SetOrbitFrame((m_OrbitHistory.front()).GetOrbitFrame());
    }
    else
    { // there happens to be meshpoint data at the requested time, return it.
         _returnOrbitState = m_OrbitHistory[nearestTimeIndex];
    }

    return;
}
} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitHistory.cpp,v $
*	Revision 1.7  2003/05/22 21:01:31  nilspace
*	Updated comments and added SetOrbitRepresentation(new PositionVelocity).
*	
*	Revision 1.6  2003/05/20 17:50:01  nilspace
*	Updated comments.
*	
*	Revision 1.5  2003/05/13 18:45:35  nilspace
*	Added interpolation functionality.
*	
*	Revision 1.4  2003/05/01 18:24:36  nilspace
*	Prevented overlapping Appends by removing the old states and times.
*	
*	Revision 1.3  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.2  2003/04/25 17:15:00  nilspace
*	Added OrbitHistory & made sure it builds.
*	Moved Appending time to History.cpp.
*	
*	Revision 1.1  2003/04/25 13:39:08  nilspace
*	Initial Submission.
*	
*	Revision 1.1  2003/03/27 20:29:19  nilspace
*	Initial Submission.
*
******************************************************************************/

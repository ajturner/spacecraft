//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file History.cpp
*  \brief Encapsulation of History memento object.
*  \author $Author: rsharo $
*  \version $Revision: 1.11 $
*  \date    $Date: 2003/10/18 21:37:27 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "History.h"
#include "utils/LinearInterpolator.h"
namespace O_SESSAME {

History::History() : m_OriginalInterpolator(new LinearInterpolator)
{
    ResetHistory();
    m_TimeHistory.reserve(HISTORY_RESERVE_SIZE);
    m_TimeInterpolations.reserve(HISTORY_RESERVE_SIZE);
    m_TimeInterpolations.front() = NULL;
}

History::~History()
{
    // delete the old interpolator 
    if(m_OriginalInterpolator)
        delete m_OriginalInterpolator;
}

void History::AppendHistory(const double &_appendTime)
{
    AppendHistory(ssfTime(_appendTime));
}
void History::AppendHistory(const ssfTime &_appendTime)
{
    m_TimeHistory.push_back(_appendTime);
}

vector<ssfTime>::difference_type History::AppendHistory(const vector<ssfTime> &_appendTime)
{
    vector<ssfTime>::const_iterator iter;
    
    // Determine if there is already a time history that overlaps with the appending time
    vector<ssfTime>::iterator replacementTime = std::find_if(m_TimeHistory.begin(), m_TimeHistory.end(), bind2nd(greater_equal<ssfTime>(), *(_appendTime.begin())));
    vector<ssfTime>::difference_type retDistance = 0;

    // If there is an overlap, delete the times following the overlap point.
    if(replacementTime != m_TimeHistory.end())
    {
        // Store the distance from the overlapping point to the end & then delete the overlap.
        retDistance = distance(replacementTime, m_TimeHistory.end());
        m_TimeHistory.erase(replacementTime, m_TimeHistory.end());
    }
    // Append the new times to the time history.
    for(iter = _appendTime.begin(); iter != _appendTime.end(); ++iter)
        m_TimeHistory.push_back(*iter);

    return retDistance;
}
    
void History::ResetHistory()
{
    vector<ssfTime> newTime(0);
    m_TimeHistory.swap(newTime);
    return;
}

Matrix History::GetHistory()
{
    Matrix returnMatrix(m_TimeHistory.size(), 1);
    int ii = 0;
    vector<ssfTime>::const_iterator iter;
    for(iter = m_TimeHistory.begin(); iter != m_TimeHistory.end(); ++iter)
    {
        returnMatrix(MatrixIndexBase + ii, MatrixIndexBase) = iter->GetSeconds();
        ++ii;
    }
    
    return returnMatrix;

}

vector<ssfTime>::difference_type  History::GetState(const ssfTime& _requestedTime)
{
    // Find the nearest (lower) corresponding time point
    vector<ssfTime>::iterator nearestTimeIterator = find_if(m_TimeHistory.begin(), m_TimeHistory.end(), bind2nd(greater_equal<ssfTime>(), _requestedTime));
    // Store the distance from the first matching data point to the end
    vector<ssfTime>::difference_type nearestTimeIndex = distance(m_TimeHistory.begin(), nearestTimeIterator);

    /* The code commented out below was a model for interpolation in the derived classes. It is not needed, but 
        was left to verify against for the time being. nilspace:(13.5.03)
    int numDataPoints = 0;
    if(m_OriginalInterpolator)
        numDataPoints = m_OriginalInterpolator->GetNumberDataPoints();
    else 
        return nearestTimeIndex;
    Vector timeVector(numDataPoints);
    Matrix dataMatrix(numDataPoints, 1);
    
    // See if there is data at the requested time.
    if((*nearestTimeIterator != _requestedTime) && (nearestTimeIterator != m_TimeHistory.end()))
    {
        // Determine if there is currently an interpolation through the requested point.
        //	if there isn't, create one, then evaluate the interpolation at the requested data point.
        while(m_TimeInterpolations.capacity() < nearestTimeIndex)
        {
            m_TimeInterpolations.reserve(m_TimeInterpolations.capacity() + HISTORY_RESERVE_SIZE);
        }
        if(!m_TimeInterpolations[nearestTimeIndex])
        {
        
            // fill in the 'missing' interpolations
            for(int kk = m_TimeInterpolations.size(); kk < nearestTimeIndex; ++kk)
                    m_TimeInterpolations.push_back(m_OriginalInterpolator->NewPointer());

            m_TimeInterpolations.push_back(m_OriginalInterpolator->NewPointer());
        }
        // Calculate the interpolation parameters if necessary
        if(!m_TimeInterpolations[nearestTimeIndex]->GetValid())
        {
            for(int ii = 1; ii <= numDataPoints; ++ii) 
            {
                timeVector(ii) = m_TimeHistory[nearestTimeIndex - (numDataPoints/2-1) + ii].GetSeconds();
                for(int jj = 1; jj <= dataMatrix[MatrixColsIndex].getIndexBound(); ++jj)
                {
                    dataMatrix(ii,jj) = m_TimeHistory[nearestTimeIndex - (numDataPoints/2-1) + ii].GetSeconds();
                }
            }
            
            m_TimeInterpolations[nearestTimeIndex]->Interpolate(timeVector, dataMatrix); 
        }

        _requestedTime.Set(m_TimeInterpolations[nearestTimeIndex]->Evaluate(_requestedTime.GetSeconds())(1));

    }
    else if((nearestTimeIterator == m_TimeHistory.begin()) || (nearestTimeIterator == m_TimeHistory.end()))
    { // the requested time isn't in the stored interval
        return (nearestTimeIndex = -1);
    }
    else
    { // there happens to be meshpoint data at the requested time, return it.
        _requestedTime = *nearestTimeIterator;
    }
    */
    return nearestTimeIndex;
}

void History::SetInterpolator(Interpolator* _newInterpolator)
{
    // delete the old interpolator 
    if(m_OriginalInterpolator)
        delete m_OriginalInterpolator;
        
    // make a copy of the new base interpolator
    m_OriginalInterpolator = _newInterpolator->Clone();
}

} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: History.cpp,v $
*	Revision 1.11  2003/10/18 21:37:27  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.10  2003/05/22 21:01:44  nilspace
*	Updated comments.
*	
*	Revision 1.9  2003/05/20 17:50:01  nilspace
*	Updated comments.
*	
*	Revision 1.8  2003/05/15 18:10:50  nilspace
*	Fixed the constructor initialize error of an extra ,
*	
*	Revision 1.7  2003/05/13 18:45:35  nilspace
*	Added interpolation functionality.
*	
*	Revision 1.6  2003/05/01 18:24:36  nilspace
*	Prevented overlapping Appends by removing the old states and times.
*	
*	Revision 1.5  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.4  2003/04/25 17:14:59  nilspace
*	Added OrbitHistory & made sure it builds.
*	Moved Appending time to History.cpp.
*	
*	Revision 1.3  2003/04/23 17:01:02  nilspace
*	Time is now stored as an ssfTime object.
*	
*	Revision 1.2  2003/04/23 16:30:58  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/03/27 20:29:02  nilspace
*	Initial Submission.
*
******************************************************************************/

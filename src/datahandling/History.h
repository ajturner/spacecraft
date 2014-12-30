//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file History.h
*  \brief Interface to the abstract History class.
*  \author $Author: rsharo $
*  \version $Revision: 1.14 $
*  \date    $Date: 2003/10/18 21:37:27 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __HISTORY_H__
#define __HISTORY_H__
#include <vector>
#include <functional>
#include <algorithm>
#include "utils/Time.h"
#include "utils/Interpolator.h"
using namespace std;
namespace O_SESSAME {
//////////////////////////////////////////////////////////////////////////////////////////////////
/*! @defgroup DataHandling Data Handling
*	This toolbox includes all the functionality regarding the handling, storage, importing, and 
* exporting of data from the spacecraft simulation environment. The primary classes include the 
* History class and its derived classes. These History objects store various spacecraft states and 
* provide for various manipulations of the data.
*
* \par Extension Points:
*
*/

/*! @defgroup StateHistory State History 
* \ingroup DataHandling
*/
#define HISTORY_RESERVE_SIZE 1000 /*!< \brief expected history storage size. Used to reserve memory of states ahead of time. This number should be characteristic of the typical number of states in a history matrix. */
/*! \brief Base class for histories storing state variables, also stores time states.
* \ingroup StateHistory
*
*  The History class provides a common interface for the group of classes which
*	store previous state information. The user can append new state information, 
*	output the current state history, or reset the entire history. If the user appends
*	a time which earlier than the end of the current history, the current history
*	is deleted from that point on, and the new time is appended.
*	The History class also provides the common storage of the time history.
*
* \par Examples:
\code
History myHistory;          // create a history with an empty collection
myHistory.AppendHistory(0); // add 0 seconds to the history
myHistory.ResetHistory();   // reset the history to an empty collection
myHistory.AppendHistory(10);// add 10 seconds to the history

cout << myHistory.GetHistory() << endl;  // Get a matrix of the stored times and output
\endcode
*/
class History
{
public:
    /*! \brief Creates an instance of History.
        */
    History();
    
    /*! \brief Default Deconstructor
        */
    virtual ~History();
    
    /*! \brief Add a time (in seconds) to the stored history.
        *
        *  if the new time is earlier than any of the stored values
        *	then the time history will be erased from the overlap point 
        *	and the new value will be appended.
        * @param _appendTime time (in seconds) to be added.
        */
    virtual void AppendHistory(const double &_appendTime);

    /*! \brief Add an ssfTime object to the stored history.
        *
        *  if the new time is earlier than any of the stored values
        *	then the time history will be erased from the overlap point 
        *	and the new value will be appended.
        * @param _appendTime an ssfTime object to be appended. 
        */
    virtual void AppendHistory(const ssfTime &_appendTime);
    
    /*! \brief Add a vector of ssfTime objects to the stored history.
        *
        *  if the beginning of the new time vector is earlier than 
        *	any of the stored values then the time history will be erased 
        *	from the overlap point and the new time vector will be appended.
        * @param _appendTime vector of ssfTime objects to be appended. 
        */
    virtual vector<ssfTime>::difference_type AppendHistory(const vector<ssfTime> &_appendTime);

    /*! \brief Erases the time history */
    void ResetHistory();
    
    /*! \brief Returns a matrix of the time history
        * @return nx1 matrix of the state history, where n is the number of time states stored.
        */
    virtual Matrix GetHistory();
    
    /*! \brief Returns the nearest stored,lower mesh point to the requested time.
        *
        *  interpolates using the specified interpolator if necessary.
        * @param _requestedTime Desired time to retrieve the state. Used to find the nearest corresponding
        *	lower mesh point.
        * @return The index of the time history vector of the nearest, lower mesh point.
        */

    /*! \brief Sets the interpolator used for calculating the states in-between stored mesh points.
        * @param _newInterpolator pointer to the interpolator that serves as the model type for all the 
        *	interpolations between meshpoints.
        */
    virtual void SetInterpolator(Interpolator* _newInterpolator);
    
protected:
    /*! \brief Returns the nearest stored,lower mesh point to the requested time.
        *
        *  interpolates using the specified interpolator if necessary.
        * @param _requestedTime Desired time to retrieve the state. Used to find the nearest corresponding
        *	lower mesh point.
        * @return The index of the time history vector of the nearest, lower mesh point.
        */
    vector<ssfTime>::difference_type  GetState(const ssfTime& _requestedTime);
    
    /*! \brief internal vector container of the ssfTime objects describing the state history */
    vector<ssfTime> m_TimeHistory;
    
    /*! \brief internal storage of the original, nominal interpolator to be copied and used for all interpolations */
    Interpolator* m_OriginalInterpolator;  
    
    /*! \brief internal vector of time interpolations */
    vector<Interpolator*> m_TimeInterpolations;


};

} // close namespace O_SESSAME

#endif


// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: History.h,v $
*	Revision 1.14  2003/10/18 21:37:27  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.13  2003/06/06 00:34:16  nilspace
*	?
*	
*	Revision 1.12  2003/05/27 17:35:52  nilspace
*	Updated to prevent errors.
*	
*	Revision 1.11  2003/05/22 21:01:45  nilspace
*	Updated comments.
*	
*	Revision 1.10  2003/05/20 17:50:01  nilspace
*	Updated comments.
*	
*	Revision 1.9  2003/05/15 18:10:24  nilspace
*	Added <functional> and <algorithm> to the include files.
*	
*	Revision 1.8  2003/05/13 18:45:35  nilspace
*	Added interpolation functionality.
*	
*	Revision 1.7  2003/05/01 23:59:48  nilspace
*	Commented the API.
*	
*	Revision 1.6  2003/05/01 18:24:36  nilspace
*	Prevented overlapping Appends by removing the old states and times.
*	
*	Revision 1.5  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.4  2003/04/25 17:15:00  nilspace
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

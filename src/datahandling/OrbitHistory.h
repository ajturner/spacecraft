//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitHistory.h
*  \brief Interface to the Orbit History class.
*  \author $Author: nilspace $
*  \version $Revision: 1.7 $
*  \date    $Date: 2003/05/22 21:01:31 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ORBIT_HISTORY_H__
#define __ORBIT_HISTORY_H__

#include "Matrix.h"
#include "Rotation.h"
#include "History.h"
#include "OrbitState.h"
#include "orbitstaterep/PositionVelocity.h"
#include <vector>
using namespace std;
namespace O_SESSAME {

/*! \brief Class for storing a time history of orbital states.
* \ingroup StateHistory
*
*  The OrbitHistory class provides a container of previous OrbitState objects. The user
*	may append new states, reset the collection of states, or return the orbit history 
*	in a matrix. If the user appends orbit states at time which earlier than the end 
*	of the current history, the current history is deleted from that point on, and the 
*	new orbit states are appended.
*
* \par Examples:
\code
    OrbitState myOrbitState;
    myOrbitState.SetStateRepresentation(new PositionVelocity);
    myOrbitState.SetOrbitFrame(new OrbitFrameIJK);
    Vector initPV(6);
    myOrbitState.SetState(initPV);
    myOrbit->SetStateObject(myOrbitState);

    OrbitHistory myOrbitHistory;                     // create an orbit history with an empty collection
    myOrbitHistory.AppendHistory(0, myOrbitState);   // add the state myOrbitState which occured at t=0 to the history

    cout << myOrbitHistory.GetHistory() << endl;     // Get a matrix of the stored state and output 
                                                     // [t0, orbit elements @ t=0]
                                                     // [t1, orbit elements @ t=1]
                                                     // [t2, orbit elements @ t=2] etc...
\endcode
*/
class OrbitHistory : public History
{
public:
    /*! \brief Default Constructor
        */
    OrbitHistory();    
    
    /*! \brief Add the orbit state that occured at a time in seconds to the history.
        *
        *  Appends the state at t=_appendTime. if the new state 
        *	occured at a time that is earlier than any of the stored values
        *	then the time history will be erased from the overlap point 
        *	and the new state will be appended.
        * @param _appendTime time (in seconds) to be added.
        * @param _appendOrbitState the new orbital state to be added.
        */
    void AppendHistory(const double &_appendTime, const OrbitState &_appendOrbitState);

    /*! \brief Add the orbit state that occured with an ssfTime object to the history.
        *
        *  Appends the state at t=_appendTime. if the new state 
        *	occured at a time that is earlier than any of the stored values
        *	then the time history will be erased from the overlap point 
        *	and the new state will be appended.
        * @param _appendTime the ssfTime object specifying when the state occured.
        * @param _appendOrbitState the new orbital state to be added.
        */
    void AppendHistory(const ssfTime &_appendTime, const OrbitState &_appendOrbitState);

    /*! \brief Add a vector of ssfTime and OrbitState objects to the stored history.
        *
        *  if the beginning of the new state vector occured earlier than 
        *	any of the stored values then the orbit history will be erased 
        *	from the overlap point and the new orbit state vector will be appended.
        * @param _appendTime vector of ssfTime objects to be appended. 
        * @param _appendOrbitState vector of OrbitState objects to be appended. 
        */
    void AppendHistory(const vector<ssfTime> &_appendTime, const vector<OrbitState> &_appendOrbitState);

    /*! \brief Erases the orbit state history */
    void ResetHistory();

    /*! \brief Returns a matrix of the orbit state history
        *
        * returns the matrix of the form:    // Get a matrix of the stored state and output 
                                                     // [t0, orbit elements @ t=0]
                                                     // [t1, orbit elements @ t=1]
                                                     // [t2, orbit elements @ t=2] etc...
        * @return nxm matrix of the state history, where n is the number of time states stored and m is the number of elements in the OrbitStateRepresentation.
        */
    Matrix GetHistory();

    /*! \brief Returns the Orbit state at the requested time.
        * \warning Always interpolates using position \& velocity.
        *
        * May require interpolation (see Interpolator).
        * @param _requestedTime requested state time. If it is not an integrated mesh point, interpolation will be used to determine the approximated value.
        *	The _requestedTime may be different due to errors (outside state bounds, uncalculable interpolation).
        * @param _returnOrbitState the orbital state at the requested time (the requested time @em may be different due to errors)
        */
    void GetState(const ssfTime& _requestedTime, OrbitState& _returnOrbitState);
    
    /*! \brief Returns the Orbit state at the requested time.
        * \warning Always interpolates using position \& velocity.
        *
        *  Performs the same functionality as GetState(ssfTime& _requestedTime, OrbitState& _returnOrbitState), but returns the orbit state from the 
        *	function rather than by reference.
        * @param _requestedTime requested state time. If it is not an integrated mesh point, interpolation will be used to determine the approximated value.
        *	The _requestedTime may be different due to errors (outside state bounds, uncalculable interpolation).
        * @return the orbital state at the requested time (the requested time @em may be different due to errors)
        */
    OrbitState GetState(const ssfTime& _requestedTime);
private:
    /*! \brief internal vector container of the OrbitState objects describing the state history */
    vector<OrbitState> m_OrbitHistory;
    /*! \brief internal vector of orbit interpolations */
    vector<Interpolator*> m_OrbitInterpolations; 
};
} // close namespace O_SESSAME

#endif


// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitHistory.h,v $
*	Revision 1.7  2003/05/22 21:01:31  nilspace
*	Updated comments and added SetOrbitRepresentation(new PositionVelocity).
*	
*	Revision 1.6  2003/05/20 17:50:01  nilspace
*	Updated comments.
*	
*	Revision 1.5  2003/05/13 18:45:35  nilspace
*	Added interpolation functionality.
*	
*	Revision 1.4  2003/05/01 23:59:48  nilspace
*	Commented the API.
*	
*	Revision 1.3  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.2  2003/04/25 17:15:00  nilspace
*	Added OrbitHistory & made sure it builds.
*	Moved Appending time to History.cpp.
*	
*	Revision 1.1  2003/04/25 13:39:09  nilspace
*	Initial Submission.
*	
*	Revision 1.1  2003/03/27 20:29:20  nilspace
*	Initial Submission.
*
******************************************************************************/

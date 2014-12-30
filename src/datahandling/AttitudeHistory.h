//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file AttitudeHistory.h
*  \brief Interface to the Attitude History class.
*  \author $Author: rsharo $
*  \version $Revision: 1.11 $
*  \date    $Date: 2003/10/18 21:37:27 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTITUDE_HISTORY_H__
#define __ATTITUDE_HISTORY_H__

#include "Rotation.h"
#include "AttitudeState.h"
#include "utils/Time.h"
#include "History.h"
#include <vector>
using namespace std;
namespace O_SESSAME {

/*! \brief Class for storing a time history of attitude states.
* \ingroup StateHistory
*
*  The AttitudeHistory class provides a container of previous AttitudeState objects. The user
*	may append new states, reset the collection of states, or return the attitude history 
*	in a matrix. If the user appends attitude states at time which earlier than the end 
*	of the current history, the current history is deleted from that point on, and the 
*	new attitude states are appended.
*
* \par Examples:
\code
    AttitudeState myAttitudeState;
    myAttitudeState.SetRotation(Rotation(Quaternion(0,0,0,1)));
    Vector initAngVelVector(3);
        initAngVelVector(1) = 0.1;
    myAttitudeState.SetAngularVelocity(initAngVelVector);

    AttitudeHistory myAttitudeHistory;                     // create an attitude history with an empty collection
    myAttitudeHistory.AppendHistory(0, myAttitudeState);   // add the state myAttitudeState which occured at t=0 to the history

    cout << myAttitudeHistory.GetHistory() << endl;  // Get a matrix of the stored state and output 
                                                     // [t0, attitude parameters @ t=0]
                                                     // [t1, attitude parameters @ t=1]
                                                     // [t2, attitude parameters @ t=2] etc...
\endcode
*/
class AttitudeHistory : public History
{
public:
    /*! \brief Constructs an empty attitude history.
        */
    AttitudeHistory();
    
    /*! \brief Default Deconstructor
        */
    ~AttitudeHistory();
    
    /*! \brief Add the attitude rotation and angular velocity, which occured at a time in seconds, to the history.
        *
        *  Appends the state at t=_appendTime. if the new state 
        *	occured at a time that is earlier than any of the stored values
        *	then the time history will be erased from the overlap point 
        *	and the new state will be appended.
        * @param _appendTime time (in seconds) to be added.
        * @param _appendRotation the new Rotation describing the attitude to be added (by default the rotation is stored with respect to the inertial frame).
        * @param _appendAngVel Angular Velocity vector (3-elements) to be appended. 
        */
    void AppendHistory(const double &_appendTime, const Rotation &_appendRotation, const Vector &_appendAngVel);
    
    /*! \brief Add the attitude rotation and angular velocity, which occured with an ssfTime object, to the history.
        *
        *  Appends the state at t=_appendTime. if the new state 
        *	occured at a time that is earlier than any of the stored values
        *	then the time history will be erased from the overlap point 
        *	and the new state will be appended.
        * @param _appendTime the ssfTime object specifying when the state occured.
        * @param _appendRotation the new Rotation describing the attitude to be added (by default the rotation is stored with respect to the inertial frame).
        * @param _appendAngVel Angular Velocity vector (3-elements) to be appended. 
        */
    void AppendHistory(const ssfTime &_appendTime, const Rotation &_appendRotation, const Vector &_appendAngVel);

    /*! \brief Add the attitude state that occured at a time in seconds to the history.
        *
        *  Appends the state at t=_appendTime. if the new state 
        *	occured at a time that is earlier than any of the stored values
        *	then the time history will be erased from the overlap point 
        *	and the new state will be appended.
        * @param _appendTime time (in seconds) to be added.
        * @param _appendAttitudeState the new attitude state to be added.
        */
    void AppendHistory(const double &_appendTime, const AttitudeState &_appendAttitudeState);

    /*! \brief Add the attitude state that occured with an ssfTime object to the history.
        *
        *  Appends the state at t=_appendTime. if the new state 
        *	occured at a time that is earlier than any of the stored values
        *	then the time history will be erased from the overlap point 
        *	and the new state will be appended.
        * @param _appendTime the ssfTime object specifying when the state occured.
        * @param _appendAttitudeState the new attitude state to be added.
        */
    void AppendHistory(const ssfTime &_appendTime, const AttitudeState &_appendAttitudeState);
    
    /*! \brief Add a vector of ssfTime and AttitudeState objects to the stored history.
        *
        *  if the beginning of the new state vector occured earlier than 
        *	any of the stored values then the attitude history will be erased 
        *	from the overlap point and the new attitude state vector will be appended.
        * @param _appendTime vector of ssfTime objects to be appended. 
        * @param _appendAttitudeState vector of AttitudeState objects describing the attitude to be appended. 
        */
    void AppendHistory(const vector<ssfTime> &_appendTime, const vector<AttitudeState> &_appendAttitudeState);

    /*! \brief Add a vector of ssfTime, Rotation, and Angular Velocity vector objects to the stored history.
        *
        *  if the beginning of the new state vector occured earlier than 
        *	any of the stored values then the attitude history will be erased 
        *	from the overlap point and the new attitude state vector will be appended.
        * @param _appendTime vector of ssfTime objects to be appended. 
        * @param _appendRotation vector of Rotation objects describing the attitude to be appended (stores by default with repect to inertial reference frame). 
        * @param _appendAngVel vector of Angular Velocity vectors (3-elements) to be appended. 
        */
    void AppendHistory(const vector<ssfTime> &_appendTime, const vector<Rotation> &_appendRotation, const vector<Vector> &_appendAngVel);

    /*! \brief Erases the attitude state history */
    void ResetHistory();

    /*! \brief Returns a matrix of the attitude state history
        *
        *  returns the matrix of the form:    // Get a matrix of the stored state and output 
                                                     // [t0, attitude parameters @ t=0]
                                                     // [t1, attitude parameters @ t=1]
                                                     // [t2, attitude parameters @ t=2] etc...
        * @param _rotType rotation type to return the state in (ie quaternion, MRP, DCM, Euler Angles, etc.). Default (ie no type specified) to quaternion elements.
        * @return nxm matrix of the state history, where n is the number of time states stored and m is the number of elements in the RotationType.
        */
    Matrix GetHistory(const RotationType &_rotType = Quaternion_Type);
    
    /*! \brief Returns the attitude state at the requested time.
        *
        * \warning Always interpolates using quaternions
        *  May require interpolation (see Interpolator).
        * @param _requestedTime requested state time. If it is not an integrated mesh point, interpolation will be used to determine the approximated value.
        *	The _requestedTime may be different due to errors (outside state bounds, uncalculable interpolation).
        * @param _returnRotation the rotation at the requested time.
        * @param _returnAngVelVector the angular velocity vector at the requested time. 
        */
    void GetState(const ssfTime& _requestedTime, Rotation& _returnRotation, Vector& _returnAngVelVector);
    
    /*! \brief Returns the Attitude state at the requested time.
        *
        * \warning Always interpolates using quaternions
        *  Performs the same functionality as GetState(ssfTime& _requestedTime, Rotation& _returnRotation, Vector& _returnAngVelVector), but returns the attitude state from the 
        *	function rather than by reference.
        * @param _requestedTime requested state time. If it is not an integrated mesh point, interpolation will be used to determine the approximated value.
        *	The _requestedTime may be different due to errors (outside state bounds, uncalculable interpolation).
        * @return the attitude state at the requested time 
        */
    AttitudeState GetState(const ssfTime& _requestedTime);
private:
    /*! \brief internal vector container of the AttitudeState objects describing the state history */
    vector<AttitudeState> m_AttitudeHistory;
    /*! \brief internal vector of attitude interpolations */
    vector<Interpolator*> m_AttitudeInterpolations; 

};
} // close namespace O_SESSAME

#endif


// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: AttitudeHistory.h,v $
*	Revision 1.11  2003/10/18 21:37:27  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.10  2003/05/22 21:01:01  nilspace
*	Updated comments.
*	
*	Revision 1.9  2003/05/20 17:50:01  nilspace
*	Updated comments.
*	
*	Revision 1.8  2003/05/13 18:45:35  nilspace
*	Added interpolation functionality.
*	
*	Revision 1.7  2003/05/01 23:59:48  nilspace
*	Commented the API.
*	
*	Revision 1.6  2003/04/29 20:57:46  nilspace
*	Updated to work with Propagator.
*	
*	Revision 1.5  2003/04/28 20:11:52  nilspace
*	Made Quaternion_Type the default GetHistory rotation return type.
*	
*	Revision 1.4  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.3  2003/04/23 17:00:47  nilspace
*	Changed to work with AttitudeState and not Rotation and AngVel seperately.
*	Time is now stored as ssfTime.
*	
*	Revision 1.2  2003/04/23 16:30:58  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/03/27 20:29:20  nilspace
*	Initial Submission.
*
******************************************************************************/

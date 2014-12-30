//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file AttitudeState.h
*  \brief Interface to the AttitudeState class.
*  \author $Author: rsharo $
*  \version $Revision: 1.8 $
*  \date    $Date: 2003/10/18 21:37:27 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ATTITUDE_STATE_H__
#define __SSF_ATTITUDE_STATE_H__

#include "Matrix.h"
#include "Rotation.h"

namespace O_SESSAME {
typedef int AttitudeFrame; /** \todo Implement AttitudeFrame class */
class OrbitState;

/*! \brief Encapsulation of an Attitude State, including its coordinate type and reference frame.
* \ingroup AttitudeToolkit
*
* \detail AttitudeState encapsulates an instantaneous representation of an attitude, as well as 
*	the frame from which it is referenced. Also included is all the functionality for converting
*	between the frames and accessing or changing the associated rotation.
*
* \par Examples:
\code
AttitudeState satAtt;
Vector AngVel(3); AngVel(1) = 0.1;
satAtt.SetRotation(Rotation(Quaternion(0,0,0,1)));
satAtt.SetFrame(new AttitudeFrameBO);
satAtt.GetFrame()->SetReference(satOrbitState);
satAtt.SetAngularVelocity(AngVel);

cout << satAtt.GetRotation().GetDCM() << endl;
\endcode

* \example testAttitudeIntegration.cpp
* \example testPropagation.cpp
*/
class AttitudeState
{
public:
    /*! \brief Default Constructor.
    */
    AttitudeState();
    /*! \brief Default Deconstructor.
    */
    virtual ~AttitudeState();

    /*! \brief Creates an attitude state given a rotation and attitude frame (defaults to no frame)
        * @param _Rot rotation to be stored
        * @param _pAttFrame pointer to the attitude reference frame
        */
    AttitudeState(const Rotation &_Rot, AttitudeFrame* _pAttFrame = NULL);

    /*! \brief Creates an attitude state given a rotation, an angular velocity and attitude frame (defaults to no frame)
        * @param _Rot rotation to be stored
        * @param _AngVel angular velocity (rad/s)
        * @param _pAttFrame pointer to the attitude reference frame
        */
    AttitudeState(const Rotation &_Rot, const Vector &_AngVel, AttitudeFrame* _pAttFrame = NULL);

    /*! \brief Set the reference frame of the stored attitude.
        * \detail Will convert the old rotation to the new attitude frame if one was specified.
        * @param _pNewAttitudeFrame pointer to the new reference frame
        */
    void SetAttitudeFrame(AttitudeFrame* _pNewAttitudeFrame);

    /*! \brief Returns a pointer to the attitude reference frame.
        * @return pointer to the attitude reference frame
        */
    AttitudeFrame* GetAttitudeFrame() const;
    
    /*! \brief Set the attitude state given a rotation, an angular velocity and attitude frame (defaults to no frame)
        * @param _Rot rotation to be stored
        * @param _AngVel angular velocity (rad/s)
        * @param _pAttFrame pointer to the attitude reference frame
        */    
    void SetState(const Rotation& _Rotation, const Vector& _AngVel, AttitudeFrame* _attFrame = NULL);
    
    /*! \brief Return the attitude state rotation in vector format.
        * @param _rotType Rotation type to return the attitude state in (ie QUAT_TYPE, MRP_TYPE, etc.)
        * @param _attFrame corresponding reference frame to return the rotation in (if none is specified, returns the rotation in the stored reference frame)
        * @param _Sequence if the requested rotation type is EULER_ANGLE_TYPE, then specify the desired rotation sequence.
        * @return full n x 1 vector of state values corresponding to the rotation and angular velocity components (n is the number of elements in specified rotation return type)
        */    
    Vector GetState(const RotationType& _rotType = Quaternion_Type, AttitudeFrame* _attFrame = NULL, const int& _Sequence = 123) const;
        
    /*! \brief Set the stored rotation.
        * @param _Rot rotation to be stored as the state.
        */
    void SetRotation(const Rotation &_Rot);

    /*! \brief Set the stored rotation and corresponding reference frame.
        * @param _Rot rotation to be stored as the state.
        * @param _pAttFrame reference frame of the specified attitude.
        */
    void SetRotation(const Rotation &_Rot, AttitudeFrame* _pAttFrame);

    /*! \brief Returns the current rotation of the attitude state.
        * @param Rotation of the attitude state.
        */
    Rotation GetRotation() const;
    
    /*! \brief Set the stored angular velocity state.
        * @param _angVel 3x1 Vector of angular velocities about reference frame (rad/s)
        */
    void SetAngularVelocity(const Vector &_angVel);
    
    /*! \brief Returns the stored angular velocity state.
        * @return 3x1 Vector of angular velocities about reference frame (rad/s)
        */
    Vector GetAngularVelocity() const;
        
    /*! \brief Calculates the rotation from the current attitude state to the specified orbit reference frame.
        *
        * \todo Implement algorithm.
        * @param _orbState orbit state to use for specifying the reference orbital frame.
        * @return Rotation from current attitude frame to orbital frame.
        */
    Rotation GetRotation2Orbital(const OrbitState& _orbState) const;
    
private:
    Rotation m_AttitudeRotation; 	/*!< internally stored attitude state rotation */
    Vector m_AngularVelocity;		/*!< internally stored angular velocity */
    AttitudeFrame* m_pAttitudeFrame;	/*!< rotation reference frame */
};

} // close namespace O_SESSAME
#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: AttitudeState.h,v $
*	Revision 1.8  2003/10/18 21:37:27  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.7  2003/06/12 23:07:08  nilspace
*	Fixed to calculate Orbital rotation.
*	
*	Revision 1.6  2003/06/12 17:59:35  nilspace
*	Added GetRotation2Orbit function.
*	
*	Revision 1.5  2003/05/20 17:46:25  nilspace
*	Updated comments.
*	
*	Revision 1.4  2003/05/13 18:50:24  nilspace
*	Fixed comments.
*	
*	Revision 1.3  2003/04/27 22:04:31  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.2  2003/04/23 16:30:58  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/04/08 22:51:24  nilspace
*	Initial submission in new directory.
*	
******************************************************************************/

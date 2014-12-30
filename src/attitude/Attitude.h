//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Attitude.h
*  \brief Interface to the Attitude class.
*  \author $Author: rsharo $
*  \version $Revision: 1.11 $
*  \date    $Date: 2003/10/18 21:37:27 $
//////////////////////////////////////////////////////////////////////////////////////////////////
* \todo Make Attitude derivable for diff't types of attitude representations (point-to, etc)
* \todo Implement export & import plug-ins (STK, matlab, excel...)
* \todo Add Attitude history storage
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ATTITUDE_H__
#define __ATTITUDE_H__

#include "Rotation.h"
#include "utils/Integrator.h"
#include "Propagator.h"
#include "AttitudeHistory.h"
#include "AttitudeState.h"
namespace O_SESSAME {
class Propagator; // forward declaration

/*! \brief Defined function pointer to integrated attitude state conversion function.
    * \ingroup PropagatorToolkit
    *
    *  Converts a vector of meshpoints (from integrated states) to the corresponding generalized AttitudeState.
    * @param _meshPoint vector of values of the meshpoint to be converted
    * @param _convertedAttitudeState Calculated AttitudeState from the converted meshpoint that is returned to the caller.
    */
typedef void (*IntegratedAttitudeStateConversionFunction)(const Matrix &_meshPoint, AttitudeState &_convertedAttitudeState);

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! @defgroup AttitudeToolkit Attitude Toolkit 
*
*/
/*! @defgroup AttitudeEquationsOfMotion Attitude Equations of Motion
* @ingroup AttitudeToolkit
* 
*/

/*! \brief Class encapsulating the rotational attitude of a rigid body frame with respect to another frame.
* \ingroup AttitudeToolkit
*
* \detail The Attitude class allows for the attitude to be stored, retrieved, history logged, 
* \todo Verify attitude is inheritable.
* \example testAttitudeIntegration.cpp
* \example testPropagation.cpp
*/
class Attitude
{
public:
    /*! Default Constructor */
    Attitude();
    /*! Default Deconstructor */
    virtual ~Attitude();
    
public:    
    void SetStateObject(const AttitudeState &_newAttitudeState);
    AttitudeState GetStateObject() const;

private:
    AttitudeState m_AttitudeState; 

// ***************************** 
// ********** TORQUES ********** 
// ***************************** 
public:
    /*! Set the control torques
        * @param _ControlTorques 3-element vector of control torques applied about body primary axes [N-m]
        */
    void SetControlTorques(const Vector &_ControlTorques);
    
    /*! Returns the current set of control torques
        * @return 3-element vector of current control torques applied about body primary axes [N-m]
        */
    Vector GetControlTorques() const;
    
    
    /*! Return total sum of torques applied to the rigid body
        * @return 3-element vector of current torques applied about body primary axes [N-m]
        */
    Vector GetTorques() const;
private:
    /*! 3-element vector of current control torques applied about body primary axes [N-m] */
    Vector m_ControlTorques;
    
// ***************************** 
// ******** PROPAGATION ******** 
// ***************************** 
public:    
    /*! Set the Dynamics Equation right-hand side file.
        * Also makes the attitude integrateable.
        * @param _AttDynEqFuncPtr pointer to the right-hand side dynamics equation
        */
    void SetDynamicsEq(odeFunctor _AttDynEqFuncPtr);	
    
    /*! Return the pointer to the Dynamics Equation right-hand side
        * @return _AttDynEqFuncPtr pointer to the right-hand side dynamics equation
        */
    odeFunctor GetDynamicsEq() const;

    
    /*! \brief Set the Attitude state conversion function.
        * @param _ConversionFunction pointer to the conversion function (takes a meshpoint and returns a Rotation object and Angular Velocity vector).
        */
    void SetStateConversion(IntegratedAttitudeStateConversionFunction _ConversionFunction);

    /*! \brief Get the Attitude state conversion function.
        * @return pointer to the conversion function (takes a meshpoint and returns a Rotation object and Angular Velocity vector).
        */
    IntegratedAttitudeStateConversionFunction GetStateConversion() const;
    
    /*! Propagates the rigid body attitude forward in time.
        * @param _time 3-element vector specifying the initial, final and stepsize of times to be integrated [timeInitial, timeStep, timeFinal] (s)
        * @return matrix of integrated states.
        */
    Matrix Propagate(const vector<ssfTime> &_time);
    
    /*!
        * \brief Sets the propagator used for integrating the attitude.
        * @param _pPropagator Pointer to the propagator to be used.
        */
    void SetPropagator(Propagator *_pPropagator);
        
    /*! \brief Returns whether the attitude is integrateable or not.
        * Determined if there is a dynamics equation present.
        * @return true if the attitude can be integrated, false if it can't.
        */
    bool IsIntegrateable();
private:
    /*! pointer to the right-hand side dynamics equation */
    odeFunctor m_AttDynEqFuncPtr;
    
    /*! Conversion function for converting from the integrated states to a Rotation and Angular Velocity. */
    IntegratedAttitudeStateConversionFunction m_AttitudeStateConversionFunction;
    
    /*! Pointer to the propagator */
    Propagator *m_pPropagator;

    /*! \brief Is the attitude integrateable? (true if it is, false if is not) */
    bool m_Integrateable;
    
// ***************************** 
// ********* Physical ********** 
// ***************************** 
public:
    void SetParameters(const Matrix &_Parameters);
    Matrix GetParameters() const;
    
private:
    Matrix m_Parameters;
    
// ***************************** 
// ******** ENVIRONMENT ********
// *****************************  
public:
    /*! \brief Assign the environment to be used when evaluating attitude disturbance torques.
        * The environment contains the list of torque disturbance functions, environment parameters, and
        * central body definition of the spacecraft. This functions sets the pointer (reference) to the 
        * environment object. This environment should be the same as the orbit's environment if there is an 
        * orbit being modeled.
        * @param _pNewEnvironment this variable is a pointer to the environment object to be stored.
        */
    void SetEnvironment(Environment* _pNewEnvironment);
    /*! \brief Return the reference to the environment object of the attitude.
        * This function is useful for returning the current environment that is being used by the attitude.
        *  It can be used to inspect and set the environment variables (such as adding torque disturbance 
        *  functions, setting the central body, or changing environment parameters), or to use the reference 
        *  for setting another environment (the coupled orbit, or another spacecraft's orbit and attitude 
        *  that are in the same environment as this spacecraft.
        * @return this function returns a pointer to the environment object that is currently stored in the attitude.
        */
    Environment* GetEnvironment() const;
    
    /*! \brief Returns the function reference (functor) to the function that evaluates the environment disturbance torques.
        * This function is used to get the reference, or function pointer, to the environmental disturbance torque function.
        * The reference may then be evalauated (\sa ObjectFunctor) to calculate the disturbance torques at a specified 
        * time, attitude, and possibly orbit, if applicable for the defined disturbance function (such as magnetic or gravity-gradient 
        * with a higher-order gravity model). 
        * @return this function returns a functor, or function reference of an object's member function, that refers to the disturbance function.
        */
    ObjectFunctor<Environment> GetEnvironmentForcesFunctor();
private:
    /*! \brief Pointer to the Environment object */
    Environment *m_pEnvironment;
    /*! \brief Pointer to the Environment forces function */
    ObjectFunctor<Environment> m_EnvironmentForcesFunctor;
// *************************
// ******** HISTORY ******** 
// ************************* 
public:
    /*! \brief Retrieve a reference to the attitude's state history.
        * By returning a reference, no copy is made, which is more efficient than copying a large matrix of 
        * states. The user can then inspect the history (\sa History, \sa AttitudeHistory).
        * @return this function returns a reference, which acts as an object, but is also like a pointer.
        */
    AttitudeHistory& GetHistoryObject();
    
private:
    /*! \brief This private data member is the stored attitude state, including [time, rotation, angular velocity] */
    AttitudeHistory m_AttitudeHistory;


};
} // close namespace O_SESSAME
#endif
/*!***************************************************************************
*	$Log: Attitude.h,v $
*	Revision 1.11  2003/10/18 21:37:27  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.10  2003/06/10 14:51:42  nilspace
*	Changed GetHistory to GetHistoryObject
*	
*	Revision 1.9  2003/05/20 17:46:25  nilspace
*	Updated comments.
*	
*	Revision 1.8  2003/05/13 18:50:47  nilspace
*	Fixed comments.
*	
*	Revision 1.7  2003/04/28 20:12:45  nilspace
*	GetHistory return by reference.
*	
*	Revision 1.6  2003/04/27 22:11:51  nilspace
*	Moved all of the function definitions out of the class interface definition.
*	
*	Revision 1.5  2003/04/27 22:04:31  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.4  2003/04/25 13:44:58  nilspace
*	Updated to work with current History, Environment & Propagator objects.
*	
*	Revision 1.3  2003/04/23 21:54:33  nilspace
*	Updated to work with AttitudeState, Environment.
*	Removed the setting and getting of AngVel, AngAccel, Rotation.
*	
*	Revision 1.4  2003/03/27 20:25:17  nilspace
*	Implemented calling the propagator & history objects.
*	
*	Revision 1.3  2003/03/27 02:48:54  nilspace
*	Added the Propagator object functionality. Documented some of the new functions.Fixed history storage.
*	
*	Revision 1.2  2003/03/25 19:43:37  nilspace
*	fixed to pre-ruined state.
*	Changed enum to be auto number defining.
*	
*	Revision 1.1  2003/03/25 02:41:05  nilspace
*	initial Submission. Attitude.h may not be current due to lost copy from ProjectBuilder crash.
*	
*	Revision 1.1  2003/02/27 18:37:26  nilspace
*	Initial submission of Attitude class implementation.
*	
*
******************************************************************************/

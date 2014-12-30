//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Orbit.h
*  \brief Implementation of the Orbit Class.
*  \author $Author: rsharo $
*  \version $Revision: 1.10 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_H__
#define __SSF_ORBIT_H__

#include "utils/Functor.h"
#include "Environment.h"
#include "Propagator.h"
#include "OrbitState.h"
#include "OrbitHistory.h"


namespace O_SESSAME {
class Propagator; // forward declaration

/*! \brief Defined function pointer to integrated orbital state conversion function.
    * \ingroup PropagatorToolkit
    *
    *  Converts a vector of meshpoints (from integrated states) to the corresponding generalized OrbitState.
    * @param _meshPoint vector of values of the meshpoint to be converted
    * @param _convertedOrbitState Calculated Orbit state from the converted meshpoint that is returned to the caller.
    */
typedef void (*IntegratedOrbitStateConversionFunction)(const Matrix &_meshPoint, OrbitState &_convertedOrbitState);


//////////////////////////////////////////////////////////////////////////////////////////////////
/*! @defgroup OrbitToolkit Orbit Toolkit 
*
* Collection of orbit analysis and simulation tools.
* @{
*/

/*! @defgroup OrbitEquationsOfMotion Orbit Equations of Motion 
* @ingroup OrbitToolkit
*
*/

/*! \brief Complete representation of a spacecraft orbt.
* 
* The Orbit class is a composition of all the information that is part of a spacecraft orbit. This includes 
the dynamic equations, disturbance force functions, environmen objects, state history and control forces.
*/

/** \example testOrbitIntegration.cpp
* \example testPropagation.cpp
*/
class Orbit
{
public:
    /*! Default Constructor */
    Orbit();
    /*! Default Deconstructor */
    virtual ~Orbit();
    
public:
    /*! \brief Set the current orbit state object that represents the spacecraft's position in space.
        * @param _currentOrbitPosition Current orbital state of the spacecraft.
        */
    void SetStateObject(const OrbitState& _currentOrbitPosition);
    
    /*! \brief Return the current orbital state of the spacecraft. 
        * @return Current stored orbital state of the spacecraft.
        */
    OrbitState GetStateObject() const;
  
protected:
    /*! \brief Current stored orbital state of the spacecraft. */
    OrbitState m_CurrentOrbitPosition;
    
    
// ***************************** 
// ******** PROPAGATION ******** 
// ***************************** 
public:
    /*! \brief Set the Dynamics Equation right-hand side file
        * @param _orbitDynamicsEq pointer to the right-hand side dynamics equation
        */
    void SetDynamicsEq(odeFunctor _orbitDynamicsEq);

    /*! \brief Return the pointer to the Dynamics Equation right-hand side
        * @return pointer to the right-hand side dynamics equation
        */
    odeFunctor GetDynamicsEq();

    /*! \brief Set the Orbit state conversion function.
        * @param _ConversionFunction pointer to the conversion function (takes a meshpoint and returns an object of OrbitState).
        */
    void SetStateConversion(IntegratedOrbitStateConversionFunction _ConversionFunction);

    /*! \brief Get the Orbit state conversion function.
        * @return pointer to the conversion function (takes a meshpoint and returns an object of OrbitState).
        */
    IntegratedOrbitStateConversionFunction GetStateConversion() const;

    /*! \brief Sets the propagator used for integrating the orbit.
        * @param _pPropagator Pointer to the propagator to be used.
        */
    void SetPropagator(Propagator *_pPropagator);
    
    /*! \brief Returns the pointer to the propagator being used.
        * @return pointer to the orbit's propagator.
        */
    Propagator* GetPropagator();
    
    /*! \brief Propagate the orbit through the vector of times.
        */
    void Propagate(const Vector &_propTime);
        
    /*! \brief Returns whether the orbit is integrateable or not.
        * Determined if there is a dynamics equation present.
        * @return true if the orbit can be integrated, false if it can't.
        */
    bool IsIntegrateable();
        
private:
    /*! \brief Internal pointer to the current orbit propagator algorithm */
    Propagator *m_pPropagator;
    
    /*! Conversion function for converting from the integrated states to an Orbit State. */
    IntegratedOrbitStateConversionFunction m_OrbitStateConversionFunction;
    
    /*! \brief Right-hand side of the orbit dynamics equation: \f$\dot{x} = RHS(t, x)\f$ */
    odeFunctor m_OrbitDynamicsEq;

    /*! \brief Is the orbit integrateable? (true if it is, false if is not) */
    bool m_Integrateable;
    
// ***************************** 
// ********* Physical ********** 
// ***************************** 
public:
    /*! \brief Set the physical parameters of the spacecraft orbit 
        * 
        * \todo determine what physical parameters are pertinent.
        */
    void SetParameters(const Matrix &_Parameters);
    
    /*! \brief Return a matrix of the current stored spacecraft orbital parameters.
        *
        */
    Matrix GetParameters() const;
    
private:
    Matrix m_Parameters;

// ***************************** 
// ******** ENVIRONMENT ********
// *****************************  
public:
    /*! \brief Sets the environment used for integrating the orbit.
        * @param _pEnvironment Instance of the environment to be used.
        */
    void SetEnvironment(Environment *_pEnvironment);	
    
    /*! \brief Returns the environment used for integrating the orbit.
        * @return pointer to the instance of the environment being used.
        */
    Environment* GetEnvironment();
        
    
    void SetControlForces(const Vector &_controlForces);
    Vector GetControlForces();
    
    /*! \brief Return a reference to the environmental forces function.
        * @return the Functor that references the Environment force function of the orbit. Used as a 
        *	callback function for evaluating the forces on the spacecraft orbit due to 
        *	specified environmental disturbances.
        */
    ObjectFunctor<Environment> GetEnvironmentForcesFunctor();
private:
    /*! \brief Internal pointer to the orbit's environment object. */
    Environment *m_pEnvironment;
    /*! \brief Internal Vector of the current control forces being applied to the spacecraft. */
    Vector m_ControlForces;
    
    /*! Pointer to the Environment forces function */
    ObjectFunctor<Environment> m_EnvironmentForcesFunctor;
    
// *************************
// ******** HISTORY ******** 
// ************************* 
public:
    /*! \brief Return a reference to the spacecraft's orbit history.
        * 
        *  This function is used to make evaluations on the spacecraft's orbit history.
        * \code
        * // Get the orbit state at t=30 seconds.
        * OrbitState OrbState30 = myOrbit.GetHistoryObject().GetState(ssfTime(30));
        * \endcode
        * @return reference (acts as a normal object, but actually "points" to the private data member) 
        *	to the spacecraft's orbit history object.
        */
    OrbitHistory& GetHistoryObject();
    
private:
    OrbitHistory m_OrbitHistory;

};
/** @} */ // End of OrbitToolkit Group

} // close namespace O_SESSAME
#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Orbit.h,v $
*	Revision 1.10  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.9  2003/06/10 14:52:05  nilspace
*	Changed GetHistory to GetHistoryObject
*	
*	Revision 1.8  2003/05/20 17:47:59  nilspace
*	Updated comments.
*	
*	Revision 1.7  2003/05/02 16:16:46  nilspace
*	Documented the API.
*	
*	Revision 1.6  2003/04/28 20:13:18  nilspace
*	GetHistory return by reference.
*	
*	Revision 1.5  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.4  2003/04/27 21:17:42  nilspace
*	Finished moving function declarations out of the class interface.
*	
*	Revision 1.3  2003/04/27 21:14:01  nilspace
*	Added to the namespace O_SESSAME.
*	Moved function definitions outside of the class interface definition.
*	
*	Revision 1.2  2003/04/25 13:36:28  nilspace
*	Updated to work with current History, Environment & Propagator objects.
*	
*	Revision 1.1  2003/04/08 22:48:59  nilspace
*	Initial Submission.
*
******************************************************************************/

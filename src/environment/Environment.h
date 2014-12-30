//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Environment.h
*  \brief Interface to the Environment encapsulation object.
*  \author $Author: rsharo $
*  \version $Revision: 1.13 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* \todo Add name strings and outputting of "turned-on" disturbances
* \todo Add reference counter to ensure deletion when not used anymore.
* \todo Add CreateIterator() function
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "Rotation.h"
#include "utils/Integrator.h"
#include "Matrix.h"
#include "utils/Time.h"
#include <set>
#include <vector>

using namespace std;

namespace O_SESSAME {
class CentralBody;

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! @defgroup EnvironmentToolkit Environment Toolkit  
* The Environment Toolkit is the collection of classes and functions that assist in modeling a 
* spacecraft's external environment. This includes the central bodies, disturbance forces and 
* disturbance torques. 
*
* \par Extension Points:
* 	The current toolkit provides functionality for the main planets of the solar system as 
* central bodies. There are other central bodies such as moons, asteroids, comets, or stars that 
* could be added by deriving from the CentralBody interface class. Furthermore, only a couple of 
* the primary disturbance torque and force functions have been implemented. There are numerous 
* models of varying complexity that could be added. The only stipulation is that these new disturbance 
* functions match the parameterization specified by pt2EnvFunc. 
*/

/*! specification of the parameter list type to be used for environmental function pointers */
typedef vector<void*> EnvFuncParamaterType;
/*! defines a pointer to a Environmental disturbance calculating function */
typedef Vector(*pt2EnvFunc)(const ssfTime &_currentTime, const OrbitState &_currentOrbitState, const AttitudeState &_currentAttitudeState, const EnvFuncParamaterType &_parameterList);

/*! \brief Encapsulation of an environmental disturbance function.
* \ingroup EnvironmentToolkit
*
* 	An EnvFunction is used to store a function pointer and the list of parameters
*	that are used in evaluating an environmental disturbance function. The 
* 	function can either be a force or torque disturbance. Examples include:<p>
*
*	\par (force) Gravity, aerodynamic drag, solar radiation pressure
*	\par (torque) Gravity gradient, magnetic, aerodynamic, fuel slosh <p>
*
*	\oar The parameters are the constants (such as Ballistic coefficient, 
*	magnetic dipole, cross-sectional area), in the appropriate function
*	order, and can be set or removed individually. Furthermore, because
*	they are actually pointers to data, once the pointer is set, the data
*	can still change (for example the mass of the spacecraft) without 
*	having to alter the EnvFunction parameter list.</p>
*
*	\par Usage:
*	To use the EnvFunction class, the user first creates a disturbance
*	function that matches the prototype of pt2EnvFunc, which takes the 
*	current time, orbit state, attitude state, and an STL vector
*	of pointers to the parameters. They then must create an instance of
*	an EnvFunction with a pointer to the function:
*	\code
		EnvFunction DragForce(&myDisturbanceFunction);
*	\endcode
*	and then fill out the parameter list:
*	\code
                DragForce.AddParameter(reinterpret_cast<void*>(*CrossArea), 1);
*	\endcode
*	Notice it is important to only give a pointer to a value that will 
*	stay "in scope" as long as needed for the simulation. Also, the 
*	reinterpret_cast<void*>() is needed to make the value 'look like' a void
* 	pointer. Don't worry too much about this, but read Stroustrop if 
*	you'd like to know more.
*
*	\par Example disturbance function:
        \code
// Force function that will be called each timestep
Vector DragForceFunction(const ssfTime* _currentTime, const OrbitState* _currentOrbitState, const AttitudeState* _currentAttitudeState, EnvFuncParamaterType _parameterList)
{
    Vector Forces(3);
    double BC = *(reinterpret_cast<double*>(_parameterList[1]));
    double Density = *(reinterpret_cast<double*>(_parameterList[2])); // kg/m^3
    Vector Vrel(3); Vrel = _currentOrbitState->GetState()(_(VectorIndexBase+3,VectorIndexBase+5));
    double Vrel_mag = norm2(Vrel);
    Forces = -1/2 * rho / BC * pow(Vrel_mag,2) * Vrel / Vrel_mag; 
    return Forces;
}
        \endcode
*    
* \example testEnvironment.cpp
* Example using an Environment object for integration.
*
* \example testPropagation.cpp
* Example propagation of a combined satellite orbit \& attitude.
*/
class EnvFunction
{
public:
    EnvFunction(pt2EnvFunc _EnvFuncPtr);

    EnvFunction(pt2EnvFunc _EnvFuncPtr, const int & _numParameters);

    Vector Evaluate(const ssfTime &_currentTime, const OrbitState &_currentOrbitState, const AttitudeState &_currentAttitudeState);

    void AddParameter(void* _parameter, int _paramNumber = -1);
    
    void RemoveParameter(int _paramNumber = -1);

    void ChangeParameter(void* _parameter, int _paramNumber = -1);
private:
    /*! \brief internal pointer to the environmental disturbance function */
    pt2EnvFunc m_EnvFuncPtr;
    /*! \brief internal storage of the number of parameters in the list */
    int m_NumParameters;
    /*! \brief list of pointers to the parameters */
    EnvFuncParamaterType m_EnvFuncParameters;

};

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! @defgroup EnvironmentForceFunctions Environment Force Disturbance Functions  
* @ingroup EnvironmentToolkit
* 
* 
*/
/*! @defgroup EnvironmentTorqueFunctions Environment Torque Disturbance Functions  
* @ingroup EnvironmentToolkit
* 
* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

/*!\brief Encapsulation of a spacecraft environment (disturbance forces, torques, central body, etc.)
* \ingroup EnvironmentToolkit Environment Toolkit
* 
*       The Environment class is used to contain all the different aspects of the external
*	environment of the spacecraft. This currently includes disturbance forces (gravity, drag, solar radiation pressure),
*	disturbance torques (gravity gradient, magnetic dipole, fuel slosh), and central body (for constants).
*
*	To use the Environment class, the user should create (or include) and assign the desired force and torque 
*	disturbance functions (EnvFunction), and CentralBody. The integrator or propagator would then use the GetTorque() and
* 	GetForce() functions to modify the dynamics.
*
*	\par Example:
    \code
    * Environment* pEarthEnv = new Environment;
    * EarthCentralBody *pCBEarth = new EarthCentralBody;
    * pEarthEnv->SetCentralBody(pCBEarth);
    
    * // Add Gravity force function
    * EnvFunction TwoBodyGravity(&GravityForceFunction);
    * double Mass = 100; \\kg
    * TwoBodyGravity.AddParameter(reinterpret_cast<void*>(&Mass), 1);
    * pEarthEnv->AddForceFunction(TwoBodyGravity);
    
    * // Add Drag Force Function
    * EnvFunction DragForce(&DragForceFunction);
    * double BallisticCoefficient = 200;
    * DragForce.AddParameter(reinterpret_cast<void*>(&BallisticCoefficient), 1);
    * pEarthEnv->AddForceFunction(DragForce);
        
    * // Add Magnetic Dipole
    * EnvFunction MagDipole(&MagneticDipoleFunction);
    * MagDiple.AddParameter(reinterpret_cast<void*>(&Spacecraft.GetDipole(), 1);
    * pEarthEnv->AddTorqueFunction(MagDipole);
    \endcode
*
*/
class Environment
{
public:
    Environment();

    virtual ~Environment();

    Vector GetTorques(const ssfTime& _currentTime, const OrbitState& _currentOrbitState, const AttitudeState& _currentAttitudeState);

    Vector GetForces(const ssfTime& _currentTime, const OrbitState& _currentOrbitState, const AttitudeState& _currentAttitudeState);

    void AddForceFunction(const EnvFunction &_forceFunc);

    void AddTorqueFunction(const EnvFunction &_torqueFunc);

    const Functor& GetForceFunction() const;

    const Functor& GetTorqueFunction() const;
    
    void SetCentralBody(CentralBody *_pCB);

    const CentralBody* GetCentralBody() const;
    
private:
    /*! \brief internal vector of the pointers to the force disturbance functions */
    vector<EnvFunction> m_ForceFunctions;
    /*! \brief internal vector of the pointers to the torque disturbance functions */
    vector<EnvFunction> m_TorqueFunctions;
    /*! \brief internal iterator for stepping through the disturbance function vectors */
    vector<EnvFunction>::iterator m_funcIterator;
    /*! \brief internal pointer to the environment central body */
    CentralBody *m_pCB;
    
    /*! \brief internal Vector of the most recent calculated disturbance forces */
    Vector m_CalculatedForces;
    /*! \brief internal Vector of the most recent calculated disturbance torques */
    Vector m_CalculatedTorques;
    /*! \brief internal pointer to the Environment::GetForces() function */
    ObjectFunctor<Environment> m_ForcesFunctor;
    /*! \brief internal pointer to the Environment::GetTorques() function */
    ObjectFunctor<Environment> m_TorquesFunctor;


};
} // close namespace O_SESSAME
#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Environment.h,v $
*	Revision 1.13  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.12  2003/06/12 18:06:35  nilspace
*	.
*	
*	Revision 1.11  2003/06/10 14:48:03  nilspace
*	Changed include CentralBody.h to look in CentralBody directory.
*	
*	Revision 1.10  2003/06/06 17:35:52  nilspace
*	Moved to CentralBody directory.
*	
*	Revision 1.9  2003/05/22 21:04:16  nilspace
*	Updated comments.
*	
*	Revision 1.8  2003/05/22 03:42:32  nilspace
*	Moved documentation to the implementation file.
*	
*	Revision 1.7  2003/05/20 17:51:12  nilspace
*	Updated comments.
*	
*	Revision 1.6  2003/05/13 18:59:16  nilspace
*	Fixed some comments.
*	
*	Revision 1.5  2003/05/05 20:45:46  nilspace
*	Changed the pass-by-address parameters to pass-by-reference.
*	
*	Revision 1.4  2003/05/02 16:16:28  nilspace
*	Documented the API.
*	
*	Revision 1.3  2003/05/02 02:16:29  nilspace
*	Documented the API.
*	Added a GetTorquesFunction().
*	
*	Revision 1.2  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.1  2003/04/08 22:37:22  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

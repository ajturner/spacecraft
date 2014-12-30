//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Integrator.h
*  \brief Abstract interface to the Integrator Strategy.
*  \author $Author: rsharo $
*  \version $Revision: 1.10 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_INTEGRATOR_H__
#define __SSF_INTEGRATOR_H__

#include <Matrix.h>
#include "Functor.h"
#include "utils/Time.h"
#include <vector.h>
using namespace std;
namespace O_SESSAME {
class Orbit;
class Attitude;

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! @defgroup IntegrationLibrary Integration Library */
/* @{ */

/*! \brief A generalized pointer to a function that takes a vector as a parameter and returns a vector */
typedef Vector (*vectorFuncPtr)(const Vector& _vectorFuncPtrParams);

/*! \brief defines a pointer to an integrator's right-hand side (RHS) function */
typedef Vector (*odeFunc)(const double& _time, const Vector& _state, const Matrix& _parameters, vectorFuncPtr _funcPtr);
//typedef Vector(*odeFunc)(const double& _time, const Vector& _states, const Matrix& _params);

/*! \brief defines a pointer to an integrator's right-hand side (RHS) function using a functor for the arbitrary vector function 
*
* @param _time This is the time at this step of the integration
* @param _integratingState This is the current state at the time of integration. The state can be any vector 
    of values the user desires to integrate, such as quaternions, angular momentum, energy, or position. These values 
    are the result of the time derivative values being combined through the integration.
* @param _pOrbit This is a pointer to an Orbit object. It is only necessary if the RHS function needs to inspect values of
    the orbit (OrbitHistory, OrbitState, etc.). If the user does not need to use the orbit object, the integration function will 
    have passed in a NULL value (pointer to nothing), and the orbit object should not be used.
* @param _pAttitude This is a pointer to an Attitude object. It is only necessary if the RHS function needs to inspect values of
    the attitude (AttitudeHistory, AttitudeState, etc.). If the user does not need to use the attitude object, the integration function will 
    have passed in a NULL value (pointer to nothing), and the attitude object should not be used.
* @param _parameters This is a matrix of constants that is passed to the RHS function for the user to store constants throughout 
    the integration. Examples include the Moment of Inertia matrix, mass, ballistic coefficient, etc. The matrix can be any size, but the 
    user needs to note how values were stored into the matrix in order to correctly extract them. (ex the first 3x3 sub-matrix is the MOI, 
    while element (4,1) is the mass, and element (4,2) is the drag area).
* @param _forceFunctorPtr This is a call-back function meant for use in calculating disturbance functions. By setting this reference to a 
    force or torque disturbance function, the user can call this function within the RHS function, giving the current (integrated) states 
    as parameters to calculate the instantaneous disturbance vector. (see Functor)
* The right-hand side (RHS) is the function that calculates the time derivatives of the state: \f$\dot{\bf x}=f(t,{\bf x})\f$.
The type @em odeFunctor is a definition of the interface to the RHS function, which requires the calculation time, state at that time, 
a possible pointer to an Orbit and Attitude Object, a matrix of parameter constants, and a call-back function pointer that can be used to 
evaluate any function of OrbitState and AttitudeState. An Example of a RHS function for 2-body orbital dynamics is:
\code
static Vector TwoBodyDynamics(const ssfTime &_time, const Vector& _integratingState, Orbit *_pOrbit, Attitude *_pAttitude, const Matrix &_parameters, const Functor &_forceFunctorPtr)
{
    static Vector Forces(3);
    static Vector Velocity(3);
    static Vector stateDot(6);
    static OrbitState orbState
    (new PositionVelocity);

    orbState.GetStateRepresentation()->SetPositionVelocity(_integratingState);

    Forces = _forceFunctorPtr.Call(_time, orbState, _Attitude->GetStateObject());
    Velocity(_) = _integratingState(_(VectorIndexBase+3,VectorIndexBase+5));
    
    stateDot(_(VectorIndexBase, VectorIndexBase+2)) = Velocity(_);
    stateDot(_(VectorIndexBase+3, VectorIndexBase+5)) = Forces(_);
    return stateDot;
}
\endcode
*/
typedef Vector (*odeFunctor)(const ssfTime& _time, const Vector& _integratingState, Orbit *_pOrbit, Attitude *_pAttitude, const Matrix& _parameters, const Functor& _forceFunctorPtr);
/** @} */

/*! \class Integrator 
* \brief Interface class to the Integrator algorithm strategies.
* \ingroup IntegrationLibrary
*
* This class defines the functions that are required for all Integrator types (ie \sa RungeKuttaIntegrator, 
\sa AdamsBashfourthIntegrator, etc). 

\par
Integration in the Open-Sessame Framework is modeled after integration in <a href="http://www.mathworks.com" target=_new>MatLab</a>.
To integrate, a user must specify a Right-Hand Side (RHS) function that has the form \f$\dot{\bf x} = f\left(t,{\bf x}, {\bf P}, T(t, {\bf x})\right)\f$, 
where \f$t\f$ is the time (in seconds), \f${\bf x}\f$ is the vector of states being integrated, \f${\bf P}\f$ is a matrix of constants, and 
\f$T(t, {\bf x})\f$ is a reference to an external function which can be used to evaluate other parameters necessary 
for the RHS equation. The integration strategy will then evaluate the function \f$f\f$ at various timesteps, depending on the 
integration algorithm, and combine the results together to approximate the integrated solution. 

\par
Integration is specifically useful in the Open-Sessame Framework for numerically evaluating the equations of motion (EOM) 
of a spacecraft. The attitude \& orbit EOM are usually defined as the time rate of change of the states (rotations, angular 
velocities, position, angular momentum, energy, etc) which can be integrated to determine the 
state of the spacecraft at some future time. For example, to evaluate the quaternion at some time \f$T\f$:
\f[\frac{d\bar{\bf q}}{dt} = \dot{\bar{\bf q}} \Rightarrow d\bar{\bf q} = \dot{\bar{\bf q}} dt\f]
\f[ \bar{\bf q}(T) = \int^{T}_{0}{\dot{\bar{\bf q}}(t, \bar{\bf q}(T)) dt} \f]

\example testAttitudeIntegration.cpp
\example testOrbitIntegration.cpp
*/
class Integrator
{
public:
    /*! Standard Integration Function */
//    virtual Matrix Integrate(const Vector& _propTime, odeFunc _FuncPtr, const Vector& _initialConditions, const Matrix& _constants, vectorFuncPtr _vectorFuncPtr) = 0;
    
    
    /*! Interface to the Orbit \& Attitude integration function.
        * 
        * This function defines just the interface to any of the derived integration strategies. Because it 
        * is pure virtual (virtual ... = 0;), it is not actually implemented, but defines a member function that 
        * is required to be implemented by all derived classes. Therefore, the user can be assured this integration 
        * function will exist for all derived classes.
        *
        * @param _propTime This input variable specifies the list of integration times, from the starting value (first time) to the ending integration (last time) with the specified intervals.
        *	This vector is built by creating ssfTime object, and "push_back" them onto the vector list:
            * \code
            * vector<ssfTime> integrationTimes;
            * ssfTime begin(0);
            * ssfTime end(begin + 20);
            * integrationTimes.push_back(begin);
            * integrationTimes.push_back(end);
            * \endcode
        * @param _FunctorPtr This is the reference (see odeFunctor) to the Right-Hand side (RHS) of the integration equation. It should be a single function that computes the time derivative 
        *	of the state given the time, current state, and other parameters.
        * @param _initialConditions The vector of initial conditions of the state being integrated. It can be any sized. And should be in the order specified by the user. 
            (ex. \f$[q_1, q_2, q_3, q_4, \omega_1, \omega_2, \omega_3]^{T}\f$) 
        * @param _Orbit This is a pointer to an Orbit object. It will be passed directly to the RHS and may be used for evaluating the dynamics or disturbance torque/forces. 
        *	However, if no orbit is required, or used, the user should only pass a NULL pointer and the orbit object shouldn't be used in the user's RHS function.
        * @param _Attitude This is a pointer to an Attitude object. It behaves much the same way as _Orbit above. It will be passed directly to the RHS function for use in 
        * 	evaluation, but if not used, the user should only pass a NULL pointer, and the attitude object not used in the RHS function. 
        * @param _constants This is a matrix of constants that is required by the RHS function. The constants are passed to each evaluation of the RHS, and may be any size, and 
        *	store any values the user requires. Examples include Moments of Inertia, ballistic coefficients, mass, etc. 
                Example: \f[\begin{bmatrix} I_{11} & I_{12} & I_{13} \\ I_{21} & I_{22} & I_{23} \\ I_{31} & I_{32} & I_{33} \\ mass & drag area & 0 \end{bmatrix}\f]
        * @param _functorPtr The Functor is a call-back function that the RHS can use to evaluate an external function call. The prototype of the _functorPtr must correspond to the Functor 
        *	definition, but other than that, may perform any calculations required by the user in the RHS function.
        * @return The output of the integration function is a matrix of calculated integration times (meshpoints), and integrated state values at each of the meshpoints.
            * \f[
            * \begin{bmatrix}
            * t_0 & x_{1,0} & x_{2,0} & ...\\
            * t_1 & x_{1,1} & x_{2,1} & ...\\
            * t_2 & x_{1,2} & x_{2,2} & ...\\
            * . & . & . & . \\
            * t_{final} & x_{1,f} & x_{2,f} & ...
            * \end{bmatrix}
            * \f]
            * where \f$t_T\f$ is the time at step T, and \f$x_{i,T}\f$ is the state value of element i, at time step T.
        */
    virtual Matrix Integrate(const vector<ssfTime>& _propTime, odeFunctor _FunctorPtr, const Vector& _initialConditions, Orbit* _pOrbit, Attitude* _pAttitude, const Matrix& _constants, const Functor& _functorPtr) = 0;
protected:
//    Integrator() {};
};

} // close namespace O_SESSAME

#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Integrator.h,v $
*	Revision 1.10  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.9  2003/05/22 21:03:52  nilspace
*	Updated comments.
*	
*	Revision 1.8  2003/05/22 02:59:38  nilspace
*	Changed to pass pointers instead of references of Orbit & Attitude objects.
*	
*	Revision 1.7  2003/05/21 19:45:01  nilspace
*	Updated documentation.
*	
*	Revision 1.6  2003/05/20 17:44:21  nilspace
*	Updated comments.
*	
*	Revision 1.5  2003/05/13 18:58:27  nilspace
*	Cleaned up comments.
*	
*	Revision 1.4  2003/04/27 22:04:34  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.3  2003/04/25 13:45:55  nilspace
*	const'd Get() functions.
*	
*	Revision 1.2  2003/04/23 16:30:59  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/04/08 22:32:20  nilspace
*	Initial submission.
*	
*
******************************************************************************/

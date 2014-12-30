//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file GravityFunctions.h
*  \brief Gravity force function models.
*  \author $Author: rsharo $
*  \version $Revision: 1.4 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_GRAVITYFUNCTIONS_H__
#define __OSESSAME_GRAVITYFUNCTIONS_H__
#include "matrix/Matrix.h"
#include "utils/Time.h"
#include "OrbitState.h"
#include "Attitude.h"
#include "Environment.h"
#include <vector.h>
using namespace std;
using namespace O_SESSAME;

/*! \brief Gravity force function modeling two-body gravity.
* @ingroup EnvironmentForceFunctions
*
* 
Newton formulated the simplified two-body equation, or Law of Universal Gravitation. This formulation is a simplified model because it only accounts for two bodies: the central body, and the spacecraft. In general it can be applied to any two massive bodies which have a gravitational attraction with the following assumptions:
-# The bodies are spherically symmetric. 
-# There are no external or internal forces acting on the system other than the gravitational forces which act along the line joining the centers of the two bodies.

\image html images\TwoBody.jpg
\image latex images\TwoBody.pdf "Two body gravity diagram" 
\par
Newton's Law of Universal Gravitation states that the force of gravity between two bodies is proportional to the product of their masses and inversely proportional to the square of the distance between them:
\f[
{\bf F}_{g} = - \frac{GMm}{r^{2}}\frac{{\bf r}}{r}
\f]
where \f${\bf F}_{g}\f$ is the force of gravity acting on mass \f$M\f$ and \f$m\f$, and the vector between the two masses is \f${\bf r}={\bf r}_{M}-{\bf r}_{m}\f$. The parameter \f$G\f$ is the universal contant, which is usually measured by observing the quantity \f$Gm_{\oplus}\f$, since the mass of the earth is large and more easily measured. This gravitational parameter, \f$\mu\f$ has a modern (most recent, accurate) value of \f$3.986\,004\,415\times 10^{5} \frac{km^{3}}{s^{2}}\f$. It is important to note that the vector \f${\bf r}\f$ is measured with respect to inertial axes. 

* @param _currentTime current simulation time
* @param _currentOrbitState current orbit state, including representation and reference frame
* @param _currentAttitudeState current attitude state, including rotation and reference frame
* @param _parameterList EnvFuncParamaterType parameter list for external variables = [\f$\mu\f$], gravitational parameter [km^3/(solar s)^2]
* @return This force functions returns a 3-element vector of forces (x,y,z) due to gravity using a 
*	two-body simplified force model.
*/
inline Vector GravityForceFunction(const ssfTime &_currentTime, const OrbitState  &_currentOrbitState, const AttitudeState &_currentAttitudeState, const EnvFuncParamaterType &_parameterList)
{
    static Vector Forces(3);
    static Vector Position(3); 
    Position(_) = _currentOrbitState.GetState()(_(VectorIndexBase,VectorIndexBase+2));
    Forces = - *(reinterpret_cast<double*>(_parameterList[0])) / pow(norm2(Position),3) * Position;
    return Forces;
}

/*! \brief Gravity gradient torque function modeling two-body gravity.
* @ingroup EnvironmentTorqueFunctions
*
The spacecraft body is subject to a non-uniform gravity field which can cause external torques about the body 
center. This non-uniformity is due to the inverse-square relation of the force field and the distance from the 
mass center, as well as a non-spherical, non-homogenous central body (such as the Earth, but especially true 
for asteroid or irregularly shaped central bodies). 

The gravity gradient torque about the body principal axes is:
\f[
{\bf T}_{gg}  = 3\omega _c ^2 {\bf o_3} ^{\times} {\bf{I}}{\bf o_3} 
\f]
where \f$\omega_c = 3\frac{\mu}{r^{3}}\f$ and \f$\mathbf{o_{3}}\f$ is the 
\f$3^{rd}\f$ column of the body-orbital rotation.

For enhanced accuracy, a better model would include a higher order gravity field that is dependent on the 
spacecraft's position and the central body's orientation. Furthermore, it is useful to analyze the spacecraft's 
moment of inertia matrix to evaluate its stability due to the gravity gradient disturbance torque.

* @param _currentTime current simulation time
* @param _currentOrbitState current orbit state, including representation and reference frame
* @param _currentAttitudeState current attitude state, including rotation and reference frame
* @param _parameterList EnvFuncParamaterType parameter list for external variables = [\f$MOI; \mu\f$], Moments of Inertia, gravitational parameter
* @return This force functions returns a 3-element vector of torques (Tx,Ty,Tz) due to gravity gradient using a 
*	two-body simplified force model.
*/
inline Vector GravityGradientTorque(const ssfTime &_currentTime, const OrbitState  &_currentOrbitState, const AttitudeState &_currentAttitudeState, const EnvFuncParamaterType &_parameterList)
{
    static Matrix MOI(3,3); MOI = *(reinterpret_cast<Matrix*>(_parameterList[0]));
    static Vector o3(3); o3 = (_currentAttitudeState.GetRotation2Orbital(_currentOrbitState)).GetDCM()(_,3);
    static Vector Position(3); Position = (_currentOrbitState.GetStateRepresentation()->GetPositionVelocity())(_(1,3));
    return 3 * *(reinterpret_cast<double*>(_parameterList[1]))/(pow(norm2(Position),3))   * skew(o3) * MOI * o3;
}

#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: GravityFunctions.h,v $
*	Revision 1.4  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.3  2003/06/12 23:06:21  nilspace
*	Fixed torque function.
*	
*	Revision 1.2  2003/06/12 21:26:50  nilspace
*	Replaced minus sign in Forces calculation.
*	
*	Revision 1.1  2003/06/12 17:58:40  nilspace
*	Initial Submission.
*	
*	Revision 1.6  2003/05/22 21:03:26  nilspace
*	Fixed to run faster with static variables.
*	
*	Revision 1.5  2003/05/20 17:47:59  nilspace
*	Updated comments.
*	
*	Revision 1.4  2003/05/13 18:49:41  nilspace
*	Fixed to get the StateObjects.
*	
*	Revision 1.3  2003/05/10 00:43:13  nilspace
*	Updated the includes for Orbit.h and Attitude.h
*	
*	Revision 1.2  2003/04/22 20:25:44  simpliciter
*	Updated LaTeX formulas for \ddot{r} and \dot{state vector} for
*	proper display.
*	
*	Revision 1.1  2003/04/08 22:48:29  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

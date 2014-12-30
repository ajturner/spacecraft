//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file AttituteDynamics_QuaternionAngVel.h
*  \brief Attitude Dynamic equations using Quaternions and Angular Velocities.
*  \author $Author: rsharo $
*  \version $Revision: 1.3 $
*  \date    $Date: 2003/10/18 21:37:27 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_ATTDYN_QUATANGVEL_H__
#define __OSESSAME_ATTDYN_QUATANGVEL_H__
#include "matrix/Matrix.h"
#include "Integrator.h"
#include "utils/Time.h"
#include "Orbit.h"
#include "OrbitState.h"
#include "Attitude.h"
#include <vector.h>
using namespace std;
using namespace O_SESSAME;

/*! \brief Attitude state conversion function from Quaternion and Angular Velocity state vector.
* \relates AttituteDynamics_QuaternionAngVel 
*
* This function converts a matrix of states from the AttituteDynamics_QuaternionAngVel right-hand
* side function into an AttitudeState object. This conversion function is necessary for propagators 
* to store to an AttitudeHistory object regardless of the equations of motion state vector being
* used.
* @param _meshPoint State vector from integration mesh point, [Quaternion (4), AngularVelocity (3)].
* @param _convertedAttitudeState AttitudeState object that is converted from the mesh point vector.
*/
static void QuaternionAngVelConvFunc(const Matrix &_meshPoint, AttitudeState &_convertedAttitudeState)
{
    static Vector tempQ(4); 
    static Vector tempAngVel(3); 
    
    tempQ(_) = ~_meshPoint(_,_(2, 5));
    tempAngVel(_) = ~_meshPoint(1, _(6, 8));
    _convertedAttitudeState.SetState(Rotation(Quaternion(tempQ)), tempAngVel);
    return;
}

/*! \brief Attitude Dynamics equation using Quaternions and Angular Velocities as the state variables
* @ingroup AttitudeEquationsOfMotion
* 
*
The rotation of a rigid body is described by the kinematic equations of motion and the kinetic equations 
of motion. As discussed above, the kinematics specifically model the current attitude of the body with 
respect to time. The dynamics are characterized by the absolute angular velocity vector, $\omega$.

Each attitude representation has a set of equations that describe its time rate of change due to the 
dynamics of the rigid body. 

The propagation of the Quaternion kinematics is defined as:
\f[
\dot {\bar{\bf q}} = {Q}\left(\bar{\bf q}\right){\bf \omega}
\f] 
\f[
 = \frac{1}{2}\begin{bmatrix}
   {{\bf{q}}^{\times}  + q_4  {\bf 1}}  \\
   { - {\bf{q}}^T }  \\
\end{bmatrix} {\bf \omega}
\f]
\par
The differential equations for the angular velocity in the body frame are based on Euler's equation:
\f[
\bf{I}\dot{\bf \omega}  = \bf{g} - \omega  \times \bf{I}\omega
\f]
where \f$\textbf{I}\f$ is the spacecraft moment of inertia matrix, \f$\omega\f$ is the body angular 
velocity, and \f$\textbf{g}\f$ are the spacecraft torques.

This equation can be verified for an axis-symmetric body under torques about the 1,2 axes as follows:
\f[
\omega_{1} = \omega_{01}\cos{\omega_{p}t} + \omega_{02}\sin{\omega_{p}t} + \frac{1}{I_{T}}\int^{t}_{0}{[g_{1}(\tau)\cos{(\omega_{p}(t-\tau))}+g_{2}(\tau)\sin{(\omega_{p}(t-\tau))}]d\tau}
\f]
\f[
\omega_{2} = -\omega_{01}\sin{\omega_{p}t} + \omega_{02}\cos{\omega_{p}t} + \frac{1}{I_{T}}\int^{t}_{0}{[-g_{1}(\tau)\sin{(\omega_{p}(t-\tau))}+g_{2}(\tau)\cos{(\omega_{p}(t-\tau))}]d\tau}
\f]
\f[
\omega_{3} = \omega_{03}
\f]

* @param _time current time (in seconds)
* @param _state vector of states, \f$\left[\bar{\bf q},\bf{\omega}\right]^{T}\f$ (-, radians/second)
* @param _pOrbit pointer to the current Orbit instance
* @param _pAttitude pointer to the current Attitude instance
* @param _parameters additional parameters for integration \f$\left[MOI(3\times3); MOI^{-1}(3\times3)\right]\f$ 
* @param _torqueFuncPtr pointer to the torque calculating function
* @return This attitude dynamics RHS returns the 7-element vector of time derivatives of state \f$\left[\dot{\bar{\mathbf q}},\dot{\mathbf \omega}\right]^{T}\f$
*/
static Vector AttituteDynamics_QuaternionAngVel(const ssfTime &_time, const Vector& _integratingState, Orbit *_Orbit, Attitude *_Attitude, const Matrix &_parameters, const Functor &_torqueFuncPtr)
{
    static Vector stateDot(7);
    static Matrix bMOI(3,3); 
    static Matrix invMOI(3,3);
    static Matrix qtemp(4,3); 
    static Vector Tmoment(3);
    static Vector qIn(4); 
    static Vector wIn(3);
    qIn = _integratingState(_(VectorIndexBase,VectorIndexBase + 3));
    wIn = _integratingState(_(VectorIndexBase + 4,VectorIndexBase + 6));
    qIn /= norm2(qIn);

//    _attitudeState->SetState(Rotation(Quaternion(qIn)), wIn);  // Need to speed up in some way
    qtemp(_(VectorIndexBase+0,VectorIndexBase+2),_(VectorIndexBase+0,VectorIndexBase+2)) = skew(qIn(_(VectorIndexBase+0,VectorIndexBase+2))) + qIn(VectorIndexBase+3) * eye(3);
    qtemp(VectorIndexBase+3, _(VectorIndexBase+0,VectorIndexBase+2)) = -(~qIn(_(VectorIndexBase+0,VectorIndexBase+2)));

    bMOI = _parameters(_(MatrixIndexBase+0,MatrixIndexBase+2),_(MatrixIndexBase+0,MatrixIndexBase+2));
    invMOI = _parameters(_(MatrixIndexBase+3,MatrixIndexBase+5),_(MatrixIndexBase+0,MatrixIndexBase+2));
    Tmoment = _torqueFuncPtr.Call(_time, _Orbit->GetStateObject(), _Attitude->GetStateObject());
    
    stateDot(_(VectorIndexBase,VectorIndexBase + 3)) = 0.5 * qtemp * wIn;
    stateDot(_(VectorIndexBase + 4,VectorIndexBase + 6)) = (invMOI * (Tmoment - skew(wIn) * (bMOI * wIn)));
    return stateDot;
}

#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: QuaternionAngVelDynamics.h,v $
*	Revision 1.3  2003/10/18 21:37:27  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.2  2003/06/12 20:51:14  nilspace
*	Requires a precomputer MOI inverse.
*	
*	Revision 1.1  2003/06/12 19:17:42  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

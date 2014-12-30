//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file TwoBodyDynamics.h
*  \brief Dynamic equations and forces of two-body motion.
*  \author $Author: rsharo $
*  \version $Revision: 1.8 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_TWOBODYDYNAMICS_H__
#define __OSESSAME_TWOBODYDYNAMICS_H__
#include "matrix/Matrix.h"
#include "Integrator.h"
#include "utils/Time.h"
#include "Orbit.h"
#include "OrbitState.h"
#include "Attitude.h"
#include <vector.h>
using namespace std;
using namespace O_SESSAME;

/*! \brief Orbit state conversion function from Position and Velocity state vector.
* \relates TwoBodyDynamics 
*
* This function converts a matrix of states from the TwoBodyDynamics right-hand
* side function into an OrbitState object. This conversion function is necessary for propagators 
* to store to an OrbitHistory object regardless of the equations of motion state vector being
* used.
* @param _meshPoint State vector from integration mesh point, [Position (3), Velocity (3)].
* @param _convertedOrbitState OrbitState object that is converted from the mesh point vector. This function 
*	just sets the position and velocity state representation and requires the user to set the 
*	corresponding reference frame.
*/
static void PositionVelocityConvFunc(const Matrix &_meshPoint, OrbitState &_convertedOrbitState)
{
    static Vector tempPosVelVector(_meshPoint[MatrixColsIndex].getIndexBound() - 1);
    tempPosVelVector(_) = ~_meshPoint(_,_(MatrixIndexBase+1, _meshPoint[MatrixColsIndex].getIndexBound()));
    _convertedOrbitState.GetStateRepresentation()->SetPositionVelocity(tempPosVelVector);
    return;
}

/*! \brief Orbit equation of motion using position and velocity.
* @ingroup OrbitEquationsOfMotion
*
*
* Calculate the new time rate of change of state (position & velocity) using two-body dynamics with disturbance forces
\f[
\ddot{\vec{r}}  =  -\frac{\mu}{r^{2}}\frac{\vec{r}}{r}\f]
The returned state vector is:
\f[
\begin{bmatrix}
\dot{\vec{r}}\\
\dot{\vec{v}}
\end{bmatrix}
 = 
\begin{bmatrix}
\vec{v}\\
-\frac{\mu}{\left|\vec{r}\right|^{3}}\vec{r}
\end{bmatrix}
\f]
* @param _time current time (in seconds)
* @param _state vector of states, \f$\left[\vec{r},\vec{v}\right]^{T}\f$ (kilometers, kilometers/second)
* @param _pOrbit pointer to the current Orbit instance
* @param _pAttitude pointer to the current Attitude instance
* @param _parameters additional parameters for integration \f$\left[\mu\right]\f$ 
* @param _forceFuncPtr pointer to the force calculating function
* @return 6x1 vector of time derivatives of state \f$\left[\dot{\vec{r}},\dot{\vec{v}}\right]^{T}\f$
*/
static Vector TwoBodyDynamics(const ssfTime &_time, const Vector& _integratingState, Orbit *_pOrbit, Attitude *_pAttitude, const Matrix &_parameters, const Functor &_forceFunctorPtr)
{
//    _Orbit->SetStateObject(OrbitState(new PositionVelocity(_integratingState)));
    static Vector Forces(3);
    static Vector Velocity(3);
    static Vector stateDot(6);
    static AttitudeState tempAttState; // don't need this except to pass an empty one if there is no attitude
    static OrbitState orbState(new PositionVelocity);

    orbState.GetStateRepresentation()->SetPositionVelocity(_integratingState);

    if(_pAttitude)
        Forces = _forceFunctorPtr.Call(_time, orbState, _pAttitude->GetStateObject());
    else 
        Forces = _forceFunctorPtr.Call(_time, orbState, tempAttState);

    Velocity(_) = _integratingState(_(VectorIndexBase+3,VectorIndexBase+5));
    

    stateDot(_(VectorIndexBase, VectorIndexBase+2)) = Velocity(_);
    stateDot(_(VectorIndexBase+3, VectorIndexBase+5)) = Forces(_);
    return stateDot;
}

#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: TwoBodyDynamics.h,v $
*	Revision 1.8  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.7  2003/06/12 18:02:37  nilspace
*	Fixed evaluation.
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

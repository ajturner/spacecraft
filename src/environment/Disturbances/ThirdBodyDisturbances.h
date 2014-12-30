//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file ThirdBodyDisturbances.h
*  \brief Environmental disturbances due to Third Bodies.
*  \author $Author: rsharo $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_THIRDBODY_PERTUBATIONS_H__
#define __OSESSAME_THIRDBODY_PERTUBATIONS_H__
#include "matrix/Matrix.h"
#include "utils/Time.h"
#include "OrbitState.h"
#include "Attitude.h"
#include "Environment.h"
#include <vector.h>
using namespace std;
using namespace O_SESSAME;

/*! \brief The third body force disturbance due to gravity.
* @ingroup EnvironmentForceFunctions
*
* 
* @param _currentTime current simulation time
* @param _currentOrbitState current orbit state, including representation and reference frame
* @param _currentAttitudeState current attitude state, including rotation and reference frame
* @param _parameterList EnvFuncParamaterType parameter list for external variables, [CentralBody* orbiting central body, CentralBody* third-body]  
* @return This force functions returns a 3-element vector of forces (x,y,z) due to gravity using a 
*	two-body simplified force model.
*/
Vector ThirdBodyForceDisturbance(const ssfTime &_currentTime, const OrbitState  &_currentOrbitState, const AttitudeState &_currentAttitudeState, const EnvFuncParamaterType &_parameterList)
{
    static Vector Forces(3);
    static Vector Position(3); 
    static CentralBody* pOrbCB, pThirdBody;
    pOrbCB = reinterpret_cast<CentralBody*>(_parameterList[0]);
    pThirdBody = reinterpret_cast<CentralBody*>(_parameterList[1]);
    
    static double massThirdBody = pThirdBody->GetMass();
    static Vector vectorOrbCB2ThirdBody = pOrbCB->GetVector2Body(pThirdBody);
    static Vector vectorThirdBody2Satellite(3); 
        vectorSat2ThirdBody = - pThirdBody->GetVector2Body(_currentOrbitState); // negative to "switch the head" around
    static double B = norm2(vectorOrbCB2ThirdBody) / norm2(vectorSat2ThirdBody) - 1;  
    static double beta = pow(1+B, 3);
    
    Position(_) = _currentOrbitState.GetState()(_(VectorIndexBase,VectorIndexBase+2));
    Forces = - c_GravitationalConstant * massThirdBody / pow(vectorOrbCB2ThirdBody, 3) * (Position(_) - beta * vectorSat2ThirdBody);
    return Forces;
}

#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: ThirdBodyDisturbances.h,v $
*	Revision 1.2  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.1  2003/06/12 17:58:42  nilspace
*	Initial Submission.
*	
*	
******************************************************************************/

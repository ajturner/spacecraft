//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file SolarDisturbances.h
*  \brief Solar disturbance function models.
*  \author $Author: rsharo $
*  \version $Revision: 1.3 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_SOLAR_DISTURBANCES_H__
#define __OSESSAME_SOLAR_DISTURBANCES_H__
#include "matrix/Matrix.h"
#include "utils/Time.h"
#include "OrbitState.h"
#include "Attitude.h"
#include "Environment.h"
#include <vector.h>
using namespace std;
using namespace O_SESSAME;

/*! \brief Solar radiation pressure environmental disturbance force function.
* @ingroup EnvironmentForceFunctions
*
Another non-conservative disturbance force, like atmospheric drag, is due to the fact that light photons can 
impart a force on an absorbing or reflecting body. The force of these photons is usually very low, but can vary 
largely between eclipse, based on the body, and during solar storms. The solar-radiation pressure is even the 
basis for such spacecraft propulsion designs as solar sails, and so should be used for accurate models.

The solar pressure, \f$p_{SR}\f$, or change in momentum, is the main parameter in determing the force of the 
solar-radiation pressure. For the Earth, this has a nominal value of \f$4.51 \times 10^{-6}\frac{N}{m^{2}}\f$, 
where more precise values can be calculated depending on the time of year, as well as position from the Sun. The 
effect of solar-radiation pressure also varies due to the reflectivity, \f$c_{R}\f$, of the spacecraft, where 0.0 
indicates no effect, 1.0 is a completely absorbing body, and 2.0 is an absorbing and reflecting body. 

The combined force of the solar radiation pressure is found to be:
\f[
    \vec{a}_{radiation} = -\frac{p_{SR}c_{R}A_{S}}{m}\frac{\vec{\bf{r}}_{\odot sat}}{\left|\vec{\bf{r}}_{\odot sat}\right|}
\f]
where \f$\vec{\bf{r}}_{\odot sat}\f$ is the distance from the satellite to the sun (or light-emitting body), and \f$A_{S}\f$ is the spacecraft's exposed area to the sun. This value of area is very important for calculating the disturbance difference as the spacecraft passes from full sunlight, into eclipse, or when being shadowed by another body (moon or another spacecraft). 

Using basic geometry, it can be shown that simple conditions for determining if a satellite is in sunlight are\cite{Vallado:97}:
\f[
    \tau_{min} = \frac{\left|\vec{\bf{r}}_{sat}\right|^{2}-\vec{\bf{r}}_{sat}\cdot\vec{\bf{r}}_{\odot}}{\left|\vec{\bf{r}}_{sat}\right|^{2} + \left|\vec{\bf{r}}_{\oplus}\right|^{2}-2\vec{\bf{r}}_{sat}\cdot\vec{\bf{r}}_{\odot}}
\f] 
\f[
    \mbox{Sunlight if }   \tau_{min} < 0\mbox{ or }\tau_{min}>1  
\f] 
\f[
    \mbox{ or }   \left|\vec{c}\left(\tau_{min}\right)\right|^{2}  = \left(1-\tau_{min}\right)\left|\vec{\bf{r}}_{sat}\right|^{2}+\left(\vec{\bf{r}}_{sat}\cdot\vec{\bf{r}}_{\oplus}\right)\tau_{min}\geq 1.0  
\f]
 
* \todo Add checking for eclipse.
* @param _currentTime current simulation time
* @param _currentOrbitState current orbit state, including representation and reference frame
* @param _currentAttitudeState current attitude state, including rotation and reference frame
* @param _parameterList EnvFuncParamaterType parameter list for external variables
    \par 
        \f[\begin{bmatrix}
        \left[r_{\odot sat_{x}}, r_{\odot sat_{y}}, r_{\odot sat_{z}}\right]^{T} \\
         m, mass (kg) \\ p_{SR}, solar pressure (N/m^2) \\ c_{R}, reflectivity \\ A, Area (m^2) 
        \end{bmatrix}\f]
        \f$r_{\odot sat}\f$ = distance from satellite to the sun (m)
* @return This force functions returns a 3-element vector of forces (x,y,z) due to solar radiation pressure using a 
*	 simplified force model.
*/
Vector SolarRadiationPressureForceFunction(const ssfTime &_currentTime, const OrbitState  &_currentOrbitState, const AttitudeState &_currentAttitudeState, const EnvFuncParamaterType &_parameterList)
{
    static Vector Forces(3);
    static Vector SunVector(3);
    static double p_SR, c_R, m, A_S;
    SunSatVector(_) = *(reinterpret_cast<Vector*>(_parameterList[0]));
    m 	 = *(reinterpret_cast<double*>(_parameterList[1]));
    p_SR = *(reinterpret_cast<double*>(_parameterList[2]));
    c_R  = *(reinterpret_cast<double*>(_parameterList[3]));
    A_R  = *(reinterpret_cast<double*>(_parameterList[4]));
    
    Forces = -p_SR * c_R * A_S / m * SunSatVector / norm2(SunSatVector);
    return Forces;
}

#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: SolarDisturbances.h,v $
*	Revision 1.3  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.2  2003/06/12 21:51:54  nilspace
*	Removed & alignment characters from comments.
*	
*	Revision 1.1  2003/06/12 17:58:42  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

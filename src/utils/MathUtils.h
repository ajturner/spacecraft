//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file ssfMathUtils.h
*  \brief Collection of math constants and utility functions.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/05/22 03:00:07 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_MATH_UTILS_H__
#define __SSF_MATH_UTILS_H__
#include <math.h>
namespace O_SESSAME {
//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \defgroup MathUtils Math Utilities
* \ingroup Utilities
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
/** @defgroup Trigonometry Trigonometry Routines
* \ingroup MathUtils
* Toolbox of Trigonometry routines useful for spacecraft operations.
* @{
*/

/*! \brief Representation of an angle in radians.
    * Currently the angle representation is assumed to be radians, and can be used in any of the other 
    * Trigonometry functions to convert to Degrees or Degrees-Minutes-Seconds. In the future, the Angle 
    * should be a class that is unit independent and include the appropriate conversion functions.
    */
typedef double Angle;

/*! \brief Converts an angle from Degrees, Minutes, Seconds (^o,','') to a single quantity in degrees
 *	and fractions of a degree.
 * @param _Degrees Number of degrees in angle (^o).
 * @param _Minutes Number of minutes in angle (').
 * @param _Seconds Number of seconds in angle ('').
 * @returns Angle in degrees (with decimal part).
 */
inline double DMS2Deg(const double& _Degrees, const double& _Minutes, const double& _Seconds)
{
    return _Degrees + _Minutes / 60 + _Seconds / 3600;
}

/*! \brief Converts an angle from a single quantity in degrees
 *	and fractions of a degree to Degrees, Minutes, Seconds (^o,','').
 * @param _Angle in degrees (with decimal part).
 * @param _Degrees Number of degrees in angle (^o).
 * @param _Minutes Number of minutes in angle (').
 * @param _Seconds Number of seconds in angle ('').
 */
inline void Deg2DMS(const double& _Angle, double& Degrees, double& Minutes, double& Seconds)
{
    Degrees = floor(_Angle);
    Minutes = floor((_Angle - Degrees) * 60);
    Seconds = (_Angle - Degrees - Minutes / 60) * 3600;
}

/*! \brief Converts an angle from Degrees, Minutes, Seconds (^o,','') to radians.
 * @param _Degrees Number of degrees in angle (^o).
 * @param _Minutes Number of minutes in angle (').
 * @param _Seconds Number of seconds in angle ('').
 * @returns Angle in radians (with decimal part).
 */
inline Angle DMS2Rad(const double& _Degrees,const double& _Minutes, const double& _Seconds)
{
    return DMS2Deg(_Degrees, _Minutes, _Seconds) * M_PI / 180;
}

/*! \brief Converts an angle from Degrees to radians.
 * @param _Degrees Angle to be converted (^o).
 * @returns Angle in radians (with decimal part).
 */
inline Angle Deg2Rad(const Angle& _Degrees)
{
    return _Degrees * M_PI / 180;
}

/*! \brief Converts an angle from radians to degrees, minutes, second format.
 * @param _Radians Angle to be converted (rad).
 * @param Degrees returned number of degrees in angle (^o).
 * @param Minutes returned number of minutes in angle (').
 * @param Seconds returned number of seconds in angle ('').
 */
inline void Rad2DMS(const Angle& _Radians, double& Degrees, double& Minutes, double& Seconds)
{
    double Angle = _Radians * 180 / M_PI;
    Deg2DMS(Angle, Degrees, Minutes, Seconds);
    return;
}

/*! \brief Converts an angle from radians to degrees.
 * @param _Radians The angle to be converted (rad).
 * @return returned number of degrees in angle (^o).
 */
inline Angle Rad2Deg(const Angle& _Radians)
{
    return _Radians * 180 / M_PI;
}
/*! \brief Calculates the hyperbolic arctangent of an value using \f$1/2 * log((1+z)/(1-z))$\f.
 * @param z value to be calculated.
 * @returns hyperbolic arctangent in radians.
 */
inline Angle atanh(const double& _z)
{
    return 0.5 * log((1+_z)/(1-_z));
}
/** @} */ // end of Trigonometry


} // close namespace O_SESSAME

#endif 

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: MathUtils.h,v $
*	Revision 1.2  2003/05/22 03:00:07  nilspace
*	Updated Angle type and inline'd all functions.
*	
*	Revision 1.1  2003/05/15 18:32:20  nilspace
*	Initial submission.
*	
*
******************************************************************************/

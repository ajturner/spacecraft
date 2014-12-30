//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file EarthCentralBody.h
*  \brief Interface to the EarthCentralBody object.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/06/09 15:20:39 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __EARTH_CENTRALBODY_H__
#define __EARTH_CENTRALBODY_H__
#include "math.h"
#include "Rotation.h"
//#include "Units.h"
#include "CentralBody.h"
#define PI 3.141592

namespace O_SESSAME {

/*! Earth Radius [/f$m^3/kg-s^2/f$] */
const double GRAVITATIONAL_CONSTANT = 6.669 * pow(10.0,-11.0); 
/*! Earth Radius [-] */
const double deg2rad = (float)PI / 180.0;

class EarthCentralBody : public CentralBody
{
public:
    EarthCentralBody();

private:
};
} // close namespace O_SESSAME

#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: EarthCentralBody.h,v $
*	Revision 1.2  2003/06/09 15:20:39  nilspace
*	Changed CentralBody directory.
*	
*	Revision 1.1  2003/06/06 17:34:53  nilspace
*	Moved to CentralBody directory.
*	
*	Revision 1.2  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.1  2003/04/08 22:36:51  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

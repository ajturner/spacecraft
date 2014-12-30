//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitFrameRSW.h
*  \brief Interface to the RSW Satellite Coordinate System Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.7 $
*  \date    $Date: 2003/05/21 03:51:38 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_FRAME_RSW_H__
#define __SSF_ORBIT_FRAME_RSW_H__
#include "OrbitFrame.h"

/*! \brief RSW Satellite Coordinate System
* \ingroup OrbitFrames
*
* \detail Applies to studies of relative motion because the system moves 
* with the satellite. The R axis is defined as pointing from the Earth's center along the 
* radius vector toward the satellite, and the W axis is fixed along the direction normal to 
* orbital plane. The S axis points in the direction of the velocity vector and is perpendicular 
* to the radius vector. 
* Radial: positions and displacements are parallel to the position vector (along R axis)
* Along-track: displacements are normal to the position vector and (for small e) are nearly
* 	parallel to the satellite's instantaneous velocity vector (along the S axis)
* Cross-track: positions are normal to the plane defined by thte current position and 
* 	velocity vectors (along the W axis). 
* Sometimes called the Gaussian coordinate system. (Vallado, pg. 42-43)	
*/
class OrbitFrameRSW : public OrbitFrame
{
public:
    OrbitFrameRSW();
    virtual ~OrbitFrameRSW();

    OrbitFramePQW* NewPointer();
    OrbitFramePQW* Clone();
protected:
    
    
private:

};
inline OrbitFrameRSW::OrbitFrameRSW() {};
inline OrbitFrameRSW::~OrbitFrameRSW() {};
inline OrbitFrameRSW* OrbitFrameRSW::NewPointer()		{ return new OrbitFrameRSW(); }
inline OrbitFrameRSW* OrbitFrameRSW::Clone()			{ return new OrbitFrameRSW(*this); }

#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitFrameRSW.h,v $
*	Revision 1.7  2003/05/21 03:51:38  nilspace
*	Fixed spelling of "the" in comments.
*	
*	Revision 1.6  2003/05/20 17:47:59  nilspace
*	Updated comments.
*	
*	Revision 1.5  2003/04/29 20:17:40  nilspace
*	Added NewPointer() and Clone() functions.
*	
*	Revision 1.4  2003/04/29 18:45:35  nilspace
*	Moved all function definitions out of class interface definition.
*	
*	Revision 1.3  2003/04/23 16:26:07  nilspace
*	Updated directory structure & default parameters.
*	
*	Revision 1.2  2003/04/22 17:37:25  nilspace
*	Added reference frames.
*	
*	Revision 1.1  2003/04/08 22:48:04  nilspace
*	Initial Submission.
*	
*
******************************************************************************/
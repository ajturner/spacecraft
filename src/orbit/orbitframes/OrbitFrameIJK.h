//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitFrameIJK.h
*  \brief Interface to the Geocentric Orbit Coordinate System Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.7 $
*  \date    $Date: 2003/05/20 17:47:59 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_FRAME_IJK_H__
#define __SSF_ORBIT_FRAME_IJK_H__
#include "Rotation.h"
#include "OrbitFrame.h"
/*! \brief Geocentric Orbit Coordinate System
* \ingroup OrbitFrames
*
* \detail Detailed Description. 	
*/
class OrbitFrameIJK : public OrbitFrame
{
public:
    OrbitFrameIJK();
    virtual ~OrbitFrameIJK();
    Rotation GetRotation2IJK() const;
    Rotation GetRotationFromIJK() const;
    
    OrbitFrameIJK* NewPointer();
    /*! \brief Returns a pointer to a copy of the Orbit Frame
        *
        * \detail Since orbit frames don't change, the function actually just returns a new pointer since
        *	its cheaper than copying useless information.
        */ 
    OrbitFrameIJK* Clone();
protected:
    
    
private:

};
inline OrbitFrameIJK::OrbitFrameIJK() {};
inline OrbitFrameIJK::~OrbitFrameIJK() {};
inline Rotation OrbitFrameIJK::GetRotation2IJK() const		{return eye(3);};
inline Rotation OrbitFrameIJK::GetRotationFromIJK() const	{return eye(3);};
inline OrbitFrameIJK* OrbitFrameIJK::NewPointer()		{ return new OrbitFrameIJK(); }
inline OrbitFrameIJK* OrbitFrameIJK::Clone()			{ return new OrbitFrameIJK(/**this*/); }
#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitFrameIJK.h,v $
*	Revision 1.7  2003/05/20 17:47:59  nilspace
*	Updated comments.
*	
*	Revision 1.6  2003/04/29 20:17:39  nilspace
*	Added NewPointer() and Clone() functions.
*	
*	Revision 1.5  2003/04/29 18:45:31  nilspace
*	Moved all function definitions out of class interface definition.
*	
*	Revision 1.4  2003/04/24 20:05:55  nilspace
*	Made GetRotation functions const.
*	
*	Revision 1.3  2003/04/23 16:26:05  nilspace
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
//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitFramePQW.h
*  \brief Interface to the Perifocal Satellite Coordinate System Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.8 $
*  \date    $Date: 2003/05/21 03:51:38 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_FRAME_PQW_H__
#define __SSF_ORBIT_FRAME_PQW_H__
#include "OrbitFrame.h"

/*! \brief Satellite Radial Coordinate System
* \ingroup OrbitFrames
*
* \detail The fundamental plane is the satellite's orbit, and the origin is at the 
* center of the Earth. The P axis points towards perigee, and the Q axis is \f$90^{\circ}\f$
* from the P axis in the direction of satellite motion. The W axis is then normal to the orbit. 
* The PQW system always maintains an orientation towards perigee and is therefore best
* suited for robits with a well-defined eccentricity. (Vallado, pg 41)
* 	
*/
class OrbitFramePQW : public OrbitFrame
{
    /*! \brief Constructor
        * @param _LongAscNode Longitude of the Ascending Node (rad)
        * @param _Inclination Inclination (rad)
        * @param _ArgPerigee Argument of Perigee (rad)
        */
    OrbitFramePQW(const double &_LongAscNode, const double &_Inclination, const double &_ArgPerigee);
    
    /*! \brief Deconstructor */
    virtual ~OrbitFramePQW();
    /*! \brief Return the rotation \f$R^{PQW-IJK}\f$
        * \f${\bf r}_{IJK} = R_{3}\left(-\Omega\right)R_{1}\left(-i\right)R_{3}\left(-\omega\right){\bf r}_{ECEF}\f$
        * @return rotation from PQW to IJK
        */
    Rotation GetRotation2IJK() const;
    
    /*! \brief Return the rotation \f$R^{IJK-PQW}\f$
        * \f${\bf r}_{ECEF} = R_{3}\left(\omega\right)R_{1}\left(i\right)R_{3}\left(\Omega\right){\bf r}_{IJK}\f$
        * @return rotation from IJK to PQW
        */
    Rotation GetRotationFromIJK() const;
    
    OrbitFramePQW* NewPointer();
    OrbitFramePQW* Clone();
protected:
    
private:

};
inline OrbitFramePQW::OrbitFramePQW(const double &_LongAscNode, const double &_Inclination, const double &_ArgPerigee): OrbitFrame(R3(-_LongAscNode)*R1(-_Inclination)*R3(-_ArgPerigee)) {};
inline OrbitFramePQW::~OrbitFramePQW() {};

inline Rotation OrbitFramePQW::GetRotation2IJK() const {return m_Transformation2IJK;};
inline Rotation OrbitFramePQW::GetRotationFromIJK() const {return ~m_Transformation2IJK;};
inline OrbitFramePQW* OrbitFrameIJK::NewPointer()		{ return new OrbitFramePQW(); }
inline OrbitFramePQW* OrbitFrameIJK::Clone()			{ return new OrbitFramePQW(*this); }

#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitFramePQW.h,v $
*	Revision 1.8  2003/05/21 03:51:38  nilspace
*	Fixed spelling of "the" in comments.
*	
*	Revision 1.7  2003/05/20 17:47:59  nilspace
*	Updated comments.
*	
*	Revision 1.6  2003/04/29 20:17:40  nilspace
*	Added NewPointer() and Clone() functions.
*	
*	Revision 1.5  2003/04/29 18:45:35  nilspace
*	Moved all function definitions out of class interface definition.
*	
*	Revision 1.4  2003/04/24 20:05:55  nilspace
*	Made GetRotation functions const.
*	
*	Revision 1.3  2003/04/23 16:26:06  nilspace
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
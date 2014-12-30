//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitFrameNTW.h
*  \brief Interface to the NTW Satellite Coordinate System Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.6 $
*  \date    $Date: 2003/04/29 20:17:39 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_FRAME_NTW_H__
#define __SSF_ORBIT_FRAME_NTW_H__
#include "OrbitFrame.h"

/*! \brief NTW Satellite Coordinate System
*
* Detailed Description. The primary axis lies in the orbital plane, normal to the velocity
* vector. The T axis is tangential to the orbit, and the W axis is normal to the orbital plane.
* In-track: deviations along the T axis.
* Used mainly to analyze drag effects on the orbit because drag always acts along the velocity
* vector. Also referred to as the Frenet System. (Vallado, pg. 43-44)	
*/
class OrbitFrameNTW : public OrbitFrame
{
    /*! \brief Constructor
        * @param _LongAscNode Longitude of the Ascending Node (rad)
        * @param _Inclination Inclination (rad)
        * @param _ArgPerigee Argument of Perigee (rad)
        * @param _ArgLatitude Argument of Latitude (rad)
        */
    OrbitFrameNTW(const double &_LongAscNode, const double &_Inclination, const double &_ArgPerigee, const double &_ArgLatitude);
    
    /*! \brief Deconstructor */
    virtual ~OrbitFrameNTW();
    
    /*! \brief Return the rotation \f$R^{NTW-IJK}\f$
        * \f${\bf r}_{IJK} = R_{3}(-\Omega)R_{1}(-i)R_{3}(-u)R_{3}(-\phi_{fpa}){\bf r}_{NTW}\f$
        * @return rotation from NTW to IJK
        */
    Rotation GetRotation2IJK() const;
    
    /*! \brief Return the rotation \f$R^{IJK-NTW}\f$
        * \f${\bf r}_{NTW} = R_{3}(\phi_{fpa})R_{3}(u)R_{1}(i)R_{3}(\Omega){\bf r}_{IJK}\f$
        * @return rotation from IJK to NTW
        */
    Rotation GetRotationFromIJK() const;

    OrbitFrameNTW* NewPointer();
    OrbitFrameNTW* Clone();
protected:
    
private:

};
inline OrbitFrameNTW::OrbitFrameNTW(const double &_LongAscNode, const double &_Inclination, const double &_ArgPerigee, const double &_ArgLatitude): OrbitFrame(R3(-_LongAscNode)*R1(-_Inclination)*R3(-_ArgPerigee)*R3(-_ArgLatitude)) {};
inline OrbitFrameNTW::~OrbitFrameNTW() {};

inline Rotation OrbitFrameNTW::GetRotation2IJK() const {return m_Transformation2IJK;};
inline Rotation OrbitFrameNTW::GetRotationFromIJK() const {return ~m_Transformation2IJK;};
inline OrbitFrameNTW* OrbitFrameNTW::NewPointer()		{ return new OrbitFrameNTW(); }
inline OrbitFrameNTW* OrbitFrameNTW::Clone()			{ return new OrbitFrameNTW(*this); }
#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitFrameNTW.h,v $
*	Revision 1.6  2003/04/29 20:17:39  nilspace
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
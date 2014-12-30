//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitFrameECEF.h
*  \brief Interface to the ECEF Satellite Coordinate System Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/05/20 17:47:59 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_FRAME_ECEF_H__
#define __SSF_ORBIT_FRAME_ECEF_H__

/*! \brief Earth-Centered, Earth-Fixed Satellite Coordinate System
* \ingroup OrbitFrames
*
* Detailed Description. 	
*/
class OrbitFrameECEF : public OrbitFrame
{
public:
    /*! \brief Constructor
        * @param _ApparentSiderealTime Apparent Sidereal Time (rad)
        */
    OrbitFrameECEF(const double &_ApparentSiderealTime):OrbitFrame(R3(-_ApparentSiderealTime));
    
    /*! \brief Return the rotation \f$R^{IJK-ECEF}\f$
        * \detail ignores transformation due to precession, nutation, and polar motion.
        * \f$\vec{r}_{IJK} = R_{3}\left(-\theta_{AST}\right)\vec{r}_{ECEF}\f$
        * @param _ApparentSiderealTime Apparent Sidereal Time (rad)
        * @return rotation from ECEF to IJK
        */
    Rotation GetRotation2IJK() const {return m_Transformation2IJK;};
    
    /*! \brief Return the rotation \f$R^{ECEF-IJK}\f$
        * \detail ignores transformation due to precession, nutation, and polar motion.
        * \f$\vec{r}_{ECEF} = R_{3}\left(\theta_{AST}\right)\vec{r}_{IJK}\f$
        * @param _ApparentSiderealTime Apparent Sidereal Time (rad)
        * @return rotation from IJK to ECEF
        */
    Rotation GetRotationFromIJK() const {return ~m_Transformation2IJK;};
    
protected:
    
private:

};

#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitFrameECEF.h,v $
*	Revision 1.2  2003/05/20 17:47:59  nilspace
*	Updated comments.
*	
*	Revision 1.1  2003/04/25 13:38:04  nilspace
*	Initial Submission.
*	
*
******************************************************************************/
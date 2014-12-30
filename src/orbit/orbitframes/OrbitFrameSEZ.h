//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitFrameSEZ.h
*  \brief Interface to the SEZ Satellite Coordinate System Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/05/20 17:47:59 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_FRAME_SEZ_H__
#define __SSF_ORBIT_FRAME_SEZ_H__
#include "OrbitFrame.h"

/*! \brief Topocentric Horizon, SEZ, Satellite Coordinate System
* \ingroup OrbitFrames
*
* \detail Detailed Description. 
*/
class OrbitFrameSEZ : public OrbitFrame
{
    /*! \brief Constructor
        * @param _LocalSiderealTime Apparent Sidereal Time (rad)
        * @param _GeodeticLatitude Geodetic Latitude (rad)
        */
    OrbitFrameSEZ(const double &_LocalSiderealTime, const double &_GeodeticLatitude): OrbitFrame(R3(-m_LocalSiderealTime)*R2(m_GeodeticLatitude-PI/2));
    
    /*! \brief Deconstructor */
    ~OrbitFrameSEZ() {};
    
    /*! \brief Return the rotation \f$R^{SEZ-IJK}\f$
        * \f${\bf r}_{IJK} = R_{3}\left(-\theta_{LST}\right)R_{2}\left(\theta_{LST}-\pi\right){\bf r}_{ECEF}\f$
        * @return rotation from SEZ to IJK
        */
    Rotation GetRotation2IJK() const {return m_Transformation2IJK;};
    
    /*! \brief Return the rotation \f$R^{IJK-SEZ}\f$
        * \f${\bf r}_{ECEF} = R_{2}\left(\pi-\theta_{LST}\right)R_{3}\left(\theta_{LST}\right){\bf r}_{IJK}\f$
        * @return rotation from IJK to SEZ
        */
    Rotation GetRotationFromIJK() const {return ~m_Transformation2IJK;};
    
protected:
    
private:

};


#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitFrameSEZ.h,v $
*	Revision 1.2  2003/05/20 17:47:59  nilspace
*	Updated comments.
*	
*	Revision 1.1  2003/04/25 13:38:04  nilspace
*	Initial Submission.
*	
*	Revision 1.1  2003/04/08 22:48:04  nilspace
*	Initial Submission.
*	
*
******************************************************************************/
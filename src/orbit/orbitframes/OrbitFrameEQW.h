//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitFrameEQW.h
*  \brief Interface to the EQW Orbit Frame Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.7 $
*  \date    $Date: 2003/05/20 17:47:59 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_FRAME_EQW_H__
#define __SSF_ORBIT_FRAME_EQW_H__
#include "OrbitFrame.h"

/*! \brief Equinoctial Coordinate System
* \ingroup OrbitFrames
*
* \detail Detailed Description	
*/
class OrbitFrameEQW : public OrbitFrame
{
public:
{
    /*! \brief Constructor
        * @param _LongAscNode Longitude of the Ascending Node (rad)
        * @param _Inclination Inclination (rad)
        */
    OrbitFrameEQW(const double &_LongAscNode, const double &_Inclination);
    
    /*! \brief Deconstructor */
    virtual ~OrbitFrameEQW();
    
    /*! \brief Return the rotation \f$R^{IJK-SEZ}\f$
        * \f${\bf r}_{IJK} = R_{3}\left(-\theta_{LST}\right)R_{2}\left(\theta_{LST}-\pi\right){\bf r}_{ECEF}\f$
        * @return rotation from SEZ to IJK
        */
    Rotation GetRotation2IJK() const;
    
    /*! \brief Return the rotation \f$R^{ECEF-SEZ}\f$
        * \f${\bf r}_{ECEF} = R_{2}\left(\pi-\theta_{LST}\right)R_{3}\left(\theta_{LST}\right){\bf r}_{IJK}\f$
        * @return rotation from IJK to SEZ
        */
    Rotation GetRotationFromIJK() const;
    
    OrbitFrameEQW* NewPointer();
    OrbitFrameEQW* Clone();
    
protected:
    int m_fr;
private:

};
inline OrbitFrameEQW::OrbitFrameEQW(const double &_LongAscNode, const double &_Inclination)
            {
                if(_Inclination>0 && _Inclination<=PI/2) {m_fr = 1;} 
                else{m_fr = -1;} 
                m_Transformation2IJK = R3(-m_fr*m_LongAscNode)*R1(-m_Inclination)*R3(m_LongAscNode);
            };
inline OrbitFrameEQW::~OrbitFrameEQW() {};
inline Rotation OrbitFrameEQW::GetRotation2IJK() const 	  {return m_Transformation2IJK;};
inline Rotation OrbitFrameEQW::GetRotationFromIJK() const {return ~m_Transformation2IJK;};

inline OrbitFrameEQW* OrbitFrameEQW::NewPointer()	{ return new OrbitFrameEQW(); }
inline OrbitFrameEQW* OrbitFrameEQW::Clone()		{ return new OrbitFrameEQW(*this); }
#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitFrameEQW.h,v $
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
*	Revision 1.1  2003/04/08 22:48:03  nilspace
*	Initial Submission.
*		
*
******************************************************************************/
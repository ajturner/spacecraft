//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitFrame.h
*  \brief Interface to the Orbit Frame abstract Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.9 $
*  \date    $Date: 2003/05/20 17:47:59 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_FRAME_H__
#define __SSF_ORBIT_FRAME_H__
#include "Rotation.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \defgroup OrbitFrames Orbit Frames
* \ingroup OrbitToolkit
*
* \detail
*/

/*! \brief Abstract class representating an orbital reference frame.
* \ingroup OrbitFrames
*
* \detail
*/

class OrbitFrame
{
public:
    virtual Rotation GetRotation2IJK() const = 0;
    virtual Rotation GetRotationFromIJK() const = 0;
    virtual OrbitFrame* NewPointer() = 0;
    virtual OrbitFrame* Clone() = 0;
    virtual ~OrbitFrame();

protected:
    OrbitFrame();
    OrbitFrame(const Rotation &_Transformation);
private:
    /** pointer to the origin object */
//    void *m_Origin;
//    m_FundamentalPlane;
//    m_PreferredDirection;
    RotationSense m_Sense;
    Rotation m_Transformation2IJK;

};

inline OrbitFrame::OrbitFrame(): m_Sense(RIGHT_HAND) {};
inline OrbitFrame::OrbitFrame(const Rotation &_Transformation) : m_Sense(RIGHT_HAND), m_Transformation2IJK(_Transformation) {};
inline OrbitFrame::~OrbitFrame() {};

#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitFrame.h,v $
*	Revision 1.9  2003/05/20 17:47:59  nilspace
*	Updated comments.
*	
*	Revision 1.8  2003/04/29 20:17:39  nilspace
*	Added NewPointer() and Clone() functions.
*	
*	Revision 1.7  2003/04/29 18:45:30  nilspace
*	Moved all function definitions out of class interface definition.
*	
*	Revision 1.6  2003/04/27 21:14:02  nilspace
*	Added to the namespace O_SESSAME.
*	Moved function definitions outside of the class interface definition.
*	
*	Revision 1.5  2003/04/25 14:02:41  nilspace
*	Made the destructor public.
*	
*	Revision 1.4  2003/04/24 20:05:54  nilspace
*	Made GetRotation functions const.
*	
*	Revision 1.3  2003/04/23 16:26:05  nilspace
*	Updated directory structure & default parameters.
*	
*	Revision 1.2  2003/04/22 17:37:24  nilspace
*	Added reference frames.
*	
*	Revision 1.1  2003/04/08 22:48:03  nilspace
*	Initial Submission.
*	
*	
*
******************************************************************************/

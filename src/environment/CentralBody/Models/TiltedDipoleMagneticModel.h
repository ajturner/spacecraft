//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file TiltedDipoleMagenticModel.h
*  \brief Magnetic field model using a tilted dipole.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/06/12 18:00:31 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_TILTED_DIPOLE_MAGNETIC_MODEL_H__
#define __OSESSAME_TILTED_DIPOLE_MAGNETIC_MODEL_H__

#include "MagneticModel.h"

namespace O_SESSAME {

/** @brief Define the model of a magnetic field using a tilted dipole model.
* @ingroup EnvironmentModels
*/
class TiltedDipoleMagneticModel : public MagneticModel
{
public:
    TiltedDipoleMagneticModel() {};
    virtual ~TiltedDipoleMagneticModel() {};
    
    virtual Vector GetMagneticField(const ssfTime& _currentTime, const Vector& _PositionVector); 

protected:
    
private:
    
};
}
#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: TiltedDipoleMagneticModel.h,v $
*	Revision 1.2  2003/06/12 18:00:31  nilspace
*	Fixed references to CentralBody.
*	
*	Revision 1.1  2003/06/10 14:26:50  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

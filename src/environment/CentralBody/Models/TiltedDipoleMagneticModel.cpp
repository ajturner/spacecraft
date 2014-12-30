//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file TiltedDipoleMagneticModel.cpp
*  \brief Algorithm for determining the magnetic field of a central body using a titled dipole mognetic model.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/06/12 18:00:31 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "TiltedDipoleMagneticModel.h"

namespace O_SESSAME {

/*! \brief Calculates the local magnetic field about a central body used a tilted dipole model.
*
*/
Vector TiltedDipoleMagneticModel::GetMagneticField(const ssfTime& _currentTime, const Vector& _PositionVector)
{
    m_MagFieldCoeffs.modelEpoch.Set(_currentTime.GetSeconds());
    double alpha_m = m_MagFieldCoeffs.modelEpoch.GetEpochGreenwichMeanSiderealTime() 
                        + m_MagFieldCoeffs.CBAvgRotationRate * m_MagFieldCoeffs.modelEpoch.SecondsSinceEpoch() 
                        + m_MagFieldCoeffs.DipoleEastLongitude;
    
    static Vector DipoleDirection(3);
        DipoleDirection(1) = sin(m_MagFieldCoeffs.DipoleCoelevation) * cos(alpha_m);
        DipoleDirection(2) = sin(m_MagFieldCoeffs.DipoleCoelevation) * sin(alpha_m);
        DipoleDirection(3) = cos(m_MagFieldCoeffs.DipoleCoelevation);
    
    return pow(m_MagFieldCoeffs.CBRadius,3) * m_MagFieldCoeffs.H0 
            / pow(norm2(_PositionVector),3) 
            * (3 * (~DipoleDirection * _PositionVector) * _PositionVector - DipoleDirection);
    
}
}


// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: TiltedDipoleMagneticModel.cpp,v $
*	Revision 1.2  2003/06/12 18:00:31  nilspace
*	Fixed references to CentralBody.
*	
*	Revision 1.1  2003/06/10 14:26:50  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file EarthCentralBody.cpp
*  \brief Implementation of the EarthCentralBody encapsulation object.
*  \author $Author: nilspace $
*  \version $Revision: 1.4 $
*  \date    $Date: 2003/08/24 20:59:13 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "EarthCentralBody.h"
namespace O_SESSAME {


EarthCentralBody::EarthCentralBody()
{
    m_Radius = 6378.140;// * _KM;
    m_Mass = 5.9742 * pow(10,24);// * _KG;
    m_GravitationalParameter = 398600.4415;// * km^3/(solar s)^2;
    
    m_AvgRotationRate = 7.2921152 * pow(10, -5); // rad/s
    
    // Set the coefficients of the magnetic field corresponding the IGRF2000
    m_MagFieldCoeffs.modelEpoch.SetEpoch(2000, 1, 1, 0, 0, 0);
    m_MagFieldCoeffs.H0 	  	= 30115; // nT
    m_MagFieldCoeffs.DipoleCoelevation 	= Deg2Rad(196.54);
    m_MagFieldCoeffs.DipoleEastLongitude= Deg2Rad(108.43);
    m_MagFieldCoeffs.CBAvgRotationRate 	= m_AvgRotationRate;
    m_MagFieldCoeffs.CBRadius		= m_Radius;
}
/*
void EarthCentralBody::CalcWc(const double &_altitude)
{
    m_wc = ::sqrt(GRAVITATIONAL_CONSTANT * m_Mass / pow(_altitude+m_Radius, 3)); 
    return;
}*/
} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: EarthCentralBody.cpp,v $
*	Revision 1.4  2003/08/24 20:59:13  nilspace
*	Updated.
*	
*	Revision 1.3  2003/06/12 18:01:09  nilspace
*	Added magnetic parameters.
*	
*	Revision 1.2  2003/06/09 15:20:39  nilspace
*	Changed CentralBody directory.
*	
*	Revision 1.1  2003/06/06 17:34:53  nilspace
*	Moved to CentralBody directory.
*	
*	Revision 1.2  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.1  2003/04/08 22:36:51  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

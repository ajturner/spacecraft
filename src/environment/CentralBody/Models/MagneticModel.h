//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file MagneticModel.h
*  \brief Class for describing the magnetic model of a central body.
*  \author $Author: rsharo $
*  \version $Revision: 1.4 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_MAGNETIC_MODEL_H__
#define __OSESSAME_MAGNETIC_MODEL_H__

#include "Matrix.h"
#include "utils/Time.h"

namespace O_SESSAME {

    /** @brief Structure to hold typical magnetic model coefficients. */
    typedef struct {
        ssfTime modelEpoch;		/**< time of model epoch, set in ssfTime::Epoch */
        double H0;			/**< coefficient of Field strength, [nT] */
        double DipoleCoelevation;	/**< coelevation of the dipole at epoch, [rad] */
        double DipoleEastLongitude;	/**< east longitude of the dipole at epoch, [rad] */
        double CBAvgRotationRate;	/**< average rotation rate of central body, [rad/s] */
        double CBRadius;		/**< radius of the central body, [km] */
    } MagneticFieldCoefficients;
    
/** @brief The MagneticModel class encapsulates a magnetic model of a central body.
*   @ingroup EnvironmentModels
*/
class MagneticModel 
{
public:
    virtual ~MagneticModel() {}
    
    virtual Vector GetMagneticField(const ssfTime& _currentTime, const Vector& _PositionVector) = 0; 
    virtual void SetMagFieldCoefficients(const MagneticFieldCoefficients& _newMagFieldCoeffs) {m_MagFieldCoeffs = _newMagFieldCoeffs;}

protected:
    MagneticModel() 				{}

    MagneticFieldCoefficients m_MagFieldCoeffs;
    
private:

};
}
#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: MagneticModel.h,v $
*	Revision 1.4  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.3  2003/06/12 18:00:31  nilspace
*	Fixed references to CentralBody.
*	
*	Revision 1.2  2003/06/10 14:45:43  nilspace
*	Changed include from Vector.h to Matrix.h
*	
*	Revision 1.1  2003/06/10 14:26:50  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

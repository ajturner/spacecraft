//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file CentralBody.h
*  \brief Interface to the CentralBody encapsulation object.
*  \author $Author: rsharo $
*  \version $Revision: 1.4 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* \todo Add reference counter to ensure deletion when not used anymore.
* \todo finish implementation of the abstract and concrete central bodies.
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __O_SESSAME_CENTRALBODY_H__
#define __O_SESSAME_CENTRALBODY_H__

#include "Rotation.h"
#include "Matrix.h"
#include "OrbitState.h"
#include "utils/Time.h"
#include "Models/MagneticModel.h"

namespace O_SESSAME {

/*! \brief Abstract representation of a central body 
* \ingroup EnvironmentToolkit
*
* \detail The CentralBody class provides a common interface to the group of central body 
*	objects (Planet, moon, asteroid, etc.) The central body group stores the pertinent 
*	parameters that affect the operating environment of a spacecraft. This includes 
*	the radius, mass, gravity field, atmosphere characteristics (if they is an atm), and
*	relationship to other central bodies (such as from the sun, or a moon to planet). 
*
*/
class CentralBody
{
public:    
    /*! \brief Default Deconstructor */
    virtual ~CentralBody() {};
    
            
    // MAGNETIC MODEL
    void SetMagneticModel(MagneticModel* _pNewMagModel);

    
    // PHYSICAL PARAMETERS
    virtual inline double GetAvgRotationRate();
    virtual inline double GetRadius();
    virtual inline double GetGravitationalParameter() { return m_GravitationalParameter; }
            
    /*! \brief calculate the vector from the central body to another central body */
    Vector GetVector2Body(CentralBody*) const;
    
    /*! \brief calculate the vector from the central body to a satellite */
    Vector GetVector2Body(const OrbitState& _satOrbitState) const;
    

    /*! \brief Returns a pointer to the instance of the central body. */
    CentralBody* operator= (CentralBody*);

    /*! \brief decrease the number of references to the central body pointer */
    void ReleaseReference();
    
protected:
    /*! \brief Construct a central body object */
    CentralBody();
    
    /*! \brief increase the number of references to the central body pointer */
    void GetReference();


    double m_Radius;		/**< radius of the central body, [km] */
    double m_Mass;		/**< mass of the central body, [kg] */
    double m_GravitationalParameter; /**< gravitational parameter, \f$\mu\f$ [km^3/(solar s)^2] */
    
    double m_AtmHeight;
    double m_AvgRotationRate; 	/**< average rotation rate of the central body, [rad/s] */
    Vector m_GravitationalFieldConstants; 
   
    int m_ReferenceCount;
    MagneticModel* m_pMagneticFieldModel;
    MagneticFieldCoefficients m_MagFieldCoeffs;
};
} // close namespace O_SESSAME

/** @defgroup EnvironmentModels Environment Models
* @ingroup EnvironmentToolkit
* Collection of models of the environment of a central body.
*
* Examples include magnetic field, atmosphere, radiation, etc.
*/

#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: CentralBody.h,v $
*	Revision 1.4  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.3  2003/06/12 17:57:41  nilspace
*	Added magnetic models.
*	
*	Revision 1.2  2003/06/09 15:20:39  nilspace
*	Changed CentralBody directory.
*	
*	Revision 1.1  2003/06/06 17:34:53  nilspace
*	Moved to CentralBody directory.
*	
*	Revision 1.7  2003/05/20 17:51:12  nilspace
*	Updated comments.
*	
*	Revision 1.6  2003/05/13 18:59:16  nilspace
*	Fixed some comments.
*	
*	Revision 1.5  2003/05/05 20:45:46  nilspace
*	Changed the pass-by-address parameters to pass-by-reference.
*	
*	Revision 1.4  2003/05/02 16:16:28  nilspace
*	Documented the API.
*	
*	Revision 1.3  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.2  2003/04/23 16:29:47  nilspace
*	Updated makefile directories.
*	
*	Revision 1.1  2003/04/08 22:35:11  nilspace
*	Initial Submission.
*
******************************************************************************/

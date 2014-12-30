//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Keplerian.h
*  \brief Implementation of the Keplerian Orbit State Representation Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.12 $
*  \date    $Date: 2003/08/24 20:59:13 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
* \todo include conversion functions
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_KEPLERIAN_H__
#define __SSF_KEPLERIAN_H__
#include "Matrix.h"
#include "OrbitStateRepresentation.h"
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;

#define MU 1	// not a good value for MU.
#ifndef PI
#include <math.h>
#define PI M_PI
#endif
namespace O_SESSAME {

/*! \ingroup OrbitStateRepresentation @{ */
#define NUM_KEPLERIAN_ELEMENTS 6 /*!< number of elements in a Keplerian state representation */
const int SEMIMAJOR_AXIS = VectorIndexBase + 0; /*!< position of the Semimajor axis, \f$a\f$, in the element vector */
const int ECCENTRICITY 	= VectorIndexBase + 1; /*!< position of the eccentricity, \f$e\f$, in the element vector */
const int INCLINATION 	= VectorIndexBase + 2; /*!< position of the inclination, \f$i\f$, in the element vector */
const int LONG_ASC_NODE = VectorIndexBase + 3; /*!< position of the longitude of the ascending node, \f$\Omega\f$, in the element vector */
const int ARG_PERIGEE 	= VectorIndexBase + 4; /*!< position of the argument of perigee, \f$\omega\f$, in the element vector */
const int TRUE_ANOMALY 	= VectorIndexBase + 5; /*!< position of the true anomaly, \f$\nu\f$, in the element vector */
/** @} */

typedef struct tleStruct {
	string	satName;				/*!< Satellite Name, from Line Zero */
	int		satNumber;				/*!< Satellite Number, from Line One */
	char	satClassification;		/*!< Almost always "U"nclassified (L1) */
	int		launchYear;				/*!< Launched in... (L1) */
	int		launchNumber;			/*!< Which launch of that year... (L1) */
	string	launchPiece;			/*!< Which piece of that launch... (L1) */
	int		epochYear;				/*!< Epoch year for this TLE (L1) */
	double	epochDay;				/*!< Epoch day and time for this TLE (L1) */
	double	meanmotion1stDeriv;		/*!< \f$\dot{meanMotion}\f$ (L1) */
	double	meanmotion2ndDeriv;		/*!< \f$\ddot{meanMotion}\f$ (L1) */
	double	bstarDrag;				/*!< B* drag term (L1) */
	int		ephemerisType;			/*!< The type of ephemeris data (L1) */
	int		elementNumber;			/*!< The TLE # (L1) */
	int		checksumLine1;			/*!< Checksum for L1 */
	double	meanAnomaly;			/*!< The TLE reports Mean Anomaly (L2) */
	double	eccentricAnomaly;		/*!< We calculate Eccentric Anomaly */
	double	meanMotion;				/*!< We calculate Mean Motion */
	int		revolutionNumber;		/*!< How many orbits at epoch? (L2) */
	int		checksumLine2;			/*!< Checksum for L2 */
};

		
		
/*! \brief Keplerian orbital element representation of the orbital position.
 * \ingroup OrbitStateRepresentation 
 *
 * The Keplerian class stores the orbital elements of an orbital position.
 *
 *	\par Example:
 *	
 */ 
class Keplerian : public OrbitStateRepresentation
{
public:
    
    virtual ~Keplerian();

	virtual Keplerian* NewPointer();

    virtual Keplerian* Clone();

	Keplerian();
    
    Keplerian(const Vector& _Elements);

    void SetPositionVelocity(const Vector& _Position, const Vector& _Velocity);

    void SetPositionVelocity(const Vector& _PositionVelocity);

	void SetPositionVelocity(const Vector& _Position, const Vector& _Velocity, const OrbitFrame& _OrbFrame);
    
    void SetPositionVelocity(const Vector& _PositionVelocity, const OrbitFrame& _OrbFrame);

    Vector GetPositionVelocity() const;

    Vector GetPositionVelocity(const OrbitFrame& _TargetOrbFrame) const;

    void GetPositionVelocity(Vector& _Position, Vector& _Velocity) const;
  
    void GetPositionVelocity(Vector& _Position, Vector& _Velocity, const OrbitFrame& _TargetOrbFrame) const;

	double GetEccentricAnomalyFromMeanAnomaly(const double& _MeanAnomaly);
	
	void GetTrueAnomalyFromEccentricAnomaly(const double& _EccentricAnomaly);
	
	tleStruct ReadTwoLineElementSet(const string& _TwoLineElementSet);



/* ********* KEPLERIAN SPECIFIC FUNCTIONS ********* */    

/*! @defgroup ElementAccessFunctions Element Access functions 
 * \ingroup OrbitStateRepresentation
 * \brief Functions to access the specific elements of the Keplerian Orbital Elements.
 * @{ 
 */
/*! \brief Compute and return the Semiparameter \f$p\f$ of the orbit position.
 * @return the semiparameter: \f$p = a * (1-e^{2})\f$. (km)
 */
    inline double GetSemiParameter() const {return GetSemimajorAxis() * (1 - pow(GetEccentricity(),2));};

/*! \brief Return the Semimajor Axis \f$a\f$ of the orbit position. (km) */
    inline double GetSemimajorAxis() const {return m_OrbitalElements(SEMIMAJOR_AXIS);};

/*! \brief Return the Eccentricity \f$e\f$ of the orbit position. (-) */
    inline double GetEccentricity() const {return m_OrbitalElements(ECCENTRICITY);};

/*! \brief Return the Inclination \f$i\f$ of the orbit position. (-) */
    inline double GetInclination() const {return m_OrbitalElements(INCLINATION);};

/*! \brief Return the Longitude of the Ascending Node \f$\Omega\f$ of the orbit position. (rad) */
    inline double GetLongAscNode() const {return m_OrbitalElements(LONG_ASC_NODE);};

/*! \brief Return the Argument of Perigee \f$\omega\f$ of the orbit position. (rad) */
    inline double GetArgPerigee() const  {return m_OrbitalElements(ARG_PERIGEE);};

/*! \brief Return the True Anomaly \f$\nu\f$ of the orbit position. (rad) */
    inline double GetTrueAnomaly() const {return m_OrbitalElements(TRUE_ANOMALY);};

/*! \brief Return the Mean orbital motion \f$n\f$ of the orbit position. (rad/s) */
    inline double GetMeanMotion() const  {return sqrt(MU/pow(GetSemimajorAxis(),3));};

/*! @} */
    
/* ********* ********* ******** ********* ********* */    
	
	
	
	
	
/* ********* DEPRECATED FUNCTIONS ********* */    

    virtual void SetState(const Vector& _Elements);

    virtual Vector GetState() const;
	
    virtual void GetState(Vector& _Elements) const;
	
/* ********* ********** ********* ********* */    	

	

private:
    /*! 6x1 vector of Keplerian orbital elements [a, e, i, \f$\Omega\f$, \f$\omega\f$, \f$\nu\f$] (km, -, rad, rad, rad, rad)*/
    Vector m_OrbitalElements;

	/*! All of the non-orbital element data that's inside of a TLE. */
	tleStruct m_tleData;
};
} // close namespace O_SESSAME

#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Keplerian.h,v $
*	Revision 1.12  2003/08/24 20:59:13  nilspace
*	Updated.
*	
*	Revision 1.11  2003/05/23 19:28:14  simpliciter
*	Moved comments to implementation file, basic housekeeping.
*	
*	Revision 1.10  2003/05/20 20:49:42  simpliciter
*	Added new functions for parsing TLEs:
*	  - GetEccentricAnomalyFromMeanAnomaly,
*	  - GetTrueAnomalyFromEccentricAnomaly,
*	  - ReadTwoLineElementSet.
*	
*	Revision 1.9  2003/05/13 18:47:56  nilspace
*	Fixed comments for better formatting.
*	
*	Revision 1.8  2003/05/05 20:46:38  nilspace
*	Added inertial Get/SetPositionVelocity to conform to new OrbitStateRepresentation abstract class.
*	
*	Revision 1.7  2003/05/02 16:16:46  nilspace
*	Documented the API.
*	
*	Revision 1.6  2003/04/29 18:48:30  nilspace
*	Added NewPointer and Clone functions to help in getting the correct memory allocation.
*	
*	Revision 1.5  2003/04/24 21:14:23  nilspace
*	const'd all Get() functions.
*	
*	Revision 1.4  2003/04/24 20:10:47  nilspace
*	const'd all Get() functions.
*	
*	Revision 1.3  2003/04/23 18:52:29  nilspace
*	Updated to call correct OrbitFrame::GetRotation calls.
*	Added temporary PI and MU values.
*	Added K_Vector Values.
*	
*	Revision 1.2  2003/04/22 18:06:08  nilspace
*	Added math for Matthew Berry.
*	
*	Revision 1.1  2003/04/08 22:47:35  nilspace
*	Initial Submission.
*
******************************************************************************/

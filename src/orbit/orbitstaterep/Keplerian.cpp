//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Keplerian.cpp
 *  \brief Implementation of the Keplerian orbit state representation.
 *  \author $Author: simpliciter $
 *  \version $Revision: 1.10 $
 *  \date    $Date: 2003/05/23 19:28:32 $
 *//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
 *
 */
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Keplerian.h"
namespace O_SESSAME {

/*! \brief Default Deconstructor */
Keplerian::~Keplerian()
{
}


/*! \brief Return a pointer to a new instance of a Keplerian orbit state representation type.
 *
 *  This is used to request memory for a new instance of a Keplerian. It is necessary 
 *	when attempting to get a pointer from the abstract data type OrbitStateRepresentation 
 *	and the actual representation type isn't known.
 * @return a pointer to a new allocation of memory for the Keplerian object.
 */
Keplerian* Keplerian::NewPointer()
{
    return new Keplerian();
}


/*! \brief Return a pointer to a copy of the Keplerian orbit state representation instance.
 *
 *  This is used to request memory for a copy of this instance of Keplerian. It is necessary 
 *	when attempting to get a pointer from the abstract data type OrbitStateRepresentation 
 *	and the actual representation type isn't known.
 * @return a pointer to a copy of the Keplerian object.
 */
Keplerian* Keplerian::Clone()
{
    return new Keplerian(*this);
}


/*! \brief Create an initially empty Keplerian orbit state representation. */
Keplerian::Keplerian() : m_OrbitalElements(NUM_KEPLERIAN_ELEMENTS)
{
}


/*! Create a Keplerian orbit state representation from a vector of orbital elements.
 * @param _Elements 6-element vector of Keplerian orbital elements [a, e, i, \f$\Omega\f$, \f$\omega\f$, \f$\nu\f$]. (km, -, rad, rad, rad, rad)
 */
Keplerian::Keplerian(const Vector& _Elements)
{
    SetState(_Elements);
}


/*! \brief Set the Keplerian representation by converting the position and velocity vectors in inertial coordinates.
 * 
 * Required to match the OrbitStateRepresentation abstract class interface.
 * \todo implement Keplerian conversion functions
 * @param _Position 3-element vector of position components in inertial coordinates. (km)
 * @param _Velocity 3-element vector of vector components in inertial coordinates. (km/s)
 */
void Keplerian::SetPositionVelocity(const Vector& _Position, const Vector& _Velocity)
{
    Vector K_Vector(3); K_Vector(VectorIndexBase+2) = 1;
    Vector AngMomentum = crossP(_Position, _Velocity);
    Vector LineNodes = crossP(K_Vector, AngMomentum);
    double r = norm2(_Position);
    double v = norm2(_Velocity);
    double n = norm2(LineNodes);
    Vector Eccentricity = 1/MU * (pow(v,2) - MU/r) * _Position - _Position.dot(_Velocity)*_Velocity;
    m_OrbitalElements(ECCENTRICITY) = norm2(Eccentricity);
    double xi = pow(v,2) / 2 - MU/r;
    
    // Semimajor Axis, a
    m_OrbitalElements(SEMIMAJOR_AXIS) = -MU / (2 * xi);
    
    // Inclination, i
    m_OrbitalElements(INCLINATION) = acos(AngMomentum(VectorIndexBase + 2) / norm2(AngMomentum));
    
    // Longitude of the Ascending Node, Omega
    m_OrbitalElements(LONG_ASC_NODE) = LineNodes(VectorIndexBase) / norm2(LineNodes);
        if (LineNodes(VectorIndexBase+1) < 0)
            m_OrbitalElements(LONG_ASC_NODE) = 2*PI - m_OrbitalElements(LONG_ASC_NODE);
    
    // Argument of perigee, omega
    m_OrbitalElements(ARG_PERIGEE) = LineNodes.dot(Eccentricity) / (n * m_OrbitalElements(ECCENTRICITY));
        if (Eccentricity(VectorIndexBase+2) < 0)
             m_OrbitalElements(ARG_PERIGEE) = 2*PI - m_OrbitalElements(ARG_PERIGEE);
    
    // True Anomaly, nu
    m_OrbitalElements(TRUE_ANOMALY) = Eccentricity.dot(_Position) / (r * m_OrbitalElements(ECCENTRICITY));
        if (_Position.dot(_Velocity) < 0)
             m_OrbitalElements(TRUE_ANOMALY) = 2*PI - m_OrbitalElements(TRUE_ANOMALY);
    
    // Special Cases
    if(m_OrbitalElements(ECCENTRICITY) == 0)
    { // Circular
        m_OrbitalElements(ARG_PERIGEE) = 0;
        if(m_OrbitalElements(INCLINATION) == 0)
        { // Circular Equatorial -  define True Longitude, lambda_true
            m_OrbitalElements(LONG_ASC_NODE) = 0;
            m_OrbitalElements(TRUE_ANOMALY) = _Position(VectorIndexBase) / r;
                if(_Position(VectorIndexBase+1) < 0)
                    m_OrbitalElements(TRUE_ANOMALY) = 2*PI - m_OrbitalElements(TRUE_ANOMALY); 
        }
        else
        { // Circular Inclined - define Argument of Latitude, u
            m_OrbitalElements(TRUE_ANOMALY) = LineNodes.dot(_Position)/(n * r);
                if(_Position(VectorIndexBase+2) < 0)
                    m_OrbitalElements(TRUE_ANOMALY) = 2*PI - m_OrbitalElements(TRUE_ANOMALY); 
        }
    }
    else if(m_OrbitalElements(INCLINATION) == 0)
    { // Elliptical Equitorial - define True Longitude of Periapsis, ~omega~
        m_OrbitalElements(LONG_ASC_NODE) = 0;
        m_OrbitalElements(ARG_PERIGEE) = Eccentricity(VectorIndexBase) / m_OrbitalElements(ECCENTRICITY);
            if (Eccentricity(VectorIndexBase+2) < 0)
                m_OrbitalElements(ARG_PERIGEE) = 2*PI - m_OrbitalElements(ARG_PERIGEE); 
    }
    return;
}


/*! \brief Set the Keplerian representation by converting the position and velocity vector given in inertial coordinates.
 * 
 * required to match the OrbitStateRepresentation abstract class interface.
 * \todo implement Keplerian conversion functions
 * @param _Position 6-element vector of position and velocity components in inertial coordinates. (km, km/s)
 */
void Keplerian::SetPositionVelocity(const Vector& _PositionVelocity)
{
    Vector Pos(3); Pos(_) = _PositionVelocity(_(VectorIndexBase, VectorIndexBase+2));
    Vector Vel(3); Vel(_) = _PositionVelocity(_(VectorIndexBase+3, VectorIndexBase+5));
    
    SetPositionVelocity(Pos, Vel);
}


/*! \brief Set the Keplerian representation by converting the position and velocity vectors.
 * \todo implement Keplerian conversion functions
 * @param _Position 3-element vector of position components. (km)
 * @param _Velocity 3-element vector of vector components. (km/s)
 * @param _TargetOrbFrame Reference frame that the vector components are in.
 */
void Keplerian::SetPositionVelocity(const Vector& _Position, const Vector& _Velocity, const OrbitFrame& _OrbFrame)
{
    // Convert the position and velocity vectors to inertial frame components
    Vector Position = _OrbFrame.GetRotation2IJK() * _Position;
    Vector Velocity = _OrbFrame.GetRotation2IJK() * _Velocity;
    
    // Call the inertial version of the SetPositionVelocity()
    SetPositionVelocity(Position, Velocity);
}

    
 /*! \brief Set the Keplerian representation by converting the position and velocity vector.
  * \todo implement Keplerian conversion functions
  * @param _Position 6-element vector of position and velocity components. (km, km/s)
  * @param _TargetOrbFrame Reference frame that the vector components are in.
  */
void Keplerian::SetPositionVelocity(const Vector& _PositionVelocity, const OrbitFrame& _OrbFrame)
{
	Vector Pos(3); Pos(_) = _PositionVelocity(_(VectorIndexBase, VectorIndexBase+2));
    Vector Vel(3); Vel(_) = _PositionVelocity(_(VectorIndexBase+3, VectorIndexBase+5));
    
    SetPositionVelocity(Pos, Vel, _OrbFrame);
}	


/*! \brief Convert the Keplerian orbit representation to position and velocity vectors in the inertial frame.
  * 
  * Required to match the OrbitStateRepresentation abstract class interface.
  * @return 6-element vector of position and velocity vector components in the inertial reference frame. [km, km, km, km/s, km/s, km/s]^T
  */   
Vector Keplerian::GetPositionVelocity() const
{
    Vector rv(6);
    rv(VectorIndexBase + 0) = (GetSemiParameter() * cos(GetTrueAnomaly())) / (1 + GetEccentricity() * cos(GetTrueAnomaly()));
    rv(VectorIndexBase + 1) = (GetSemiParameter() * sin(GetTrueAnomaly())) / (1 + GetEccentricity() * cos(GetTrueAnomaly()));
  //rv(VectorIndexBase + 2) = 0;
    rv(VectorIndexBase + 3) = -sqrt(MU/GetSemiParameter()) * sin(GetTrueAnomaly());
    rv(VectorIndexBase + 4) = sqrt(MU/GetSemiParameter()) * (GetEccentricity() + cos(GetTrueAnomaly()));
  //rv(VectorIndexBase + 5) = 0;
    return rv;
}


/*! \brief Convert the Keplerian orbit representation to position and velocity vectors in the specified frame.
 * @param _TargetOrbFrame the desired reference frame to return the vector components in.
 * @return 6-element vector of position and velocity vector components in the specified reference frame. [km, km, km, km/s, km/s, km/s]^T
 */ 
Vector Keplerian::GetPositionVelocity(const OrbitFrame& _TargetOrbFrame) const
{
    // Call the inertial version of GetPositionVelocity()
    Vector rv = GetPositionVelocity();

    // Convert from the inertial frame to the specified target frame
    rv(_(VectorIndexBase, VectorIndexBase+2)) = _TargetOrbFrame.GetRotationFromIJK() * rv(_(VectorIndexBase, VectorIndexBase+2));
    rv(_(VectorIndexBase+3, VectorIndexBase+5)) = _TargetOrbFrame.GetRotationFromIJK() * rv(_(VectorIndexBase+3, VectorIndexBase+5));
    return rv;
}


/*! \brief Return by reference the converted the Keplerian orbit representation to position and velocity vectors in the inertial frame.
 * 
 * required to match the OrbitStateRepresentation abstract class interface.
 * @param _Position a Vector through which to return the 3-element position vector in inertial corrdinates. (km)
 * @param _Velocity a Vector through which to return the 3-element velocity vector in inertial corrdinates. (km/s)
 * @param _TargetOrbFrame the desired reference frame to return the vector components in.
 */
void Keplerian::GetPositionVelocity(Vector& _Position, Vector& _Velocity) const
{ 
    _Position(VectorIndexBase + 0) = (GetSemiParameter() * cos(GetTrueAnomaly())) / (1 + GetEccentricity() * cos(GetTrueAnomaly()));
    _Position(VectorIndexBase + 1) = (GetSemiParameter() * sin(GetTrueAnomaly())) / (1 + GetEccentricity() * cos(GetTrueAnomaly()));
    _Position(VectorIndexBase + 2) = 0;
    _Velocity(VectorIndexBase + 0) = -sqrt(MU/GetSemiParameter()) * sin(GetTrueAnomaly());
    _Velocity(VectorIndexBase + 1) = sqrt(MU/GetSemiParameter()) * (GetEccentricity() + cos(GetTrueAnomaly()));
    _Velocity(VectorIndexBase + 2) = 0;
    return;
}


/*! \brief Return by reference the converted Keplerian orbit representation to position and velocity vectors in the specified frame.
 * @param _Position a Vector through which to return the 3-element position vector. (km)
 * @param _Velocity a Vector through which to return the 3-element velocity vector. (km/s)
 * @param _TargetOrbFrame the desired reference frame to return the vector components in.
 */
void Keplerian::GetPositionVelocity(Vector& _Position, Vector& _Velocity, const OrbitFrame& _TargetOrbFrame) const
{ 
    // Call the inertial version of GetPositionVelocity()
    GetPositionVelocity(_Position, _Velocity);
    
    // Convert from the inertial frame to the specified target frame
    _Position = _TargetOrbFrame.GetRotationFromIJK() * _Position;
    _Velocity = _TargetOrbFrame.GetRotationFromIJK() * _Velocity;
    return;
}


/*! \brief Solves Kepler's Equation in order to compute eccentric anomaly (E) from mean anomaly (M) and eccentricity (e). 
 * Adapted from Appendix A, Orbits,
 * by Christopher D. Hall.  Class notes for AOE 4140.
 * Available at http://www.aoe.vt.edu/~chall/courses/aoe4140/ 
 * \todo Allow user to specify tolerance for numerical convergence. */
double Keplerian::GetEccentricAnomalyFromMeanAnomaly(const double& _MeanAnomaly)
{
	
	double		tolerance = 1e-11;		// sets convergence level
	/*! \todo Allow user to specify tolerance for numerical convergence. */
	double		_EccentricAnomaly;		// returned value
	double		testEccAnomaly;			// candidate EA, for convergence test
	double		eccentricity = m_OrbitalElements(ECCENTRICITY);
										// from Keplerian private data member

	testEccAnomaly  = _MeanAnomaly;
	_EccentricAnomaly = testEccAnomaly - 
		( testEccAnomaly - eccentricity*sin(testEccAnomaly) - _MeanAnomaly ) /
		( 1 - eccentricity*cos(testEccAnomaly) );
	
	while ( fabs(_EccentricAnomaly-testEccAnomaly) > tolerance ) // iterate until _EA = testEA
	{
		testEccAnomaly = _EccentricAnomaly;
		_EccentricAnomaly = testEccAnomaly - 
			( testEccAnomaly - eccentricity*sin(testEccAnomaly) - _MeanAnomaly ) /
			( 1 - eccentricity*cos(testEccAnomaly) );
	}

	return _EccentricAnomaly;
}


/*! \brief Calculates true anomaly (\f$\nu\f$) from eccentric 
 * anomaly (E), semimajor axis (a), and eccentricity (e). 
 */
/*! Adapted from Appendix A, Orbits,
 * by Christopher D. Hall.  Class notes for AOE 4140.
 * Available at http://www.aoe.vt.edu/~chall/courses/aoe4140/ 
 */
void Keplerian::GetTrueAnomalyFromEccentricAnomaly(const double& _EccentricAnomaly)
{
	
	double		cosTrueAnomaly;
	double		sinTrueAnomaly;
	double		semimajoraxis = m_OrbitalElements(SEMIMAJOR_AXIS);
	double		eccentricity = m_OrbitalElements(ECCENTRICITY);
	
	cosTrueAnomaly = ( eccentricity - cos(_EccentricAnomaly) ) / 
		( eccentricity*cos(_EccentricAnomaly) - 1 );
	sinTrueAnomaly = ( ( semimajoraxis*sqrt(1 - eccentricity*eccentricity) ) / 
		( semimajoraxis*(1 - eccentricity*cos(_EccentricAnomaly)) ) ) * 
		sin(_EccentricAnomaly);
	
	m_OrbitalElements(TRUE_ANOMALY) = atan2( sinTrueAnomaly, cosTrueAnomaly );
	if ( m_OrbitalElements(TRUE_ANOMALY) < 0 );
	{
		m_OrbitalElements(TRUE_ANOMALY) = m_OrbitalElements(TRUE_ANOMALY) + 2*PI;
	}
	
	return;
}


/*! \brief Parses a two line element set and updates orbital
 *	elements, returns a struct of additional information. 
 */
/*! Adapted from Appendix A, Orbits,
 *	by Christopher D. Hall.  Class notes for AOE 4140.
 *	Available at http://www.aoe.vt.edu/~chall/courses/aoe4140/ 
 *
 *	Sample TLEs:
 *	COSMOS 2278 
 *	1 23087U 94023A 98011.59348139 .00000348 00000-0 21464-3 0 5260 
 *	2 23087 71.0176 58.4285 0007185 172.8790 187.2435 14.12274429191907
 *	
 *	NOAA 14 
 *	1 23455U 94089A 97320.90946019 .00000140 00000-0 10191-3 0 2621 
 *	2 23455 99.0090 272.6745 0008546 223.1686 136.8816 14.11711747148495
 *	
 *	
 *	TLE Definition
 *	AAAAAAAAAAAAAAAAAAAAAAAA
 *	1 NNNNNU NNNNNAAA NNNNN.NNNNNNNN +.NNNNNNNN +NNNNN-N +NNNNN-N N NNNNN
 *	2 NNNNN NNN.NNNN NNN.NNNN NNNNNNN NNN.NNNN NNN.NNNN NN.NNNNNNNNNNNNNN
 *	Line 0 is a twenty-four character name (to be consistent with the
 *	name length in the NORAD SATCAT).
 *	Lines 1 and 2 are the standard Two-Line Orbital Element Set Format
 *	identical to that used by NORAD and NASA. 
 */
tleStruct Keplerian::ReadTwoLineElementSet(const string& _TwoLineElementSet)
{
	
	int		finder = 0;		// the start of each substring
	int		endlfinder;		// the end of each substring
	int		finderLength;	// the length of each substring
	
	string	LineZero;		// of the tle...
	string	LineOne;
	string	LineTwo;
	
	stringstream	placeholder;	// an aptly named translator
	int				exponent;		// for \ddot{meanmotion} and bstar
	
// Parse the TLE into three lines by finding endline markers ('\n')...
	endlfinder = _TwoLineElementSet.find('\n',finder);  // found one!
	finderLength = endlfinder - finder;					// "how long is it?"
	LineZero = _TwoLineElementSet.substr(finder,finderLength);  // ok, get it.
	
	finder = endlfinder + 1;							// go to the next character
	endlfinder = _TwoLineElementSet.find('\n',finder);	// and repeat x2!
	finderLength = endlfinder - finder;
	LineOne = _TwoLineElementSet.substr(finder,finderLength);
	
	finder = endlfinder + 1;
	endlfinder = _TwoLineElementSet.size();
	finderLength = endlfinder - finder;
	LineTwo = _TwoLineElementSet.substr(finder,finderLength);
	
	/*! \todo Error checking for syntactically correct TLEs, including endlines, carriage returns. */
// Done parsing the TLE into lines.
	
	
// Unpack Line Zero.
	// Line 0 Column Description
	// 01-24 Satellite SATCAT Name
	m_tleData.satName = LineZero.substr(0,24);
// It's a short line!
		
// Unpack Line One.
	// Line 1 Column Description
	// 01 Line Number of Element Data, not saved.
	// 03-07 Satellite Number
	finder = 2;									// LineOne = [1 SatNum...
	endlfinder = LineOne.find(' ',finder);		// Look for the next space
	finderLength = endlfinder - finder;			// Just for readability
	placeholder << LineOne.substr(finder,finderLength-1);	// Pull string into streamstring
	placeholder >> m_tleData.satNumber;						// Push streamstring into _____ (in this case, an int)
	// 08 Classification (U=Unclassified)
	placeholder.clear();						// Still part of the first substring
	placeholder << LineOne.substr(endlfinder-1,1);
	placeholder >> m_tleData.satClassification;
												// ah, whitespace.
	// 10-11 International Designator (Last two digits of launch year)
	finder = endlfinder + 1;
	endlfinder = LineOne.find(' ',finder);
	placeholder.clear();
	placeholder << LineOne.substr(finder,2);		// gotta be 2 (ints) long
	placeholder >> m_tleData.launchYear;
	/*! \todo Include full year info logic as per the tle standard, 
	wherein 57-99 --> 19__ and 00-56 --> 20__. */
	// 12-14 International Designator (Launch number of the year)
	placeholder.clear();
	placeholder << LineOne.substr(finder+2,3);		// assuming 3 ints, as per the standard
	placeholder >> m_tleData.launchNumber;
	// 15-17 International Designator (Piece of the launch)
	placeholder.clear();
	finderLength = endlfinder - finder;
	placeholder << LineOne.substr(finder+5,finderLength-5);		// should be 3 chars, but who knows?
	placeholder >> m_tleData.launchPiece;
	
	// 19-20 Epoch Year (Last two digits of year)
	finder = endlfinder + 1;
	endlfinder = LineOne.find(' ',finder);
	placeholder.clear();
	placeholder << LineOne.substr(finder,2);		// gotta be 2 ints long
	placeholder >> m_tleData.epochYear;
	// 21-32 Epoch (Day of the year and fractional portion of the day)
	placeholder.clear();
	finderLength = endlfinder - finder;
	placeholder << LineOne.substr(finder+2,finderLength-2);		// double until next whitespace.
	placeholder >> m_tleData.epochDay;
	
	// 34-43 First Time Derivative of the Mean Motion
	finder = endlfinder + 1;
	endlfinder = LineOne.find(' ',finder);
	finderLength = endlfinder - finder;
	placeholder.clear();
	placeholder << LineOne.substr(finder,finderLength);
	placeholder >> m_tleData.meanmotion1stDeriv;
	
	// 45-52 Second Time Derivative of Mean Motion (leading decimal point assumed)
	finder = endlfinder + 1;
	endlfinder = LineOne.find_first_of("-+",finder+1);	// +- starts the exponent 
	finderLength = endlfinder - finder;
	placeholder.clear();
	placeholder << LineOne.substr(finder,finderLength);
	placeholder >> m_tleData.meanmotion2ndDeriv;			// so this is just the raw operand
	finder = endlfinder;
	endlfinder = LineOne.find(' ',finder);
	finderLength = endlfinder - finder;
	placeholder.clear();
	placeholder << LineOne.substr(finder,finderLength);
	placeholder >> exponent;							// here's the exponent
	m_tleData.meanmotion2ndDeriv *= pow(10.0,exponent);	// this is op^exp
	if ( LineOne[finder] == '+' || LineOne[finder] == '-' )		// now include the leading decimal point
		m_tleData.meanmotion2ndDeriv /= pow(10.0,finderLength-1);
	else
		m_tleData.meanmotion2ndDeriv /= pow(10.0,finderLength);
	
	// 54-61 BSTAR drag term (leading decimal point assumed)
	finder = endlfinder + 1;
	endlfinder = LineOne.find_first_of("-+",finder+1);
	finderLength = endlfinder - finder;
	placeholder.clear();
	placeholder << LineOne.substr(finder,finderLength);
	placeholder >> m_tleData.bstarDrag;
	finder = endlfinder;
	endlfinder = LineOne.find(' ',finder);
	placeholder.clear();
	placeholder << LineOne.substr(finder,finderLength);
	placeholder >> exponent;
	m_tleData.bstarDrag *= pow(10.0,exponent);
	if ( LineOne[finder] == '+' || LineOne[finder] == '-' )
		m_tleData.bstarDrag /= pow(10.0,finderLength-1);
	else
		m_tleData.bstarDrag /= pow(10.0,finderLength);
	
	// 63 Ephemeris type
	finder = endlfinder + 1;
	endlfinder = LineOne.find(' ',finder);
	finderLength = endlfinder - finder;			// = 1
	placeholder.clear();
	placeholder << LineOne.substr(finder,finderLength);
	placeholder >> m_tleData.ephemerisType;

	// 65-68 Element number
	finder = endlfinder + 1;
	endlfinder = LineOne.size()-1;			// end of the line, minus 1 for checksum and 1 for \n
	finderLength = endlfinder - finder;
	placeholder.clear();
	placeholder << LineOne.substr(finder,finderLength);
	placeholder >> m_tleData.elementNumber;
	
	// 69 Checksum (Modulo 10)
	placeholder.clear();
	placeholder << LineOne.substr(endlfinder,1);	// end of the line, less \n
	placeholder >> m_tleData.checksumLine1;
// Done with LineOne.

// Onto LineTwo!
	// Line 2 Column Description
	// 01 Line Number of Element Data, not saved
	// 03-07 Satellite Number, not saved here (saved in Line 1)
	// 09-16 Inclination [Degrees], in m_OrbitalElements [radians]
	endlfinder = LineTwo.find(' ',2);	// start looking for ' ' inside the satellite number
	finder = endlfinder + 1;
	endlfinder = LineTwo.find(' ',finder);
	finderLength = endlfinder - finder;
	placeholder.clear();
	placeholder << LineTwo.substr(finder,finderLength);
	placeholder >> m_OrbitalElements(INCLINATION);	// Keplerian private data member
	m_OrbitalElements(INCLINATION) *= PI/180.0;		// consistent units are good squishy.
	
	// 18-25 Right Ascension of the Ascending Node [Degrees], in m_OrbitalElements [radians]
	finder = endlfinder + 1;
	endlfinder = LineTwo.find(' ',finder);
	finderLength = endlfinder - finder;
	placeholder.clear();
	placeholder << LineTwo.substr(finder,finderLength);
	placeholder >> m_OrbitalElements(LONG_ASC_NODE);
	m_OrbitalElements(LONG_ASC_NODE) *= PI/180.0;
	/*! \todo verify that RAAN = longitude of the ascending node. */
	
	// 27-33 Eccentricity (leading decimal point assumed), in m_OrbitalElements
	finder = endlfinder + 1;
	endlfinder = LineTwo.find(' ',finder);
	finderLength = endlfinder - finder;
	placeholder.clear();
	placeholder << "0." << LineTwo.substr(finder,finderLength);
	placeholder >> m_OrbitalElements(ECCENTRICITY);
	m_OrbitalElements(ECCENTRICITY) *= PI/180.0;
	
	// 35-42 Argument of Perigee [Degrees], in m_OrbitalElements [radians]
	finder = endlfinder + 1;
	endlfinder = LineTwo.find(' ',finder);
	finderLength = endlfinder - finder;
	placeholder.clear();
	placeholder << LineTwo.substr(finder,finderLength);
	placeholder >> m_OrbitalElements(ARG_PERIGEE);
	m_OrbitalElements(ARG_PERIGEE) *= PI/180.0;

	// 44-51 Mean Anomaly [Degrees], in m_OrbitalElements [radians]
	finder = endlfinder + 1;
	endlfinder = LineTwo.find(' ',finder);
	finderLength = endlfinder - finder;
	placeholder.clear();
	placeholder << LineTwo.substr(finder,finderLength);
	placeholder >> m_tleData.meanAnomaly;
	m_tleData.meanAnomaly *= PI/180.0;
	m_tleData.eccentricAnomaly = GetEccentricAnomalyFromMeanAnomaly(m_tleData.meanAnomaly);
	
	// 53-63 Mean Motion [Revs per day]
	finder = endlfinder + 1;
	endlfinder = LineTwo.size()-1;			// last substring
	placeholder.clear();
	placeholder << LineTwo.substr(finder,11);
	placeholder >> m_tleData.meanMotion;
	// Buy one mean motion, get a semi-major axis at no extra charge!
	m_OrbitalElements(SEMIMAJOR_AXIS) = pow( (MU/pow(m_tleData.meanMotion,2)), (1.0/3.0) );
	// And now we can get true anomaly.
	GetTrueAnomalyFromEccentricAnomaly(m_tleData.eccentricAnomaly);
	
	// 64-68 Revolution number at epoch [Revs]
	placeholder.clear();
	placeholder << LineTwo.substr(finder+11,5);
	placeholder >> m_tleData.revolutionNumber;
	
	// 69 Checksum (Modulo 10)
	placeholder.clear();
	placeholder << LineTwo.substr(endlfinder,1);
	placeholder >> m_tleData.checksumLine2;
	
	return m_tleData;
}


// end jls 030512












/* ********* DEPRECATED FUNCTIONS ********* */



/*! \brief Set the vector of the representation's state vector.
 * \warning Deprecated - Do Not Use - will be moved internally
 */
void Keplerian::SetState(const Vector& _Elements)
{
    m_OrbitalElements = _Elements;
    return;
}


/*! \brief Return a vector of the representation's state vector.
 * \warning Deprecated - Do Not Use - will be moved internally
 */
Vector Keplerian::GetState() const
{
    return m_OrbitalElements;
}


/*! \brief Return a vector by reference of the representation's state vector.
 * \warning Deprecated - Do Not Use - will be moved internally
 */
void Keplerian::GetState(Vector& _Elements) const
{
    _Elements = m_OrbitalElements;
    return;
}




} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Keplerian.cpp,v $
*	Revision 1.10  2003/05/23 19:28:32  simpliciter
*	Moved comments from header file, basic housekeeping.
*	
*	Revision 1.9  2003/05/20 20:49:05  simpliciter
*	Added new functions for parsing TLEs:
*	 - GetEccentricAnomalyFromMeanAnomaly,
*	 - GetTrueAnomalyFromEccentricAnomaly,
*	 - ReadTwoLineElementSet.
*	
*	Revision 1.8  2003/05/15 21:00:44  nilspace
*	Added SetPositionVelocity(Vector) function implementation.
*	
*	Revision 1.7  2003/05/05 20:46:37  nilspace
*	Added inertial Get/SetPositionVelocity to conform to new OrbitStateRepresentation abstract class.
*	
*	Revision 1.6  2003/04/29 18:48:30  nilspace
*	Added NewPointer and Clone functions to help in getting the correct memory allocation.
*	
*	Revision 1.5  2003/04/24 21:14:23  nilspace
*	const'd all Get() functions.
*	
*	Revision 1.4  2003/04/24 20:10:46  nilspace
*	const'd all Get() functions.
*	
*	Revision 1.3  2003/04/23 18:52:28  nilspace
*	Updated to call correct OrbitFrame::GetRotation calls.
*	Added temporary PI and MU values.
*	Added K_Vector Values.
*	
*	Revision 1.2  2003/04/22 18:06:07  nilspace
*	Added math for Matthew Berry.
*	
*	Revision 1.1  2003/04/08 22:47:35  nilspace
*	Initial Submission.
*	
******************************************************************************/

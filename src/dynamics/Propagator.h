//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Propagator.h
*  \brief Interface to the Propagator abstract class.
*  \author $Author: rsharo $
*  \version $Revision: 1.11 $
*  \date    $Date: 2003/10/18 21:37:27 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* \todo Finish documentation
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_PROPAGATOR_H__
#define __OSESSAME_PROPAGATOR_H__

#include "Rotation.h"
#include "utils/Integrator.h"
#include "Orbit.h"
#include "Attitude.h"
#include "AttitudeHistory.h"
#include "OrbitHistory.h"


namespace O_SESSAME {
//////////////////////////////////////////////////////////////////////////////////////////////////
/*! @defgroup PropagatorToolkit Propagator Toolkit 
* The propagator toolkit contains all the functionality required to propagate the full dynamics 
* of a spacecraft. This can include only attitude or orbit dynamics, combined, or even propagation 
* using an external source of states, such as another simulation program or hardware.
*
* \par 
* The Propagator class offers an abstract interface to the specific propagation strategies 
* that implement each of the examples given above, as well as any further user defined algorithms. 
A propagator requires the following parts:
    - Orbit object (if propagating with an orbit), including:
        - Dynamic equations, the right-hand side, or time derivate equations (odeFunctor)
        - A state conversion function that converts the integrated state variables to an 
            object stored in OrbitHistory.
        - An Interpolator in the OrbitHistory.
    - Attitude object (if propagating with an attitude), including:
        - Dynamic equations, the right-hand side, or time derivate equations (odeFunctor)
        - A state conversion function that converts the integrated state variables to an 
            object stored in AttitudeHistory
        - An Interpolator in the AttitudeHistory
    - An attitude state propagator
        - Use either an Integrator
        - Tie in the external source to the AttitudeHistory object (Exporter, Communications)
    - An orbit state propagator
        - Use either an Integrator
        - Tie in the external source to the OrbitHistory object (Exporter, Communications)
    - An Environment object
        - Environmental force and torque disturbance functions (EnvFunction)
        - A CentralBody (EarthCentralBody, MoonCentralBody, etc.)
        
An example of a propagator use is included in testPropagation.cpp.
        
*
* \par Extension Points:
* 	The propagation toolkit currently has functionality for independent attitude \& orbit 
* propagation, as well as combined propagation using weak coupling, and full coupling. Any new 
* propagation schemes should be derived from the appropriate AnalyticPropagator or NumericPropagator 
* interface classes as necessary.
*/

class Attitude;
class Orbit;


/*! \brief Encapsulation of the propagation of the spacecraft dynamics (attitude, orbital, etc.)
* \ingroup PropagatorToolkit
*
*  The propagator is used to tie together the various spacecraft dynamics that are desired to be 
* propagated. The user has the ability to set the time derivative equations, integrators, parameters,
* etc. as necessary. Furthermore, the Propagator class can be derived for more functionality.
*/
class Propagator
{
public:
    /*! \brief Default Deconstructor */
    virtual ~Propagator();
    
    /*! \brief Propagates the dynamics forward through time
        * @param _propTime STL vector of values specifying beginning, ending times of propagation as well as time step [initialTime, timeStep, finalTime] (s)
        */
    virtual void Propagate(const vector<ssfTime> &_propTime);
    
    /*! \brief Sets the Attitude Representation object to be propagated
        * @param _AttitudeObject pointer to the attitude representation
        */
    virtual void SetAttitudeObject(Attitude *_pAttitudeObject);
    
    /*! \brief Sets the Orbit Representation object to be propagated
        * @param _OrbitObject pointer to the Orbit representation
        */
    virtual void SetOrbitObject(Orbit *_pOrbitObject);

protected:
    /*! \brief Propagate the orbit through a specified time 
        * @param _propTime vector of values specifying beginning, ending times of propagation as well as time step [initialTime, timeStep, finalTime] (s)
        * @param _initConditions Vector of initial conditions of the orbit propagation. 
        * @return Matrix of integrated times and states as returned by the orbit dynamics equation
        */
    virtual Matrix PropagateOrbit(const vector<ssfTime> &_propTime, const Vector &_initConditions);

    /*! \brief Propagate the attitude through a specified time
        * @param _propTime Vector of values specifying beginning, ending times of propagation as well as time step [initialTime, timeStep, finalTime] (s)
        * @param _initConditions Vector of initial conditions of the attitude propagation. 
        * @return Matrix of integrated times and states as returned by the attitude dynamics equation
        */
    virtual Matrix PropagateAttitude(const vector<ssfTime> &_propTime, const Vector &_initConditions);

protected:
    /*! \brief Default Constructor */
    Propagator();

    /*! Pointer to the Orbit Representation being propagated */
    Orbit *m_pOrbitObject;
    /*! Pointer to the Attitude Representation being propagated */
    Attitude *m_pAttitudeObject;
    
    /*! Collection of calculated orbit state mesh points */
    OrbitHistory m_OrbitStateMeshPoints;
    /*! Collection of calculated attitude state mesh points */
    AttitudeHistory m_AttitudeStateMeshPoints;
        
};
// end of Propagator
}
#endif
/*****************************************************************************
*	$Log: Propagator.h,v $
*	Revision 1.11  2003/10/18 21:37:27  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.10  2003/06/10 02:24:04  nilspace
*	Updated moving of StateConversion functions to Attitude and Orbit.
*	
*	Revision 1.9  2003/05/22 15:09:46  nilspace
*	Updated documentation.
*	
*	Revision 1.8  2003/05/20 17:55:35  nilspace
*	Updated comments, also now use derived CombinedNumericProp.
*	
*	Revision 1.7  2003/05/13 18:52:45  nilspace
*	Fixed comments. Passed in initial conditions to propagate functions.
*	
*	Revision 1.6  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.5  2003/04/25 18:23:43  nilspace
*	Added implementation of ~Propagator()
*	
*	Revision 1.4  2003/04/25 13:43:52  nilspace
*	Updated to actually work. Still needs verification.
*	
*	Revision 1.3  2003/04/23 16:30:58  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.2  2003/04/08 22:50:28  nilspace
*	Updated to derive classes based on numeric or analytical nature.
*	
*	Revision 1.1  2003/03/27 02:49:20  nilspace
*	Initial submission
*
******************************************************************************/

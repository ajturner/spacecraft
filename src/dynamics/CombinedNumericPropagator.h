//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file CombinedNumericPropagator.h
*  \brief Interface to the Combined Numeric Propagator class.
*  \author $Author: rsharo $
*  \version $Revision: 1.4 $
*  \date    $Date: 2003/10/18 21:37:27 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* \todo Finish documentation
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_COMBINED_NUMERIC_PROPAGATOR_H__
#define __OSESSAME_COMBINED_NUMERIC_PROPAGATOR_H__

#include "Matrix.h"
#include "Rotation.h"
#include "utils/Integrator.h"
#include "NumericPropagator.h"

namespace O_SESSAME {

/*! \brief Propagation of orbit & attitude using a numeric integrator.
* \ingroup PropagatorToolkit
*
* \example testPropagation.cpp
* This example demonstrates how to use a CombinedNumericPropagator to propagate a combined
orbit \& attitude. 
*/
class CombinedNumericPropagator : public NumericPropagator
{
public:
    /*! Default Constructor */
    CombinedNumericPropagator();
    /*! Default Deconstructor */
    virtual ~CombinedNumericPropagator();
    
    /*! Propagates the dynamics forward through time
        * @param _propTime vector of ssfTime values specifying beginning, ending times of propagation as well as time step [initialTime, timeStep, finalTime] (s)
        * @param _orbitInitConditions initial conditions of the orbit integration.
        * @param _attInitConditions initial conditions of the attitude integration.
        */
    virtual void Propagate(const vector<ssfTime> &_propTime, const Vector &_orbitInitConditions, const Vector &_attInitConditions);
    
    void SetOrbitIntegrator(Integrator* _pOrbitIntegrator);
    void SetAttitudeIntegrator(Integrator* _pAttitudeIntegrator);

    Integrator* GetOrbitIntegrator() const;
    Integrator* GetAttitudeIntegrator() const;

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
    
private:
    /*! \brief Matrix of calculated integration mesh points for the orbit dynamics */
    Matrix m_OrbitStateMeshPoints;
    /*! \brief Matrix of calculated integration mesh points for the attitude dynamics */
    Matrix m_AttitudeStateMeshPoints;
    
    /*! \brief pointer to the integrator used by the numeric propagator for orbit integration. */
    Integrator* m_pOrbitIntegrator;
    /*! \brief pointer to the integrator used by the numeric propagator for attitude integration. */
    Integrator* m_pAttitudeIntegrator;
};
} // close namespace O_SESSAME

#endif
/*****************************************************************************
*	$Log: CombinedNumericPropagator.h,v $
*	Revision 1.4  2003/10/18 21:37:27  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.3  2003/06/10 02:24:04  nilspace
*	Updated moving of StateConversion functions to Attitude and Orbit.
*	
*	Revision 1.2  2003/05/22 21:02:28  nilspace
*	Updated comments.
*	
*	Revision 1.1  2003/05/20 17:56:24  nilspace
*	Initial submission.
*	
*
******************************************************************************/

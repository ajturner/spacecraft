//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file CombinedNumericPropagator.cpp
*  \brief Implementation of the Combined Numeric Propagator class.
*  \author $Author: nilspace $
*  \version $Revision: 1.5 $
*  \date    $Date: 2003/06/10 02:24:03 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/ 
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "CombinedNumericPropagator.h"
namespace O_SESSAME {

CombinedNumericPropagator::CombinedNumericPropagator()
{

}

CombinedNumericPropagator::~CombinedNumericPropagator()
{
    /*! \todo figure out how to delete m_pIntegrator only when it is not being used */
    if(m_pOrbitIntegrator)
        delete m_pOrbitIntegrator;
    if(m_pAttitudeIntegrator)
        delete m_pAttitudeIntegrator;
}

void CombinedNumericPropagator::Propagate(const vector<ssfTime> &_propTime, const Vector &_orbitInitConditions, const Vector &_attInitConditions)
{
    /** \todo Determine what prop times exist and what times are req'd to recalc */

    // Test to see if propagation is 'too long' & needs to be broken up
    
    
    // Propagate the orbit & attitude, store in the matrix of integration meshpoints
    if(m_pOrbitObject)
        if (m_pOrbitObject->IsIntegrateable())
            PropagateOrbit(_propTime, _orbitInitConditions);
    if(m_pAttitudeObject)
        if (m_pAttitudeObject->IsIntegrateable())
            PropagateAttitude(_propTime, _attInitConditions);
    
    return;
}

Matrix CombinedNumericPropagator::PropagateOrbit(const vector<ssfTime> &_propTime, const Vector &_initConditions)
{
    // Create temporary orbit & attitude that have the same types (copy of) the current state objects
    // 		the actual state vectors will be replaced, but we need to make sure to have the same 
    //		representation & frame types
    static OrbitState tempOrbit = m_pOrbitObject->GetStateObject();
    static vector<ssfTime> timeVector;		timeVector.clear(); // clear since static
    static vector<OrbitState> orbitVector;	orbitVector.clear(); // clear since static		
    
    /*! \todo determine if having vector<State> in Propagate is polymorphic */

    m_OrbitStateMeshPoints.initialize(m_pOrbitIntegrator->Integrate(   
                                    _propTime, 
                                    m_pOrbitObject->GetDynamicsEq(),
                                    _initConditions, 
                                    m_pOrbitObject,
                                    m_pAttitudeObject,
                                    m_pOrbitObject->GetParameters(),
                                    m_pOrbitObject->GetEnvironmentForcesFunctor() 
                                ));
    /** \todo Append the requested time steps in the appropriate component history */
    // Convert the meshpoints to stored objects and append them to the appropriate history.
    for (int ii = MatrixIndexBase; ii < m_OrbitStateMeshPoints[MatrixRowsIndex].getIndexBound() + MatrixIndexBase; ++ii)
    {
        (m_pOrbitObject->GetStateConversion())(m_OrbitStateMeshPoints(ii,_(MatrixIndexBase+1,m_OrbitStateMeshPoints[MatrixColsIndex].getIndexBound())), tempOrbit);
        timeVector.push_back(ssfTime(m_OrbitStateMeshPoints(ii,MatrixIndexBase)));
        orbitVector.push_back(tempOrbit);
    }
    
    // Store the new histories to the orbit & attitude objects
    if(m_pOrbitObject)
        m_pOrbitObject->GetHistoryObject().AppendHistory(timeVector, orbitVector);
        
    // Set the stored Attitude & Orbit
    /*! \todo Determine if the updated attitude & orbit should be set in Propagator */
    m_pOrbitObject->SetStateObject(tempOrbit);
    
    return m_OrbitStateMeshPoints;
}

Matrix CombinedNumericPropagator::PropagateAttitude(const vector<ssfTime> &_propTime, const Vector &_initConditions)
{
    // Create temporary orbit & attitude that have the same types (copy of) the current state objects
    // 		the actual state vectors will be replaced, but we need to make sure to have the same 
    //		representation & frame types
    static AttitudeState tempAttitude = m_pAttitudeObject->GetStateObject();
    static vector<ssfTime> timeVector;			timeVector.clear(); // clear since static
    static vector<AttitudeState> attitudeVector;	attitudeVector.clear(); // clear since static
     
    static OrbitState tempOrbit = m_pOrbitObject->GetStateObject();

    m_AttitudeStateMeshPoints.initialize(m_pAttitudeIntegrator->Integrate(   
                                    _propTime, 
                                    m_pAttitudeObject->GetDynamicsEq(),
                                    _initConditions, 
                                    m_pOrbitObject,
                                    m_pAttitudeObject,
                                    m_pAttitudeObject->GetParameters(),
                                    m_pAttitudeObject->GetEnvironmentForcesFunctor() 
                                ));
                                
    /** \todo Append the requested time steps in the appropriate component history */
    // Convert the meshpoints to stored objects and append them to the appropriate history.
    for (int ii = MatrixIndexBase; ii < m_AttitudeStateMeshPoints[MatrixRowsIndex].getIndexBound() + MatrixIndexBase; ++ii)
    {
        (m_pAttitudeObject->GetStateConversion())(m_AttitudeStateMeshPoints(ii,_(MatrixIndexBase+1,m_AttitudeStateMeshPoints[MatrixColsIndex].getIndexBound())), tempAttitude);
        timeVector.push_back(ssfTime(m_AttitudeStateMeshPoints(ii,MatrixIndexBase)));
        attitudeVector.push_back(tempAttitude);
    }
    
    // Store the new histories to the attitude object
    m_pAttitudeObject->GetHistoryObject().AppendHistory(timeVector, attitudeVector);

    // Set the stored Attitude
    m_pAttitudeObject->SetStateObject(tempAttitude);
    
    return m_AttitudeStateMeshPoints;
}

void CombinedNumericPropagator::SetOrbitIntegrator(Integrator* _pOrbitIntegrator)
{
    m_pOrbitIntegrator = _pOrbitIntegrator;
    return;
}
void CombinedNumericPropagator::SetAttitudeIntegrator(Integrator* _pAttitudeIntegrator)
{
    m_pAttitudeIntegrator = _pAttitudeIntegrator;
    return;
}    
Integrator* CombinedNumericPropagator::GetOrbitIntegrator() const
{
    return m_pOrbitIntegrator;
}
Integrator* CombinedNumericPropagator::GetAttitudeIntegrator() const
{
    return m_pAttitudeIntegrator;
}
} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: CombinedNumericPropagator.cpp,v $
*	Revision 1.5  2003/06/10 02:24:03  nilspace
*	Updated moving of StateConversion functions to Attitude and Orbit.
*	
*	Revision 1.4  2003/05/27 17:36:24  nilspace
*	Updated to handle different integration stepsizes.
*	
*	Revision 1.3  2003/05/26 21:15:20  nilspace
*	Fixed the static timevector and static attitude/orbitVec to be cleared on each propagate.
*	
*	Revision 1.2  2003/05/22 03:00:43  nilspace
*	Updated to pass pointers of Orbit & Attitude objects rather than references.
*	
*	Revision 1.1  2003/05/20 17:56:24  nilspace
*	Initial submission.
*	
*
******************************************************************************/

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Orbit.cpp
*  \brief Implementation of the Orbit Interface Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.8 $
*  \date    $Date: 2003/06/10 14:52:04 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Orbit.h"
#include "Environment.h"
namespace O_SESSAME {

Orbit::Orbit() : m_CurrentOrbitPosition(), m_pPropagator(NULL), m_Integrateable(false), m_Parameters(), m_pEnvironment(NULL), m_ControlForces() 
{
}

Orbit::~Orbit()
{
/*! \todo determine how to clean up the orbit pointers without leaving references hanging
    if(m_pEnvironment)
        delete m_pEnvironment;
    if(m_pPropagator)
        delete m_pPropagator;
*/
}
void Orbit::SetStateObject(const OrbitState &_currentOrbitPosition) 	
{
    m_CurrentOrbitPosition = _currentOrbitPosition;
}

OrbitState Orbit::GetStateObject() const
{
    return m_CurrentOrbitPosition;
}
    
void Orbit::SetPropagator(Propagator *_pPropagator)
{
    m_pPropagator = _pPropagator; 
    m_pPropagator->SetOrbitObject(this);
}
    
Propagator* Orbit::GetPropagator()
{
    return m_pPropagator;
}

void Orbit::SetDynamicsEq(odeFunctor _orbitDynamicsEq)	
{
    m_OrbitDynamicsEq = _orbitDynamicsEq;
    m_Integrateable = true;
}
odeFunctor Orbit::GetDynamicsEq()				
{
    return m_OrbitDynamicsEq;
}

void Orbit::SetStateConversion(IntegratedOrbitStateConversionFunction _ConversionFunction) 
{
    m_OrbitStateConversionFunction = _ConversionFunction;
}

IntegratedOrbitStateConversionFunction Orbit::GetStateConversion() const
{
    return m_OrbitStateConversionFunction;
}


bool Orbit::IsIntegrateable()
{
    return m_Integrateable;
}

void Orbit::SetParameters(const Matrix &_Parameters)	
{
    m_Parameters.initialize(_Parameters);
}

Matrix Orbit::GetParameters() const				
{
    return m_Parameters;
} 
void Orbit::SetEnvironment(Environment *_pEnvironment)	
{
    m_pEnvironment = _pEnvironment;
    m_EnvironmentForcesFunctor.Set(m_pEnvironment, &Environment::GetForces);
}

Environment* Orbit::GetEnvironment()			
{
    return m_pEnvironment;
}
void Orbit::SetControlForces(const Vector &_controlForces)
{
    m_ControlForces.initialize(_controlForces);
}

Vector Orbit::GetControlForces()				
{
    return m_ControlForces;
}

ObjectFunctor<Environment> Orbit::GetEnvironmentForcesFunctor()		
{
    return m_EnvironmentForcesFunctor;
}

OrbitHistory& Orbit::GetHistoryObject()				
{
    return m_OrbitHistory;
}
} // end of namespace O_SESSAME
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Orbit.cpp,v $
*	Revision 1.8  2003/06/10 14:52:04  nilspace
*	Changed GetHistory to GetHistoryObject
*	
*	Revision 1.7  2003/05/22 21:03:07  nilspace
*	Updated comments.
*	
*	Revision 1.6  2003/05/20 17:47:59  nilspace
*	Updated comments.
*	
*	Revision 1.5  2003/04/28 20:13:17  nilspace
*	GetHistory return by reference.
*	
*	Revision 1.4  2003/04/27 21:17:42  nilspace
*	Finished moving function declarations out of the class interface.
*	
*	Revision 1.3  2003/04/27 21:14:01  nilspace
*	Added to the namespace O_SESSAME.
*	Moved function definitions outside of the class interface definition.
*	
*	Revision 1.2  2003/04/25 13:36:57  nilspace
*	Updated to work with current History, Environment, & Propagator objects.
*	
*	Revision 1.1  2003/04/08 22:48:59  nilspace
*	Initial Submission.
*	
*	
*
******************************************************************************/

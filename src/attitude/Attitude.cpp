//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Attitude.cpp
*  \brief Implementation of the attitude class.
*  \author $Author: rsharo $
*  \version $Revision: 1.11 $
*  \date    $Date: 2003/10/18 21:37:27 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* \todo Fix propagate & resizing of the attitude history  
*  \todo Implement History object that stores the state and history dependent on the parameters being stored (by registering variables?)
*/ 
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Attitude.h"
#include "utils/RungeKutta.h"


namespace O_SESSAME {

Attitude::Attitude(): m_AttitudeState(), m_ControlTorques(3), m_pPropagator(NULL), m_Parameters(), m_pEnvironment(NULL), m_AttitudeHistory()
{

}

Attitude::~Attitude()
{
/*! \todo determine how to clean up the attitude pointers without leaving references hanging
    if(m_pEnvironment)
        delete m_pEnvironment;
    if(m_pPropagator)
        delete m_pPropagator;
*/
}

void Attitude::SetStateObject(const AttitudeState &_newAttitudeState) 	
{
    m_AttitudeState = _newAttitudeState;
}

AttitudeState Attitude::GetStateObject() const				
{
    return m_AttitudeState;
}

void Attitude::SetPropagator(Propagator *_propagator)
{
    m_pPropagator = _propagator;
    m_pPropagator->SetAttitudeObject(this);
    return;
}

odeFunctor Attitude::GetDynamicsEq() const
{
    return m_AttDynEqFuncPtr;
}

void Attitude::SetDynamicsEq(odeFunctor _AttDynEqFuncPtr)
{
    m_AttDynEqFuncPtr = _AttDynEqFuncPtr;
    m_Integrateable = true;
    return;
}

void Attitude::SetStateConversion(IntegratedAttitudeStateConversionFunction _ConversionFunction)
{
    m_AttitudeStateConversionFunction = _ConversionFunction;
}
    
IntegratedAttitudeStateConversionFunction Attitude::GetStateConversion() const
{
    return m_AttitudeStateConversionFunction;
}

void Attitude::SetControlTorques(const Vector &_ControlTorques)
{
    /** \todo add error checking */
    m_ControlTorques.initialize(_ControlTorques);
    return;
}
Vector Attitude::GetControlTorques() const
{
    return m_ControlTorques;
}
    
void Attitude::SetParameters(const Matrix &_Parameters)	
{
    m_Parameters.initialize(_Parameters);
}

Matrix Attitude::GetParameters() const				
{
    return m_Parameters;
}

Matrix Attitude::Propagate(const vector<ssfTime> &_propTime)
{
    cout << "Begin propagating... " << endl;
    m_pPropagator->Propagate(_propTime);
    // Store the propagated states
    return Matrix(3,3);
}
   
bool Attitude::IsIntegrateable()
{
    return m_Integrateable;
}

// ***************************** 
// ******** ENVIRONMENT ********
// *****************************     
void Attitude::SetEnvironment(Environment *_pEnvironment)	
{
    m_pEnvironment = _pEnvironment;
    m_EnvironmentForcesFunctor.Set(m_pEnvironment, &Environment::GetTorques);
} 

Environment* Attitude::GetEnvironment() const					
{
    return m_pEnvironment;
}

ObjectFunctor<Environment> Attitude::GetEnvironmentForcesFunctor()		
{
    return m_EnvironmentForcesFunctor;
}

// *************************
// ******** HISTORY ******** 
// ************************* 
AttitudeHistory& Attitude::GetHistoryObject()
{
    return m_AttitudeHistory;
}

} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Attitude.cpp,v $
*	Revision 1.11  2003/10/18 21:37:27  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.10  2003/06/10 14:51:41  nilspace
*	Changed GetHistory to GetHistoryObject
*	
*	Revision 1.9  2003/05/20 17:46:25  nilspace
*	Updated comments.
*	
*	Revision 1.8  2003/04/28 20:12:44  nilspace
*	GetHistory return by reference.
*	
*	Revision 1.7  2003/04/28 14:29:18  nilspace
*	Added data member constructor calls in default constructor.
*	
*	Revision 1.6  2003/04/27 22:11:51  nilspace
*	Moved all of the function definitions out of the class interface definition.
*	
*	Revision 1.5  2003/04/27 22:04:31  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.4  2003/04/25 13:44:58  nilspace
*	Updated to work with current History, Environment & Propagator objects.
*	
*	Revision 1.3  2003/04/23 21:54:32  nilspace
*	Updated to work with AttitudeState, Environment.
*	Removed the setting and getting of AngVel, AngAccel, Rotation.
*	
*	Revision 1.2  2003/04/23 16:30:58  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/04/08 22:51:24  nilspace
*	Initial submission in new directory.
*
******************************************************************************/

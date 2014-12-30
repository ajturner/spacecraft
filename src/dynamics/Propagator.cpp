//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Propagator.cpp
*  \brief Implementation of the Propagator class.
*  \author $Author: nilspace $
*  \version $Revision: 1.7 $
*  \date    $Date: 2003/06/10 02:24:04 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/ 
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Propagator.h"

namespace O_SESSAME {
Propagator::Propagator() : m_pOrbitObject(0), m_pAttitudeObject(0)
{    
    m_OrbitStateMeshPoints.ResetHistory();
    m_AttitudeStateMeshPoints.ResetHistory();
}
    
void Propagator::Propagate(const vector<ssfTime> &_propTime)
{
}

Propagator::~Propagator()
{
}

void Propagator::SetAttitudeObject(Attitude *_pAttitudeObject)		
{
    m_pAttitudeObject = _pAttitudeObject;
}

void Propagator::SetOrbitObject(Orbit *_pOrbitObject)
{
    m_pOrbitObject = _pOrbitObject;
}

Matrix Propagator::PropagateOrbit(const vector<ssfTime> &_propTime, const Vector &_initConditions) 
{ 
    return Matrix(0);
}

Matrix Propagator::PropagateAttitude(const vector<ssfTime> &_propTime, const Vector &_initConditions) 
{ 
    return Matrix(0);
}

} // close namespace O_SESSAME
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Propagator.cpp,v $
*	Revision 1.7  2003/06/10 02:24:04  nilspace
*	Updated moving of StateConversion functions to Attitude and Orbit.
*	
*	Revision 1.6  2003/05/13 18:53:04  nilspace
*	Passed in initial conditions to propagate functions.
*	
*	Revision 1.5  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
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
*	Revision 1.1  2003/03/27 20:24:28  nilspace
*	Initial submission
*
******************************************************************************/

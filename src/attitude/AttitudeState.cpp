//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file AttitudeState.cpp
*  \brief Implementation of the Attitude State Interface Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.5 $
*  \date    $Date: 2003/06/12 23:07:08 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "AttitudeState.h"
#include "orbitstaterep/Keplerian.h"
#include "OrbitState.h"
namespace O_SESSAME {
AttitudeState::AttitudeState() : m_AngularVelocity(3)
{

}
AttitudeState::~AttitudeState()
{
    /*! \todo delete AttitudeState data members */
/*
    if(m_pAttitudeFrame)
        delete m_pAttitudeFrame;*/
}
AttitudeState::AttitudeState(const Rotation &_Rot, AttitudeFrame* _pAttFrame)
{
    SetRotation(_Rot);
    SetAttitudeFrame(_pAttFrame);
}

AttitudeState::AttitudeState(const Rotation &_Rot, const Vector &_AngVel, AttitudeFrame* _pAttFrame)
{
    SetRotation(_Rot);
    SetAngularVelocity(_AngVel);
    SetAttitudeFrame(_pAttFrame);
}
void AttitudeState::SetAttitudeFrame(AttitudeFrame* _pNewAttitudeFrame)
{ /** \todo add conversion of Rotation to the new frame */
    m_pAttitudeFrame = _pNewAttitudeFrame;
    return;
}

AttitudeFrame* AttitudeState::GetAttitudeFrame() const
{
    return m_pAttitudeFrame;
}

void AttitudeState::SetRotation(const Rotation &_Rot)
{
    m_AttitudeRotation = _Rot;
}

void AttitudeState::SetRotation(const Rotation &_Rot,  AttitudeFrame* _pAttFrame)
{
    SetRotation(_Rot);
    SetAttitudeFrame(_pAttFrame);
}

Rotation AttitudeState::GetRotation() const
{
    return m_AttitudeRotation;
}

void AttitudeState::SetState(const Rotation& _Rotation, const Vector& _AngVel, AttitudeFrame* _attFrame)
{
    SetRotation(_Rotation);
    SetAngularVelocity(_AngVel);
    if(_attFrame)
        SetAttitudeFrame(_attFrame);
    return;
}


Vector AttitudeState::GetState(const RotationType& _rotType, AttitudeFrame* _attFrame, const int& _Sequence) const
{
    Vector rotOutput = GetRotation().GetRotation(_rotType, _Sequence);
    Vector output(rotOutput.getIndexBound() + m_AngularVelocity.getIndexBound());
    output(_(VectorIndexBase, VectorIndexBase + rotOutput.getIndexBound() - 1)) = rotOutput(_);
    output(_(VectorIndexBase + rotOutput.getIndexBound(), VectorIndexBase + rotOutput.getIndexBound() + m_AngularVelocity.getIndexBound() - 1)) = m_AngularVelocity(_); 
    return output;
}

void AttitudeState::SetAngularVelocity(const Vector &_angVel)
{
    m_AngularVelocity = _angVel;
}

Vector AttitudeState::GetAngularVelocity() const
{
    return m_AngularVelocity;
}

Rotation AttitudeState::GetRotation2Orbital(const OrbitState& _orbState) const 
{
    Keplerian kepElements; kepElements.SetPositionVelocity(_orbState.GetStateRepresentation()->GetPositionVelocity());
    return GetRotation() * R3(kepElements.GetLongAscNode()) * R1(kepElements.GetInclination()) * R3(kepElements.GetArgPerigee());
}

} // close namespace O_SESSAME
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: AttitudeState.cpp,v $
*	Revision 1.5  2003/06/12 23:07:08  nilspace
*	Fixed to calculate Orbital rotation.
*	
*	Revision 1.4  2003/04/27 22:04:31  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.3  2003/04/23 19:16:35  nilspace
*	Removed default argument for AttitudeState::SetState.
*	
*	Revision 1.2  2003/04/23 16:30:58  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/04/08 22:51:24  nilspace
*	Initial submission in new directory.
*	
*
******************************************************************************/

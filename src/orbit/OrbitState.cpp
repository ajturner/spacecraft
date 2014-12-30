//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitState.cpp
*  \brief Implementation of the Orbit State Interface Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.9 $
*  \date    $Date: 2003/06/12 23:08:20 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "OrbitState.h"
namespace O_SESSAME {

OrbitState::OrbitState(): m_pOrbitStateRepresentation(NULL), m_pOrbitFrame(NULL)
{

}

OrbitState::OrbitState(const OrbitState &_OrbStateCopy)
{
    /*! \todo Determine if the OrbitState copy function is req'd or hacked. */
    /*! \bug if OrbitFrame is not set, but a vector::push_back function is called, 
        * _OrbStateCopy.m_pOrbitFrame = 0xffffffff, which indicates a failure. Need 
        * to fix this.
        */
    // If there is a current representation or frame, delete it to free the memory
    // 	then copy the data members of the orbit state to be copied.
    if(_OrbStateCopy.m_pOrbitStateRepresentation)
        m_pOrbitStateRepresentation = _OrbStateCopy.m_pOrbitStateRepresentation->Clone();
    if(_OrbStateCopy.m_pOrbitFrame)
        m_pOrbitFrame = _OrbStateCopy.m_pOrbitFrame->Clone();
    
}

OrbitState::~OrbitState()
{
    /*! \todo determine how to delete OrbitState pointers */
/*
    if(m_pOrbitStateRepresentation)
        delete m_pOrbitStateRepresentation;
    if(m_pOrbitFrame)
        delete m_pOrbitFrame;
*/
}
OrbitState::OrbitState(OrbitStateRepresentation* _pOrbRep, OrbitFrame* _pOrbFrame)
{
    SetOrbitFrame(_pOrbFrame);
    SetStateRepresentation(_pOrbRep);
}
void OrbitState::SetOrbitFrame(OrbitFrame* _pNewOrbitFrame)
{ /** \todo add conversion of OrbitStateRepresentation to the new frame */
    if(_pNewOrbitFrame)
    {
        if(m_pOrbitFrame)
            delete m_pOrbitFrame;
        m_pOrbitFrame = _pNewOrbitFrame->Clone();
    }
    return;
}

OrbitFrame* OrbitState::GetOrbitFrame() const
{
    return m_pOrbitFrame;
}
void OrbitState::SetStateRepresentation(OrbitStateRepresentation* _pStateRep)
{
    if(_pStateRep)
    {
        if(m_pOrbitStateRepresentation)
            delete m_pOrbitStateRepresentation;
        m_pOrbitStateRepresentation = _pStateRep->Clone();
    }
}

void OrbitState::SetStateRepresentation(OrbitStateRepresentation* _pStateRep,  OrbitFrame* _pOrbFrame)
{
    SetStateRepresentation(_pStateRep);
    SetOrbitFrame(_pOrbFrame);
}

OrbitStateRepresentation* OrbitState::GetStateRepresentation() const
{
    return m_pOrbitStateRepresentation;
}

double OrbitState::GetOrbitAngularMomentum() const
{
    Vector Position(3);
    Vector Velocity(3);
    m_pOrbitStateRepresentation->GetPositionVelocity(Position, Velocity);
    return norm2(skew(Position) * Velocity);
}


void OrbitState::SetState(const Vector &_State)
{
    if(m_pOrbitStateRepresentation)
        m_pOrbitStateRepresentation->SetState(_State); 
    return;
}
Vector OrbitState::GetState() const
{
    if(m_pOrbitStateRepresentation)
        return m_pOrbitStateRepresentation->GetState();
    else
        return Vector(3);
}

OrbitState OrbitState::operator= (const OrbitState& _OrbStateCopy)
{
    // If there is a current representation or frame, delete it to free the memory
    // 	then copy the data members of the orbit state to be copied.
    if(_OrbStateCopy.GetStateRepresentation())
    {
        if( m_pOrbitStateRepresentation)
            delete m_pOrbitStateRepresentation;
        m_pOrbitStateRepresentation = _OrbStateCopy.GetStateRepresentation()->Clone();
    }
    if(_OrbStateCopy.GetOrbitFrame())
    {
        if(m_pOrbitFrame)
            delete m_pOrbitFrame;
        m_pOrbitFrame = _OrbStateCopy.GetOrbitFrame()->Clone();
    }
    return (*this);
}
} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitState.cpp,v $
*	Revision 1.9  2003/06/12 23:08:20  nilspace
*	Fixed to calculate angular momentum.
*	
*	Revision 1.8  2003/06/12 18:02:15  nilspace
*	Added GetAngularVelocity() function.
*	
*	Revision 1.7  2003/05/22 14:37:32  nilspace
*	Return *this in operator=
*	
*	Revision 1.6  2003/05/20 17:47:59  nilspace
*	Updated comments.
*	
*	Revision 1.5  2003/05/13 18:46:28  nilspace
*	Checked pointers if they were initialized before calling.
*	
*	Revision 1.4  2003/04/29 20:56:24  nilspace
*	Update to work with Propagator.
*	
*	Revision 1.3  2003/04/29 18:47:31  nilspace
*	Added copy constructor and operator= functions.
*	
*	Revision 1.2  2003/04/27 21:14:01  nilspace
*	Added to the namespace O_SESSAME.
*	Moved function definitions outside of the class interface definition.
*	
*	Revision 1.1  2003/04/25 14:01:28  nilspace
*	Recommited to fix capitalization.
*	
*	Revision 1.1  2003/04/23 16:26:03  nilspace
*	Updated directory structure & default parameters.
*	
*
******************************************************************************/
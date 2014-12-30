//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file PositionVelocity.cpp
*  \brief Implementation of the Position/Velocity Coordinate Type Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.4 $
*  \date    $Date: 2003/04/29 18:48:31 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "PositionVelocity.h"
namespace O_SESSAME {
PositionVelocity::PositionVelocity() : m_Elements(NUM_POSVEL_ELEMENTS)
{

}

PositionVelocity::~PositionVelocity()
{
}

PositionVelocity::PositionVelocity(const Vector &_Elements)
{
    SetState(_Elements);
}

PositionVelocity::PositionVelocity(const Vector &_Position, const Vector &_Velocity)
{
    SetState(_Position, _Velocity);
}

void PositionVelocity::SetState(const Vector &_Elements)
{
    m_Elements = _Elements;
    return;
}
void PositionVelocity::SetState(const Vector &_Position, const Vector &_Velocity)
{
    m_Elements(_(VectorIndexBase, VectorIndexBase + _Position.getIndexBound()-1)) = _Position(_);
    m_Elements(_(VectorIndexBase + _Position.getIndexBound(), VectorIndexBase+ _Position.getIndexBound()+ _Velocity.getIndexBound()-1)) = _Velocity(_);
    return;
}
Vector PositionVelocity::GetState() const
{
    return m_Elements;
}

void PositionVelocity::GetState(Vector &_Position, Vector &_Velocity) const
{
    int numPosElements = _Position.getIndexBound();
    int numVelElements = _Velocity.getIndexBound();
    _Position = m_Elements(_(VectorIndexBase,VectorIndexBase+numPosElements-1));
    _Velocity = m_Elements(_(VectorIndexBase+numPosElements, VectorIndexBase+numPosElements+numVelElements-1));
    return;
}

void PositionVelocity::SetPositionVelocity(const Vector &_Position, const Vector &_Velocity)
{
    SetState(_Position, _Velocity);
    return;
}

PositionVelocity* PositionVelocity::NewPointer()
{
    return new PositionVelocity();
}

PositionVelocity* PositionVelocity::Clone()
{
    return new PositionVelocity(*this);
}

} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: PositionVelocity.cpp,v $
*	Revision 1.4  2003/04/29 18:48:31  nilspace
*	Added NewPointer and Clone functions to help in getting the correct memory allocation.
*	
*	Revision 1.3  2003/04/24 21:14:24  nilspace
*	const'd all Get() functions.
*	
*	Revision 1.2  2003/04/24 20:19:30  nilspace
*	const'd all Get() functions.
*	
*	Revision 1.1  2003/04/08 22:47:35  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

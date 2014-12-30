//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file CentralBody.cpp
*  \brief Implementation of the CentralBody encapsulation object.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/06/12 17:57:41 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "CentralBody.h"
#include "Models/MagneticModel.h"
namespace O_SESSAME {

CentralBody::CentralBody() : m_ReferenceCount(0)
{

}

void CentralBody::GetReference()
{
    ++m_ReferenceCount;
    return;
}
void CentralBody::ReleaseReference()
{
    --m_ReferenceCount;
    if(m_ReferenceCount <= 0)
    { /** \todo Check how to verify the number of references & delete the object */
        //delete *this;
    }
    return;
}

void CentralBody::SetMagneticModel(MagneticModel* _pNewMagModel) 
{ 
    m_pMagneticFieldModel = _pNewMagModel; 
    m_pMagneticFieldModel->SetMagFieldCoefficients(m_MagFieldCoeffs);
}

double CentralBody::GetAvgRotationRate()		{return m_AvgRotationRate;}

double CentralBody::GetRadius()			{return m_Radius;}

CentralBody* CentralBody::operator= (CentralBody*) 
{
    GetReference(); return this;
}

} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: CentralBody.cpp,v $
*	Revision 1.2  2003/06/12 17:57:41  nilspace
*	Added magnetic models.
*	
*	Revision 1.1  2003/06/06 17:34:53  nilspace
*	Moved to CentralBody directory.
*	
*	Revision 1.3  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.2  2003/04/23 16:29:46  nilspace
*	Updated makefile directories.
*	
*	Revision 1.1  2003/04/08 22:35:11  nilspace
*	Initial Submission.
*
******************************************************************************/

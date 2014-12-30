//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file NumericPropagator.cpp
*  \brief Implementation of the Numeric Propagator class.
*  \author $Author: nilspace $
*  \version $Revision: 1.8 $
*  \date    $Date: 2003/05/20 17:55:35 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/ 
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "NumericPropagator.h"
namespace O_SESSAME {

NumericPropagator::NumericPropagator()
{

}

NumericPropagator::~NumericPropagator()
{

}

void NumericPropagator::Propagate(const vector<ssfTime> &_propTime, const Vector &_orbitInitConditions, const Vector &_attInitConditions)
{

}

} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: NumericPropagator.cpp,v $
*	Revision 1.8  2003/05/20 17:55:35  nilspace
*	Updated comments, also now use derived CombinedNumericProp.
*	
*	Revision 1.7  2003/05/13 18:54:04  nilspace
*	Fixed comments & various propagate functions.
*	
*	Revision 1.6  2003/04/30 14:45:35  nilspace
*	Set the OrbitStateObject() and AttitudeStateObject() in the Propagate() function.
*	
*	Revision 1.5  2003/04/29 20:56:03  nilspace
*	Updated to work.
*	
*	Revision 1.4  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.3  2003/04/25 13:43:52  nilspace
*	Updated to actually work. Still needs verification.
*	
*	Revision 1.1  2003/04/08 22:49:56  nilspace
*	Initial Submission.
*
******************************************************************************/

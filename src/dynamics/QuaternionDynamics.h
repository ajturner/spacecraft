//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file QuaternionDynamics.h
*  \brief Rigid body dynamic equations of attitude motion in quaternion form.
*  \author $Author: nilspace $
*  \version $Revision: 1.3 $
*  \date    $Date: 2003/04/23 16:30:58 $
//////////////////////////////////////////////////////////////////////////////////////////////////
* \todo document the QuaternionDynamics function
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef QUATERNIONDYNAMICS_H
#define QUATERNIONDYNAMICS_H
#include "../rotation/Rotation.h"

static Vector QuaternionDynamics(const double &_time, const Vector &w_BI, const Matrix &_params)
{
    Matrix MOI(3,3); 
    MOI = _params(_(MatrixIndexBase+0,MatrixIndexBase+2),_(MatrixIndexBase+0,MatrixIndexBase+2));
    Matrix Tmoment(3,1); 
    Tmoment = ~_params(MatrixIndexBase + 3, _);
    Tmoment = (MOI.inverse() * (Tmoment - skew(w_BI) * (MOI * w_BI)));
    Vector temp(3); 
    temp(_) = Tmoment(_,MatrixIndexBase);
    return temp;
}

#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: QuaternionDynamics.h,v $
*	Revision 1.3  2003/04/23 16:30:58  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.2  2003/03/27 02:51:08  nilspace
*	Fixed to prevent incorrect vector indexing.
*	
*	Revision 1.1  2003/03/25 02:29:56  nilspace
*	initial submission. Needs to be verified.
*
******************************************************************************/

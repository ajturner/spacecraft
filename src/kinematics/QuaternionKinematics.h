////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file QuaternionKinematics.h
*  \brief Rigid body kinematic equations of attitude motion in quaternion form.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/04/23 16:30:58 $
//////////////////////////////////////////////////////////////////////////////////////////////////
* \todo document the QuaternionKinematics class
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef QUATERNIONKINEMATICS_H
#define QUATERNIONKINEMATICS_H
#include "../rotation/Rotation.h"

static Vector QuaternionKinematics(const double &_time, const Vector &_qIn, const Matrix &_wIn)
{
    Matrix qtemp(4,3); 
    qtemp(_(VectorIndexBase+0,VectorIndexBase+2),_(VectorIndexBase+0,VectorIndexBase+2)) = skew(_qIn(_(VectorIndexBase+0,VectorIndexBase+2))) + _qIn(VectorIndexBase+3) * eye(3);
    qtemp(VectorIndexBase+3, _(VectorIndexBase+0,VectorIndexBase+2)) = -(~_qIn(_(VectorIndexBase+0,VectorIndexBase+2)));

    qtemp.initialize(0.5 * qtemp * _wIn);
    Vector qDot(QUATERNION_SIZE);qDot(_) = qtemp(_,MatrixIndexBase);
    return (Vector)qDot;
}

#endif
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: QuaternionKinematics.h,v $
*	Revision 1.2  2003/04/23 16:30:58  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/03/25 02:28:20  nilspace
*	initial submission. Needs to be verified.
*
******************************************************************************/

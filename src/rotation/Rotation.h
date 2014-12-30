//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Rotation.h
 *  \brief Rotation toolkit.
 *  \brief Provides a set of functions to use Rotation matrices
 *         and their various representations.
 *  \author $Author: rsharo $
 *  \version $Revision: 1.19 $
 *  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  \todo Implement Gibbs vector representation
 */
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_ROTATION_H__
#define __OSESSAME_ROTATION_H__
#include "matrix/Matrix.h"
#include <math.h>
#include "utils/MathUtils.h"
using namespace O_SESSAME;

namespace O_SESSAME {
// Prototype definitions of classes in Rotation Toolbox
class Quaternion;
class DirectionCosineMatrix;
class ModifiedRodriguezParameters;
class Rotation;			

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \defgroup RotationLibrary Rotation Library
*  The Rotation Library is a collection of attitude representation class definitions that are meant to
* assist in the implementation of spacecraft analysis and operation code. Each attitude representation
* is implemented as a class with member functions that perform transformations and retrievals of the
* rotation information.
*
* The Rotation class is the most general, and useful, of the Kinematics Toolbox classes. All
* attitudes can be stored as a Rotation, and then retrieved in any of the desired formats
* (MRP, DCM, Quaternion, Euler Axis & Angle, Euler Angle).
*
* Here are some examples of using the kinematics toolbox in general. For more specific examples
* refer to the appropriate classes documentation.
* \par Examples:
*
\code
DirectionCosineMatrix dcm1(deg2rad(30),deg2rad(-10),deg2rad(5), 123); // create a DCM with successive rotations of [30,-10,5] degs in a 123 rotation order
Quaternion q1(dcm1); // create a quaternion that is the same attitude transformation as dcm1
Quaternion q2(~dcm1); // create a second quaternion that is the transpose of dcm1 (~dcm1)
Rotation rot1(q1 * q2); // create a rotation that is the successive rotation of q1 and q2
cout << rot1; // output rot1 to the standard stream (usually the screen)
\endcode
\code
Vector eulerAxis;
double eulerAngle;
rot1.GetEulerAxisAngle(eulerAxis, eulerAngle);
cout << eulerAxis << eulerAngle;
\endcode
*
* \example testRotation.cpp
* Demonstrates the use of the Rotation class and associated kinematic representations.
* @{
*/

/*! \brief Number of elements in a quaternion vector */
const int QUATERNION_SIZE = 4;
/*! \brief Number of elements in a MRP vector */
const int MRP_SIZE = 3;
/*! \brief Number of elements in a DCM row or column */
const int DCM_SIZE = 3;
/*! \brief Number of elements in an euler axis */
const int EULERAXIS_SIZE = 3;
/*! \brief Number of elements in an euler angle sequence */
const int EULERANGLES_SIZE = 3;

/*! \brief Various representations of a rotation */
enum RotationType{DCM_Type, EulerAngle_Type, EulerAxisAngle_Type, MRP_Type, Quaternion_Type};

/*! \brief The Sense, or "handedness" of a rotation system */
enum RotationSense{LEFT_HAND = -1, RIGHT_HAND = 1};

/** @} */

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \brief 3x3 direction cosine matrix attitude representation.
* \ingroup RotationLibrary
*  
* 
*  A simple way to describe and represent an Euler Angle sequence is by the use of a Direction Cosine Matrix (DCM). A DCM is a 3x3 matrix of values, a rotation matrix, that represent the transformation of a vector from one coordinate frame to another:
\f[

{\bf v}^{b} = {\bf R}^{ba}{\bf v}^{a}

\f]
where \f${\bf v}^{a}\f$ and \f${\bf v}^{b}\f$ are the \f$\hat{\bf v}\f$ vectors in \f$\mathcal{F}_{a}\f$ (Frame {\it a\/}) and \f$\mathcal{F}_{b}\f$ respectively. \f${\bf R}^{ba}\f$ is the DCM describing the rotation from \f$\mathcal{F}_{a}\f$ to \f$\mathcal{F}_{b}\f$.

The direction cosine matrix is constructed by the components of the angles between the frame axes:
\f[
{\bf R}^{21} = \begin{bmatrix}
\cos{\theta_{x_{2}x_{1}}} && \cos{\theta_{x_{2}y_{1}}} && \cos{\theta_{x_{2}z_{1}}}\\
\cos{\theta_{y_{2}x_{1}}} && \cos{\theta_{y_{2}y_{1}}} && \cos{\theta_{y_{2}z_{1}}}\\
\cos{\theta_{z_{2}x_{1}}} && \cos{\theta_{z_{2}y_{1}}} && \cos{\theta_{z_{2}z_{1}}}\end{bmatrix}
\f]
where \f$\cos{\theta_{x_{2}x_{1}}}\f$ is the cosine of the angle between the \f$x\f$ axis of the first frame and the \f$x\f$ axis of the second frame.

To determine successive rotations (say from \f$\mathcal{F}_{a}\f$ to \f$\mathcal{F}_{b}\f$ to \f$\mathcal{F}_{c}\f$), we can simply combine the rotation matrices by multiplying them together:
\f[
{\bf R}^{ca} = {\bf R}^{cb}{\bf R}^{ba}
\f]

<hr>
A DCM can be created from any of the other attitude representations
\code
DirectionCosineMatrix myEulerDCM(40*RPD, 20*RPD, -120*RPD, 312); // creates a 312 rotation DCM from 3 euler angles
DirectionCosineMatrix myQuatDCM(myQuaternion);	// where myQuaternion is an instance of Quaternion
DirectionCosineMatrix myMRPDCM(myMRP);		// where myMRP is an instance of ModifiedRodriguezParameters
\endcode

and can also return the transformation in any of the representations. The successive and relative rotations
* between 2 DCMS can be computed:
\code
dcm3 = dcm1 * dcm2; \\ successive rotation
dcm3 = dcm1 + dcm2; \\ successive rotation
dcm1 = dcm3 - dcm2; \\ relative rotation
\endcode
* If the inverse transformation of a direction cosine matrix is required, the transpose operation
* is used:
\code
dcmOI = ~dcmIO;
\endcode
* 
* The DirectionCosineMatrix class is derived from Matrix, so therefore includes all
* of the functionality of the Matrix class. This includes subarray accessing, element
* accessing, multiplication, addition (except where redefined by the subclass).
\code
double element11 = dcm1(MatrixBaseIndex + 0, MatrixBaseIndex + 0);
Vector column2 = dcm1(_,MatrixBaseIndex+1);
\endcode
* 
*/
class DirectionCosineMatrix:public Matrix
{
public:

    // DCM CONSTROCTURS
    DirectionCosineMatrix();
    
    DirectionCosineMatrix(const DirectionCosineMatrix& _DCM);

    DirectionCosineMatrix(const Matrix& _DCM);

    DirectionCosineMatrix(const Vector& _EulerAngles, const int& _Sequence);

    DirectionCosineMatrix(const Vector& _EulerAxis, const Angle& _EulerAngle);

    DirectionCosineMatrix(const Angle& _Angle1, const Angle& _Angle2, const Angle& _Angle3, const int& _Sequence);

    DirectionCosineMatrix(const ModifiedRodriguezParameters& _MRP);

    DirectionCosineMatrix(const Quaternion& _quat);
    
    virtual ~DirectionCosineMatrix();

    // DCM MUTATORS
    void Set(const DirectionCosineMatrix& _DCM);

    void Set(const Matrix& _DCM);
    
    void Set(const Vector& _EulerAngles, const int& _Sequence);

    void Set(const Angle& _Angle1, const Angle& _Angle2, const Angle& _Angle3, const int& _Sequence);

    void Set(const Vector& _EulerAxis, const Angle& _EulerAngle);

    void Set(const ModifiedRodriguezParameters& _MRP);
    
    void Set(const Quaternion& _qIn);

    // DCM INSPECTORS
    Vector GetEulerAngles(const int& _Sequence) const;

    void GetEulerAxisAngle(Vector& _EulerAxis, Angle& _EulerAngle) const;
    
    ModifiedRodriguezParameters GetMRP() const;
    
    Quaternion GetQuaternion() const;

    // DCM OPERATORS
    void Normalize();

    DirectionCosineMatrix operator+ (const DirectionCosineMatrix& _DCM2) const;
    
    DirectionCosineMatrix operator- (const DirectionCosineMatrix& _DCM2) const;

    inline DirectionCosineMatrix operator* (DirectionCosineMatrix _DCM2) const;

    inline Vector operator* (const Vector& _vec) const;

    inline DirectionCosineMatrix operator~ ();
    
};


DirectionCosineMatrix R1(const Angle& _Angle);

DirectionCosineMatrix R2(const Angle& _Angle);

DirectionCosineMatrix R3(const Angle& _Angle);
// end of DirectionCosineMatrix

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \brief 3x1 Modified Rodriguez Parameters attitude representation.
* \ingroup RotationLibrary
*  
Another method of specifying a rigid body attitude is through the
use of Modified Rodriguez Parameters (MRP). The 3-element set is
defined as follows:
\f[
{\bf \sigma}  = \hat{\bf e}\tan{\frac{\Phi }{4}}.
\f]
Like the quaternions, the MRP is not a unique solution to the transformation, but also has a shadow set, \f${\bf \sigma}^{S}\f$:
\f[
{\bf \sigma}^{S} = -\frac{1}{|{\bf \sigma}^{2}}{\bf \sigma}
\f]
This can be evaluated whenever \f$|{\bf \sigma}| > 1\f$ since the shadow set will be a shorter rotational distance back to the original frame. 

*/
class ModifiedRodriguezParameters:public Vector
{
public:
    // MRP CONSTRUCTORS
    ModifiedRodriguezParameters();

    ModifiedRodriguezParameters(const ModifiedRodriguezParameters& _MRP);
    
    ModifiedRodriguezParameters(const double& _s1, const double& _s2, const double& _s3);

    ModifiedRodriguezParameters(const Vector& _sVector);

    ModifiedRodriguezParameters(const DirectionCosineMatrix& _DCM);

    ModifiedRodriguezParameters(const Vector& _Angles, const int& _Sequence);

    ModifiedRodriguezParameters(const Vector& _EulerAxis, const Angle& _EulerAngle);

    ModifiedRodriguezParameters(const Quaternion& _qIN);

    // MRP MUTATORS
    void Set(const ModifiedRodriguezParameters& _MRP);

    void Set(const double& _s1, const double& _s2, const double& _s3);

    void Set(const Vector& _sVector);

    void Set(const DirectionCosineMatrix& _DCM);

    void Set(const Vector& _EulerAngles, const int& _Sequence);

    void Set(const Angle& _Angle1, const Angle& _Angle2, const Angle& _Angle3, const int& _Sequence);

    void Set(const Vector& _EulerAxis, const Angle& _EulerAngle);

    void Set(const Quaternion& _qIN);

    // MRP INSPECTORS
    DirectionCosineMatrix GetDCM() const;

    Vector GetEulerAngles(int _Sequence) const;

    void GetEulerAxisAngle(Vector& _EulerAxis, Angle& _EulerAngle) const;

    Quaternion GetQuaternion() const;

    // MRP OPERATORS
    void Switch(int _SwitchThreshold = 1);

    void AutoSwitch(bool _SwitchBoolean = false);

    ModifiedRodriguezParameters ShadowSet() const;

    ModifiedRodriguezParameters operator+ (const ModifiedRodriguezParameters& _MRP2) const;

    ModifiedRodriguezParameters operator- (const ModifiedRodriguezParameters& _MRP2) const;
    // end of MRPOperators
private:
    /*! \brief Configuration for auto-switching to shadow set. */
    bool m_AutoSwitch;
};
// end of ModifiedRodriguezParameters

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \brief The non-singular, redundant Euler parameter (quaternion) vector.
* \ingroup RotationLibrary
* 
*
The 4-element quaternion set, \f${\bf{\bar q}}\f$ contains no
singularities similar to those found in an Euler angle set.  The
quaternion, \f$\bar{\bf q}=[{\bf q}^{T}, q_{4}]^{T}\f$, can be determined from the Euler-axis parameters set
(\f$\hat{\bf e}\f$, \f$\Phi \f$) as follows:
\f[{\bf{q}} = \hat{\bf e}\sin \frac{\Phi}{2}\f]
\f[q_4  = \cos \frac{\Phi }{2}\f]
The quaternion representation has the useful characteristic that it should have unit length. Therefore, the quaternion can be normalized during computations to help accuracy, \f$\bar{\bf q}_{new}=\frac{\bar{\bf q}}{|\bar{\bf q}|}\f$. Also, the quaternion is not unique, but can also equal its negative \f$\bar{\bf q}=-\bar{\bf q}\f$.
*/
class Quaternion:public Vector
{
public:
    // QUATERNION CONSTRUCTORS
    Quaternion();

    Quaternion(double _q1, double _q2, double _q3, double _q4);

//    Quaternion(const Matrix& _qMatrix);

    Quaternion(const Vector& _qVector);

    Quaternion(const DirectionCosineMatrix& _DCM);

    Quaternion(const Vector& _EulerAngles, const int& _Sequence);

    Quaternion(const Vector& _EulerAxis, const Angle& _EulerAngle);

    Quaternion(const ModifiedRodriguezParameters& _MRP);

    // QUATERNION MUTATORS
    void Set(const Quaternion& _qIn);

    void Set(double _q1, double _q2, double _q3, double _q4);

//    void Set(const Matrix& _qMatrix);

    void Set(const Vector& _qVector);

    void Set(const DirectionCosineMatrix& _DCM);

    void Set(const Vector& _EulerAngles, const int& _Sequence);

    void Set(const Vector& _EulerAxis, const Angle& _EulerAngle);

    void Set(const ModifiedRodriguezParameters& _MRP);

    // QUATERNION INSPECTORS
    DirectionCosineMatrix GetDCM() const;

    Vector GetEulerAngles(const int& _Sequence) const;

    Vector GetEulerAxisAngle(Vector& _EulerAxis, Angle& _EulerAngle) const;

    Vector GetEulerAxisAngle() const;

    ModifiedRodriguezParameters GetMRP() const;

    // QUATERNION OPERATORS
    void Normalize();
    
    Quaternion operator+ (const Quaternion& _quat2) const;

    Quaternion operator- (const Quaternion& _quat2) const;

private:

};
// end of Quaternion

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \brief A generalized rotation class to represent any attitude coordinate transformation.
* \ingroup RotationLibrary
* \todo Write description of rotation class.
*
*
\par Examples:
It is very easy to setup and output rotations.  Note that to output a rotation you must first choose what attitude state to represent it in (you cannot "cout << MyRotation" directly:

\code
Rotation rotOB;
rotOB.Set(deg2rad(40),deg2rad(-10),deg2rad(0), 321); \\ setup a 321 rotation of euler angles with [40, -10, 0] deg
cout << rotOB.GetDCM();
\endcode

Successive Rotations:
\code
Rotation rotOB(quatOB); // create a rotation given the quaternion from Body to Orbital
Rotation rotIO(quatIO); // create a rotation given the quaternion from Orbital to Inertial
Rotation rotIB;
rotIB = rotIO * rotOB; // the successive rotation can be calculate by 'multiplying' the rotations
rotIB = rotIO + rotOB; // or by 'adding' them
\endcode
*
* Inverse Transformation:
\code
Rotation rotBI;
rotBI = ~rotIB; // determine the transformation from Inertial to Body from the inverse (transpose) of Body to Inertial
\endcode
*
* Relative Rotation:
\code
Rotation rotError;
rotError = rotTrue - rotActual; // determine the error rotation by taking the 'difference' between the two respective rotations
\endcode
* 
*/
class Rotation
{
public:
    // ROTATION CONSTRUCTORS
    Rotation();

    Rotation(const Matrix& _inMatrix);

    Rotation(const DirectionCosineMatrix& _DCM);

    Rotation(const Vector& _Angles, const int& _Sequence);

    Rotation(const Angle& _Angle1, const Angle& _Angle2, const Angle& _Angle3, const int& _Sequence);

    Rotation(const Vector& _Axis, const Angle& _Angle);

    Rotation(const ModifiedRodriguezParameters& _MRP);

    Rotation(const Quaternion& _quat);

     virtual ~Rotation();

    // ROTATION MUTATORS
    void Set(const Matrix& _inMatrix);

    void Set(const DirectionCosineMatrix& _DCM);

    void Set(const Vector& _Angles, const int& _Sequence);

    void Set(const Angle& _Angle1, const Angle& _Angle2, const Angle& _Angle3, const int& _Sequence);

    void Set(const Vector& _Axis, const Angle& _Angle);

    void Set(const ModifiedRodriguezParameters& _MRP);

    void Set(const Quaternion& _quat);

    // end of RotationMutators

    // ROTATION INSPECTORS
    DirectionCosineMatrix GetDCM() const;

    Vector GetEulerAngles(const int& _Sequence) const;

    Vector GetEulerAxisAngle(Vector& _EulerAxis, Angle& _EulerAngle) const;

    Vector GetEulerAxisAngle() const;
    
    ModifiedRodriguezParameters GetMRP() const;

    Quaternion GetQuaternion() const;

    Vector GetRotation(const RotationType& _type, const int& _Sequence = 123) const;
    
    // ROTATION OPERATORS
    Rotation Rotation::operator* (const Rotation& _rot2) const;

    Vector Rotation::operator* (const Vector& _vec) const;
    
    Rotation Rotation::operator~ () const;

    Rotation Rotation::operator+ (const Rotation& _rot2) const;

    Rotation Rotation::operator- (const Rotation& _rot2) const;
    // end of RotationOperators

private:
        /*! \brief internal representation of the attitude transformation.*/
        Quaternion m_quaternion;
        
        /*! \brief Handed-ness of the rotation, either LEFT_HANDED or RIGHT_HANDED */
        RotationSense m_RotationSense;

};
}

#endif 
/*!***************************************************************************
*	$Log: Rotation.h,v $
*	Revision 1.19  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.18  2003/08/24 20:59:13  nilspace
*	Updated.
*	
*	Revision 1.17  2003/05/22 03:03:38  nilspace
*	Update documentation, and changed all angles to use Angle type.
*	
*	Revision 1.16  2003/05/21 22:18:05  nilspace
*	Moved the documentation to the implementation file.
*	
*	Revision 1.15  2003/05/20 17:53:51  nilspace
*	Updated comments.
*	
*	Revision 1.14  2003/05/13 19:45:10  nilspace
*	Updated comments.
*	
*	Revision 1.13  2003/04/28 14:16:26  nilspace
*	Moved all function definitions out of header file into implementation file.
*	
*	Revision 1.12  2003/04/27 20:41:10  nilspace
*	Encapsulated the rotation library into the namespace O_SESSAME.
*	
*	Revision 1.11  2003/04/23 14:56:18  simpliciter
*	Clarified comments on quaternions (automatic normalization) and
*	outputting rotations (can't do it).
*	
*	Revision 1.10  2003/04/22 21:59:58  nilspace
*	Fixed Quaternion::Set(DCM) so it evaluates correctly.
*	Implemented Rotation::operator-()
*	
*	Revision 1.9  2003/04/22 19:36:03  nilspace
*	Various bug fixes to DCM & quaternion conversions. Added DirectionCosineMatrix Normalize().
*	
*	Revision 1.8  2003/04/22 16:03:11  nilspace
*	Updated MRP::Set(Quaternion) to correctly set.
*	
*	Revision 1.7  2003/04/10 17:25:52  nilspace
*	changelog
*	
*	Revision 1.6  2003/04/08 23:02:27  nilspace
*	Added Rotation Sense, or "Handedness". Defaults to RIGHT_HAND
*	
*	Revision 1.5  2003/03/27 20:22:27  nilspace
*	Added GetRotation() function.
*	Fixed Quaternion.Set(Quaternion) function.
*	Added RotationType enum.
*	Made sure to normalize the Quaternions for all the Set() functions.
*	
*	Revision 1.4  2003/03/25 02:37:36  nilspace
*	Added quaternion matrix set and constructor.
*	Added Rotation generalized matrix set to check for quaternion.
*	
*	Revision 1.3  2003/03/04 17:36:20  nilspace
*	Added CVS tags for documenting uploads. Also chmod'd to not be executable.
*	
*	Revision 1.1  2003/02/27 18:37:26  nilspace
*	Initial submission of Attitude class implementation.
*	
*
******************************************************************************/

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Rotation.cpp
*  \brief Implementation of Rotation Namespace Objects.
*  \brief Provides a set of functions to use Rotation matrices
*         and their various representations.
*  \author $Author: rsharo $
*  \version $Revision: 1.24 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  \warning Testing not complete
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Rotation.h"

namespace O_SESSAME {
/*! \brief Default Constructor.
    * \brief Create a Rotation with no offset.
    */
Rotation::Rotation() : m_RotationSense(RIGHT_HAND) { }

/*! \brief Default Destructor.
        */   
Rotation::~Rotation() { }

/*! \brief Create a Rotation from a direction cosine matrix.
    * @param _inMatrix 3x3 matrix of Direction Cosine Matrix (DCM) values.
    */
Rotation::Rotation(const Matrix& _inMatrix) { Set(_inMatrix); }

/*! \brief Create a Rotation from a direction cosine matrix.
        * @param _DCM instance of Direction Cosine Matrix (DCM) class.
        */
Rotation::Rotation(const DirectionCosineMatrix& _Matrix) { Set(_Matrix); }

/*! \brief Create a Rotation from an euler angle sequence.
        * @param _Angles 3x1 matrix of euler angles.
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
Rotation::Rotation(const Vector& _Angles, const int& _Sequence) { Set(_Angles, _Sequence); }

/*! \brief Create a Rotation from an euler angle sequence.
        * @param _Angle1 first angles in Euler angle set. [rad]
        * @param _Angle2 second angles in Euler angle set. [rad]
        * @param _Angle3 third angles in Euler angle set. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
Rotation::Rotation(const Angle& _Angle1, const Angle& _Angle2, const Angle& _Angle3, const int& _Sequence) { Set(_Angle1, _Angle2, _Angle3, _Sequence); }

/*! \brief Create a Rotation from a given euler axis and angle.
        * @param Axis 3x1 Euler Axis
        * @param Angle Angle rotation about axis [rad].
        */
Rotation::Rotation(const Vector& _Axis, const Angle& _Angle) { Set(_Axis, _Angle); }

/*! \brief Create a Rotation from a given set of Modified Rodriguez Parameters.
        * @param _MRP 3x1 MRP vector to be represented.
        */
Rotation::Rotation(const ModifiedRodriguezParameters& _MRP) { Set(_MRP); }

/*! \brief Create a Rotation from a given quaternion.
        * @param _quat 4x1 quaternion to be represented.
        */
Rotation::Rotation(const Quaternion& _quat) { Set(_quat); }

/*! \brief Set the Rotation from a converted DCM.
        * @param _inMatrix 3x3 matrix of Direction Cosine Matrix (DCM) values.
        */
void Rotation::Set(const Matrix& _inMatrix)
{/*! \todo Add testing for other types of matrix inputs */
    if((_inMatrix[MatrixRowsIndex].getIndexCount() == 3) && (_inMatrix[MatrixColsIndex].getIndexCount() == 3))
    {
        m_quaternion.Set(DirectionCosineMatrix(_inMatrix));
    }
    if((_inMatrix[MatrixRowsIndex].getIndexCount() == QUATERNION_SIZE) && (_inMatrix[MatrixColsIndex].getIndexCount() == 1))
    {
//        m_quaternion.Set(_inMatrix(_,MatrixIndexBase));
    }
    return;
}

    /*! \brief Set the Rotation from a converted DCM.
        * @param _DCM 3x3 matrix of Direction Cosine Matrix (DCM) values.
        */
void Rotation::Set(const DirectionCosineMatrix& _DCM)
{
    m_quaternion.Set(_DCM);
    return;
}

    /*! \brief Set the Rotation from an euler angle sequence.
        * @param _Angles 3x1 matrix of euler angles.
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
void Rotation::Set(const Vector& _Angles, const int& _Sequence)
{
    m_quaternion.Set(_Angles, _Sequence);
    return;
}

    /*! \brief Create a Rotation from an euler angle sequence.
        * @param _Angle1 first angles in Euler angle set. [rad]
        * @param _Angle2 second angles in Euler angle set. [rad]
        * @param _Angle3 third angles in Euler angle set. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
void Rotation::Set(const Angle& _Angle1, const Angle& _Angle2, const Angle& _Angle3, const int& _Sequence)
{
    m_quaternion.Set(_Angle1, _Angle2, _Angle3, _Sequence);
    return;
}

    /*! \brief Set the Rotation from a converted Euler Axis and Angle set.
        * @param _Axis 3x1 Euler Axis.
        * @param _Angle Angle rotation about axis [rad].
        */
void Rotation::Set(const Vector& _Axis, const Angle& _Angle)
{
    m_quaternion.Set(_Axis, _Angle);
    return;
}

    /*! \brief Set the Rotation from a converted vector of MRP.
        * @param _MRP 3x1 vector of Modified Rodriguez Parameters to set the Rotation.
        */
void Rotation::Set(const ModifiedRodriguezParameters& _MRP)
{
    m_quaternion.Set(_MRP);
    return;
}

    /*! \brief Set the Rotation from a converted quaternion.
        * @param _quat 4x1 quaternion to set the Rotation.
        */
void Rotation::Set(const Quaternion& _quat)
{
    m_quaternion(1) = _quat(1);
    m_quaternion(2) = _quat(2);
    m_quaternion(3) = _quat(3);
    m_quaternion(4) = _quat(4);
    return;
}

// Inspectors
    /*! \brief Return the Direction Cosine Matrix (DCM) form of the attitude transformation.
        * @return 3x3 Direction Cosine Matrix (DCM).
        */
DirectionCosineMatrix Rotation::GetDCM() const
{
    return DirectionCosineMatrix(m_quaternion);
}

    /*! \brief Return the Euler angles from the rotation representation.
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        * @return _Angles 3x1 matrix of euler angles.
        */
Vector Rotation::GetEulerAngles(const int& _Sequence) const
{
    return m_quaternion.GetEulerAngles(_Sequence);
}

    /*! \brief Return the Euler Axis and Angle form of the attitude transformation.
        * @return 4-element vector of the Euler Axis and Angle [EulerAxis; EulerAngle].
        */
Vector Rotation::GetEulerAxisAngle() const
{
    return m_quaternion.GetEulerAxisAngle();
}

    /*! \brief Return the Euler Axis and Angle form of the attitude transformation.
        * @param _EulerAxis 3x1 Euler Axis to be returned.
        * @param _EulerAngle Euler angle of rotation [rad].
        */
Vector Rotation::GetEulerAxisAngle(Vector& _EulerAxis, Angle& _EulerAngle) const
{
    return m_quaternion.GetEulerAxisAngle(_EulerAxis, _EulerAngle);
}

    /*! \brief Return the Modified Rodriguez Parameters vector form of the attitude transformation.
        * @return 3x1 MRP vector.
        */
ModifiedRodriguezParameters Rotation::GetMRP() const
{
    return ModifiedRodriguezParameters(m_quaternion);
}

    /*! \brief Return the quaternion form of the attitude transformation.
        * @return 4x1 quaternion.
        */
Quaternion Rotation::GetQuaternion() const
{
    return m_quaternion;
}

    /*! \brief Return the rotation based on the specified parameterization.
        * \todo completely document various rotation return types
        * @param _type rotation parameterization type to return the rotation representation in.
        * @param _Sequence for Euler Angle sets, specify the desired rotation sequence.
        * @return the rotation represented by the specified rotation.
        */
Vector Rotation::GetRotation(const RotationType& _type, const int& _Sequence) const
{
    if(_type == DCM_Type)
    {       
        Matrix tempMatrix = GetDCM();
        Vector tempVector(DCM_SIZE * DCM_SIZE);
        // convert the 3x3 matrix into a 9x1 vector, by rows.
        for (int ii = VectorIndexBase; ii < DCM_SIZE + VectorIndexBase; ++ii)
        {
            tempVector(_(VectorIndexBase + DCM_SIZE*(ii-VectorIndexBase),VectorIndexBase + DCM_SIZE*ii-1)) = ~tempMatrix(ii, _);
        }
        return tempVector;
    }
    else if(_type == EulerAngle_Type)
    {
        return GetEulerAngles(_Sequence);
    }
    else if(_type == EulerAxisAngle_Type)
    {
        return GetEulerAxisAngle();
    }
    else if(_type == MRP_Type)
    {
        return (Vector)GetMRP();
    }
    else if(_type == Quaternion_Type)
    {
        return (Vector)GetQuaternion();
    }
    
    // When in doubt, return the quaternion.
    return (Vector)GetQuaternion();
}

    /*! \brief Multiply the rotation matrices together to determine the successive rotation.
        * @return the successive rotation representation.
        */
Rotation Rotation::operator* (const Rotation& _rot2) const
{
    return Rotation((*this).GetDCM() * _rot2.GetDCM());
}
    /*! \brief Multiply the rotation by the Vector for a rotation.
        * @return 3x1 Rotated vector.
        */
Vector Rotation::operator* (const Vector& _vec2) const
{
    return ((*this).GetDCM() * _vec2);
}
    
    /*! \brief Take the inverse of the rotation matrix.
        * @return 3x3 Direction Cosine Matrix (DCM).
        */
Rotation Rotation::operator~ () const
{
    Rotation rotOut(~((*this).GetDCM()));
    return rotOut;
}
    /*! \brief Determine the successive rotation from the summation of two rotations.
        * @param _rot2 Rotation to be summed with.
        */
Rotation Rotation::operator+ (const Rotation& _rot2) const
{
    Rotation rotOut(this->operator*(_rot2));
    return rotOut;
}
    /*! \brief Determine the relative rotation from the difference of two rotations.
        *  \f$R^{31} = R^{32} * R^{21} \Rightarrow R^{32} = R^{31} - R^{21} = R^{32} * R^{21}^{T}/f$
        * @param _rot2 Rotation to be differenced with.
        * @return rotation of difference between given rotations.
        */
Rotation Rotation::operator- (const Rotation& _rot2) const
{
    Rotation rotOut(this->operator*(~_rot2));
    return rotOut;
}
//////////////////////////////////////////////////////////////////////////
// DirectionCosineMatrix Class
    /*! \brief Create a DCM equal to the identity matrix [1,0,0;0,1,0;0,0,1].
    *  @return 3x3 Direction Cosine Matrix equal to the identity matrix. 
    */
DirectionCosineMatrix::DirectionCosineMatrix():Matrix(DCM_SIZE, DCM_SIZE)
{
    (*this) = eye(DCM_SIZE);
}
    /*! \brief Create a copy of a DCM from an existing DCM.
    * @param _DCM 3x3 Direction Cosine Matrix to be copied.
    */
DirectionCosineMatrix::DirectionCosineMatrix(const DirectionCosineMatrix& _DCM):Matrix(DCM_SIZE, DCM_SIZE)
{
    Set(_DCM);
}
    /*! \brief Create a copy of a DCM from an existing matrix of DCM values.
        * @param _DCM 3x3 matrix of DCM values to be copied.
        */
DirectionCosineMatrix::DirectionCosineMatrix(const Matrix& _DCM):Matrix(DCM_SIZE, DCM_SIZE)
{
    Set(_DCM);
}

    /*! \brief Create a Direction Cosine Matrix (DCM) from Euler Angles.
        * @param _EulerAngles 3x1 matrix of Euler Angles. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
DirectionCosineMatrix::DirectionCosineMatrix(const Vector& _EulerAngles, const int& _Sequence):Matrix(DCM_SIZE, DCM_SIZE)
{	
    Set(_EulerAngles, _Sequence);
}

    /*! \brief Create a Direction Cosine Matrix (DCM) from Euler Angles.
        * @param _Angle1 first angles in Euler angle set. [rad]
        * @param _Angle2 second angles in Euler angle set. [rad]
        * @param _Angle3 third angles in Euler angle set. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
DirectionCosineMatrix::DirectionCosineMatrix(const Angle& _Angle1, const Angle& _Angle2, const Angle& _Angle3, const int& _Sequence):Matrix(DCM_SIZE, DCM_SIZE)
{	
    Set(_Angle1, _Angle2, _Angle3, _Sequence);
}

    /*! \brief Create a Direction Cosine Matrix (DCM) from an Euler Axis and rotation.
        * @param _EulerAxis 3x1 Euler Axis vector (\f$\hat{e}\f$).
        * @param _EulerAngle Angle rotation about axis (\f$\Phi\f$)[rad].
        */
DirectionCosineMatrix::DirectionCosineMatrix(const Vector& _EulerAxis, const Angle& _EulerAngle):Matrix(DCM_SIZE, DCM_SIZE)
{	
    Set(_EulerAxis, _EulerAngle);
}

    /*! \brief Create a Direction Cosine Matrix (DCM) from a vector of Modified Rodriguez Parameters (MRP).
        * @param _MRP 3x1 MRP to be converted.
        */
DirectionCosineMatrix::DirectionCosineMatrix(const ModifiedRodriguezParameters& _MRP):Matrix(DCM_SIZE, DCM_SIZE)
{	
    Set(_MRP);
}
    /*! \brief Create a Direction Cosine Matrix (DCM) from a quaternion.
        * @param _quat 4x1 quaternion to be converted.
        *  @return 3x3 Direction Cosine Matrix. 
        */
DirectionCosineMatrix::DirectionCosineMatrix(const Quaternion& _quat):Matrix(DCM_SIZE, DCM_SIZE)
{	
    Set(_quat);
}
    /*! \brief Default deconstructor. 
    */
DirectionCosineMatrix::~DirectionCosineMatrix() 
{
}

    /*! \brief Set a DCM to a copy of another DCM.
        * @param _DCM 3x3 DCM to be copied.
        */
void DirectionCosineMatrix::Set(const DirectionCosineMatrix& _DCM)
{
    for (int ii = MatrixIndexBase; ii <= _DCM[MatrixRowsIndex].getIndexBound(); ++ii)
        for (int jj = MatrixIndexBase; jj <= _DCM[MatrixColsIndex].getIndexBound(); ++jj)
            (*this)(ii,jj) = _DCM(ii,jj);
    Normalize();
    return;
}

    /*! \brief Set a DCM to a copy of an matrix that is a DCM.
        * @param _DCM 3x3 Matrix of DCM values to be copied.
        */
void DirectionCosineMatrix::Set(const Matrix& _DCM)
{
    for (int ii = MatrixIndexBase; ii <= _DCM[MatrixRowsIndex].getIndexBound(); ++ii)
        for (int jj = MatrixIndexBase; jj <= _DCM[MatrixColsIndex].getIndexBound(); ++jj)
            (*this)(ii,jj) = _DCM(ii,jj);
    Normalize();
    return;
}

    /*! \brief Set the DCM to the transformation of set of Euler Angles.
        * @param _EulerAngles 3x1 matrix of Euler Angles. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
void DirectionCosineMatrix::Set(const Vector& _EulerAngles, const int& _Sequence)
{
    Set(_EulerAngles(VectorIndexBase+0), _EulerAngles(VectorIndexBase+1), _EulerAngles(VectorIndexBase+2), _Sequence);
    return;
}

    /*! \brief Set the DCM to the transformation of set of Euler Angles.
        * @param _Angle1 first angles in Euler angle set. [rad]
        * @param _Angle2 second angles in Euler angle set. [rad]
        * @param _Angle3 third angles in Euler angle set. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
void DirectionCosineMatrix::Set(const Angle& _Angle1, const Angle& _Angle2, const Angle& _Angle3, const int& _Sequence)
{
    switch(_Sequence)
    {
        case 121: (*this) = R1(_Angle3) * R2(_Angle2) * R1(_Angle1); break;
        case 131: (*this) = R1(_Angle3) * R3(_Angle2) * R1(_Angle1); break;
        case 132: (*this) = R2(_Angle3) * R3(_Angle2) * R1(_Angle1); break;
        case 123: (*this) = R3(_Angle3) * R2(_Angle2) * R1(_Angle1); break;
        case 212: (*this) = R2(_Angle3) * R1(_Angle2) * R2(_Angle1); break;
        case 321: (*this) = R1(_Angle3) * R2(_Angle2) * R3(_Angle1); break;
        case 232: (*this) = R2(_Angle3) * R3(_Angle2) * R2(_Angle1); break;
        case 231: (*this) = R1(_Angle3) * R3(_Angle2) * R2(_Angle1); break;
        case 213: (*this) = R3(_Angle3) * R1(_Angle2) * R2(_Angle1); break;
        case 313: (*this) = R3(_Angle3) * R1(_Angle2) * R3(_Angle1); break;
        case 323: (*this) = R3(_Angle3) * R2(_Angle2) * R3(_Angle1); break;
        case 312: (*this) = R2(_Angle3) * R1(_Angle2) * R3(_Angle1); break;
        default: (*this) = eye(DCM_SIZE);
    }
    Normalize();
    return;
}

/*! \brief Set the DCM to the transformation of an Euler Axis and Angle.
        * @param _EulerAxis 3x1 Euler Axis vector (\f$\hat{e}\f$).
        * @param _EulerAngle Angle rotation about axis (\f$\Phi\f$)[rad].
        *
        * \par Equation: (Ref Wertz, pg. 413)
	* \f[
	* \bf{R}
	* =
	* \begin{bmatrix}
	* e^{2}_1 \Phi + \cos{\phi} & e_1 e_2 \Phi + e_3\sin{\phi} & e_1 e_3 \Phi - e_2\sin{\phi}\\
	* e_2 e_1 \Phi - e_3\sin{\phi} & e^{2}_2 \Phi + \cos{\phi} & e_2 e_3 \Phi + e_1\sin{\phi}\\
	* e_3 e_1 \Phi + e_2\sin{\phi} & e_3 e_2 \Phi - e_1\sin{\phi} & e^{2}_3 \Phi + \cos{\phi}
	* \end{bmatrix}
	* \f]
	* where \f$\Phi= 1 - \cos{\phi}\f$ (Ref Hughes p.12)
        */
void DirectionCosineMatrix::Set(const Vector& _EulerAxis, const Angle& _EulerAngle)
{
    // Calculations done for each element to increase speed
    double Phi = 1 - cos(_EulerAngle);
    double e1 = _EulerAxis(VectorIndexBase+0);
    double e2 = _EulerAxis(VectorIndexBase+1);
    double e3 = _EulerAxis(VectorIndexBase+2);
    double cosPhi = cos(_EulerAngle);
    double sinPhi = sin(_EulerAngle);
    
    // Column 1
    (*this)(MatrixIndexBase+0,MatrixIndexBase+0) = e1 * e1 * Phi + cosPhi;
    (*this)(MatrixIndexBase+1,MatrixIndexBase+0) = e2 * e1 * Phi - e3 * sinPhi;
    (*this)(MatrixIndexBase+2,MatrixIndexBase+0) = e3 * e1 * Phi + e2 * sinPhi;
        
    // Column 2
    (*this)(MatrixIndexBase+0,MatrixIndexBase+1) = e1 * e2 * Phi + e3 * sinPhi;
    (*this)(MatrixIndexBase+1,MatrixIndexBase+1) = e2 * e2 * Phi + cosPhi; 
    (*this)(MatrixIndexBase+2,MatrixIndexBase+1) = e3 * e2 * Phi - e1 * sinPhi;
    
    // Column 3
    (*this)(MatrixIndexBase+0,MatrixIndexBase+2) = e1 * e3 * Phi - e2 * sinPhi;
    (*this)(MatrixIndexBase+1,MatrixIndexBase+2) = e2 * e3 * Phi + e1 * sinPhi;
    (*this)(MatrixIndexBase+2,MatrixIndexBase+2) = e3 * e3 * Phi + cosPhi;
    Normalize();
    return;
}

/*! \brief Set the DCM to the transformation of Modified Rodriguez Paramaters (MRP).
        * @param _MRP 3x1 matrix of Modified Rodriguez Parameters (MRP).
        * \par Equation: 
        * \f[
        * \left[\bf{R}\left(\bf{\sigma}\right)\right]
        * =
        * \frac{1}{\left(1+\sigma^2\right)^2}
        * \begin{bmatrix}
        * 4\left(\sigma^{2}_1-\sigma^{2}_2-\sigma^{2}_3\right)+\Sigma^2 & 8\sigma_1\sigma_2+4\sigma_3\Sigma & 8\sigma_1\sigma_3-4\sigma_2\Sigma\\
        * 8\sigma_2\sigma_1-4\sigma_3\Sigma & 4\left(-\sigma^{2}_1+\sigma^{2}_2-\sigma^{2}_3\right)+\Sigma^2 & 8\sigma_2\sigma_3+4\sigma_1\Sigma
        * 8\sigma_3\sigma_1+4\sigma_2\Sigma & 8\sigma_3\sigma_2-4\sigma_1\Sigma & 4\left(-\sigma^{2}_1-\sigma^{2}_2+\sigma^{2}_3\right)+\Sigma^2
        * \end{bmatrix}
        * \f]
        * where \f$\Sigma=1-\bf{\sigma}^T\bf{\sigma}\f$
        */
void DirectionCosineMatrix::Set(const ModifiedRodriguezParameters& _MRP)
{
    // Calculations done for each element to increase speed
    Matrix tempMatrix = (~(_MRP) * _MRP);
    double Sigma = 1 - tempMatrix(MatrixIndexBase,MatrixIndexBase);
    double sigma1 = _MRP(VectorIndexBase+0);
    double sigma2 = _MRP(VectorIndexBase+1);
    double sigma3 = _MRP(VectorIndexBase+2);
    
    // Column 1
    (*this)(MatrixIndexBase+0,MatrixIndexBase+0) = 4*(sigma1*sigma1 - sigma2*sigma2 - sigma3*sigma3) + Sigma*Sigma;
    (*this)(MatrixIndexBase+1,MatrixIndexBase+0) = 8*sigma2*sigma1 - 4*sigma3*Sigma;
    (*this)(MatrixIndexBase+2,MatrixIndexBase+0) = 8*sigma3*sigma1 + 4*sigma2*Sigma;
    
    // Column 2
    (*this)(MatrixIndexBase+0,MatrixIndexBase+1) = 8*sigma1*sigma2 + 4*sigma3*Sigma;
    (*this)(MatrixIndexBase+1,MatrixIndexBase+1) = 4*(-sigma1*sigma1 + sigma2*sigma2 - sigma3*sigma3) + Sigma*Sigma;
    (*this)(MatrixIndexBase+2,MatrixIndexBase+1) = 8*sigma3*sigma2 - 4*sigma1*Sigma;
    
    // Column 3
    (*this)(MatrixIndexBase+0,MatrixIndexBase+2) = 8*sigma1*sigma3 - 4*sigma2 * Sigma;
    (*this)(MatrixIndexBase+1,MatrixIndexBase+2) = 8*sigma2*sigma3 + 4*sigma1*Sigma;
    (*this)(MatrixIndexBase+2,MatrixIndexBase+2) = 4*(-sigma1*sigma1 - sigma2*sigma2 + sigma3*sigma3) + Sigma*Sigma;

    // Multiplying factor
    (*this) /= pow(1 + tempMatrix(MatrixIndexBase,MatrixIndexBase), 2);
    Normalize();
    return;
}

/*! \brief Set a DCM to the transformation of a quaternion.
        * \par Equation: 
        * @param _qIn 4x1 quaternion to be converted.
        * \par Equation: (Ref Wertz, pg. 414)
        * \f[
        * \left[\bf{R}\left(\bf{\bar{q}}\right)\right]
        * =
        * \begin{bmatrix}
        * 1-2(q_{2}^{2}+q_{3}^{2}) & 2\left(q_1 q_2 + q_4 q_3\right) & 2\left(q_1 q_3 - q_4 q_2\right)\\
        * 2\left(q_1 q_2 - q_4 q_3\right) & 1-2(q_{1}^{2}+q_{3}^{2}) & 2\left(q_2 q_3 + q_4 q_1\right)\\
        * 2\left(q_1 q_3 + q_4 q_2\right) & 2\left(q_2 q_3 - q_4 q_1\right) & 1-2(q_{1}^{2}+q_{2}^{2})
        * \end{bmatrix}
        * \f]
        */
void DirectionCosineMatrix::Set(const Quaternion& _qIn)
{
    // Calculations done for each element to increase speed
    double q1 = _qIn(VectorIndexBase+0);
    double q2 = _qIn(VectorIndexBase+1);
    double q3 = _qIn(VectorIndexBase+2);
    double q4 = _qIn(VectorIndexBase+3);

    // Column 1
    (*this)(MatrixIndexBase+0,MatrixIndexBase+0) = q4*q4 + q1*q1 - q2*q2 - q3*q3;
//    (*this)(MatrixIndexBase+0,MatrixIndexBase+0) = 1 - 2 * (q2*q2 + q3*q3);
    (*this)(MatrixIndexBase+1,MatrixIndexBase+0) = 2 * (q1*q2 - q4*q3);
    (*this)(MatrixIndexBase+2,MatrixIndexBase+0) = 2 * (q1*q3 + q4*q2);
    
    // Column 2
    (*this)(MatrixIndexBase+0,MatrixIndexBase+1) = 2 * (q1*q2 + q4*q3);
    (*this)(MatrixIndexBase+1,MatrixIndexBase+1) = q4*q4 - q1*q1 + q2*q2 -q3*q3;
//    (*this)(MatrixIndexBase+0,MatrixIndexBase+0) = 1 - 2 * (q1*q1 + q3*q3);
    (*this)(MatrixIndexBase+2,MatrixIndexBase+1) = 2 * (q2*q3 - q4*q1);
    
    // Column 3
    (*this)(MatrixIndexBase+0,MatrixIndexBase+2) = 2 * (q1*q3 - q4*q2);
    (*this)(MatrixIndexBase+1,MatrixIndexBase+2) = 2 * (q2*q3 + q4*q1);
//    (*this)(MatrixIndexBase+0,MatrixIndexBase+0) = 1 - 2 * (q1*q1 + q2*q2);
    (*this)(MatrixIndexBase+2,MatrixIndexBase+2) = q4*q4 - q1*q1 - q2*q2 + q3*q3; 
    
    Normalize();
    return;
}

    /*! 
        * \brief Convert a DCM to a set of Euler Angles.
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        * @return (3 x 1) Euler Angles based on given rotation sequence. 
        */
Vector DirectionCosineMatrix::GetEulerAngles(const int& _Sequence) const
{
    /*! \todo Implement DCM::GetEulerAngles function */
    return Vector(EULERANGLES_SIZE);
}

/*! \brief Convert the DCM to an Euler Axis and Angle.
        * @param _EulerAxis 3x1 Euler Axis vector (\f$\hat{e}\f$).
        * @param _EulerAngle Angle rotation about axis (\f$\Phi\f$)[rad].
        * \par Equation: 
        * Ref Wertz, pg 413-4
        * \f[ \cos\Phi = \frac{1}{2}\left[tr\left(R\right)-1\right] \f]
        * if \f$\sin\Phi \ne 0\f$, the componnets of \f$\hat{\bf e}\f$ are given by:
        * \f[
        * e1 = (A_{23} - A_{32})/(2\sin\Phi)
        * e2 = (A_{31} - A_{13})/(2\sin\Phi)
        * e3 = (A_{12} - A_{21})/(2\sin\Phi)
        * \f]
        */
void DirectionCosineMatrix::GetEulerAxisAngle(Vector& _EulerAxis, Angle& _EulerAngle) const
{
    _EulerAngle = acos(0.5 * (trace(*this) - 1));
    if(sin(_EulerAngle) != 0)
    {
        _EulerAxis(VectorIndexBase + 0) = ((*this)(MatrixIndexBase+1,MatrixIndexBase+2)
                                           - (*this)(MatrixIndexBase+1,MatrixIndexBase+2))
        / (2 * sin(_EulerAngle));
        _EulerAxis(VectorIndexBase + 1) = ((*this)(MatrixIndexBase+2,MatrixIndexBase+0)
                                           - (*this)(MatrixIndexBase+0,MatrixIndexBase+2))
            / (2 * sin(_EulerAngle));
        _EulerAxis(VectorIndexBase + 2) = ((*this)(MatrixIndexBase+0,MatrixIndexBase+1)
                                           - (*this)(MatrixIndexBase+0,MatrixIndexBase+1))
            / (2 * sin(_EulerAngle));
    }
    else
    { // no rotation, or rotation of 180 degs, therefore arbitrary axis.
        _EulerAxis.setToValue(0.0);
        _EulerAxis(VectorIndexBase + 0) = 1;
    }
    return;
}

/*! \brief Convert a DCM to an MRP representation.
        * This conversion is performed by creating a new instance of an MRP
        *	from this DCM. (\sa ModifiedRodriguezParameters::Set(DirectionCosineMatrix))
        * @return This conversion returns a (3 x 1) converted MRP. 
        */
ModifiedRodriguezParameters DirectionCosineMatrix::GetMRP() const
{
    return ModifiedRodriguezParameters(*this);
}

/*! \brief Convert a DCM to a quaternion representation.
        * This conversion is performed by creating a new instance of a Quaternion
        *	from this DCM. (\sa Quaternion::Set(DirectionCosineMatrix))
        *  @return This conversion returns a (4 x 1) converted quaternion. 
        */
Quaternion DirectionCosineMatrix::GetQuaternion() const
{
    return Quaternion(*this);
}

/*! \brief Normalize the Direction Cosine Matrix.
        *  This member function normalizes and stores the DCM. Normalization is performed 
        *	by dividing each element in a column by the square-root of the sum of the squares of a column.
        *	\f[R_{ij}^{norm} = \frac{R_{ij}}{\sum_{k=1}^{k=3}{R_{ik}}}\f] 
        */
void DirectionCosineMatrix::Normalize()
{
    double total = 0;
    
    for (int ii = MatrixIndexBase; ii < MatrixIndexBase + DCM_SIZE; ++ii)
    {
        total = sqrt(pow((*this)(ii, MatrixIndexBase),2) 
                        + pow((*this)(ii, MatrixIndexBase+1),2) 
                        + pow((*this)(ii, MatrixIndexBase+2),2));
        for (int jj = MatrixIndexBase; jj < MatrixIndexBase + DCM_SIZE; ++jj)
        {
            (*this)(ii, jj) /= total;
        }
    }    
    return;
}

    /*! \brief Determine the successive rotation from the summation of two DCMs.
        * @param _DCM2 DCM to be summed with.
        */
DirectionCosineMatrix DirectionCosineMatrix::operator+ (const DirectionCosineMatrix& _DCM2) const
{
    return DirectionCosineMatrix(Matrix::operator+(static_cast<Matrix>(_DCM2)));
}

    /*! 
        * \brief Determine the relative rotation from the difference of two DCMs.
        * @param _DCM2 DCM to be differenced with.
        */
DirectionCosineMatrix DirectionCosineMatrix::operator- (const DirectionCosineMatrix& _DCM2) const
{
    return DirectionCosineMatrix(Matrix::operator-(static_cast<Matrix>(_DCM2)));
}

/*! \brief Determine the successive rotation of the DCMs through multiplication.
        * @param _DCM2 DCM to be multiplied by.
        */
DirectionCosineMatrix DirectionCosineMatrix::operator* (DirectionCosineMatrix _DCM2) const 
{
    return DirectionCosineMatrix(Matrix::operator*(static_cast<Matrix>(_DCM2)));
}

    /*! \brief Determine the rotation of a vector by a DCM.
        * @param _DCM2 DCM to be multiplied by.
        */
inline Vector DirectionCosineMatrix::operator* (const Vector& _vec) const 
{
    return Matrix::operator*(_vec);
}

    /*! \brief Determines the inverse of a DCM by taking the transpose (same operation).
        * @return Inverse (transpose) of DCM.
        */
DirectionCosineMatrix DirectionCosineMatrix::operator~ () 
{
    return DirectionCosineMatrix(Matrix::operator~());
}

/*! \brief Calculates the principal rotation of the angle about the 1-axis.
    * \relates DirectionCosineMatrix
    * \ingroup RotationLibrary
    * @param _Angle Angle of Rotation [rad].
    *  \par Equation:
    * \f[
    * R_1\left(\theta\right) =
    * \begin{bmatrix}
    * 1 & 0 & 0\\
    * 0 & \cos{\theta} & \sin{\theta}\\
    * 0 & -\sin{\theta} & \cos{\theta}
    * \end{bmatrix}
    * \f]
    */
DirectionCosineMatrix R1(const Angle& _Angle)
{
    DirectionCosineMatrix R1_Out;
    R1_Out(MatrixIndexBase+1, MatrixIndexBase+1) = cos(_Angle);
    R1_Out(MatrixIndexBase+1, MatrixIndexBase+2) = sin(_Angle);
    R1_Out(MatrixIndexBase+2, MatrixIndexBase+1) = -sin(_Angle);
    R1_Out(MatrixIndexBase+2, MatrixIndexBase+2) = cos(_Angle);
    return R1_Out;
}

/*! \brief Calculates the principal rotation of the angle about the 2-axis.
    * \relates DirectionCosineMatrix
    * \ingroup RotationLibrary
    * @param _Angle Angle of Rotation [rad].
    * \par Equation:
    * \f[
    * R_2\left(\theta\right) =
    * \begin{bmatrix}
    * \cos{\theta} & 0 & -\sin{\theta}\\
    * 0 & 1 & 0\\
    * \sin{\theta} & 0 & \cos{\theta}
    * \end{bmatrix}
    * \f]
    */
DirectionCosineMatrix R2(const Angle& _Angle)
{
    DirectionCosineMatrix R2_Out;
    R2_Out(MatrixIndexBase+0, MatrixIndexBase+0) = cos(_Angle);
    R2_Out(MatrixIndexBase+0, MatrixIndexBase+2) = -sin(_Angle);
    R2_Out(MatrixIndexBase+2, MatrixIndexBase+0) = sin(_Angle);
    R2_Out(MatrixIndexBase+2, MatrixIndexBase+2) = cos(_Angle);
    return R2_Out;
}

/*! \brief Calculates the principal rotation of the angle about the 3-axis.
    * \relates DirectionCosineMatrix
    * \ingroup RotationLibrary
    * @param _Angle Angle of Rotation [rad].
    * \par Equation:
    * \f[
    * R_3\left(\theta\right) =
    * \begin{bmatrix}
    * \cos{\theta} & \sin{\theta} & 0\\
    * -\sin{\theta} & \cos{\theta} & 0\\
    * 0 & 0 & 1
    * \end{bmatrix}
    * \f]
    */
DirectionCosineMatrix R3(const Angle& _Angle)
{
    DirectionCosineMatrix R3_Out;
    R3_Out(MatrixIndexBase+0, MatrixIndexBase+0) = cos(_Angle);
    R3_Out(MatrixIndexBase+0, MatrixIndexBase+1) = sin(_Angle);
    R3_Out(MatrixIndexBase+1, MatrixIndexBase+0) = -sin(_Angle);
    R3_Out(MatrixIndexBase+1, MatrixIndexBase+1) = cos(_Angle);
    return R3_Out;
}

//////////////////////////////////////////////////////////////////////////
// ModifiedRodriguezParameters Class
    /*! \brief Default Constructor.
    * \brief Create an MRP set with intial value of [0,0,0]^T.
    */
ModifiedRodriguezParameters::ModifiedRodriguezParameters():Vector(MRP_SIZE)
{
    AutoSwitch();
}

    /*! \brief Copy Constructor.
    * \brief Create a copy of an MRP set.
    */
ModifiedRodriguezParameters::ModifiedRodriguezParameters(const ModifiedRodriguezParameters& _MRP):Vector(MRP_SIZE)
{
    Set(_MRP);
    AutoSwitch();
}

    /*! \brief Create an MRP set based on 3 values.
    * @param _s1 first MRP value.
    * @param _s2 second MRP value.
    * @param _s3 third MRP value.
    */
ModifiedRodriguezParameters::ModifiedRodriguezParameters(const double& _s1, const double& _s2, const double& _s3):Vector(MRP_SIZE)
{
    Set(_s1,_s2,_s3);
    AutoSwitch();
}
    
    /*! \brief Create an MRP set from a vector 3 values.
        * @param _sVector 3x1 vector of MRP values.
        */
ModifiedRodriguezParameters::ModifiedRodriguezParameters(const Vector& _sVector):Vector(MRP_SIZE)
{
    Set(_sVector);
    AutoSwitch();
}

    /*! \brief Create an MRP set converted from a Direction Cosine Matrix (DCM).
        * @param _DCM 3x3 Direction Cosine Matrix (DCM) to be converted.
        */
ModifiedRodriguezParameters::ModifiedRodriguezParameters(const DirectionCosineMatrix& _DCM):Vector(MRP_SIZE)
{
    Set(_DCM);
    AutoSwitch();
}

    /*! \brief Create an MRP set from an Euler Angle sequence.
        * @param _Angles 3x1 matrix of euler angles. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
ModifiedRodriguezParameters::ModifiedRodriguezParameters(const Vector& _Angles, const int& _Sequence):Vector(MRP_SIZE)
{
    Set(_Angles, _Sequence);
    AutoSwitch();
}

    /*! 
        * \brief Create the MRP from an Euler Axis and Angle.
        * @param _EulerAxis 3x1 Euler Axis vector (\f$\hat{e}\f$).
        * @param _EulerAngle Angle rotation about axis (\f$\Phi\f$)[rad].
        */
ModifiedRodriguezParameters::ModifiedRodriguezParameters(const Vector& _EulerAxis, const Angle& _EulerAngle):Vector(MRP_SIZE)
{
    Set(_EulerAxis, _EulerAngle);
    AutoSwitch();
}
    
    /*! \brief Create an MRP set converted from a quaternion.
        * @param _DCM 4x1 quaternion to be converted.
        */
ModifiedRodriguezParameters::ModifiedRodriguezParameters(const Quaternion& _qIn):Vector(MRP_SIZE)
{
    Set(_qIn);
    AutoSwitch();
}

    /*! \brief Set the MRP to the copy of an existing MRP vector
        * @param _MRP MRP Vector to be copied
        */
void ModifiedRodriguezParameters::Set(const ModifiedRodriguezParameters& _MRP)
{
    for(int ii = VectorIndexBase;ii < VectorIndexBase + MRP_SIZE; ++ii)
        (*this)(ii) = _MRP(ii);
    return;
}
    
    /*! \brief Set the MRP vector based on 3 values.
        * @param _s1 first MRP value.
        * @param _s2 second MRP value.
        * @param _s3 third MRP value.
        */
void ModifiedRodriguezParameters::Set(const double& _s1, const double& _s2, const double& _s3)
{
    (*this)(VectorIndexBase+0) = _s1;
    (*this)(VectorIndexBase+1) = _s2;
    (*this)(VectorIndexBase+2) = _s3;
    return;
}

    /*! \brief Set the MRP set from a vector 3 values.
        * @param _sVector 3x1 vector of MRP values.
        */
void ModifiedRodriguezParameters::Set(const Vector& _sVector)
{
    for(int ii = VectorIndexBase;ii < VectorIndexBase + MRP_SIZE; ++ii)
        (*this)(ii) = _sVector(ii);
    return;
}
    
    /*! \brief Set the MRP from a converted Direction Cosine Matrix (DCM).
        * @param _DCM 3x3 Direction Cosine Matrix (DCM) to be converted
        */
void ModifiedRodriguezParameters::Set(const DirectionCosineMatrix& _DCM)
{
    Set(_DCM.GetQuaternion());
    return;
}

    /*! \brief Set the MRP from the transformation of set of Euler Angles.
        * @param _EulerAngles 3x1 matrix of Euler Angles. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
void ModifiedRodriguezParameters::Set(const Vector& _EulerAngles, const int& _Sequence)
{
    /*! \todo Change implementation to calculate directly from Euler angles and not create a DCM? */
    Set(DirectionCosineMatrix(_EulerAngles, _Sequence));
    return;
}

    /*! \brief Set the MRP from the transformation of set of Euler Angles.
        * @param _Angle1 first angles in Euler angle set. [rad]
        * @param _Angle2 second angles in Euler angle set. [rad]
        * @param _Angle3 third angles in Euler angle set. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
void ModifiedRodriguezParameters::Set(const Angle& _Angle1, const Angle& _Angle2, const Angle& _Angle3, const int& _Sequence)
{
    /*! \todo Fix Change implementation to calculate directly from Euler angles and not create a DCM? */
    Set(DirectionCosineMatrix(_Angle1, _Angle2, _Angle3, _Sequence));
    return;
}


    /*! \brief Set the MRP from the transformation of an Euler Axis and Angle.
        * @param _EulerAxis 3x1 Euler Axis vector (\f$\hat{e}\f$).
        * @param _EulerAngle Angle rotation about axis (\f$\Phi\f$)[rad].
        * \par Equation: 
        * \f[ \bf{\sigma} = \tan{\frac{\phi}{4}}\bf{\hat{e}} \f] (Ref Schaub99)
        * singluar whenever \f$\phi \rightarrow \pm 360^{\circ}\f$
        */
void ModifiedRodriguezParameters::Set(const Vector& _EulerAxis, const Angle& _EulerAngle)
{
    (*this) = (ModifiedRodriguezParameters) (tan(0.25 * _EulerAngle) * _EulerAxis);
    return;
}

    
    /*! \brief Set the MRPs from a converted quaternion.
        * @param _qIN 4x1 quaternion to be converted
        * \par Equation: 
        * \f[\sigma_i = \frac{\bf{q}_i}{1+q_4}\f] for i=1,2,3 (Ref Schaub99)
        * 	if q4 = -1, then q = -q. (prevent singularity)
        */
void ModifiedRodriguezParameters::Set(const Quaternion& _qIN)
{
    double denom = (1+_qIN(VectorIndexBase+3));
    if(denom == 0)
    {
        denom = 2;
        (*this)(1) = (-_qIN(1) / denom);
        (*this)(2) = (-_qIN(2) / denom);
        (*this)(3) = (-_qIN(3) / denom);
    }
    else
    {
        (*this)(1) = (_qIN(1) / denom);
        (*this)(2) = (_qIN(2) / denom);
        (*this)(3) = (_qIN(3) / denom);
    }
    return;
}

    /*! \brief Convert the MRP vector to a Direction Cosine Matrix (DCM).
        * @return 3x3 Direction Cosine Matrix.
        */
DirectionCosineMatrix ModifiedRodriguezParameters::GetDCM() const
{
    return DirectionCosineMatrix(*this);
}

    /*! \brief Convert the MRP vector to a set of Euler Angles.
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        * @return 3x1 vector of euler angles.
        */
Vector ModifiedRodriguezParameters::GetEulerAngles(int _Sequence) const
{
    /*! \todo Implement ModifiedRodriguezParameters::GetEulerAngles Function */
    return Vector(MRP_SIZE);
}

    /*! \brief Convert the MRP vector to the Euler Axis and Angle set.
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        * @return 3x1 vector of euler angles.
        */
void ModifiedRodriguezParameters::GetEulerAxisAngle(Vector& _EulerAxis, Angle& _EulerAngle) const
{
    /*! \todo Implement to directly convert and not use a temporary quaternion */
    Quaternion qTemp(*this);
    qTemp.GetEulerAxisAngle(_EulerAxis, _EulerAngle);
    return;
}
    
    /*! \brief Convert the MRP vector to a quaternion.
        * @return 4x1 quaternion.
        */
Quaternion ModifiedRodriguezParameters::GetQuaternion() const
{
    return Quaternion(*this);
}
    
    /*! \brief Switches the MRP vector to the shortest rotational distance back to the origin
        *	using the shadow set if the magnitude of the vector is greater than the input value S.
        * @param _SwitchThreshold magnitude of the MRP vector at which the set is switched. A positive scalar number.
        */
void ModifiedRodriguezParameters::Switch(int _SwitchThreshold)
{
    if (norm2((Vector)*this) > _SwitchThreshold)
        (*this) = ShadowSet();
    return;
}

    /*! \brief Sets the MRP set to automatically switch between the normal set and the shadow set
        * 	based on the shortest rotational distance to the origin.
        * @param _SwitchBoolean boolean value where TRUE turns on switching, and FALSE turns off switching.
        */
void ModifiedRodriguezParameters::AutoSwitch(bool _SwitchBoolean)
{
    m_AutoSwitch = _SwitchBoolean;
    return;
}


    /*! \brief Calculates and returns the MRP shadow set.
        * @return MRP shadow set (3x1).
        * \par Equation: 
        * The equation for computer the MRP shadow set is:
        * \f[ \bf{\sigma}^{S} = - \frac{1}{|\bf{\sigma}|^2}\bf{\sigma} \f] 
        * (Ref Schaub99)
        */
ModifiedRodriguezParameters ModifiedRodriguezParameters::ShadowSet() const
{
    return (ModifiedRodriguezParameters)(-(*this)(_) / pow(norm2(*this),2));
}


    /*! \brief Determine the successive rotation from the summation of two MRP vectors.
        * @param _MRP2 MRP vector to be summed with.
        * \par Equation: 
        * Summing two MRP vectors \f$\bf{\sigma'}\f$ and \f$\bf{\sigma''}\f$:
        * \f[
        * \bf{\sigma} = \frac{(1-|\bf{\sigma'}|^2)\bf{\sigma''}+(1-|\bf{\sigma''}|^2)\bf{\sigma'}-2\bf{\sigma''} \times \bf{\sigma'}}{1+|\bf{\sigma'}|^2|\bf{\sigma''}|^2-2\bf{\sigma'} \dot \bf{\sigma''}}
        * \f]
        */
ModifiedRodriguezParameters ModifiedRodriguezParameters::operator+ (const ModifiedRodriguezParameters& _MRP2) const
{
    ModifiedRodriguezParameters MRPsum;
    MRPsum(_) = (1-pow(norm2(*this),2)) * _MRP2
        + (1-pow(norm2(_MRP2),2)) * (*this)
              - 2*crossP(_MRP2,(*this));
    MRPsum(_) = MRPsum / (1 + pow(norm2(*this),2) * pow(norm2(_MRP2),2)
        - 2 * (*this).dot( _MRP2));
    return MRPsum;
}


    /*! \brief Determine the relative rotation from the difference of two MRP vectors.
        * @param _MRP2 MRP vector to be differenced with.
        * \par Equation: 
        * Relative MRP vector \f$\bf{\sigma''} = \bf{\sigma} - \bf{\sigma'}\f$ (Ref Schaub99):
        * \f[
        * \bf{\sigma''} = \frac{\left(1-\left|\bf{\sigma'}\right|^2\right)\bf{\sigma}-\left(1-\left|\bf{\sigma}\right|^2\right)\bf{\sigma'}+2\bf{\sigma} \times \bf{\sigma'}}{1+\left|\bf{\sigma'}\right|^2\left|\bf{\sigma}\right|^2+2\bf{\sigma'} \dot \bf{\sigma}}
        * \f]
        */
ModifiedRodriguezParameters ModifiedRodriguezParameters::operator- (const ModifiedRodriguezParameters& _MRP2) const
{
    ModifiedRodriguezParameters MRPsum;
    MRPsum(_) = (1-pow(norm2(_MRP2),2)) * (*this)
        + (1-pow(norm2(*this),2)) * _MRP2
        - 2*crossP((*this), _MRP2);
    MRPsum(_) = MRPsum / ((1 + pow(norm2(_MRP2),2)) * pow(norm2(*this),2)
                        - 2 * _MRP2.dot(*this));
    return MRPsum;
}

//////////////////////////////////////////////////////////////////////////
// Quaternion Class
    /*! \brief Create a quaternion with initial value of [0,0,0,1]^T.
    *  @return (double)  - (4 x 1) quaternion = [0,0,0,1]^T. 
    */
Quaternion::Quaternion():Vector(QUATERNION_SIZE)
{
//    (*this).setToValue(0.0);
    (*this)(VectorIndexBase+3) = 1.0;	
}

    /*! \brief Create a quaternion with initial values; will be normalized to a unit quaternion automatically.
    * @param _q1 first quaternion parameter
    * @param _q2 second quaternion parameter
    * @param _q3 third quaternion parameter
    * @param _q4 fourth quaternion parameter
    *  @return (double)  - (4 x 1) quaternion = [_q1,_q2,_q3,_q4]^T. 
    */
Quaternion::Quaternion(double _q1, double _q2, double _q3, double _q4):Vector(QUATERNION_SIZE)
{
    Set(_q1, _q2, _q3, _q4);
}

    /*! \brief Create a quaternion with initial value of the input 4x1 matrix.
        * @param _qMatrix 4x1 matrix of quaternion elements.
        *  @return (double)  - (4 x 1) quaternion. 
        */
/*
Quaternion::Quaternion(const Matrix& _qMatrix):Vector(QUATERNION_SIZE)
{
    Set(_qMatrix);
}
*/

    /*! 
        * \brief Create a quaternion with initial value of the input 4x1 vector; will be normalized to a unit quaternion automatically.
        * @param _qMatrix 4x1 vector of quaternion elements.
        *  @return (double)  - (4 x 1) quaternion. 
        */
Quaternion::Quaternion(const Vector& _qVector):Vector(QUATERNION_SIZE)
{
    Set(_qVector);
}

    /*! 
        * \brief Create a quaternion from a direction cosine matrix (DCM).
        * @param _DCM 3x3 Direction Cosine Matrix to be transformed.
        *  @return (double)  - (4 x 1) quaternion. 
        */
Quaternion::Quaternion(const DirectionCosineMatrix& _DCM):Vector(QUATERNION_SIZE)
{
    Set(_DCM);
}

    /*! \brief Create a quaternion from a set of Euler Angles and Sequence.
        * @param _EulerAngles 3x1 matrix of Euler Angles. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
Quaternion::Quaternion(const Vector& _EulerAngles, const int& _Sequence):Vector(QUATERNION_SIZE)
{
    Set(_EulerAngles, _Sequence);
    Normalize();
}

    /*! \brief Create a quaternion from the transformation about an Euler Axis by a set angle.
        * @param _EulerAxis 3x1 Euler Axis vector.
        * @param _EulerAngle Angle rotation about axis [rad].
        */
Quaternion::Quaternion(const Vector& _EulerAxis, const Angle& _EulerAngle):Vector(QUATERNION_SIZE)
{
    Set(_EulerAxis, _EulerAngle);
}

    /*! \brief Create a Quaternion from the transformation of Modified Rodriguez Paramaters (MRP).
        * @param _MRP 3x1 matrix of Modified Rodriguez Parameters (MRP).
        */
Quaternion::Quaternion(const ModifiedRodriguezParameters& _MRP):Vector(QUATERNION_SIZE)
{
    Set(static_cast<ModifiedRodriguezParameters>(_MRP));
}

    /*! \brief Set the quaternion to a copy of another quaternion.
        * @param _qIn Quaternion to be copied.
        */
void Quaternion::Set(const Quaternion& _qIn)
{
    (*this)(VectorIndexBase+0) = _qIn(MatrixIndexBase+0);	
    (*this)(VectorIndexBase+1) = _qIn(MatrixIndexBase+1);	
    (*this)(VectorIndexBase+2) = _qIn(MatrixIndexBase+2);	
    (*this)(VectorIndexBase+3) = _qIn(MatrixIndexBase+3);
    Normalize();
    return;
}

    /*! \brief Sets the quaternion to the values specified.
        * @param _q1 first quaternin parameter
        * @param _q2 second quaternin parameter
        * @param _q3 third quaternin parameter
        * @param _q4 fourth quaternin parameter
        */
void Quaternion::Set(double _q1, double _q2, double _q3, double _q4)
{
    (*this)(VectorIndexBase+0) = _q1;	
    (*this)(VectorIndexBase+1) = _q2;	
    (*this)(VectorIndexBase+2) = _q3;	
    (*this)(VectorIndexBase+3) = _q4;	
    Normalize();
    return;
}

    /*! \brief Sets the quaternion with the values of the input 4x1 matrix.
        * @param _qMatrix 4x1 matrix of quaternion elements.
        */
/*
void Quaternion::Set(const Matrix& _qMatrix)
{
    if((_qMatrix[MatrixRowsIndex].getIndexBound() == QUATERNION_SIZE) && (_qMatrix[MatrixColsIndex].getIndexBound() == 1)) 
    {
	(*this)(VectorIndexBase+0) = _qMatrix(MatrixIndexBase+0,MatrixIndexBase);	
	(*this)(VectorIndexBase+1) = _qMatrix(MatrixIndexBase+1,MatrixIndexBase);	
	(*this)(VectorIndexBase+2) = _qMatrix(MatrixIndexBase+2,MatrixIndexBase);	
	(*this)(VectorIndexBase+3) = _qMatrix(MatrixIndexBase+3,MatrixIndexBase);
    }
    else
    {
	(*this) = Quaternion();
    }
    return;
}*/
    
    /*! \brief Sets the quaternion with the values of the input 4x1 vector.
        * @param _qMatrix 4x1 vector of quaternion elements.
        */
void Quaternion::Set(const Vector& _qVector)
{
    (*this)(VectorIndexBase+0) = _qVector(MatrixIndexBase+0);	
    (*this)(VectorIndexBase+1) = _qVector(MatrixIndexBase+1);	
    (*this)(VectorIndexBase+2) = _qVector(MatrixIndexBase+2);	
    (*this)(VectorIndexBase+3) = _qVector(MatrixIndexBase+3);
    Normalize();
    return;
}


/*! \brief Sets the current quaternion from a converted Direction Cosine Matrix (DCM).
    * @param _DCM 3x3 DCM to be converted.
    * \par Equation: 
    * Ref Hughes p. 18
    * \f[q_4 = \pm \frac{1}{2}\left(1+R_{11}+R_{22}+R_{33}\right)^{\frac{1}{2}}\f]
    * \f[
    * \bf{q} = \frac{1}{4q_4}
    * \begin{bmatrix}
    * R_{23}-R{32} \\ R_{31}-R{13} \\ R_{12}-R{21}
    * \end{bmatrix}\f]\f[
    * \bf{\bar{q}} = \begin{bmatrix} \bf{q} \\ q_4 \end{bmatrix}
    * \f]
    */
void Quaternion::Set(const DirectionCosineMatrix& _DCM)
{
    (*this)(VectorIndexBase+3) = 0.5 * sqrt(1 + trace(_DCM));
    (*this)(VectorIndexBase+0) = _DCM(MatrixIndexBase+1,MatrixIndexBase+2)
        - _DCM(MatrixIndexBase+2,MatrixIndexBase+1);
    (*this)(VectorIndexBase+1) = _DCM(MatrixIndexBase+2,MatrixIndexBase+0)
        - _DCM(MatrixIndexBase+0,MatrixIndexBase+2);
    (*this)(VectorIndexBase+2) = _DCM(MatrixIndexBase+0,MatrixIndexBase+1)
        - _DCM(MatrixIndexBase+1,MatrixIndexBase+0);
    (*this)(_(VectorIndexBase,VectorIndexBase+2)) /= (4 * (*this)(VectorIndexBase+3));
    Normalize();
    return;
}

    /*! \brief Set the quaternion to the transformation of set of Euler Angles.
        * @param _EulerAngles 3x1 matrix of Euler Angles. [rad]
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        */
void Quaternion::Set(const Vector& _EulerAngles, const int& _Sequence)
{
    /*! \todo Implement Quaternion::Set(EulerAngles, Sequence) as individual calcs instead of multiple conversions */
    Set(DirectionCosineMatrix(_EulerAngles, _Sequence));
    Normalize();
    return;
}


    /*! \brief Set the quaternion to the transformation about an Euler Axis by a set angle.
        * @param _EulerAxis 3x1 Euler Axis vector (\f$\hat{e}\f$).
        * @param _EulerAngle Angle rotation about axis (\f$\Phi\f$)[rad].
        * \par Equation: 
        * \f[ \bf{q}_i = \hat{e}_i \sin{\frac{\Phi}{2}} q_4 = \cos{\frac{\Phi}{2}} \f]
        * for i=1,2,3
        */
void Quaternion::Set(const Vector& _EulerAxis, const Angle& _EulerAngle)
{
    (*this)(_(VectorIndexBase+0,VectorIndexBase+2)) = _EulerAxis * sin(0.5 * _EulerAngle);		
    (*this)(VectorIndexBase+3) = cos(0.5 * _EulerAngle);
    Normalize();
    return;
}


/*! \brief Set the Quaternion to the transformation of Modified Rodriguez Paramaters (MRP).
    * @param _MRP 3x1 matrix of Modified Rodriguez Parameters (MRP).
    * \par Equation: 
    * \f[ \bf{q}_i = \frac{2\sigma_i}{1+\sigma^2} q_4 = \frac{1-\sigma^2}{1+\sigma^2} \f] 
    * for i=1,2,3 (Ref Schaub99)
    */
void Quaternion::Set(const ModifiedRodriguezParameters& _MRP)
{
    Matrix tempMatrix = (~_MRP) * (_MRP);
    double sigmaSq = tempMatrix(MatrixIndexBase,MatrixIndexBase);
    double denom = 1 + sigmaSq;
    (*this)(1) = 2 * _MRP(1) / denom;		
    (*this)(2) = 2 * _MRP(2) / denom;		
    (*this)(3) = 2 * _MRP(3) / denom;		
    (*this)(VectorIndexBase+3) = (1 - sigmaSq) /denom;
    Normalize();
    return;
}

    /*! \brief Convert the quaternion to a Direction Cosine Matrix (DCM).
        * Uses the DirectionCosineMatrix(Quaternion) constructor.
        * @return 3x3 Direction Cosine Matrix.
        */
DirectionCosineMatrix Quaternion::GetDCM() const
{
    return DirectionCosineMatrix(*this);
}

    /*! \brief Convert the quaternion to a set of Euler Angles.
        * @param _Sequence Euler angle rotation sequence. (ie 123, 213, 313, 321, etc).
        * @return (3 x 1) Euler Angles based on given rotation sequence (\f$\theta_i\f$)[rad] 
        */
Vector Quaternion::GetEulerAngles(const int& _Sequence) const
{
    /*! \todo Implement Quaternion::GetEulerAngles function */
    return Vector(EULERANGLES_SIZE);
}


/*! \brief Convert the quaternion to an Euler Axis and Angle.
    * @param _EulerAxis 3x1 Euler Axis vector (\f$\hat{e}\f$).
    * @param _EulerAngle Angle rotation about axis (\f$\Phi\f$)[rad].
    * @return 4-element vector [EulerAxis; EulerAngle]
    * \par Equation: 
    * \f[\Phi = 2\cos^{-1}{q_4} \hat{e}_i = \bf{q}_i\sin{\frac{\Phi}{2}}\f] 
    * (Ref Schaub99)
    */
Vector Quaternion::GetEulerAxisAngle(Vector& _EulerAxis, Angle& _EulerAngle) const
{
    Vector returnVector(EULERAXIS_SIZE + 1);
    _EulerAngle = 2.0 * acos((*this)(VectorIndexBase+3));
    _EulerAxis = (*this)(_(VectorIndexBase+0,VectorIndexBase+2)) * sin(0.5 * _EulerAngle);
    returnVector(_(VectorIndexBase,VectorIndexBase+EULERAXIS_SIZE-1)) = _EulerAxis;
    returnVector(VectorIndexBase + EULERAXIS_SIZE) = _EulerAngle;
    return returnVector;
}


    /*! \brief Convert the quaternion to an Euler Axis and Angle.
        * @return 4-element vector [EulerAxis; EulerAngle]
        */
Vector Quaternion::GetEulerAxisAngle() const
{
    Vector EulerAxis(EULERAXIS_SIZE);
    double EulerAngle;
    return GetEulerAxisAngle(EulerAxis, EulerAngle);
}

    
    /*! \brief Convert the quaternion to an MRP representation.
        * Uses the ModifiedRodriguezParameters(Quaternion) constructor.
        * @return (3 x 1) converted MRP. 
        */
ModifiedRodriguezParameters Quaternion::GetMRP() const
{
    return ModifiedRodriguezParameters(*this);
}


    /*! \brief Normalizes a quaternion so that \f${\bf{\bar q}}^T {\bf{\bar q}}=1$\f. 
        */
void Quaternion::Normalize()
{
    /*! \todo Add Normalize() to Vector Class */
    normalize(*this);
    return;
}

/*! \brief Determine the successive rotation from the summation of two quaternions.
    * @param _quat2 Quaternion to be summed with.
    * 
    * \par Equation: 
    * successive rotations of \f$\bf{q'}\f$ and \f$\bf{q''}\f$ (Ref Schaub99)
    * \f[
    * \begin{bmatrix}
    * q_1 \\ q_2 \\ q_3 \\ q_4
    * \end{bmatrix}
    * =
    * \begin{bmatrix}
    * q'_1 & q'_4 & -q'_3 & q'_2\\
    * q'_2 & q'_3 & q'_4 & -q'_1\\
    * q'_3 & -q'_2 & q'_1 & q'_4\\
    * q'_4 & -q'_1 & -q'_2 & -q'_3
    * \end{bmatrix}
    * \begin{bmatrix}
    * q''_1 \\ q''_2 \\ q''_3 \\ q''_4
    * \end{bmatrix}
    * \f]
    */
Quaternion Quaternion::operator+ (const Quaternion& _quat2) const
{
    Matrix qSkewed(4,4);
    // Column 1
    qSkewed(_,MatrixIndexBase+0) = (*this);
    // Column 2
    qSkewed(MatrixIndexBase+0,MatrixIndexBase+1) =  (*this)(VectorIndexBase+0);	
    qSkewed(MatrixIndexBase+1,MatrixIndexBase+1) =  (*this)(VectorIndexBase+2);
    qSkewed(MatrixIndexBase+2,MatrixIndexBase+1) = -(*this)(VectorIndexBase+1);
    qSkewed(MatrixIndexBase+3,MatrixIndexBase+1) = -(*this)(VectorIndexBase+3);
    // Column 3
    qSkewed(MatrixIndexBase+0,MatrixIndexBase+2) = -(*this)(VectorIndexBase+1);	
    qSkewed(MatrixIndexBase+1,MatrixIndexBase+2) =  (*this)(VectorIndexBase+2);
    qSkewed(MatrixIndexBase+2,MatrixIndexBase+2) =  (*this)(VectorIndexBase+3);
    qSkewed(MatrixIndexBase+3,MatrixIndexBase+2) = -(*this)(VectorIndexBase+0);
    // Column 4
    qSkewed(MatrixIndexBase+0,MatrixIndexBase+3) =  (*this)(VectorIndexBase+1);	
    qSkewed(MatrixIndexBase+1,MatrixIndexBase+3) = -(*this)(VectorIndexBase+0);
    qSkewed(MatrixIndexBase+2,MatrixIndexBase+3) =  (*this)(VectorIndexBase+3);
    qSkewed(MatrixIndexBase+3,MatrixIndexBase+3) = -(*this)(VectorIndexBase+2);

    return Quaternion(qSkewed * _quat2);
}

/*! \brief Determine the relative rotation from the difference of two quaternions.
    * @param _quat2 Quaternion to be differenced with.
    * 
    * \par Equation: 
    * subtracting \f$\bf{q'}\f$ from \f$\bf{q''}\f$ (Ref Schaub99)
    * \f[
    * \begin{bmatrix}
    * q_1 \\ q_2 \\ q_3 \\ q_4
    * \end{bmatrix}
    * =
    * \begin{bmatrix}
    * -q'_4 & q'_4 & q'_3 & -q'_2\\
    * -q'_2 & -q'_3 & q'_4 & q'_1\\
    * -q'_3 & -q'_2 & -q'_1 & q'_4\\    
    * q'_4 & q'_1 & q'_2 & q'_3
    * \end{bmatrix}
    * \begin{bmatrix}
    * q''_1 \\ q''_2 \\ q''_3 \\ q''_4
    * \end{bmatrix}
    * \f]
    */
Quaternion Quaternion::operator- (const Quaternion& _quat2) const
{
    Matrix qSkewed(4,4);
    // Column 1
    qSkewed(MatrixIndexBase+0,MatrixIndexBase+0) = -_quat2(VectorIndexBase+0);
    qSkewed(MatrixIndexBase+1,MatrixIndexBase+0) = -_quat2(VectorIndexBase+1);
    qSkewed(MatrixIndexBase+2,MatrixIndexBase+0) = -_quat2(VectorIndexBase+2);
    qSkewed(MatrixIndexBase+3,MatrixIndexBase+0) =  _quat2(VectorIndexBase+3);
    // Column 2
    qSkewed(MatrixIndexBase+0,MatrixIndexBase+1) =  _quat2(VectorIndexBase+3);	
    qSkewed(MatrixIndexBase+1,MatrixIndexBase+1) = -_quat2(VectorIndexBase+2);
    qSkewed(MatrixIndexBase+2,MatrixIndexBase+1) =  _quat2(VectorIndexBase+1);
    qSkewed(MatrixIndexBase+3,MatrixIndexBase+1) =  _quat2(VectorIndexBase+0);
    // Column 3
    qSkewed(MatrixIndexBase+0,MatrixIndexBase+2) =  _quat2(VectorIndexBase+2);	
    qSkewed(MatrixIndexBase+1,MatrixIndexBase+2) =  _quat2(VectorIndexBase+3);
    qSkewed(MatrixIndexBase+2,MatrixIndexBase+2) = -_quat2(VectorIndexBase+0);
    qSkewed(MatrixIndexBase+3,MatrixIndexBase+2) =  _quat2(VectorIndexBase+1);
    // Column 4
    qSkewed(MatrixIndexBase+0,MatrixIndexBase+3) = -_quat2(VectorIndexBase+1);	
    qSkewed(MatrixIndexBase+1,MatrixIndexBase+3) =  _quat2(VectorIndexBase+0);
    qSkewed(MatrixIndexBase+2,MatrixIndexBase+3) =  _quat2(VectorIndexBase+3);
    qSkewed(MatrixIndexBase+3,MatrixIndexBase+3) =  _quat2(VectorIndexBase+2);

    return Quaternion((qSkewed) * (*this));
}
} // end of namespace O_SESSAME
/*!***************************************************************************
*	$Log: Rotation.cpp,v $
*	Revision 1.24  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.23  2003/06/10 14:23:42  nilspace
*	Changed MRP::Set(Quaternion) to not overwrite the const.
*	
*	Revision 1.22  2003/06/10 02:25:32  nilspace
*	Fixed MRP::Set(Quaternion) since there apparently is no Vector::operator-() that returns the negative of a Vector.
*	
*	Revision 1.21  2003/05/27 20:01:38  nilspace
*	Fixed numerous bugs with MRP conversion functions.
*	
*	Revision 1.20  2003/05/27 14:39:12  nilspace
*	Fixed the MRP->Quaternion conversion.
*	
*	Revision 1.19  2003/05/22 03:03:38  nilspace
*	Update documentation, and changed all angles to use Angle type.
*	
*	Revision 1.18  2003/05/21 22:18:05  nilspace
*	Moved the documentation to the implementation file.
*	
*	Revision 1.17  2003/05/20 17:53:51  nilspace
*	Updated comments.
*	
*	Revision 1.16  2003/05/13 19:45:10  nilspace
*	Updated comments.
*	
*	Revision 1.15  2003/05/02 19:44:24  nilspace
*	Modified the DCM::Set(Quaternion) function for a more efficient calculation on the diagonals.
*	
*	Revision 1.14  2003/04/28 14:16:26  nilspace
*	Moved all function definitions out of header file into implementation file.
*	
*	Revision 1.13  2003/04/27 20:41:09  nilspace
*	Encapsulated the rotation library into the namespace O_SESSAME.
*	
*	Revision 1.12  2003/04/22 21:59:58  nilspace
*	Fixed Quaternion::Set(DCM) so it evaluates correctly.
*	Implemented Rotation::operator-()
*	
*	Revision 1.11  2003/04/22 20:52:39  nilspace
*	Added Normalize() call to all of the DCM::Set functions.
*	
*	Revision 1.10  2003/04/22 19:45:16  nilspace
*	Fixed DCM::Set to correctly calculate the MRP tempMatrix (sigma^2)
*	
*	Revision 1.9  2003/04/22 19:36:02  nilspace
*	Various bug fixes to DCM & quaternion conversions. Added DirectionCosineMatrix Normalize().
*	
*	Revision 1.8  2003/04/22 16:03:11  nilspace
*	Updated MRP::Set(Quaternion) to correctly set.
*	
*	Revision 1.7  2003/04/10 17:25:51  nilspace
*	changelog
*	
*	Revision 1.6  2003/04/08 23:02:27  nilspace
*	Added Rotation Sense, or "Handedness". Defaults to RIGHT_HAND
*	
*	Revision 1.5  2003/03/27 20:22:26  nilspace
*	Added GetRotation() function.
*	Fixed Quaternion.Set(Quaternion) function.
*	Added RotationType enum.
*	Made sure to normalize the Quaternions for all the Set() functions.
*	
*	Revision 1.4  2003/03/25 02:37:36  nilspace
*	Added quaternion matrix set and constructor.
*	Added Rotation generalized matrix set to check for quaternion.
*	
*	Revision 1.3  2003/03/04 17:36:19  nilspace
*	Added CVS tags for documenting uploads. Also chmod'd to not be executable.
*	
*	Revision 1.1  2003/02/27 18:37:26  nilspace
*	Initial submission of Rotation class implementation.
*	
*
******************************************************************************/


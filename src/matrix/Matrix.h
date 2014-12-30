//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Matrix.h
*  \brief Wrapper of CammVa Matrix & Matrix Library.
*  \author Andrew Turner <ajturner@vt.edu>
*  \version 0.1
*  \date   2003
//////////////////////////////////////////////////////////////////////////////////////////////////
*  \todo Add overloading of operators
*  \todo Reference cammva documentation
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <math.h>

#include "cammva.h"
namespace O_SESSAME {

const int MatrixIndexBase = 1; /*!<< Beginning index of Matrix class */
const int VectorIndexBase = 1; /*!<< Beginning index of Vector class */
const int MatrixRowsIndex = 1; /*!<< Value referring to the "rows" index  */
const int MatrixColsIndex = 2; /*!<< Value referring to the "columns" index  */
typedef CAMdoubleMatrix Matrix; /*!<< Encapsulation of CAMdoubleMatrix class  */
typedef CAMdoubleVector Vector; /*!<< Encapsulation of CAMdoubleVector class  */

/** Creates an square identity matrix of specified size.
* @param _rowColumns Number of rows and columns to size matrix (will be a square matrix).
* \todo Implement eye as part of Vector or CAMdoubleVector class
*/
inline Matrix eye(int _rowColumns)
{
    Matrix eyeOutput(_rowColumns,_rowColumns);
    eyeOutput.setToValue(0.0);
    for(int ii = MatrixIndexBase;ii < _rowColumns + MatrixIndexBase; ++ii)
        eyeOutput(ii,ii) = 1.0;
    return eyeOutput;
}

/** Calculates the trace of matrix (sum of elements along diagonal).
* @param _inMatrix Matrix to have trace calculated.
* \todo Implement trace as part of Vector or CAMdoubleVector class
*/
inline double trace(const Matrix &_inMatrix)
{
    double Sum = 0;
    for(int ii = MatrixIndexBase;ii < _inMatrix[MatrixRowsIndex].getIndexCount() + MatrixIndexBase; ++ii)
        Sum += _inMatrix(ii,ii);
    return Sum;
}

/** Calculates the 2-norm of the vector (square-root of the sum of the squares).
* \todo Implement norm2 as part of Vector or CAMdoubleVector class
* @param _inVector Vector to calculate the 2-norm of.
* @return Square-root of the sum of squares of elements in vector.
*/
inline double norm2(const Vector &_inVector)
{
    double Sum = 0;
    for(int ii = VectorIndexBase;ii < _inVector.getIndexCount() + VectorIndexBase; ++ii)
        Sum += _inVector(ii) * _inVector(ii);
    return sqrt(Sum);
}

/** Normalizes a vector.
 * @param _inVector Vector to be normalized.
* \todo Implement normalize as part of Vector or CAMdoubleVector class
 */
inline void normalize(Vector &_inVector)
{
    _inVector /= norm2(_inVector);
    return;
}

/** Calculates the Infinity-norm of the vector (largest value of the components).
* @param _inVector Vector to calculate the 2-norm of.
* @return Absolute value of maximum component in vector.
* \todo Implement normInf as part of Vector or CAMdoubleVector class
*/
inline double normInf(const Vector &_inVector)
{
    return _inVector.maxAbs();
}

/** Calculates the skew-symmetric matrix of a vector.
* Equation:
/f[
    \bf{v^{\times}} =
    \begin{bmatrix}
    0 & -v_3 & v_2\\
    v_3 & 0 & -v_1\\
    -v_2 & v_1 & 0
    \end{bmatrix}
/f]
* @param _inVector Vector to calculate the skew-symmetric matrix of.
* @return Skew-symmetric matrix (3x3).
* \todo Implement skew as part of Vector or CAMdoubleVector class
*/
inline Matrix skew(const Vector &_inVector)
{
    Matrix Rout(3,3);
    Rout.setToValue(0.0);
    Rout(MatrixIndexBase+0,MatrixIndexBase+1) =
        -_inVector(VectorIndexBase+2);
    Rout(MatrixIndexBase+0,MatrixIndexBase+2) =
        _inVector(VectorIndexBase+1);
    Rout(MatrixIndexBase+1,MatrixIndexBase+0) =
        _inVector(VectorIndexBase+2);
    Rout(MatrixIndexBase+1,MatrixIndexBase+2) =
        -_inVector(VectorIndexBase+0);
    Rout(MatrixIndexBase+2,MatrixIndexBase+0) =
        -_inVector(VectorIndexBase+1);
    Rout(MatrixIndexBase+2,MatrixIndexBase+1) =
        _inVector(VectorIndexBase+0);
    return Rout;
}

/** Calculates the cross product of 2 vectors.
* Equation: /f$ v_3 = v_1 \cross v_2 = v_1/f$
* @param _inVector Vector to calculate the 2-norm of.
* @return Cross product of 2 vectors.
* \todo Implement crossP as part of Vector or CAMdoubleVector class
*/
inline Vector crossP(const Vector &_v1, const Vector &_v2)
{
    return skew(_v1) * _v2;
}
}
#endif



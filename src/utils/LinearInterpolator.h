//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file LinearInterpolator.h
*  \brief Interface to the Linear Interpolator.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/06/06 00:34:47 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_LINEAR_INTERPOLATOR_H__
#define __SSF_LINEAR_INTERPOLATOR_H__

#include <Matrix.h>
#include "Interpolator.h"

namespace O_SESSAME {
/*! \brief Interpolates between a given set of data points to create a linear functional approximation.
* \ingroup InterpolationLibrary
*
* \detail Works for either a single function, or Vector of functions (such as interpolating a state).

\par Example:
\code
// Interpolate the sin() function

// Build the sin() function
int stepsize = 0.1;
Vector timeVec(2*M_PI / stepsize);
Matrix sinOutput(timeVec[MatrixRowsIndex].getIndexBound(), 1);
for (int jj = 1; jj < timeVec[MatrixRowsIndex].getIndexBound();  ++jj)
{
    timeVec(jj) = jj * stepsize;
    sinOutput(jj,1) = sin(jj * stepsize);
}

// Create interpolator
LinearInterpolator interp(timeVec,sinOutput);
Vector chk = interp.Evaluate(0.25);
\endcode
*/
class LinearInterpolator : public Interpolator
{
public:
    /*! \brief Creates an empty linear interpolation.
        *
        */
    LinearInterpolator();

    /*! \brief Creates a linear interpolation from the data points. 
        * 
        * \detail See Interpolate
        */
    LinearInterpolator(const Vector& _timePoints, const Matrix& _dataPoints);
    
    /*! \brief Default Deconstructor
        *
        */
    virtual ~LinearInterpolator();
    
    /*! \brief Creates an interpolation from the vector of time points and matrix of corresponding data points. 
        *
        * @param _timePoints Vector of time (seconds) points of the data values.
        * @param _dataPoints Matrix of data points at each time step in the _timePoints vector. 
        *\f[\begin{bmatrix}	
        * x1(t1) & x2(t1) & x3(t1) &  ... \\
        * x1(t2) & x2(t2) & x3(t2)&  ... \\
        * x1(t3) & x2(t3) & x3(t3) & ... \\
        * ...	& ...    & ...   &  ... \\ 
        * \end{bmatrix}\f]
        */
    virtual void Interpolate(const Vector& _timePoints, const Matrix& _dataPoints);

    /*! \brief Evaluate interpolation curve at a specified time.
        *
        * \detail Output = m_Slope * _inputPoint + m_Offset
        * @param _inputPoint Input point (time) at which to evaluate the vector of interpolations.
        * @return Vector of output values from the evaluated interpolation.
        */
    virtual Vector Evaluate(const double& _inputPoint);
    
    /*! \brief Returns the number of data points required for interpolation.
        *
        * \detail the number of data points is the number of X-values (time) required to interpolate.
        * @return the number of data points, centered about the evaluation time, req'd to interpolate.
        */
    virtual int GetNumberDataPoints()	{return m_NumDataPoints;};
    
    /*! \brief Return a pointer to a new instance of a linear interpolator type.
        *
        * \detail This is used to request memory for a new instance of a LinearInterpolator. It is necessary 
        *	when attempting to get a pointer from the abstract data type Interpolator 
        *	and the actual representation type isn't known.
        * @return a pointer to a new allocation of memory for the LinearInterpolator object.
        */
    virtual LinearInterpolator* NewPointer();
    /*! \brief Return a pointer to a copy of the linear interpolator instance.
        *
        * \detail This is used to request memory for a copy of this instance of LinearInterpolator. It is necessary 
        *	when attempting to get a pointer from the abstract data type Interpolator 
        *	and the actual representation type isn't known.
        * @return a pointer to a copy of the LinearInterpolator object.
        */
    virtual LinearInterpolator* Clone();
    
protected:
    /*! \brief Computes the slope and offset (intercept) of the linear interpolation given two data points.
        * 
        * \detail point1: (_x1, _y1) | point2: (_x2, _y2)
        * \f$ slope=\frac{y_2 - y_1}{x_2-x_1}\quad offset=y_2-slope * x_2 \f$
        */
    void BuildLinearInterpolation(const double& _x1, const double& _y1, const double& _x2, const double& _y2, double& _Slope, double& _Offset);
    
    /*! \brief Doesn't do anything for linear interpolator since there are always only 2 data points. */
    virtual void SetNumberDataPoints(const int& _numberDataPoints) {};
private:
    /** Number of data points used for interpolation, should always be 2 for linear interpolation */
    int m_NumDataPoints;
    /** Number of elements in the state vector. Used to determine how many linear interpolations there are per data set. */
    int m_NumElements;
    /** Vector of slope parameters. One slope parameter per element. */
    Vector m_Slope;
    /** Vector of offset parameters. One slope parameter per element. */
    Vector m_Offset;
    Vector m_tempOutput; // this is faster, but larger could be a problem for big histories
};
} // close namespace O_SESSAME

#endif 


// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: LinearInterpolator.h,v $
*	Revision 1.2  2003/06/06 00:34:47  nilspace
*	?
*	
*	Revision 1.1  2003/05/13 18:42:08  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

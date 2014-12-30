//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Interpolator.h
*  \brief Abstract interface to the Interpolator Strategy.
*  \author $Author: nilspace $
*  \version $Revision: 1.3 $
*  \date    $Date: 2003/06/06 00:34:47 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_INTERPOLATOR_H__
#define __SSF_INTERPOLATOR_H__
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif 

#include <Matrix.h>

namespace O_SESSAME {

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! @defgroup InterpolationLibrary Interpolation Library  
* \brief Interpolation schemes.
* 
* \detail Interpolators are used when there is a set of computed data points, but the user 
requires the approximated data between these data points. The interpolator creates a functional 
approximation of the intermediate data using any number of calculated @em mesh points. 

\par
The interpolator creates and stores the parameters corresponding to the interpolation function 
and functional representation. The user must enter a set of time values (independent variables) and 
a set of corresponding data values to be interpolated (dependent variables). Once the interpolation 
has been computer and has stored the functional representation, the user can Evaluate the interpolation 
at any point in between the valid mesh points.

\par Derived Classes
Each derived interpolation is a specific algorithm that determines an interpolation based upon the 
described scheme. This may include linear, lagrangian, hermitian, or a cubic spline interpolation. 
The user needs to query the GetNumberDataPoints to determine how many mesh points are required to 
perform interpolation (the higher the order, the more number of data points). Some interpolations 
may also require higher order terms (first- and second-derivatives) of the dependent variables. 
Consult the specific class's documentation.
*/

/*! \brief Abstract interface to the set of interpolators.
*
* \ingroup InterpolationLibrary
* \detail
*/
class Interpolator
{
public:
    /*! \brief Default Deconstructor */
    virtual ~Interpolator() { }
    
    /*! \brief Standard Interpolation Function. 
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
    virtual void Interpolate(const Vector& _timePoints, const Matrix& _dataPoints) = 0;

    /*! \brief Evaluate interpolation curve at a specified time.
        *
        * \detail Output = m_Slope * _inputPoint + m_Offset
        * @param _inputPoint Input point (time) at which to evaluate the vector of interpolations.
        * @return Vector of output values from the evaluated interpolation.
        */
    virtual Vector Evaluate(const double& _inputPoint) = 0;
    /*! \brief Returns the number of data points required for interpolation.
        *
        * \detail the number of data points is the number of X-values (time) required to interpolate.
        * @return the number of data points, centered about the evaluation time, req'd to interpolate.
        */
    virtual int GetNumberDataPoints() = 0;

    /*! \brief Return a pointer to a new instance of a derived interpolator type.
        *
        * \detail This is used to request memory for a new instance of a derived instance when the 
        *	actual type of the derived object is unknown. By calling this function, the compiler 
        *	links to the correct derived function to return a pointer and allocate memory of 
        *	the correct type.
        *	\par Example: 
        *	\code 
                * Interpolator* newInterp = oldInterp->NewPointer();
        *       \endcode
        * @return a pointer to a new allocation of memory for the appropriate interpolator.
        */
    virtual Interpolator* NewPointer() = 0;

    /*! \brief Return a pointer to a copy of a derived interpolator type.
        *
        * \detail This is used to request memory for and copy of an instance of a derived representation when the 
        *	actual type of the derived object is unknown. By calling this function, the compiler 
        *	links to the correct derived function to return a pointer and allocate memory of 
        *	the correct type and copy the data.
        *	\par Example: 
                \code 
                * Interpolator* newInterp = oldInterp->Clone();
                \endcode
        * @return a pointer to a copy of the appropriate interpolator.
        */
    virtual Interpolator* Clone() = 0;
    
    /*! \brief Returns whether the current interpolation parameters are valid.
        * @return TRUE if the current interpolation is valid, FALSE if it is not and should not be used to Evaluate without being reinterpolated.
        */
    virtual bool GetValid() {return m_Valid;};

protected:
    /*! \brief Sets the validity value of the interpolation parameters.
        * 
        */
    virtual void SetValid(const bool& _newValidValue) {m_Valid = _newValidValue;};
    
    /*! \brief Default constructor. Does nothing since this is an abstract class 
        *
        * \detail Specifically, it sets the default value of the m_Valid flag.
        */
    Interpolator() : m_Valid(FALSE) { };
    
private:
    /*! \brief Internal storage of the interpolation's "validity" */
    bool m_Valid;
};
} // close namespace O_SESSAME

#endif 


// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Interpolator.h,v $
*	Revision 1.3  2003/06/06 00:34:47  nilspace
*	?
*	
*	Revision 1.2  2003/05/15 16:05:44  nilspace
*	Added a TRUE and FALSE define. Move to a math header file.
*	
*	Revision 1.1  2003/05/13 18:41:23  nilspace
*	Initial submission.
*	
*
******************************************************************************/

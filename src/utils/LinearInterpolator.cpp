//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file LinearInterpolator.cpp
*  \brief Implementation of the Linear Interpolator.
*  \author $Author: nilspace $
*  \version $Revision: 1.3 $
*  \date    $Date: 2003/05/20 19:46:52 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "LinearInterpolator.h"

namespace O_SESSAME {
LinearInterpolator::LinearInterpolator() : m_NumDataPoints(2), m_NumElements(0), m_Slope(m_NumElements), m_Offset(m_NumElements), m_tempOutput(m_NumElements)
{

}

LinearInterpolator::LinearInterpolator(const Vector& _timePoints, const Matrix& _dataPoints) : m_NumDataPoints(2), m_NumElements(_dataPoints[MatrixColsIndex].getIndexBound()), m_Slope(m_NumElements), m_Offset(m_NumElements), m_tempOutput(m_NumElements)
{
    Interpolate(_timePoints, _dataPoints);
}

LinearInterpolator::~LinearInterpolator()
{
}

void LinearInterpolator::Interpolate(const Vector& _timePoints, const Matrix& _dataPoints)
{
    m_NumElements = _dataPoints[MatrixColsIndex].getIndexBound();
    if(m_Slope.getIndexBound() != m_NumElements)
        m_Slope.initialize(m_NumElements);
    if(m_Offset.getIndexBound() != m_NumElements)
        m_Offset.initialize(m_NumElements);
        
    for(int ii = MatrixIndexBase; ii <= m_NumElements; ++ii)
    {
        BuildLinearInterpolation(_timePoints(VectorIndexBase), _dataPoints(VectorIndexBase,ii), 
                        _timePoints(VectorIndexBase+1), _dataPoints(VectorIndexBase+1,ii), 
                        m_Slope(ii), m_Offset(ii));
    }
    SetValid(TRUE);
}

Vector LinearInterpolator::Evaluate(const double& _timeEvalPoint)
{
    if(m_tempOutput.getIndexBound() != m_NumElements)
        m_tempOutput.initialize(m_NumElements);

    for(int ii = VectorIndexBase; ii <= m_Slope.getIndexBound(); ++ii)
    {
        m_tempOutput(ii) = _timeEvalPoint * m_Slope(ii) + m_Offset(ii);
    }
    return m_tempOutput;
}

void LinearInterpolator::BuildLinearInterpolation(const double& _x1, const double& _y1, const double& _x2, const double& _y2, double& _Slope, double& _Offset)
{
    _Slope = (_y2 - _y1) / (_x2 - _x1);
    _Offset = _y2 - _Slope * _x2;
}

LinearInterpolator* LinearInterpolator::NewPointer()
{
    return new LinearInterpolator();
}

LinearInterpolator* LinearInterpolator::Clone()
{
    return new LinearInterpolator(*this);
}

} // close namespace O_SESSAME


// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: LinearInterpolator.cpp,v $
*	Revision 1.3  2003/05/20 19:46:52  nilspace
*	Fixed the initialization of m_NumElements and subsequent parameter vector size checks to be != rather than just <
*	
*	Revision 1.2  2003/05/20 17:44:21  nilspace
*	Updated comments.
*	
*	Revision 1.1  2003/05/13 18:42:08  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

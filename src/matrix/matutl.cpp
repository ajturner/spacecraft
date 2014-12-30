#include "dmatrix.h"
#include "bnengine.h"
//
//********************************************************************************
//                  UTILITY  MEMBER_FUNCTIONS
//********************************************************************************
//
//
// Routines return double. When adding multiple data types, I'll
// need to promote the utilities to the derived classes so that
// they can return the appropriate type.
//
double  CAMmatrixBase::max() const
{
//
//  Need Conversion Check
//
    CAMmatrixBase A;
    double* AdataP;
    long    n;
    double  value;

    if(A.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(*this);
    AdataP = (double*)A.getDataPointer();
    n      = A.Structure.getFullDataCount();
    }
    else
    {
    AdataP = (double*)getDataPointer();
    n      = Structure.getFullDataCount();
    }

    CAMbinaryEngine::doubleMaxValue(AdataP, n, value);
    return value;
}

double  CAMmatrixBase::min() const
{
//
//  Need Conversion Check
//
    CAMmatrixBase A;
    double* AdataP;
    long n;
    double  value;

    if(A.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(*this);
    AdataP = (double*)A.getDataPointer();
    n      = A.Structure.getFullDataCount();
    }
    else
    {
    AdataP = (double*)getDataPointer();
    n      = Structure.getFullDataCount();
    }

    CAMbinaryEngine::doubleMinValue(AdataP, n, value);
    return value;
}

double  CAMmatrixBase::maxAbs() const
{
//
//  Need Conversion Check
//
    CAMmatrixBase A;
    double* AdataP;
    long n;
    double  value;

    if(A.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(*this);
    AdataP = (double*)A.getDataPointer();
    n      = A.Structure.getFullDataCount();
    }
    else
    {
    AdataP = (double*)getDataPointer();
    n      = Structure.getFullDataCount();
    }

    CAMbinaryEngine::doubleMaxAbsValue(AdataP, n, value);
    return value;
}

double  CAMmatrixBase::minAbs() const
{
//
//  Need Conversion Check
//
    CAMmatrixBase A;
    double* AdataP;
    long n;
    double  value;

    if(A.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(*this);
    AdataP = (double*)A.getDataPointer();
    n      = A.Structure.getFullDataCount();
    }
    else
    {
    AdataP = (double*)getDataPointer();
    n      = Structure.getFullDataCount();
    }

    CAMbinaryEngine::doubleMinAbsValue(AdataP, n, value);
    return value;
}


double  CAMmatrixBase::infNorm() const
{
//
//  Need Conversion Check
//
    CAMmatrixBase A;
    double* AdataP;
    long    n;
    double  value;

    if(A.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(*this);
    AdataP = (double*)A.getDataPointer();
    n      = A.Structure.getFullDataCount();
    }
    else
    {
    AdataP = (double*)getDataPointer();
    n      = Structure.getFullDataCount();
    }

    CAMbinaryEngine::doubleMaxAbsValue(AdataP, n, value);
    return value;
}

double  CAMmatrixBase::pNorm(double p) const
{
//
//  Need Conversion Check
//
    CAMmatrixBase A;
    double* AdataP;
    long    n;
    double  value;

    if(A.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(*this);
    AdataP = (double*)A.getDataPointer();
    n      = A.Structure.getFullDataCount();
    }
    else
    {
    AdataP = (double*)getDataPointer();
    n      = Structure.getFullDataCount();
    }

    CAMbinaryEngine::doublepNorm(AdataP, n, p, value);
    return value;
}

double  CAMmatrixBase::pNorm(int p) const {return pNorm(double(p));}
double  CAMmatrixBase::pNorm(long p) const {return pNorm(double(p));}
double  CAMmatrixBase::pNorm(float p) const {return pNorm(double(p));}

//
//  These routines are being put in the base type for now
//

CAMmatrixBase CAMmatrixBase::inverse() const
{
    long m = (*this)[1].getIndexCount();
    long n = (*this)[2].getIndexCount();
    CAMdoubleMatrix I = CAMdoubleMatrix::identity(n);
    return (*this)/I;
}

//
//********************************************************************************
//                     CPP File End
//********************************************************************************
//

  

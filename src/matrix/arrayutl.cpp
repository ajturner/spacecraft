#include "arraybse.h"
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
double  CAMarrayBase::max() const
{
//
//  Need Conversion Check
//
    CAMarrayBase A;
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

double  CAMarrayBase::min() const
{
//
//  Need Conversion Check
//
    CAMarrayBase A;
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

double  CAMarrayBase::maxAbs() const
{
//
//  Need Conversion Check
//
    CAMarrayBase A;
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

double  CAMarrayBase::minAbs() const
{
//
//  Need Conversion Check
//
    CAMarrayBase A;
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


double  CAMarrayBase::infNorm() const
{
//
//  Need Conversion Check
//
    CAMarrayBase A;
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

double  CAMarrayBase::pNorm(double p) const
{
//
//  Need Conversion Check
//
    CAMarrayBase A;
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

double  CAMarrayBase::pNorm(int p) const {return pNorm(double(p));}
double  CAMarrayBase::pNorm(long p) const {return pNorm(double(p));}
double  CAMarrayBase::pNorm(float p) const {return pNorm(double(p));}

//
//********************************************************************************
//                     CPP File End
//********************************************************************************
//


  

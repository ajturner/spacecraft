#include "vecbse.h"
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
double  CAMvectorBase::max() const
{
//
//  Need Conversion Check
//
    CAMvectorBase A;
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

double  CAMvectorBase::min() const
{
//
//  Need Conversion Check
//
    CAMvectorBase A;
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

double  CAMvectorBase::maxAbs() const
{
//
//  Need Conversion Check
//
    CAMvectorBase A;
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

double  CAMvectorBase::minAbs() const
{
//
//  Need Conversion Check
//
    CAMvectorBase A;
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


double  CAMvectorBase::infNorm() const
{
//
//  Need Conversion Check
//
    CAMvectorBase A;
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

double  CAMvectorBase::pNorm(double p) const
{
//
//  Need Conversion Check
//
    CAMvectorBase A;
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

double  CAMvectorBase::pNorm(int p) const {return pNorm(double(p));}
double  CAMvectorBase::pNorm(long p) const {return pNorm(double(p));}
double  CAMvectorBase::pNorm(float p) const {return pNorm(double(p));}
double CAMvectorBase::dot(const CAMvectorBase& V) const
{
//
//  Need Conversion Check
//

   if(Structure.isConformingTo(V.Structure) != 1)
   {CAMvectorBase::nonConformingMessage(Structure,V.Structure);}

    long M;

    CAMvectorBase A;
    double* AdataPtr;

    CAMvectorBase Vb;
    double* VdataPtr;
    long    Vcount;

    if(Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(*this);
    AdataPtr    = (double*)A.getDataPointer();
    M = A.getIndexCount();
    }
    else
    {
    AdataPtr  = (double*)getDataPointer();
    M = getIndexCount();
    }

    if(V.Structure.isSubset() == 1)
    {
    Vb.initializeMinDuplicate(V);
    VdataPtr    = (double*)Vb.getDataPointer();
    }
    else
    {
    VdataPtr    = (double*)V.getDataPointer();
    }

   double sum = 0.0;
   long i;
   for(i = 0; i < M; i++)
   {
   sum += (*(VdataPtr + i))*(*(AdataPtr + i));
   }
   return sum;
}
//
//********************************************************************************
//                     CPP File End
//********************************************************************************
//

  

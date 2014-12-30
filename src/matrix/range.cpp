#include "range.h"
#include "mvaexit.h"
//
//******************************************************************************
//                    RANGE.CPP
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Fri Sep 01 18:43:55 1995
//
//********************************************************************************
//
// Global Instance CAMnullRange;
//
//CAMrange __IMPEXP__ CAMnullRange;
//
//********************************************************************************
//                    CONSTRUCTORS
//********************************************************************************
//
//
//********************************************************************************
//               
//********************************************************************************
//
CAMrange::CAMrange()
{
    base               = 0;
    bound              = 0;
    stride             = 0;
    singleArgumentFlag = 0;
    underscoreFlag     = 0;
    nullFlag           = 1;
}

CAMrange::CAMrange( const CAMrange& A)
{
    base                 = A.base;
    bound                = A.bound;
    stride                = A.stride;
    singleArgumentFlag    = A.singleArgumentFlag;
    underscoreFlag        = A.underscoreFlag;
    nullFlag            = A.nullFlag;
}

CAMrange::CAMrange(long inputSize)
{
    base                 = 1;
    bound                = inputSize;
    stride                = 1;
    singleArgumentFlag    = 1;
    underscoreFlag        = 0;
    nullFlag            = 0;
    CAMrange::CAMrangeError(*this);
}
CAMrange::CAMrange(long inputBase, long inputBound)
{
    base                 = inputBase;
    bound                = inputBound;
    stride                = 1;
    singleArgumentFlag    = 0;
    underscoreFlag        = 0;
    nullFlag            = 0;
    CAMrange::CAMrangeError(*this);
}
CAMrange::CAMrange(long inputBase, long inputBound, long inputStride)
{
    base                 = inputBase;
    bound                = inputBound;
    stride                = inputStride;
    singleArgumentFlag    = 0;
    underscoreFlag        = 0;
    nullFlag            = 0;
    CAMrange::CAMrangeError(*this);
}
CAMrange::CAMrange(const CAMunderscore&)
{
    base                 = 0;
    bound                = 0;
    stride                = 0;
    singleArgumentFlag    = 0;
    underscoreFlag        = 1;
    nullFlag            = 0;
}
//
//********************************************************************************
//                    DESTRUCTOR
//********************************************************************************
//
CAMrange::~CAMrange()
{
}
//
//********************************************************************************
//                    ASSIGNMENT
//********************************************************************************
//
CAMrange&  CAMrange::operator =( const CAMrange& A)
{
    base                = A.base;
    bound                = A.bound;
    stride                = A.stride;
    singleArgumentFlag    = A.singleArgumentFlag;
    underscoreFlag        = A.underscoreFlag;
    nullFlag            = A.nullFlag;
    return *this;
}

//
//********************************************************************************
//                    OUTPUT
//********************************************************************************
//
ostream&  operator <<(ostream& out_stream, const CAMrange& A)
{
//
//  Default Output  : Memberwise Output
//
    out_stream  << "base   = " << A.base
                << "  bound  = " << A.bound 
                << "  stride = " << A.stride << '\n';
    return(out_stream);
}
//
//********************************************************************************
//                    MEMBER_FUNCTIONS
//********************************************************************************
//

void      CAMrange::initialize()
{
    base               = 0;
    bound              = 0;
    stride             = 0;
    singleArgumentFlag = 0;
    underscoreFlag     = 0;
    nullFlag           = 1;
}

void      CAMrange::initialize(const CAMrange& R)
{
    base                 = R.base;
    bound                = R.bound;
    stride                = R.stride;
    singleArgumentFlag    = R.singleArgumentFlag;
    underscoreFlag        = R.underscoreFlag;
    nullFlag            = R.nullFlag;
}

void      CAMrange::initialize(long inputSize)
{
    base                 = 1;
    bound                = inputSize;
    stride                = 1;
    singleArgumentFlag    = 1;
    underscoreFlag        = 0;
    nullFlag            = 0;
    CAMrange::CAMrangeError(*this);
}

void      CAMrange::initialize(long inputBase, long inputBound)
{
    base                 = inputBase;
    bound                = inputBound;
    stride                = 1;
    singleArgumentFlag    = 0;
    underscoreFlag        = 0;
    nullFlag            = 0;
    CAMrange::CAMrangeError(*this);
}

void      CAMrange::initialize(long inputBase, long inputBound, long inputStride)
{
    base                 = inputBase;
    bound                = inputBound;
    stride                = inputStride;
    singleArgumentFlag    = 0;
    underscoreFlag        = 0;
    nullFlag            = 0;
    CAMrange::CAMrangeError(*this);
}
CAMrange      CAMrange::operator ++ (int)
{
    if(nullFlag != 1)
    {
    base  = base  + 1;
    bound = bound + 1;
    }
    return *this;
}

CAMrange      CAMrange::operator -- (int)
{
    if(nullFlag != 1)
    {
    base  = base  - 1;
    bound = bound - 1;
    }
    return *this;
}

CAMrange      CAMrange::operator + (long i)
{
    CAMrange R;
    if(nullFlag != 1)
    {R.initialize(base + i, bound + i, stride);}

    return R;
}

CAMrange      CAMrange::operator - (long i)
{
    CAMrange R;
    if(nullFlag != 1)
    {R.initialize(base - i, bound - i, stride);}

    return R;
}

CAMrange  operator + (long i, CAMrange& A)
{
    CAMrange R;
    if(A.nullFlag != 1)
    {R.initialize(A.base + i, A.bound + i, A.stride);}

    return R;
}

void  CAMrange::CAMrangeError(const CAMrange& A)
{   
    if(((A.bound - A.base) + 1) < 0 )
    {
    cerr <<"Error : Negative Number of Elements In Index Range " << endl;
    CAMmvaExit();
    } 
    if(A.stride <= 0 )
    {
    cerr <<"Error : Non Positive Stride in Index Range " << endl;
    CAMmvaExit();
    }
}
//
//********************************************************************************
//                     CPP File End 
//********************************************************************************
//


  

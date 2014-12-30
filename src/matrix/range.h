//
//******************************************************************************
//                    RANGE.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Thu Oct 26 11:40:59 1995
//
//********************************************************************************
//

#include <iostream.h>

#ifndef __CAMUNDERSCORE__  
    class CAMunderscore;
#endif

#ifndef __CAMRANGE__
#define __CAMRANGE__

#include "mvaimpexp.h" // A

class __IMPEXP__ CAMrange
{

protected :

    long  base;
    long  bound;
    long  stride;
    int  singleArgumentFlag;
    int  underscoreFlag;
    int  nullFlag;

public :

//
//  Constructors
//
    CAMrange();
    CAMrange( const CAMrange& A);
    CAMrange(long inputSize);
    CAMrange(long inputBase, long inputBound);
    CAMrange(long inputBase, long inputBound, long inputStride);
    CAMrange(const CAMunderscore& A);
//
//  Destructor 
//
    ~CAMrange();
//
//  Assignment 
//
    CAMrange& operator = ( const CAMrange& A);
//
//  Output 
//
    __IMPEXP__ friend ostream& operator <<(ostream& out_stream, const CAMrange& A);
//
//  initialize
//
    void      initialize();
    void      initialize(const CAMrange& R);
    void      initialize(long inputSize);
    void      initialize(long inputBase, long inputBound);
    void      initialize(long inputBase, long inputBound, long inputStride);
//
//  Public Member Functions
//
    long          getBase()        const {return base;};
    long          getBound()    const {return bound;};
    long          getCount()    const {return long((bound - base)/stride + 1);};
    long          getStride()    const {return stride;};
    long          length()        const {return long((bound - base)/stride + 1);};
    int          getUnderscoreFlag()        const {return underscoreFlag;};
    int          getNullFlag()        const {return nullFlag;};
    int          getSingleArgumentFlag()    const {return singleArgumentFlag;};
    CAMrange      operator ++ (int);
    CAMrange      operator -- (int);
    CAMrange      operator + (long i);
    CAMrange      operator - (long i);
    friend CAMrange  operator + (long i, CAMrange& A);
    static void  CAMrangeError(const CAMrange& A);

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//


  

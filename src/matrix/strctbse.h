//
//******************************************************************************
//                    STRCTBSE.H
//******************************************************************************
//

#include <iostream.h>
#include "mvalngbase.h"
#include "access.h"
#include "mvaexit.h"

//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Thu Nov 02 13:33:24 1995
//
//********************************************************************************
//

#ifndef __CAMSTRUCTUREBASE__
#define __CAMSTRUCTUREBASE__

#include "mvaimpexp.h" // B
//
//
//
//extern CAMrange __IMPEXP__ CAMnullRange;
//
//
//

class __IMPEXP__ CAMstructureBase
{
//
//  
//
    friend class CAMstructureBaseTest;
//
//  
//

public :

    int          dataDimension;
    MVAlongBase      indexBegin;
    MVAlongBase      indexEnd;
    MVAlongBase      indexStride;
    MVAlongBase      indexBeginBase;
    MVAlongBase      indexEndBase;

public :

    CAMstructureBase();
    CAMstructureBase( const CAMstructureBase& A);
    CAMstructureBase(long dimension);
    CAMstructureBase(const CAMrange& R1, const CAMrange& R2 = CAMnullRange,
   const CAMrange& R3 = CAMnullRange, const CAMrange&R4 = CAMnullRange,
   const CAMrange& R5 = CAMnullRange, const CAMrange&R6 = CAMnullRange,
   const CAMrange& R7 = CAMnullRange);
//
//  Destructor 
//
    ~CAMstructureBase();
//
//  Output 
//
    __IMPEXP__ friend ostream& operator <<(ostream& out_stream, const CAMstructureBase& A);
//
//  Assignment 
//
    CAMstructureBase& operator = ( const CAMstructureBase& A);
//
//  Initialization
//
    void  initialize();
    void  initialize(long dimension);
    void  initialize(const CAMstructureBase& A);
    void  initialize(const CAMrange& R1, const CAMrange& R2 = CAMnullRange,
    const CAMrange& R3 = CAMnullRange, const CAMrange&R4 = CAMnullRange,
    const CAMrange& R5 = CAMnullRange, const CAMrange&R6 = CAMnullRange,
    const CAMrange& R7 = CAMnullRange);
//
//  
//
    int  getDimension()const {return dataDimension;};
    const CAMstructureBase&  operator[](long i) const;
    CAMstructureBase&  operator[](long i);
    long  getIndexBase() const;
    long  getIndexBound() const;
    long  getIndexStride() const;
    long  getIndexCount() const;
    long  getIndexBaseBase() const;
    void  setIndexBase(long i);
    void  setIndexStride(long i);
    void  setAllIndexBase(long i);
    static long  exchangeReferenceIndex(long i);
//
//  
//
    long  getFullDataCount()const;
    long  getDataCount()const;
    int  isSubset() const;
    int  isConformingTo(const CAMstructureBase& A) const;
    int  isStrictConformingTo(const CAMstructureBase& A) const;
    int  isMatrixOpConformingTo(const CAMstructureBase& A) const;
    void  getNormalizedLoops(long& loopDimension, long& Offset, MVAlongBase& Count, MVAlongBase& Stride) const;
    void  initializeMinStructure(CAMstructureBase& A) const;
    void  setStructureSubset(const CAMrange& R1, const CAMrange& R2 = CAMnullRange,
   const CAMrange& R3 = CAMnullRange, const CAMrange&R4 = CAMnullRange,
   const CAMrange& R5 = CAMnullRange, const CAMrange&R6 = CAMnullRange,
   const CAMrange& R7 = CAMnullRange);
//
//  error handling
//
    static void  illegalDimension(long i, long dimension);
    static void  needToSelectDimension();

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//






  

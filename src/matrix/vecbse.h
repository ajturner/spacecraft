//
//******************************************************************************
//                    VECBSE.H
//******************************************************************************
//

#include <iostream.h>
#include <string.h>
#include "strctbse.h"
#include "datahndl.h"
#include "access.h"
#include "mvaexit.h"
#include "camtype.h"
#include "typehndl.h"

//
//  
//
//
//********************************************************************************
//
//            Chris Anderson  (C) UCLA
//
//            Tue Apr 16 11:30:42 1996
//
//********************************************************************************
//
#ifndef __NO_COMPLEX__
#define __NO_COMPLEX__
#endif
//
//
#include "mvaimpexp.h" // C
//
//
#ifndef _CAMMATRIXBASE_
class CAMmatrixBase;
#endif
#ifndef _CAMARRAYBASE_
class CAMarrayBase;
#endif
//
//  
//

#ifndef _CAMVECTORBASE_
#define _CAMVECTORBASE_


class __IMPEXP__ CAMvectorBase
{

public :

    CAMstructureBase  Structure;
    CAMdataHandler*  DataP;
    int  typeValue;
    int  referenceFlag;
    long  vectorBaseReferenceCount;

public :

    friend class CAMmatrixBase;

//
//  Constructors
//
    CAMvectorBase();
    CAMvectorBase( const CAMvectorBase& A);
    CAMvectorBase(int d_type);
    CAMvectorBase(int d_type, const CAMrange& R1); 
//
//  Destructor 
//
    ~CAMvectorBase();
//
//  Assignment
//
    void  operator = (double value);
    void  operator = (const CAMvectorBase& A);
    void  operator = (const CAMmatrixBase& A);
//
//  Output 
//
    __IMPEXP__ friend ostream& operator <<(ostream& out_stream, const CAMvectorBase& A);
//
//  Input
//
    __IMPEXP__ friend istream&  operator >>(istream& in_stream, CAMvectorBase& A);
//
//  Initialization Functions
//
    void  initialize();
    void  initialize(const CAMvectorBase& A);
    void  initialize(int d_type);
    void  initialize(int d_type, const CAMrange& R1); 
//
//  Unary and Binary Operations
//
    CAMvectorBase  operator-() const;
    CAMvectorBase  operator+(const CAMvectorBase& A) const;
    CAMmatrixBase  operator+(const CAMmatrixBase& A) const;
    CAMvectorBase  operator-(const CAMvectorBase& A) const;
    CAMmatrixBase  operator-(const CAMmatrixBase& A) const;
    CAMmatrixBase  operator*(const CAMvectorBase& A) const;
    CAMvectorBase  operator*(const CAMmatrixBase& A) const;
    void  operator+=(const CAMvectorBase& A);
    void  operator+=(const CAMmatrixBase& A);
    void  operator-=(const CAMvectorBase& A);
    void  operator-=(const CAMmatrixBase& A);
    CAMvectorBase operator~() const;
    CAMvectorBase transpose() const;

    long  CAMvectorBase::getIndexBase() const; 
    long  CAMvectorBase::getIndexBound() const; 
    long  CAMvectorBase::getIndexStride() const; 
    long  CAMvectorBase::getIndexCount() const; 
    void  CAMvectorBase::setIndexBase(long i); 
    void  CAMvectorBase::setIndexStride(long i); 

//
//  Scaler Operations
//
    CAMvectorBase  operator +(const double value) const;
    __IMPEXP__ friend CAMvectorBase  operator +(const double value, const CAMvectorBase& A);
    CAMvectorBase  operator -(const double value) const;
    __IMPEXP__ friend CAMvectorBase  operator -(const double value, const CAMvectorBase& A);
    void  operator +=(const double value);
    void  operator -=(const double value);
    CAMvectorBase  operator *(double value) const;
    __IMPEXP__ friend CAMvectorBase  operator *(double value, const CAMvectorBase& A);
    CAMvectorBase  operator /(double value) const;
    __IMPEXP__ friend CAMvectorBase  operator /(double value, const CAMvectorBase& A);
    void  operator *=(double value);
    void  operator /=(double value);
//
//  Additional Scalar Functions
//
    void  setToValue(double value);
    CAMvectorBase  plusValue(double value);
    CAMvectorBase  minusValue(double value);
//
//  Helper Functions
//
    void  setTemporaryFlag(){DataP->setTemporaryFlag();};
    void  initializeReturnArgument(const CAMstructureBase& S, int dataT);
    void  initializeReturnArgument(const CAMvectorBase& A);
    void  initializeMinDuplicate(const CAMvectorBase& A);
    void*  getDataPointer() const {return DataP->getDataPointer();};
    void*  getDataPointer(long i1, long i2) const; 
    CAMmatrixBase  asMatrix() const;
    CAMarrayBase  asArray() const;
//
    long  getDimension() const {return 1;};
//
//  Reference Counting
//
    void  incrementReferenceCount();
    void  decrementReferenceCount(){vectorBaseReferenceCount--;};
    int  getReferenceCount() const {return vectorBaseReferenceCount;};
    void  setReferenceCount(int refValue){vectorBaseReferenceCount = refValue;};
    static void  referenceCountError();
//
//  Error Handling Routines
//
    static void  indexCheck(const CAMstructureBase &S, long i1, long i2);
    static void  indexErrorMessage(long indexDimension, long base, long bound, long index);
    static void  nonConformingMessage(const CAMstructureBase &A,const CAMstructureBase &B);
    static void  doubleConversionError(const CAMstructureBase& A);
    static void  objectConversionError(const CAMstructureBase& A);
    static void  nullOperandError();
    static void  nullOperandError(char* Operation);
    static void  inputSizeError();
//
//  Utility Functions
//
    double  max() const;
    double  min() const;
    double  maxAbs() const;
    double  minAbs() const;
    double  infNorm() const;
    double  pNorm(int p) const;
    double  pNorm(long p) const;
    double  pNorm(float p) const;
    double  pNorm(double p) const;

    double dot(const CAMvectorBase& V) const; 

//
//  temporary and reference utility functions
//
    void  exchangeContentsWith(CAMvectorBase& B);
    void  initializeReferenceDuplicate(const CAMvectorBase& B);

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//
  

//
//******************************************************************************
//                    MATBSE.H
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
#ifndef _CAMARRAYBASE_
class CAMarrayBase;
#endif
#ifndef _CAMVECTORBASE_
class CAMvectorBase;
#endif
//
//  
//

#ifndef _CAMMATRIXBASE_
#define _CAMMATRIXBASE_


class __IMPEXP__ CAMmatrixBase
{

public :

    CAMstructureBase  Structure;
    CAMdataHandler*  DataP;
    int  typeValue;
    int  referenceFlag;
    long  matrixBaseReferenceCount;

public :

    friend class CAMvectorBase;

//
//  Constructors
//
    CAMmatrixBase();
    CAMmatrixBase( const CAMmatrixBase& A);
    CAMmatrixBase(int d_type);
    CAMmatrixBase(int d_type, const CAMrange& R1, const CAMrange& R2); 
//
//  Destructor 
//
    ~CAMmatrixBase();
//
//  Assignment
//
    void  operator = (double value);
    void  operator = (const CAMmatrixBase& A);
    void  operator = (const CAMvectorBase& A);
//
//  Output 
//
    __IMPEXP__ friend ostream& operator <<(ostream& out_stream, const CAMmatrixBase& A);
//
//  Input
//
    __IMPEXP__ friend istream&  operator >>(istream& in_stream, CAMmatrixBase& A);
//
//  Initialization Functions
//
    void  initialize();
    void  initialize(const CAMmatrixBase& A);
    void  initialize(int d_type);
    void  initialize(int d_type, const CAMrange& R1, const CAMrange& R2); 
//
//  Unary and Binary Operations
//
    CAMmatrixBase  operator-() const;
    CAMmatrixBase  operator+(const CAMmatrixBase& A) const;
    CAMmatrixBase  operator+(const CAMvectorBase& A) const;
    CAMmatrixBase  operator-(const CAMmatrixBase& A) const;
    CAMmatrixBase  operator-(const CAMvectorBase& A) const;
    CAMmatrixBase  operator*(const CAMmatrixBase& A) const;
    CAMvectorBase  operator*(const CAMvectorBase& A) const;
    CAMmatrixBase  operator/(const CAMmatrixBase& A) const;
    CAMvectorBase  operator/(const CAMvectorBase& A) const;
    void  operator+=(const CAMmatrixBase& A);
    void  operator+=(const CAMvectorBase& A);
    void  operator-=(const CAMmatrixBase& A);
    void  operator-=(const CAMvectorBase& A);
    void  operator*=(const CAMmatrixBase& A);
    void  operator*=(const CAMvectorBase& A);
    void  operator/=(const CAMmatrixBase& A);
    void  operator/=(const CAMvectorBase& A);
    CAMmatrixBase transpose() const;
    CAMmatrixBase operator~() const; 
//
//  Scaler Operations
//
    CAMmatrixBase  operator +(const double value) const;
    __IMPEXP__ friend CAMmatrixBase  operator +(const double value, const CAMmatrixBase& A);
    CAMmatrixBase  operator -(const double value) const;
    __IMPEXP__ friend CAMmatrixBase  operator -(const double value, const CAMmatrixBase& A);
    void  operator +=(const double value);
    void  operator -=(const double value);
    CAMmatrixBase  operator *(double value) const;
    __IMPEXP__ friend CAMmatrixBase  operator *(double value, const CAMmatrixBase& A);
    CAMmatrixBase  operator /(double value) const;
    __IMPEXP__ friend CAMmatrixBase  operator /(double value, const CAMmatrixBase& A);
    void  operator *=(double value);
    void  operator /=(double value);
//
//  Additional Scalar Functions
//
    void  setToValue(double value);
    CAMmatrixBase  plusValue(double value);
    CAMmatrixBase  minusValue(double value);
//
//  Helper Functions
//
    void  setTemporaryFlag(){DataP->setTemporaryFlag();};
    void  initializeReturnArgument(const CAMstructureBase& S, int dataT);
    void  initializeReturnArgument(const CAMmatrixBase& A);
    void  initializeMinDuplicate(const CAMmatrixBase& A);
    void*  getDataPointer() const {return DataP->getDataPointer();};
    void*  getDataPointer(long i1, long i2) const; 
    CAMarrayBase  asArray() const;
    CAMvectorBase  asVector() const;
//
//  Structure Functions
//
    const CAMstructureBase&  operator[](long i) const;
    CAMstructureBase&  operator[](long i);
    void  setAllIndexBase(long i){Structure.setAllIndexBase(i);};
    long  getDimension() const {return Structure.getDimension();};
//
//  Reference Counting
//
    void  incrementReferenceCount();
    void  decrementReferenceCount(){matrixBaseReferenceCount--;};
    int  getReferenceCount() const {return matrixBaseReferenceCount;};
    void  setReferenceCount(int refValue){matrixBaseReferenceCount = refValue;};
    static void  referenceCountError();
//
//  Error Handling Routines
//
    static void  indexCheck(const CAMstructureBase &S, long i1, long i2);
    static void  indexErrorMessage(long indexDimension, long base, long bound, long index);
    static void  nonConformingMessage(const CAMstructureBase &A,const CAMstructureBase &B);
    static void  doubleConversionError(const CAMstructureBase& A);
    static void  nonSquareMessage(); 
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
// 
//  Matrix Specific Utility Routines  
//
    CAMmatrixBase inverse() const;
//
//  temporary and reference utility functions
//
    void  exchangeContentsWith(CAMmatrixBase& B);
    void  initializeReferenceDuplicate(const CAMmatrixBase& B);

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//
  

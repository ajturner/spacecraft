//
//******************************************************************************
//                    ARRAYBSE.H
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
#ifndef _CAMVECTORBASE_
class CAMvectorBase;
#endif
//
//  
//

#ifndef _CAMARRAYBASE_
#define _CAMARRAYBASE_


class __IMPEXP__ CAMarrayBase
{

public :

    CAMstructureBase  Structure;
    CAMdataHandler*  DataP;
    int  typeValue;
    int  referenceFlag;
    long  arrayBaseReferenceCount;

public :

//
//  Constructors
//
    CAMarrayBase();
    CAMarrayBase( const CAMarrayBase& A);
    CAMarrayBase(int d_type);
    CAMarrayBase(int d_type, const CAMrange& R1, const CAMrange& R2 = CAMnullRange,
                        const CAMrange& R3 = CAMnullRange, const CAMrange&R4 = CAMnullRange,
                        const CAMrange& R5 = CAMnullRange, const CAMrange&R6 = CAMnullRange,
                        const CAMrange& R7 = CAMnullRange);
//
//  Destructor 
//
    ~CAMarrayBase();
//
//  Assignment
//
    void  operator = (double value);
    void  operator = (const CAMarrayBase& A);
//
//  Output 
//
    __IMPEXP__ friend ostream& operator <<(ostream& out_stream, const CAMarrayBase& A);
//
//  Input
//
    __IMPEXP__ friend istream&  operator >>(istream& in_stream, CAMarrayBase& A);
//
//  Initialization Functions
//
    void  initialize();
    void  initialize(const CAMarrayBase& A);
    void  initialize(int d_type);
    void  initialize(int d_type, const CAMrange& R1, const CAMrange& R2 = CAMnullRange,
                        const CAMrange& R3 = CAMnullRange, const CAMrange&R4 = CAMnullRange,
                        const CAMrange& R5 = CAMnullRange, const CAMrange&R6 = CAMnullRange,
                        const CAMrange& R7 = CAMnullRange);
//
//  Unary and Binary Operations
//
    CAMarrayBase  operator-() const;
    CAMarrayBase  operator+(const CAMarrayBase& A) const;
    CAMarrayBase  operator-(const CAMarrayBase& A) const;
    CAMarrayBase  operator*(const CAMarrayBase& A) const;
    CAMarrayBase  operator/(const CAMarrayBase& A) const;
    void  operator+=(const CAMarrayBase& A);
    void  operator-=(const CAMarrayBase& A);
    void  operator*=(const CAMarrayBase& A);
    void  operator/=(const CAMarrayBase& A);
//
//  Scaler Operations
//
    CAMarrayBase  operator +(const double value) const;
    __IMPEXP__ friend CAMarrayBase  operator +(const double value, const CAMarrayBase& A);
    CAMarrayBase  operator -(const double value) const;
    __IMPEXP__ friend CAMarrayBase  operator -(const double value, const CAMarrayBase& A);
    void  operator +=(const double value);
    void  operator -=(const double value);
    CAMarrayBase  operator *(double value) const;
    __IMPEXP__ friend CAMarrayBase  operator *(double value, const CAMarrayBase& A);
    CAMarrayBase  operator /(double value) const;
    __IMPEXP__ friend CAMarrayBase  operator /(double value, const CAMarrayBase& A);
    void  operator *=(double value);
    void  operator /=(double value);
//
//  Additional Scalar Functions
//
    void  setToValue(double value);
    CAMarrayBase  plusValue(double value);
    CAMarrayBase  minusValue(double value);
//
//  Helper Functions
//
    void  setTemporaryFlag(){DataP->setTemporaryFlag();};
    void  initializeReturnArgument(const CAMstructureBase& S, int dataT);
    void  initializeReturnArgument(const CAMarrayBase& A);
    void  initializeMinDuplicate(const CAMarrayBase& A);
    void*  getDataPointer() const {return DataP->getDataPointer();};
    void*  getDataPointer(long i1, long i2 = 0, long i3 = 0, long i4 = 0,
    long i5 =0, long i6 = 0, long i7 = 0) const;
    CAMmatrixBase  asMatrix() const;
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
    void  decrementReferenceCount(){arrayBaseReferenceCount--;};
    int  getReferenceCount() const {return arrayBaseReferenceCount;};
    void  setReferenceCount(int refValue){arrayBaseReferenceCount = refValue;};
    static void  referenceCountError();
//
//  Error Handling Routines
//
    static void  indexCheck(const CAMstructureBase &S, long i1);
    static void  indexCheck(const CAMstructureBase &S, long i1, long i2);
    static void  indexCheck(const CAMstructureBase &S, long i1, long i2, long i3);
    static void  indexCheck(const CAMstructureBase &S, long i1, long i2, long i3, long i4);
    static void  indexCheck(const CAMstructureBase &S, long i1, long i2, long i3, long i4, long i5);
    static void  indexCheck(const CAMstructureBase &S, long i1, long i2, long i3, long i4, long i5, long i6);
    static void  indexCheck(const CAMstructureBase &S, long i1, long i2, long i3, long i4, long i5, long i6, long i7);
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
//
//  temporary and reference utility functions
//
    void  exchangeContentsWith(CAMarrayBase& B);
    void  initializeReferenceDuplicate(const CAMarrayBase& B);

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//


  

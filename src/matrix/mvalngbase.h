//
//******************************************************************************
//                    MVALNGBASE.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//
//********************************************************************************
//
#ifndef __CAMMVALONGBASE__
#define __CAMMVALONGBASE__

#include <iostream.h>
#include "mvaimpexp.h"

class __IMPEXP__ MVAlongBase
{

public :

    long*  dataPointer;
    long  size;

public :

    MVAlongBase();
    MVAlongBase( const MVAlongBase& A);
    MVAlongBase(long inSize);
    MVAlongBase(long* data, long inSize);
//
//  Destructor 
//
    virtual ~MVAlongBase();
//
//  Output 
//
    __IMPEXP__ friend ostream& operator <<(ostream& out_stream, const MVAlongBase& A);
//
//  Input
//
    __IMPEXP__ friend istream&  operator >>(istream& in_stream, MVAlongBase& A);
//
//  Assignment 
//
    MVAlongBase& operator = ( const MVAlongBase& A);
//
//  Initialization
//
    void  initialize();
    void  initialize(const MVAlongBase& A);
    void  initialize(long inSize);
    void  initialize(long* data, long inSize);
//
//  Resizing
//
    virtual void  resizeTo(long n);
//
//  Access
//
    long  getSize() const {return size;};
    long*  getDataPointer() {return dataPointer;};
    const long*  getDataPointer() const{return dataPointer;};
    inline long  &  operator[](long Index)
{
#ifndef NOBOUNDS
   if (( Index < 0  ) || ( Index >= size))
   {MVAlongBase::indexError(Index);}
#endif
   return(*(dataPointer + Index));
};
    inline const long &  operator[] (long Index ) const
{
#ifndef NOBOUNDS
   if (( Index < 0  ) || ( Index >= size))
   {MVAlongBase::indexError(Index);}
#endif
   return(*(dataPointer + Index));
};
    void  copyToArray(long* A) const;
//
//  Logical Operands
//
    int  operator == (const MVAlongBase& A) const;
    int  operator != (const MVAlongBase& A) const;

protected :

//
//  Error Handling
//
    static void  indexError(long Index);
    static void  sizeError(long Lsize, long Rsize);
    static void  reSizeError(long size);
    static void  inputError(long ArraySize, long RequiredSize);
//
//  Input Utility
//
    static void  inputLong(istream& in, MVAlongBase& A);
//
//  Memory Allocation
//
    virtual long*  newLong(long size);
    virtual void  deleteLong();

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//

  

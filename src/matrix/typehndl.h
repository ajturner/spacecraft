//
//******************************************************************************
//                    TYPEHNDL.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Tue Oct 17 21:17:10 1995
//
//********************************************************************************
//
//
//  
//
#ifndef __NO_COMPLEX__
#include <complex.h>
#endif
//
//  
//

#include "camtype.h"
#include "iostream.h"


#ifndef __CAMTYPEHANDLER__
#define __CAMTYPEHANDLER__

#undef   __IMPEXP__
#ifdef   __BCPLUSPLUS__
#ifdef   __EXPORT_MVASUPPORT_B__
#define  __IMPEXP__ __export
#else
#define  __IMPEXP__  __import
#endif
#else
#define  __IMPEXP__
#endif

#ifdef   __STATIC__
#undef   __IMPEXP__
#define  __IMPEXP__
#endif


class __IMPEXP__ CAMTypeHandler
{

protected :

    int  dType;
    void*  dP;

public :

//
//  constructors
//
      CAMTypeHandler() {dType = 0; dP = 0;};
      CAMTypeHandler(const CAMTypeHandler& T)
    {
    dType = T.dType;
    switch (dType)
    {
      case CAMType::typeNull: dP = 0; break;
      case CAMType::typeInt :
       dP = new int[1]; *((int*)dP) = *((int*)T.dP); break;
      case CAMType::typeLong :
       dP = new long[1]; *((long*)dP) = *((long*)T.dP); break;
      case CAMType::typeFloat :
       dP = new float[1]; *((float*)dP) = *((float*)T.dP); break;
      case CAMType::typeDouble :
       dP = new double[1]; *((double*)dP) = *((double*)T.dP); break;
#ifndef __NO_COMPLEX__
      case CAMType::typeComplex :
       dP = new complex[1]; *((complex*)dP) = *((complex*)T.dP); break;
#endif
    }
   };
      CAMTypeHandler(int i)
       {dType = CAMType::typeInt; dP= new int[1]; *((int*)dP) = i;};
      CAMTypeHandler(long l)
       {dType = CAMType::typeLong; dP= new long[1]; *((long*)dP) = l;};
      CAMTypeHandler(float f)
       {dType = CAMType::typeFloat; dP= new float[1]; *((float*)dP) = f;};
      CAMTypeHandler(double d)
       {dType = CAMType::typeDouble; dP= new double[1]; *((double*)dP) = d;};
#ifndef __NO_COMPLEX__
      CAMTypeHandler(complex c)
       {dType = CAMType::typeComplex; dP= new complex[1]; *((complex*)dP) = c;};
#endif
      virtual ~CAMTypeHandler()
        {
            dPDelete();
        };
    
    /*! \brief Deletes the data pointer 
        * \detail Determines the type that the void* pointer points to, then reinterpret_cast<T*> to delete.
        */
    void dPDelete()
        {
            if(dP != 0) 
            {
                if(dType == CAMType::typeInt)
                    delete reinterpret_cast<int*>(dP);
                else if(dType == CAMType::typeLong)
                    delete reinterpret_cast<long*>(dP);
                else if(dType == CAMType::typeFloat)
                    delete reinterpret_cast<float*>(dP);
                else if(dType == CAMType::typeDouble)
                    delete reinterpret_cast<double*>(dP);
                #ifndef __NO_COMPLEX__
                else if(dType == CAMType::typeComplex)
                    delete reinterpret_cast<complex*>(dP);
                #endif                    
            }
        };

//
//  Assignment
//
    void  operator = (CAMTypeHandler & T)
    {
        dPDelete();
    switch (T.dType)
    {
      case CAMType::typeNull: dP = 0;  break;
      case CAMType::typeInt :
       dP = new int[1]; *((int*)dP) = *((int*)T.dP); break;
      case CAMType::typeLong :
       dP = new long[1]; *((long*)dP) = *((long*)T.dP); break;
      case CAMType::typeFloat :
       dP = new float[1]; *((float*)dP) = *((float*)T.dP); break;
      case CAMType::typeDouble :
       dP = new double[1]; *((double*)dP) = *((double*)T.dP); break;
#ifndef __NO_COMPLEX__
      case CAMType::typeComplex :
       dP = new complex[1]; *((complex*)dP) = *((complex*)T.dP); break;
#endif
    }
   };
    void  operator = (int i)
       {dPDelete(); dType = CAMType::typeInt; dP= new int[1]; *((int*)dP) = i;};
    void  operator = (long l)
       {dPDelete(); dType = CAMType::typeLong; dP= new long[1]; *((long*)dP) = l;};
    void  operator = (float f)
       {dPDelete(); dType = CAMType::typeFloat; dP= new float[1]; *((float*)dP) = f;};
    void  operator = (double d)
       {dPDelete(); dType = CAMType::typeDouble; dP= new double[1]; *((double*)dP) = d;};
#ifndef __NO_COMPLEX__
    void  operator = (complex c)
       {dPDelete(); dType = CAMType::typeComplex; dP= new complex[1]; *((complex*)dP) = c;};
#endif
//
//  output
//
    friend ostream&  operator <<(ostream& out_stream, const CAMTypeHandler& A)
{    switch (A.dType)
    {
      case CAMType::typeNull:  break;
      case CAMType::typeInt :
       out_stream <<  *((int*)A.dP); break;
      case CAMType::typeLong :
       out_stream << *((long*)A.dP); break;
      case CAMType::typeFloat :
       out_stream << *((float*)A.dP); break;
      case CAMType::typeDouble :
       out_stream << *((double*)A.dP); break;
#ifndef __NO_COMPLEX__
      case CAMType::typeComplex :
       out_stream << *((complex*)A.dP); break;
#endif
    }
    return out_stream;
};
//
//  Conversions
//
      operator int()
    {
    int r;
    switch (dType)
    {
     case CAMType::typeInt : r = *((int*)dP); break;
     case CAMType::typeLong : r = int(*((long*)dP)); break;
     case CAMType::typeFloat : r = int(*((float*)dP)); break;
     case CAMType::typeDouble : r =  int(*((double*)dP)); break;
#ifndef __NO_COMPLEX__
     case CAMType::typeComplex : r =  int(real(*((complex*)dP))); break;
#endif
    }
    return r;
    };
      operator long()
    {
    long r;
    switch (dType)
    {
     case CAMType::typeInt : r = long(*((int*)dP)); break;
     case CAMType::typeLong : r =     (*((long*)dP)); break;
     case CAMType::typeFloat : r = long(*((float*)dP)); break;
     case CAMType::typeDouble : r =  long(*((double*)dP)); break;
#ifndef __NO_COMPLEX__
     case CAMType::typeComplex : r =  long(real(*((complex*)dP))); break;
#endif
    }
    return r;
    };
      operator float()
    {
    float r;
    switch (dType)
    {
     case CAMType::typeInt : r = float(*((int*)dP)); break;
     case CAMType::typeLong : r = float(*((long*)dP)); break;
     case CAMType::typeFloat : r =      (*((float*)dP)); break;
     case CAMType::typeDouble : r =  float(*((double*)dP)); break;
#ifndef __NO_COMPLEX__
     case CAMType::typeComplex : r =  float(real(*((complex*)dP))); break;
#endif
    }
    return r;
    };
      operator double()
    {
    double r;
    switch (dType)
    {
     case CAMType::typeInt : r = double(*((int*)dP)); break;
     case CAMType::typeLong : r = double(*((long*)dP)); break;
     case CAMType::typeFloat : r = double(*((float*)dP)); break;
     case CAMType::typeDouble : r =   (*((double*)dP)); break;
#ifndef __NO_COMPLEX__
     case CAMType::typeComplex : r =  double(real(*((complex*)dP))); break;
#endif
    }
    return r;
    };
#ifndef __NO_COMPLEX__
      operator complex()
    {
    complex r;
    switch (dType)
    {
     case CAMType::typeInt : r = complex(*((int*)dP)); break;
     case CAMType::typeLong : r = complex(*((long*)dP)); break;
     case CAMType::typeFloat : r = complex(*((float*)dP)); break;
     case CAMType::typeDouble : r = complex(*((double*)dP)); break;
     case CAMType::typeComplex : r =  (*((complex*)dP)); break;
    }
    return r;
    };
#endif

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//


  

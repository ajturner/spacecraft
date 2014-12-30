//
//******************************************************************************
//                    CAMTYPE.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Fri Sep 22 12:31:07 1995
//
//********************************************************************************
//

#ifndef __CAMTYPE__
#define __CAMTYPE__
//
#include "mvaimpexp.h" 

class __IMPEXP__ CAMType
{

protected :

    int  Value;

public :


    enum {typeNull ,typeInt ,typeLong ,typeFloat ,typeDouble ,typeComplex  }; 
//
//  constructors
//
      CAMType() {Value = 0;};
      CAMType(const CAMType& T) {Value = T.Value; };
      CAMType(int dataTypeValue) {Value = dataTypeValue;};
      ~CAMType(){};
//
//  Assignment
//
    void  operator=(CAMType & T){Value = T.Value;};
//
//  Access Functions
//
    int  getTypeValue()  {return Value;};
    void  setTypeValue(int dataTypeValue) {Value = dataTypeValue;};
    int  getConversionValue()
    {
          int r;
          switch (Value)
          {
          case CAMType::typeInt : r = 10; break;
          case CAMType::typeLong : r =  20; break;
          case CAMType::typeFloat : r =  20; break;
          case CAMType::typeDouble : r =  30; break;
          case CAMType::typeComplex : r =  40; break;
          }
          return r;
    };

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//


  

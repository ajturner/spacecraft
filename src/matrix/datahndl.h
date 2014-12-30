//
//******************************************************************************
//                    DATAHNDL.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Mon Mar 11 12:55:09 1996
//
//********************************************************************************
//

#include <iostream.h>
#include "camtype.h"

#ifndef __NO_COMPLEX__
#define __NO_COMPLEX__
#endif
#ifndef __NO_COMPLEX__
#include<complex.h>
#endif

#ifndef __CAMDATAHANDLER__
#define __CAMDATAHANDLER__

#include "mvaimpexp.h" // B

class __IMPEXP__ CAMdataHandler
{

public :

    int  dataType;
    void*  dataPointer;
    long  dataSize;
    int  temporaryFlag;
    int  referenceCount;

public :

//
//  Constructors
//
    CAMdataHandler();
    CAMdataHandler( const CAMdataHandler& A);
    CAMdataHandler(long size, int dType);
//
//  Destructor 
//
    ~CAMdataHandler();
//
//  Assignment 
//
    CAMdataHandler& operator = ( const CAMdataHandler& A);
//
//  Output 
//
    __IMPEXP__ friend ostream& operator <<(ostream& out_stream, const CAMdataHandler& A);
//
//  
//
    void  initialize();
    void  initialize(const CAMdataHandler& H);
    void  initialize(long size, int dType);
    void  allocateData(long size, int dType);
    void  copyData(long size, void* dataP);
    void  destroyData();
    void  setTypeFlag(int dType);
    int  getDataType() const {return dataType;};
    long  getDataSize() const {return dataSize;};
    void  setDataSize(long size){dataSize = size;};
    void  setTemporaryFlag(){temporaryFlag = 1;};
    int  getTemporaryFlag()const{return temporaryFlag;};
    void  incrementReferenceCount();
    void  decrementReferenceCount(){referenceCount--;};
    int  getReferenceCount() const {return referenceCount;};
    void  setReferenceCount(int refValue){referenceCount = refValue;};
    static void  referenceCountError();
//
//  Data Pointer Access
//
    void*  getDataPointer() const {return dataPointer;};
    void  setDataPointer(int* i){dataPointer = i;};
    void  setDataPointer(long* l){dataPointer = l;};
    void  setDataPointer(float* f){dataPointer = f;};
    void  setDataPointer(double* d){dataPointer = d;};
    void  getDataValue(long index, int& i) const {i = *((int*)(dataPointer) + index);};
    void  getDataValue(long index, long& l) const {l = *((long*)(dataPointer) + index);};
    void  getDataValue(long index, float& f) const {f = *((float*)(dataPointer) + index);};
    void  getDataValue(long index, double& d) const {d = *((double*)(dataPointer) + index);};
#ifndef __NO_COMPLEX__
    void setDataPointer(complex* c){dataPointer = c;};
    void getDataValue(long index, complex& c) const {c = *((complex*)(dataPointer) + index);}
#endif

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//


  

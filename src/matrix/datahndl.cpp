#include "datahndl.h"
#include "blas.h"
#include "mvaexit.h"


//
//******************************************************************************
//                    DATAHNDL.CPP
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Thu Sep 07 00:49:17 1995
//
//********************************************************************************
//
//
//********************************************************************************
//                    CONSTRUCTORS
//********************************************************************************

CAMdataHandler::CAMdataHandler()
{
    dataType        = 0;
    dataPointer     = 0;
    dataSize        = 0;
    temporaryFlag   = 0;
    referenceCount  = 0;
}

CAMdataHandler::CAMdataHandler( const CAMdataHandler& A)
{
    if(A.temporaryFlag == 1)
    {
        dataType        = A.dataType;
        dataSize        = A.dataSize;
        dataPointer     = A.dataPointer;
        temporaryFlag   = 0;
        referenceCount  = 0;

    }
    else
    {
        allocateData(A.dataSize,A.dataType);
        setTypeFlag(A.dataType);
        copyData(A.dataSize,A.dataPointer);
        temporaryFlag   = 0;
        referenceCount  = 0;
    }
}

CAMdataHandler::CAMdataHandler(long size, int dType)
{
        allocateData(size,dType);
        setTypeFlag(dType);
        temporaryFlag   = 0;
        referenceCount  = 0;
}
//
//********************************************************************************
//                    DESTRUCTOR
//********************************************************************************
//
CAMdataHandler::~CAMdataHandler()
{
    if(temporaryFlag == 0) destroyData();
}
//
//********************************************************************************
//                    OUTPUT
//********************************************************************************
//
ostream&  operator <<(ostream& out_stream, const CAMdataHandler& A)
{

#ifndef __NO_COMPLEX__
    complex* cdataP;
#endif

    long i;

    switch(A.dataType)
    {
    case  CAMType::typeInt :
    int i_out;
    for(i = 0; i < A.dataSize; i++)
    {A.getDataValue(i, i_out); out_stream  << i_out << " ";}
    out_stream  << endl;
    break;

    case  CAMType::typeLong :
    long l_out;
    for(i = 0; i < A.dataSize; i++)
    {A.getDataValue(i, l_out); out_stream  << l_out << " ";}
    out_stream << endl;
    break;

    case  CAMType::typeFloat :
    float f_out;
    for(i = 0; i < A.dataSize; i++)
    {A.getDataValue(i, f_out); out_stream  << f_out << " ";}
    out_stream << endl;
    break;

    case  CAMType::typeDouble :
    double d_out;
    for(i = 0; i < A.dataSize; i++)
    {A.getDataValue(i, d_out); out_stream  << d_out << " ";}
    out_stream << endl;
    break;

#ifndef __NO_COMPLEX__
    case  CAMType::typeComplex :
    cdataP = (complex*)A.dataPointer;
    for(i = 0; i < A.dataSize; i++)
    out_stream << *(cdataP + i) << " ";
    out_stream << endl;
    break;
#endif

    }
    return(out_stream);

}
//
//********************************************************************************
//                    ASSIGNMENT
//********************************************************************************
//
CAMdataHandler&  CAMdataHandler::operator =( const CAMdataHandler& A)
{
    if(A.temporaryFlag == 1)
    {
        dataType        = A.dataType;
        dataSize        = A.dataSize;
        dataPointer     = A.dataPointer;
        temporaryFlag   = 0;
        referenceCount  = 0;
    }
    else
    {
        destroyData();
        allocateData(A.dataSize,A.dataType);
        setTypeFlag(A.dataType);
        copyData(A.dataSize,A.dataPointer);
        temporaryFlag   = 0;
        referenceCount  = 0;
    }
    return *this;
}

//
//********************************************************************************
//                    MEMBER_FUNCTIONS
//********************************************************************************
//

void  CAMdataHandler::initialize()
{
    destroyData();

    dataType        = 0;
    dataPointer     = 0;
    dataSize        = 0;
    temporaryFlag   = 0;
    referenceCount  = 0;
}

void  CAMdataHandler::initialize(const CAMdataHandler& A)
{


    if(A.temporaryFlag == 1)
    {
        dataType        = A.dataType;
        dataSize        = A.dataSize;
        dataPointer     = A.dataPointer;
        temporaryFlag   = 0;
    }
    else
    {
        destroyData();
        allocateData(A.dataSize,A.dataType);
        setTypeFlag(A.dataType);
        copyData(A.dataSize,A.dataPointer);
        temporaryFlag   = 0;
    }
}

void CAMdataHandler::initialize(long size, int dType)
{
        destroyData();
        allocateData(size,dType);
        setTypeFlag(dType);
        temporaryFlag   = 0;
}
void  CAMdataHandler::setTypeFlag(int dType)
{

    switch(dType)
    {
    case CAMType::typeInt :

    dataType        = CAMType::typeInt;
    break;

    case CAMType::typeLong :

    dataType        = CAMType::typeLong;
    break;

    case CAMType::typeFloat :

    dataType        = CAMType::typeFloat;
    break;

    case CAMType::typeDouble :

    dataType        = CAMType::typeDouble;
    break;

#ifndef __NO_COMPLEX__
    case CAMType::typeComplex :
    dataType        = CAMType::typeComplex;
    break;
#endif
    }

}

void  CAMdataHandler::allocateData(long size, int dType)
{

    switch(dType)
    {
    case CAMType::typeInt :
    dataSize        = size;
    dataPointer     = new int[size];
    break;

    case CAMType::typeLong :
    dataSize        = size;
    dataPointer     = new long[size];
    break;

    case CAMType::typeFloat :
    dataSize        = size;
    dataPointer     = new float[size];
    break;

    case CAMType::typeDouble :
    dataSize        = size;
    dataPointer     = new double[size];
    break;

#ifndef __NO_COMPLEX__
    case CAMType::typeComplex :
    dataSize        = size;
    dataPointer     = new complex[size];
    break;
#endif
    }
//
//  initialize with zero's
//
#ifndef __NO_BLAS__
    int    izero    = 0;
    long   lzero    = 0;
    float  fzero    = 0.0;
    double dzero    = 0.0;
    long   strideX = 0;
    long   strideY = 1;
#endif

    switch(dType)
    {
    case  CAMType::typeInt :
    register int* idataP;
#ifdef __NO_BLAS__
    for(idataP = (int*)dataPointer; idataP < (int*)dataPointer + size; idataP++)
     *(idataP) = 0;
#else
    idataP = (int*)dataPointer;
    icopy_(&size,&izero,&strideX, idataP, &strideY);
#endif
    break;

    case  CAMType::typeLong :
    register long* ldataP;
#ifdef __NO_BLAS__
    for(ldataP = (long*)dataPointer; ldataP < (long*)dataPointer + size; ldataP++)
     *(ldataP) = 0;
#else
    ldataP = (long*)dataPointer;
    lcopy_(&size,&lzero,&strideX, ldataP, &strideY);
#endif
    break;

    case  CAMType::typeFloat :
    register  float* fdataP;
#ifdef __NO_BLAS__
    for(fdataP = (float*)dataPointer; fdataP < (float*)dataPointer + size; fdataP++)
     *(fdataP) = 0.0;
#else
    fdataP = (float*)dataPointer;
    scopy_(&size,&fzero,&strideX, fdataP, &strideY);
#endif
    break;

    case  CAMType::typeDouble :
    register double* ddataP;
#ifdef __NO_BLAS__
    for(ddataP = (double*)dataPointer; ddataP < (double*)dataPointer + size; ddataP++)
     *(ddataP) = 0.0;
#else
    ddataP = (double*)dataPointer;
    dcopy_(&size,&dzero,&strideX, ddataP, &strideY);
#endif

    break;

#ifndef __NO_COMPLEX__
    case  CAMType::typeComplex :
    complex* cdataP;
    for(cdataP = (complex*)dataPointer; cdataP < (complex*)dataPointer + size; cdataP++)
    *(cdataP) = complex(0.0,0.0);
    break;
#endif

    }
}

void  CAMdataHandler::copyData(long Size, void* dataP)
{
#ifndef __NO_BLAS__
    long strideX = 1;
    long strideY = 1;
#endif

    switch(dataType)
    {
    case  CAMType::typeInt :
    register int* idataP; register  int* inIdataP;
#ifdef __NO_BLAS__
    for(idataP = (int*)dataPointer, inIdataP = (int*)dataP;
    idataP < (int*)dataPointer + Size; idataP++, inIdataP++)
    *(idataP) = *(inIdataP);
#else
    idataP   = (int*)dataPointer;
    inIdataP = (int*)dataP;
    icopy_(&Size,inIdataP,&strideX, idataP, &strideY);
#endif

    break;

    case  CAMType::typeLong :
    register long* ldataP; register  long* inLdataP;
#ifdef __NO_BLAS__
    for(ldataP = (long*)dataPointer, inLdataP = (long*)dataP;
    ldataP < (long*)dataPointer + Size; ldataP++, inLdataP++)
    *(ldataP) = *(inLdataP);
#else
    ldataP   = (long*)dataPointer;
    inLdataP = (long*)dataP;
    lcopy_(&Size,inLdataP,&strideX, ldataP, &strideY);
#endif

    break;

    case  CAMType::typeFloat :
    register float* fdataP;  register float*  inFdataP;
#ifdef __NO_BLAS__
    for(fdataP = (float*)dataPointer, inFdataP = (float*)dataP;
    fdataP < (float*)dataPointer + Size; fdataP++, inFdataP++)
    *(fdataP) = *(inFdataP);
#else
    fdataP = (float*)dataPointer;
    inFdataP = (float*)dataP;
    scopy_(&Size,inFdataP,&strideX, fdataP, &strideY);
#endif

    break;

    case  CAMType::typeDouble :
    register double* ddataP;  register double* inDdataP;
#ifdef __NO_BLAS__
    for(ddataP = (double*)dataPointer, inDdataP = (double*)dataP;
    ddataP < (double*)dataPointer + Size; ddataP++, inDdataP++)
     *(ddataP) = *(inDdataP);
#else
    ddataP   = (double*)dataPointer;
    inDdataP = (double*)dataP;
    dcopy_(&Size,inDdataP,&strideX, ddataP, &strideY);
#endif

    break;

#ifndef __NO_COMPLEX__
    case  CAMType::typeComplex :
    complex* cdataP;  complex* inCdataP;
    for(cdataP = (complex*)dataPointer, inCdataP = (complex*)dataP;
    cdataP < (complex*)dataPointer + Size; cdataP++, inCdataP++)
     *(cdataP) = *(inCdataP);
    break;
#endif

    }
}

void  CAMdataHandler::destroyData()
{
    if(dataType != 0)
    {
    switch(dataType)
    {
    case  CAMType::typeInt :
    int* idataP;
    idataP = (int*)dataPointer;
    if(idataP != 0) delete [] idataP;
    break;

    case  CAMType::typeLong :
    long* ldataP;
    ldataP = (long*)dataPointer;
    if(ldataP != 0) delete [] ldataP;
    break;

    case  CAMType::typeFloat :
    float* fdataP;
    fdataP = (float*)dataPointer;
    if(fdataP != 0) delete [] fdataP;
    break;

    case  CAMType::typeDouble :
    double* ddataP;
    ddataP = (double*)dataPointer;
    if(ddataP != 0) delete [] ddataP;
    break;

#ifndef __NO_COMPLEX__
    case  CAMType::typeComplex :
    complex* cdataP;
    cdataP = (complex*)dataPointer;
    if(cdataP != 0) delete [] cdataP;
    break;
#endif
    }

    }
}
//
//********************************************************************************
//                    Reference Counting Functions
//********************************************************************************
//

void  CAMdataHandler::incrementReferenceCount()
{
    if(referenceCount == 0) CAMdataHandler::referenceCountError();
    referenceCount++;
}

void  CAMdataHandler::referenceCountError()
{
cerr << " Cannot Use Reference Counting on Objects New\'d by the Compiler " << endl;
CAMmvaExit();
}
//
//********************************************************************************
//                     CPP File End
//********************************************************************************
//


  

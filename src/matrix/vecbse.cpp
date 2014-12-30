#include "arraybse.h"
#include "vecbse.h"
#include "matbse.h" 
#include "matbse.h"
#include "bnengine.h"
#include "matbse.h" 
#include "blas.h"
//
//***************************************************************
//                    VECBSE.CPP
//***************************************************************
//
//
//*****************************************************************
//
//            Chris Anderson
//
//            Mon Sep 11 12:49:20 1995
//
//*****************************************************************
//
//
//*****************************************************************
//                    CONSTRUCTORS
//*****************************************************************
//
//
//*****************************************************************
//               
//*****************************************************************
//
CAMvectorBase::CAMvectorBase()
: Structure()
{
    DataP                   = 0;
    typeValue               = 0;
    referenceFlag           = 0;
    vectorBaseReferenceCount = 0;
}

CAMvectorBase::CAMvectorBase(int d_type)
: Structure()
{
    DataP                   = 0;
    typeValue               = d_type;
    referenceFlag           = 0;
    vectorBaseReferenceCount = 0;
}

CAMvectorBase::CAMvectorBase(const CAMvectorBase& A)
:Structure(A.Structure)
{
    if(A.DataP == 0)
    {DataP = 0;}
    else
    {
     if(A.referenceFlag == 1)
     {DataP = A.DataP; }
     else if(A.DataP->getTemporaryFlag() == 1)
     {
      DataP = new CAMdataHandler(*(A.DataP));
      DataP ->setReferenceCount(1);
     }
     else
     {
      A.Structure.initializeMinStructure(Structure);
      DataP = new CAMdataHandler(Structure.getFullDataCount(),A.DataP->getDataType());
      DataP->setReferenceCount(1);
      //
      //  copy based on type
      //
      CAMbinaryEngine::doubleAequalToB(Structure, *DataP, A.Structure, *A.DataP);
      //
      //
      //
     }
    }
    typeValue               = A.typeValue;
    referenceFlag           = 0;
    vectorBaseReferenceCount = 0;
}

CAMvectorBase::CAMvectorBase(int d_type, const CAMrange& R1)
:Structure()
{
     Structure.initialize(R1,_(R1.getBase(),R1.getBase()));
     DataP = new CAMdataHandler(Structure.getFullDataCount(),d_type);
     DataP->setReferenceCount(1);
     referenceFlag           = 0;
     vectorBaseReferenceCount = 0;
}

//
//*****************************************************************
//                    DESTRUCTOR
//*****************************************************************
//
CAMvectorBase::~CAMvectorBase()
{
    if(DataP != 0)
     {
     DataP->decrementReferenceCount();
    if(DataP->getReferenceCount() < 0)
    {
    cerr << " Error : Reference Count < 0" << endl;
     }
     if(DataP->getReferenceCount() == 0) delete DataP;
    }
}
void CAMvectorBase::operator =(double value)
{
//
//  NEED CONVERSION CHECK
//
    if(DataP == 0)
    {
    Structure.initialize(_(1,1),_(1,1));
    DataP = new CAMdataHandler(1,CAMType::typeDouble);
    DataP->setReferenceCount(1);
    referenceFlag  = 0;
    vectorBaseReferenceCount = 0;
    }
    else
    {
    CAMstructureBase AStructure(_(1,1),_(1,1));
    if(Structure.isStrictConformingTo(AStructure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,AStructure);}
    }

    CAMbinaryEngine::doubleAequalToAlpha(Structure, *DataP, value);
}
void  CAMvectorBase::operator =( const CAMvectorBase& A)
{
//
//  NEED CONVERSION CHECK
//
    if(DataP == 0)
    {
    A.Structure.initializeMinStructure(Structure);
    DataP = new CAMdataHandler(Structure.getFullDataCount(),typeValue);
    DataP->setReferenceCount(1);
    typeValue               = CAMType::typeDouble;
    referenceFlag           = 0;
    vectorBaseReferenceCount = 0;
    }
    else
    {
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
    }

    CAMbinaryEngine::doubleAequalToB(Structure, *DataP, A.Structure, *A.DataP);
}
void  CAMvectorBase::operator =( const CAMmatrixBase& A)
{
//
//  NEED CONVERSION CHECK
//
    if(DataP == 0)
    {
    A.Structure.initializeMinStructure(Structure);
    DataP = new CAMdataHandler(Structure.getFullDataCount(),typeValue);
    DataP->setReferenceCount(1);
    typeValue               = CAMType::typeDouble;
    referenceFlag           = 0;
    vectorBaseReferenceCount = 0;
    }
    else
    {
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
    }

    CAMbinaryEngine::doubleAequalToB(Structure, *DataP, A.Structure, *A.DataP);
}

//
//********************************************************************************
//                    OUTPUT
//********************************************************************************
//
ostream& operator <<(ostream& out_stream, const CAMvectorBase& A)
{
    const long* beginPtr  = A.Structure.indexBegin.getDataPointer();
    const long* endPtr    = A.Structure.indexEnd.getDataPointer();
    const long* stridePtr = A.Structure.indexStride.getDataPointer();

    int  saveWidth=out_stream.width();
    double OutValue;

    long i1, i2;

    for(i1 = *beginPtr; i1 <= *endPtr; i1 += *stridePtr)
    {
    for(i2 = *(beginPtr+1); i2 <= *(endPtr +1); i2 += *(stridePtr+1))
    {

     out_stream.width(saveWidth);
     OutValue =*((double*)A.getDataPointer(i1,i2));
     if(OutValue < 0 )
     out_stream << OutValue <<" ";
     else
     out_stream << " " << OutValue <<" ";
    }
    out_stream << endl;
    }
    return(out_stream);
}

istream& operator >>(istream& in_stream, CAMvectorBase& A)
{
    const long* beginPtr  = A.Structure.indexBegin.getDataPointer();
    const long* endPtr    = A.Structure.indexEnd.getDataPointer();
    const long* stridePtr = A.Structure.indexStride.getDataPointer();

    long i1, i2;

    for(i1 = *beginPtr; i1 <= *endPtr; i1 += *stridePtr)
    {
    for(i2 = *(beginPtr+1); i2 <= *(endPtr +1); i2 += *(stridePtr+1))
    {
     if( !( in_stream >> *((double*)A.getDataPointer(i1,i2))))
     CAMarrayBase::inputSizeError();
    }}
    return(in_stream);
}

//
//*****************************************************************
//             INITIALIZATION MEMBER_FUNCTIONS
//*****************************************************************
//

void  CAMvectorBase::initialize()
{
    Structure.initialize();
    if(DataP != 0)
     {
      DataP->decrementReferenceCount();
      if(DataP->getReferenceCount() == 0) delete DataP;
     }
    DataP = 0;
    typeValue      = 0;
    referenceFlag  = 0;
    vectorBaseReferenceCount = 0;
}

void  CAMvectorBase::initialize(int d_type)
{
    Structure.initialize();
    if(DataP != 0)
     {
      DataP->decrementReferenceCount();
      if(DataP->getReferenceCount() == 0) delete DataP;
     }
    DataP = 0;
    typeValue      = d_type;
    referenceFlag  = 0;
    vectorBaseReferenceCount = 0;
}

void  CAMvectorBase::initialize(const CAMvectorBase& A)
{
//
//  NEED CONVERSION CHECK
//
    if(DataP != 0)
    {
    DataP->decrementReferenceCount();
    if(DataP->getReferenceCount() == 0) delete DataP;
    }

    if(A.DataP != 0)
    {
    A.Structure.initializeMinStructure(Structure);

    DataP = new CAMdataHandler(Structure.getFullDataCount(),A.DataP->getDataType());
    DataP->setReferenceCount(1);
    CAMbinaryEngine::doubleAequalToB(Structure, *DataP, A.Structure, *A.DataP);
    }
    else
    {
    DataP = 0;
    Structure.initialize();
    }

    typeValue      = A.typeValue;
    referenceFlag  = 0;
    vectorBaseReferenceCount = 0;
}

void  CAMvectorBase::initialize(int d_type, const CAMrange& R1)
{
     Structure.initialize(R1,_(R1.getBase(),R1.getBase()));

     if(DataP != 0)
     {
     DataP->decrementReferenceCount();
     if(DataP->getReferenceCount() == 0) delete DataP;
     }

     DataP = new CAMdataHandler(Structure.getFullDataCount(),d_type);
     DataP->setReferenceCount(1);
     referenceFlag  = 0;
     vectorBaseReferenceCount = 0;
}

//
//***************************************************************
//                    ARRAYOPS.CPP
//***************************************************************
//
//
//*****************************************************************
//
void  CAMvectorBase::initializeReturnArgument(const CAMvectorBase& A)
{
    A.Structure.initializeMinStructure(Structure);
    DataP = new CAMdataHandler(Structure.getFullDataCount(),A.DataP->getDataType());
    DataP->setReferenceCount(1);
}
void  CAMvectorBase::initializeReturnArgument(const CAMstructureBase& S, int dataT)
{
    S.initializeMinStructure(Structure);
    DataP = new CAMdataHandler(Structure.getFullDataCount(), dataT);
    DataP->setReferenceCount(1);
}
void  CAMvectorBase::initializeMinDuplicate(const CAMvectorBase& A)
{

    if(A.DataP == 0) return;

    long i;
    long icount    = 0;
    long dimension = 0;

    for(i = 1; i <= A.Structure.getDimension(); i++)
    if(A.Structure[i].getIndexCount() != 1) dimension++;


    if(dimension == 0) dimension = 1;
    Structure.initialize(dimension);


    for(i = 1; i <= A.Structure.getDimension(); i++)
    {
      if(A.Structure[i].getIndexCount() != 1)
      {
      Structure.indexBegin[icount]     = 1;
      Structure.indexBeginBase[icount] = 1;
      Structure.indexEndBase[icount]   = A.Structure[i].getIndexCount();
      Structure.indexEnd[icount]       = A.Structure[i].getIndexCount();
      Structure.indexStride[icount]    = 1;
      icount++;
      }
    }

    if(icount == 0)
    {
    Structure.indexBegin[icount]     = 1;
    Structure.indexBeginBase[icount] = 1;
    Structure.indexEndBase[icount]   = 1;
    Structure.indexEnd[icount]       = 1;
    Structure.indexStride[icount]    = 1;
    }
    DataP = new CAMdataHandler(Structure.getFullDataCount(), A.typeValue);
    DataP->setReferenceCount(1);
//
//  copy over data
//
    *this = A;
}
//
//*****************************************************************
//                    Operators
//*****************************************************************
//
CAMvectorBase CAMvectorBase::operator-() const
{
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S;
    S.initializeReturnArgument(*this);

    CAMbinaryEngine::doubleAequalToMinusB(S.Structure, *S.DataP, Structure, *DataP);
    S.setTemporaryFlag();
    return S;
}

CAMvectorBase CAMvectorBase::operator+(const CAMvectorBase& A) const
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S;
    S.initializeReturnArgument(A.Structure,A.DataP->getDataType());

    CAMbinaryEngine::doubleCequalAplusB(Structure, *DataP, A.Structure, *A.DataP,
    S.Structure, *S.DataP);

    S.setTemporaryFlag();
    return S;
}

CAMmatrixBase CAMvectorBase::operator+(const CAMmatrixBase& A) const
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S;
    S.initializeReturnArgument(A.Structure,A.DataP->getDataType());

    CAMbinaryEngine::doubleCequalAplusB(Structure, *DataP, A.Structure, *A.DataP,
    S.Structure, *S.DataP);

    S.setTemporaryFlag();
    return S;
}
CAMvectorBase CAMvectorBase::operator-(const CAMvectorBase& A) const
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S;
    S.initializeReturnArgument(A.Structure,A.DataP->getDataType());

    CAMbinaryEngine::doubleCequalAminusB(Structure, *DataP, A.Structure, *A.DataP,
    S.Structure, *S.DataP);

    S.setTemporaryFlag();
    return S;
}
CAMmatrixBase CAMvectorBase::operator-(const CAMmatrixBase& A) const
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S;
    S.initializeReturnArgument(A.Structure,A.DataP->getDataType());

    CAMbinaryEngine::doubleCequalAminusB(Structure, *DataP, A.Structure, *A.DataP,
    S.Structure, *S.DataP);

    S.setTemporaryFlag();
    return S;
}

CAMmatrixBase CAMvectorBase::operator*(const CAMvectorBase& A) const
{
    if(Structure.isMatrixOpConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//
//
//  Prepare Operands
//
    int STempFlag = 0;
    int TTempFlag = 0;

    CAMvectorBase* S;
    CAMvectorBase* T;

    if(Structure.isSubset()  == 0)
    { S = (CAMvectorBase*)this;}
    else
    {
     STempFlag = 1;
     S = new CAMvectorBase();
     S->initializeReturnArgument(*this);
     *S = *this;
    }

    if(A.Structure.isSubset()  == 0)
    { T = (CAMvectorBase*)&A;}
    else
    {
     TTempFlag = 1;
     T = new CAMvectorBase();
     T->initializeReturnArgument(A);
     *T = A;
    }
//
//  return argument
//
    long  Rows = (*S).Structure[1].getIndexCount();
    long  Cols = A.Structure[2].getIndexCount();

    CAMrange R1((*S).Structure[1].getIndexBase(),
    (*S).Structure[1].getIndexBase() +  Rows  - 1);

    CAMrange R2(A.Structure[2].getIndexBase(),
    A.Structure[2].getIndexBase() +  Cols  - 1);

    CAMmatrixBase R(CAMType::typeDouble,R1, R2);
//
//  dgemm performs the operation R := alpha*op(S)*op(T) + beta*R;
//  op(matrix) is either the matrix or its transpose.
//  the characters transX below specify that S and T are 'n'ot
//  to be transposed.
//
//  R = m by n
//  S = m by k
//  T = k by n
//
    char transa = 'n';
    char transb = 'n';

    long m = R[1].getIndexCount();
    long n = R[2].getIndexCount();
    long k = (*S).Structure[2].getIndexCount();

    double* s = (double*)((*S).getDataPointer());
    double* t = (double*)((*T).getDataPointer());
    double* r = (double*)(   R.getDataPointer());

    long lds =  (*S).Structure[1].getIndexCount();
    long ldt =  (*T).Structure[1].getIndexCount();
    long ldr =  R[1].getIndexCount();

    double alpha = 1.0;
    double beta  = 0.0;

    short f1 = 1;
    short f2 = 1;

    dgemm_(&transa, &transb, &m, &n, &k, &alpha, s, &lds, t, &ldt,
    &beta, r, &ldr,f1,f2);
//
//  clean up
//
    if(STempFlag == 1) delete S;
    if(TTempFlag == 1) delete T;

    R.setTemporaryFlag();
    return R;
}



CAMvectorBase CAMvectorBase::operator*(const CAMmatrixBase& A) const
{
    if(Structure.isMatrixOpConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//
//
//  Prepare Operands
//
    int STempFlag = 0;
    int TTempFlag = 0;

    CAMvectorBase* S;
    CAMmatrixBase* T;

    if(Structure.isSubset()  == 0)
    { S = (CAMvectorBase*)this;}
    else
    {
     STempFlag = 1;
     S = new CAMvectorBase();
     S->initializeReturnArgument(*this);
     *S = *this;
    }

    if(A.Structure.isSubset()  == 0)
    { T = (CAMmatrixBase*)&A;}
    else
    {
     TTempFlag = 1;
     T = new CAMmatrixBase();
     T->initializeReturnArgument(A);
     *T = A;
    }
//
//  return argument
//
    long  Rows = (*S).Structure[1].getIndexCount();
    long  Cols = A.Structure[2].getIndexCount();

    CAMrange R1((*S).Structure[1].getIndexBase(),
    (*S).Structure[1].getIndexBase() +  Rows  - 1);

    CAMrange R2(A.Structure[2].getIndexBase(),
    A.Structure[2].getIndexBase() +  Cols  - 1);

    CAMvectorBase R;
    if(R1.length() == 1)
    {R.initialize(CAMType::typeDouble,R2);}
    else    
    {R.initialize(CAMType::typeDouble,R1);}
//
//  dgemm performs the operation R := alpha*op(S)*op(T) + beta*R;
//  op(matrix) is either the matrix or its transpose.
//  the characters transX below specify that S and T are 'n'ot
//  to be transposed.
//
//  R = m by n
//  S = m by k
//  T = k by n
//
    char transa = 'n';
    char transb = 'n';

    long m = R.Structure[1].getIndexCount();
    long n = R.Structure[2].getIndexCount();
    long k = (*S).Structure[2].getIndexCount();

    double* s = (double*)((*S).getDataPointer());
    double* t = (double*)((*T).getDataPointer());
    double* r = (double*)(   R.getDataPointer());

    long lds =  (*S).Structure[1].getIndexCount();
    long ldt =  (*T).Structure[1].getIndexCount();
    long ldr =  R.Structure[1].getIndexCount();

    double alpha = 1.0;
    double beta  = 0.0;

    short f1 = 1;
    short f2 = 1;

    dgemm_(&transa, &transb, &m, &n, &k, &alpha, s, &lds, t, &ldt,
    &beta, r, &ldr,f1,f2);
//
//  clean up
//
    if(STempFlag == 1) delete S;
    if(TTempFlag == 1) delete T;

    R.setTemporaryFlag();
    return R;
}
//
//*****************************************************************
//                    op = Operators
//*****************************************************************
//

void CAMvectorBase::operator+=(const CAMvectorBase& A)
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//

    CAMbinaryEngine::doubleAplusEqualB(Structure, *DataP, A.Structure, *A.DataP);
}
//
//*****************************************************************
//                    op = Operators
//*****************************************************************
//

void CAMvectorBase::operator+=(const CAMmatrixBase& A)
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//

    CAMbinaryEngine::doubleAplusEqualB(Structure, *DataP, A.Structure, *A.DataP);
}
void CAMvectorBase::operator-=(const CAMvectorBase& A)
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//

    CAMbinaryEngine::doubleAminusEqualB(Structure, *DataP, A.Structure, *A.DataP);
}
void CAMvectorBase::operator-=(const CAMmatrixBase& A)
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//

    CAMbinaryEngine::doubleAminusEqualB(Structure, *DataP, A.Structure, *A.DataP);
}

CAMvectorBase CAMvectorBase::transpose() const
{
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S(*this);
//
//  Only need to change indices, since the copy constructor
//  moves the data.
//
    S.Structure.indexBegin[0] = Structure.indexBegin[1];
    S.Structure.indexBegin[1] = Structure.indexBegin[0];
    S.Structure.indexBeginBase[0] = Structure.indexBeginBase[1];
    S.Structure.indexBeginBase[1] = Structure.indexBeginBase[0];
    S.Structure.indexEnd[0] = Structure.indexEnd[1];
    S.Structure.indexEnd[1] = Structure.indexEnd[0];
    S.Structure.indexEndBase[0] = Structure.indexEndBase[1];
    S.Structure.indexEndBase[1] = Structure.indexEndBase[0];
    S.Structure.indexStride[0] = Structure.indexStride[1];
    S.Structure.indexStride[1] = Structure.indexStride[0];

    S.setTemporaryFlag();
    return S;
}



long  CAMvectorBase::getIndexBase() const
{
    long dimensionReference = 1;

    if((Structure.indexEndBase[0] - Structure.indexBeginBase[0]) == 0)
    dimensionReference = 2;

    return   Structure.indexBegin[dimensionReference-1];
}

long CAMvectorBase::getIndexBound() const
{
    long dimensionReference = 1;

    if((Structure.indexEndBase[0] - Structure.indexBeginBase[0]) == 0)
    dimensionReference = 2;

    return   Structure.indexEnd[dimensionReference-1];
}


long  CAMvectorBase::getIndexStride() const
{
    long dimensionReference = 1;

    if((Structure.indexEndBase[0] - Structure.indexBeginBase[0]) == 0)
    dimensionReference = 2;

    return    Structure.indexStride[dimensionReference-1];
}

long  CAMvectorBase::getIndexCount() const
{
    long dimensionReference = 1;

    if((Structure.indexEndBase[0] - Structure.indexBeginBase[0]) == 0)
    dimensionReference =2;

    return  ((Structure.indexEnd[dimensionReference - 1]
           - Structure.indexBegin[dimensionReference - 1]) + 1);
}

void  CAMvectorBase::setIndexStride(long i)
{
    long dimensionReferenceA = 1;
    long dimensionReferenceB = 2;

    if((Structure.indexEndBase[0] - Structure.indexBeginBase[0]) == 0)
    {dimensionReferenceA = 2; dimensionReferenceB = 1;}


    Structure.indexStride[dimensionReferenceA - 1] = i;
    Structure.indexStride[dimensionReferenceB - 1] = 1;


}

void  CAMvectorBase::setIndexBase(long i)
{

    long dimensionReferenceA = 1;
    long dimensionReferenceB = 2;

    if((Structure.indexEndBase[0] - Structure.indexBeginBase[0]) == 0)
    {dimensionReferenceA = 2; dimensionReferenceB = 1;}


    long k      = dimensionReferenceA - 1;

    long offset = i - Structure.indexBegin[k];
    Structure.indexBegin[k]     = Structure.indexBegin[k]     + offset;
    Structure.indexEnd[k]       = Structure.indexEnd[k]       + offset;
    Structure.indexBeginBase[k] = Structure.indexBeginBase[k] + offset;
    Structure.indexEndBase[k]   = Structure.indexEndBase[k]   + offset;

    Structure.indexBegin[dimensionReferenceB - 1]     = Structure.indexBegin[k];
    Structure.indexEnd[dimensionReferenceB - 1]       = Structure.indexBegin[k];
    Structure.indexBeginBase[dimensionReferenceB - 1] = Structure.indexBegin[k];
    Structure.indexEndBase[dimensionReferenceB - 1]   = Structure.indexBegin[k] ;


}

CAMvectorBase CAMvectorBase::operator~() const
{
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S(*this);
//
//  Only need to change indices, since the copy constructor
//  moves the data.
//
    S.Structure.indexBegin[0] = Structure.indexBegin[1];
    S.Structure.indexBegin[1] = Structure.indexBegin[0];
    S.Structure.indexBeginBase[0] = Structure.indexBeginBase[1];
    S.Structure.indexBeginBase[1] = Structure.indexBeginBase[0];
    S.Structure.indexEnd[0] = Structure.indexEnd[1];
    S.Structure.indexEnd[1] = Structure.indexEnd[0];
    S.Structure.indexEndBase[0] = Structure.indexEndBase[1];
    S.Structure.indexEndBase[1] = Structure.indexEndBase[0];
    S.Structure.indexStride[0] = Structure.indexStride[1];
    S.Structure.indexStride[1] = Structure.indexStride[0];

    S.setTemporaryFlag();
    return S;
}
//
//*****************************************************************
//                    Operations with Scalers
//*****************************************************************
//
CAMvectorBase  CAMvectorBase::operator +(const double value) const
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase AStructure(_(1,1));
    if(Structure.isStrictConformingTo(AStructure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,AStructure);}

    CAMvectorBase S(*this);
    CAMbinaryEngine::doubleAplusEqualAlpha(S.Structure, *(S.DataP), value);

    S.setTemporaryFlag();
    return S;
}
CAMvectorBase  operator +(const double value, const CAMvectorBase& A)
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase  BStructure(_(1,1));
    if(A.Structure.isStrictConformingTo(BStructure) != 1)
    {CAMvectorBase::nonConformingMessage(A.Structure,BStructure);}

    CAMvectorBase S(A);
    CAMbinaryEngine::doubleAplusEqualAlpha(S.Structure, *(S.DataP), value);

    S.setTemporaryFlag();
    return S;
}

CAMvectorBase  CAMvectorBase::operator -(const double value) const
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase AStructure(_(1,1));
    if(Structure.isStrictConformingTo(AStructure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,AStructure);}

    CAMvectorBase S(*this);
    CAMbinaryEngine::doubleAminusEqualAlpha(S.Structure, *(S.DataP), value);

    S.setTemporaryFlag();
    return S;
}

CAMvectorBase  operator -(const double value, const CAMvectorBase& A)
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase  BStructure(_(1,1));
    if(A.Structure.isStrictConformingTo(BStructure) != 1)
    {CAMvectorBase::nonConformingMessage(A.Structure,BStructure);}

    CAMvectorBase S(A);
    CAMbinaryEngine::doubleAminusEqualAlpha(S.Structure, *(S.DataP), value);

    S.setTemporaryFlag();
    return S;
}

void  CAMvectorBase::operator +=(const double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase AStructure(_(1,1));
    if(Structure.isStrictConformingTo(AStructure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,AStructure);}

    CAMbinaryEngine::doubleAplusEqualAlpha(Structure, *(DataP), value);
}

void  CAMvectorBase::operator -=(const double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase AStructure(_(1,1));
    if(Structure.isStrictConformingTo(AStructure) != 1)
    {CAMvectorBase::nonConformingMessage(Structure,AStructure);}

    CAMbinaryEngine::doubleAminusEqualAlpha(Structure, *(DataP), value);
}

CAMvectorBase  CAMvectorBase::operator*(double value) const
{
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S(*this);
    CAMbinaryEngine::doubleAtimesEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

CAMvectorBase  operator *(double value, const CAMvectorBase& A)
{
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S(A);
    CAMbinaryEngine::doubleAtimesEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

CAMvectorBase  CAMvectorBase::operator /(double value) const
{
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S(*this);
    CAMbinaryEngine::doubleAdivideEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

CAMvectorBase  operator /(double value, const CAMvectorBase& A)
{
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S(A);
    CAMbinaryEngine::doubleAdivideEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

void  CAMvectorBase::operator *=(double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMbinaryEngine::doubleAtimesEqualAlpha(Structure, *DataP, value);
}

void  CAMvectorBase::operator /=(double value)
{
    CAMbinaryEngine::doubleAdivideEqualAlpha(Structure, *DataP, value);
}



void  CAMvectorBase::setToValue(double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMbinaryEngine::doubleAequalToAlpha(Structure, *DataP, value);
}

CAMvectorBase  CAMvectorBase::plusValue(double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S(*this);
    CAMbinaryEngine::doubleAplusEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

CAMvectorBase  CAMvectorBase::minusValue(double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMvectorBase S(*this);
    CAMbinaryEngine::doubleAminusEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

//
//*****************************************************************
//            Temporary and Reference Utilities
//*****************************************************************
//
void  CAMvectorBase::exchangeContentsWith(CAMvectorBase& B)
{
//
//  This routine exchanges the contents of *this with B.
//  The routine is typically used with *this input as
//  a null object and B a temporary object (i.e. the result
//  of an operator or function which returns B with the
//  temporary flag set). In such a case, the contents of
//  B are captured by *this --- resulting in a transfer of the
//  results without invoking a data copy.
//
//
    CAMstructureBase S_temp(Structure);
    CAMdataHandler*  DataP_temp        = DataP;
    int  typeValue_temp                = typeValue;
    int  referenceFlag_temp            = referenceFlag;
    long  vectorBaseReferenceCount_temp = vectorBaseReferenceCount;

    Structure.initialize(B.Structure);
    DataP                   = B.DataP;
    typeValue               = B.typeValue;
    referenceFlag           = B.referenceFlag;
    vectorBaseReferenceCount = B.vectorBaseReferenceCount;
//
    B.Structure.initialize(S_temp);
    B.DataP                   = DataP_temp;
    B.typeValue               = typeValue_temp;
    B.referenceFlag           = referenceFlag_temp;
    B.vectorBaseReferenceCount = vectorBaseReferenceCount_temp;
}

void  CAMvectorBase::initializeReferenceDuplicate(const CAMvectorBase& B)
{
//
//  This routine initializes *this with the contents of B and
//  and sets the *this reference flag.  This results in a
//  class instance whose data is that associated with B.
//
//  Typically this routine is used in a container class which
//  contains arrays --- and one wants to have sub-array access
//  for the contained class which is based upon the sub-array
//  access of the array class. 
//
    if(DataP != 0)
    {
    DataP->decrementReferenceCount();
     if(DataP->getReferenceCount() == 0) delete DataP;
    }

    Structure.initialize(B.Structure);
    DataP                   = B.DataP;
    DataP->incrementReferenceCount();  //One Reference for local copy
    DataP->incrementReferenceCount();  //One Reference for compiler copy
    typeValue               = B.typeValue;
    referenceFlag           = 1;
    vectorBaseReferenceCount = 0;
}

//
//*****************************************************************
//                    CONVERSIONS
//*****************************************************************
//
CAMmatrixBase  CAMvectorBase::asMatrix() const
{
    CAMmatrixBase S;
    if(DataP == 0) return S;

    CAMrange R1; CAMrange R2;

    if(Structure[1].getIndexCount() != 1)
    {
    R1.initialize(Structure[1].getIndexBase(), Structure[1].getIndexBound());
    R2.initialize(Structure[2].getIndexBase(), Structure[2].getIndexBound());
    }
    else
    {
    R1.initialize(Structure[2].getIndexBase(), Structure[2].getIndexBound());
    R2.initialize(Structure[1].getIndexBase(), Structure[1].getIndexBound());
    }
//
//
    S.initialize(CAMType::typeDouble, R1,R2);
    CAMbinaryEngine::doubleAequalToB(S.Structure, *(S.DataP), Structure, *DataP);
//
//
    S.setTemporaryFlag();
    return S;
}
CAMarrayBase  CAMvectorBase::asArray() const
{
    CAMarrayBase S;
    if(DataP == 0) return S;

    CAMrange R1;

    if(Structure[1].getIndexCount() != 1)
    {
    R1.initialize(Structure[1].getIndexBase(), Structure[1].getIndexBound());
    }
    else
    {
    R1.initialize(Structure[2].getIndexBase(), Structure[2].getIndexBound());
    }
//
    S.initialize(CAMType::typeDouble, R1);
    CAMbinaryEngine::doubleAequalToB(S.Structure, *(S.DataP), Structure, *DataP);
//
//
    S.setTemporaryFlag();
    return S;
}



void*  CAMvectorBase::getDataPointer(long i1, long i2) const
{
    const long* beginPtr  = Structure.indexBeginBase.getDataPointer();
    const long* endPtr    = Structure.indexEndBase.getDataPointer();
//
//  NEED CONVERSION CHECK
//
    double* dataPtr =  (double*)(DataP->dataPointer);

    long offset;
    offset  = (i1 - *(beginPtr))
    + ((*(endPtr) - *(beginPtr)) + 1)*(i2 - *(beginPtr + 1));


    return (void*)(dataPtr + offset);
}
//
//********************************************************************************
//                    Reference Counting Functions
//********************************************************************************
//

void  CAMvectorBase::incrementReferenceCount()
{
    if(vectorBaseReferenceCount == 0) CAMvectorBase::referenceCountError();
    vectorBaseReferenceCount++;
}

void  CAMvectorBase::referenceCountError()
{
cerr << " Cannot Use Reference Counting on Objects New\'d by the Compiler " << endl;
CAMmvaExit();
}
//
//*****************************************************************
//                    MEMBER_FUNCTIONS
//*****************************************************************
//


void  CAMvectorBase::indexCheck(const CAMstructureBase &S, long i1, long i2)
{
    if(S.dataDimension != 2)
    {
     cerr << " Error : Incorrect Vector Array Index Dimension " << endl;
     cerr << " Object Dimension = " << S.dataDimension
          << "--- Dimension Used = "<< 2 << endl;
     CAMmvaExit();
     }
     const long* indexBeginP = S.indexBegin.getDataPointer();
     const long* indexEndP = S.indexEnd.getDataPointer();
     if((i1 < *indexBeginP)||(i1 > *indexEndP))
     {
     CAMvectorBase::indexErrorMessage(1, *(indexBeginP), *(indexEndP), i1);
     }
     if((i2 < *(indexBeginP +1))||(i2 > *(indexEndP+1)))
     {
     CAMvectorBase::indexErrorMessage(2, *(indexBeginP+1), *(indexEndP+1), i2);
     }
}





void  CAMvectorBase::indexErrorMessage(long indexDimension, long base, long bound, long index)
{
     cerr << " Error :  Index " << indexDimension << " Out of Range " << endl;

     cerr << " Current Index Range  :(" << base << ", " << bound << ")"  << endl;
     cerr << " Index Used          : " << index << endl;
     CAMmvaExit();
}
void CAMvectorBase::nonConformingMessage(const CAMstructureBase& A,  const CAMstructureBase& B)
{
    long i;
    cerr << endl;
    cerr << "Error :  Object Dimensions not Compatable with Operation " << endl << endl;
    cerr << "Left  Operand Dimensions :   ";
    cerr << A[1].getIndexCount();
    for(i = 2; i <= A.dataDimension; i++)
    cerr <<  " x " << A[i].getIndexCount() ;
    cerr << endl << endl;
    cerr << "Right Operand Dimensions :   ";
    cerr << B[1].getIndexCount();
    for(i = 2; i <= B.dataDimension; i++)
    cerr <<  " x " << B[i].getIndexCount();
    cerr << endl << endl;
    CAMmvaExit();
}
void CAMvectorBase::doubleConversionError(const CAMstructureBase& A)
{
    long i;
    cerr << endl;
    cerr << "Dimensions not Compatable with Conversion to Double " << endl << endl;
    cerr << "Operand Dimensions :   ";
    cerr << A[1].getIndexCount();
    for(i = 2; i <= A.dataDimension; i++)
    cerr <<  " x " << A[i].getIndexCount() ;
    cerr << endl << endl;
    CAMmvaExit();
}

void CAMvectorBase::objectConversionError(const CAMstructureBase& A)
{
    long i;
    cerr << endl;
    cerr << " Dimensions not Compatable with Conversion Operator " << endl << endl;
    cerr << "Operand Dimensions :   ";
    cerr << A[1].getIndexCount();
    for(i = 2; i <= A.dataDimension; i++)
    cerr <<  " x " << A[i].getIndexCount() ;
    cerr << endl << endl;
    CAMmvaExit();
}
void CAMvectorBase::nullOperandError()
{
    cerr << endl;
    cerr << " Error : Null Object Used As Operand  " << endl;
    CAMmvaExit();
}
void CAMvectorBase::nullOperandError(char* Operation)
{
    cerr << endl;
    cerr << " Error : Null Object Used As Operand With "<< Operation << endl;
    CAMmvaExit();
}
void CAMvectorBase::inputSizeError()
{
    cerr << endl;
    cerr << " Input error : Insufficient # of data elements in input stream " << endl;
    CAMmvaExit();
}
//
//*****************************************************************
//                     CPP File End
//*****************************************************************
//










  

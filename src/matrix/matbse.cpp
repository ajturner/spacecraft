#include "arraybse.h"
#include "vecbse.h"
#include "matbse.h"
#include "vecbse.h" 
#include "bnengine.h"
#include "blas.h"
//
//***************************************************************
//                    MATBSE.CPP
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
CAMmatrixBase::CAMmatrixBase()
: Structure()
{
    DataP                   = 0;
    typeValue               = 0;
    referenceFlag           = 0;
    matrixBaseReferenceCount = 0;
}

CAMmatrixBase::CAMmatrixBase(int d_type)
: Structure()
{
    DataP                   = 0;
    typeValue               = d_type;
    referenceFlag           = 0;
    matrixBaseReferenceCount = 0;
}

CAMmatrixBase::CAMmatrixBase(const CAMmatrixBase& A)
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
    matrixBaseReferenceCount = 0;
}


//
//  Constructors
//

CAMmatrixBase::CAMmatrixBase(int d_type, const CAMrange& R1, const CAMrange& R2)
:Structure(R1,R2)
{
     DataP = new CAMdataHandler(Structure.getFullDataCount(),d_type);
     DataP->setReferenceCount(1);
     referenceFlag           = 0;
     matrixBaseReferenceCount = 0;
}

//
//*****************************************************************
//                    DESTRUCTOR
//*****************************************************************
//
CAMmatrixBase::~CAMmatrixBase()
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
void CAMmatrixBase::operator =(double value)
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
    matrixBaseReferenceCount = 0;
    }
    else
    {
    CAMstructureBase AStructure(_(1,1),_(1,1));
    if(Structure.isStrictConformingTo(AStructure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,AStructure);}
    }

    CAMbinaryEngine::doubleAequalToAlpha(Structure, *DataP, value);
}
void  CAMmatrixBase::operator =( const CAMmatrixBase& A)
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
    matrixBaseReferenceCount = 0;
    }
    else
    {
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
    }

    CAMbinaryEngine::doubleAequalToB(Structure, *DataP, A.Structure, *A.DataP);
}
void  CAMmatrixBase::operator =( const CAMvectorBase& A)
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
    matrixBaseReferenceCount = 0;
    }
    else
    {
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
    }

    CAMbinaryEngine::doubleAequalToB(Structure, *DataP, A.Structure, *A.DataP);
}
//
//********************************************************************************
//                    OUTPUT
//********************************************************************************
//
ostream& operator <<(ostream& out_stream, const CAMmatrixBase& A)
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

//    out_stream << *((double*)A.getDataPointer(i1,i2)) << " ";
    }

    out_stream << endl;
    }
    return(out_stream);

}
istream& operator >>(istream& in_stream, CAMmatrixBase& A)
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

//    in_stream << *((double*)A.getDataPointer(i1,i2)) << " ";
    }}
    return(in_stream);

}

//
//*****************************************************************
//             INITIALIZATION MEMBER_FUNCTIONS
//*****************************************************************
//

void  CAMmatrixBase::initialize()
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
    matrixBaseReferenceCount = 0;
}

void  CAMmatrixBase::initialize(int d_type)
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
    matrixBaseReferenceCount = 0;
}

void  CAMmatrixBase::initialize(const CAMmatrixBase& A)
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
    matrixBaseReferenceCount = 0;
}

void  CAMmatrixBase::initialize(int d_type, const CAMrange& R1, const CAMrange& R2)
{
     Structure.initialize(R1,R2);

     if(DataP != 0)
     {
     DataP->decrementReferenceCount();
     if(DataP->getReferenceCount() == 0) delete DataP;
     }

     DataP = new CAMdataHandler(Structure.getFullDataCount(),d_type);
     DataP->setReferenceCount(1);
     referenceFlag  = 0;
     matrixBaseReferenceCount = 0;
}

//
//***************************************************************
//                    ARRAYOPS.CPP
//***************************************************************
//
//
//*****************************************************************
//
void  CAMmatrixBase::initializeReturnArgument(const CAMmatrixBase& A)
{
    A.Structure.initializeMinStructure(Structure);
    DataP = new CAMdataHandler(Structure.getFullDataCount(),A.DataP->getDataType());
    DataP->setReferenceCount(1);
}
void  CAMmatrixBase::initializeReturnArgument(const CAMstructureBase& S, int dataT)
{
    S.initializeMinStructure(Structure);
    DataP = new CAMdataHandler(Structure.getFullDataCount(), dataT);
    DataP->setReferenceCount(1);
}
void  CAMmatrixBase::initializeMinDuplicate(const CAMmatrixBase& A)
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
CAMmatrixBase CAMmatrixBase::operator-() const
{
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S;
    S.initializeReturnArgument(*this);

    CAMbinaryEngine::doubleAequalToMinusB(S.Structure, *S.DataP, Structure, *DataP);
    S.setTemporaryFlag();
    return S;
}

CAMmatrixBase CAMmatrixBase::operator+(const CAMmatrixBase& A) const
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
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

CAMmatrixBase CAMmatrixBase::operator+(const CAMvectorBase& A) const
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
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
CAMmatrixBase CAMmatrixBase::operator-(const CAMmatrixBase& A) const
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
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
CAMmatrixBase CAMmatrixBase::operator-(const CAMvectorBase& A) const
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
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
CAMmatrixBase CAMmatrixBase::operator*(const CAMmatrixBase& A) const
{
    if(Structure.isMatrixOpConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//
//
//  Prepare Operands
//
    int STempFlag = 0;
    int TTempFlag = 0;

    CAMmatrixBase* S;
    CAMmatrixBase* T;

    if(Structure.isSubset()  == 0)
    { S = (CAMmatrixBase*)this;}
    else
    {
     STempFlag = 1;
     S = new CAMmatrixBase();
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
    long  Cols =    A.Structure[2].getIndexCount();

    CAMrange R1( (*S).Structure[1].getIndexBase(),
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

    long m =    R.Structure[1].getIndexCount();
    long n =    R.Structure[2].getIndexCount();
    long k = (*S).Structure[2].getIndexCount();

    double* s = (double*)((*S).getDataPointer());
    double* t = (double*)((*T).getDataPointer());
    double* r = (double*)(   R.getDataPointer());

    long lds =  (*S).Structure[1].getIndexCount();
    long ldt =  (*T).Structure[1].getIndexCount();
    long ldr =     R.Structure[1].getIndexCount();

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



CAMvectorBase CAMmatrixBase::operator*(const CAMvectorBase& A) const
{
    if(Structure.isMatrixOpConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//
//
//  Prepare Operands
//
    int STempFlag = 0;
    int TTempFlag = 0;

    CAMmatrixBase* S;
    CAMvectorBase* T;

    if(Structure.isSubset()  == 0)
    { S = (CAMmatrixBase*)this;}
    else
    {
     STempFlag = 1;
     S = new CAMmatrixBase();
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
    long  Rows = (S->operator[](1)).getIndexCount();
    long  Cols = A.Structure[2].getIndexCount();

    CAMrange R1((S->operator[](1)).getIndexBase(),
    (S->operator[](1)).getIndexBase() +  Rows  - 1);

    CAMrange R2(A.Structure[2].getIndexBase(),
    A.Structure[2].getIndexBase() +  Cols  - 1);

    CAMvectorBase R;
    if(R1.length() == 1)
    {R.initialize(CAMType::typeDouble,R2);}
    else    
    {R.initialize(CAMType::typeDouble,R1);}
//
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
CAMmatrixBase CAMmatrixBase::operator/(const CAMmatrixBase& A) const
{
    if(Structure.isMatrixOpConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}

    if(Structure[1].getIndexCount() !=
       Structure[2].getIndexCount())
    {CAMmatrixBase::nonSquareMessage();}
//
//  NEED CONVERSION CHECK -- need to check for square left hand side
//
//
// Turned off equilibration in the / routine so that the input
// matrices and vectors are un-modified by the calculation.  CRA 8/1/97
//
//  Prepare Operands
//
    int STempFlag = 0;
    int TTempFlag = 0;

    CAMmatrixBase* S;
    CAMmatrixBase* T;

    if(Structure.isSubset()  == 0)
    { S = (CAMmatrixBase*)this;}
    else
    {
     STempFlag = 1;
     S = new CAMmatrixBase();
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
    long  Cols =    A.Structure[2].getIndexCount();

    CAMrange R1((*S).Structure[1].getIndexBase(),
    (*S).Structure[1].getIndexBase() +  Rows  - 1);

    CAMrange R2(A.Structure[2].getIndexBase(),
    A.Structure[2].getIndexBase() +  Cols  - 1);

    CAMmatrixBase R(CAMType::typeDouble,R1, R2);
//
//   S R = T
//   S : N by N
//   R : N by NRHS
//   T : N by NRHS
//

    char FACT    = 'N';                  // Factor - no equilibration
    char TRANS   = 'N';                  // No transpose
    long N       =  Rows;                // Rows of S, R, and T
    long NRHS    =  Cols;                // Columns of R  and T

    double* s = (double*)((*S).getDataPointer());
    double* t = (double*)((*T).getDataPointer());
    double* r = (double*)(   R.getDataPointer());

    long  LDS    = N;                // leading dimension of S
    long  LDT    = N;                // leading dimension of T
    long  LDR    = N;                // leading dimension of R


    double*  SF  = new double[N*N];      // factored form of S
    long LDSF    = N;                    // leading dimension of SF

    long* IPIV   = new long[N];          // pivot vector of dimension N

    char  EQUED  = 'N';                  // equilibration flag

    double* RS   = new double[N];        // row and column scale factors
    double* C    = new double[N];        // dimension = N


    double* FERR = new double[NRHS];     // forward error estimates
    double* BERR = new double[NRHS];     // backward error estimates
    double* WORK = new double[4*N];      // double work array
    long*  IWORK = new long[N];          // integer work array

    double RCOND = 0;                    // estimate of reciprocal of
                                         // condition number

    long INFO    = 0;                    // output information

    short f1a = 1;
    short f1b = 1;
    short f1c = 1;

    dgesvx_(&FACT,&TRANS,&N,&NRHS,s,&LDS,SF,&LDSF,IPIV,
           &EQUED,RS,C,t,&LDT,r,&LDR,&RCOND, FERR, BERR, WORK,
           IWORK,&INFO, f1a, f1b, f1c);
//
//  Error Checking
//
   if(INFO != 0)
   {
     if(INFO <= N)
     {
        cerr << "          Matrix Singular " << endl;
        cerr << " LU Factorization Stopped at Step " << INFO << endl;
        cerr << "        No Solution Returned " << endl;
     }
        
     if(INFO ==(N +1))
     {
        cerr << " Matrix Singular or Badly Conditioned " << endl;
        cerr << " Computed Solution May Be Inaccurate "  << endl;
        cerr << " Condition Number = " << 1.0/RCOND << endl;
     }
    }

//
// clean-up
//
    delete []  IWORK;
    delete []   WORK;
    delete []   BERR;
    delete []   FERR;
    delete []      C;
    delete []     RS;
    delete []     SF;
    delete []   IPIV;

    if(STempFlag == 1) delete S;
    if(TTempFlag == 1) delete T;

    R.setTemporaryFlag();
    return R;
}
CAMvectorBase CAMmatrixBase::operator/(const CAMvectorBase& A) const
{
    if(Structure.isMatrixOpConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}

    if((this)->operator[](1).getIndexCount() !=
       (this)->operator[](1).getIndexCount())
    {CAMmatrixBase::nonSquareMessage();}
//
//  NEED CONVERSION CHECK -- need to check for square left hand side
//
// Turned off equilibration in the / routine so that the input
// matrices and vectors are un-modified by the calculation.  CRA 1/14/98
//
// Prepare Operands
//
    int STempFlag = 0;
    int TTempFlag = 0;

    CAMmatrixBase* S;
    CAMvectorBase* T;

    if(Structure.isSubset()  == 0)      // point to argument if not a submatrix
    { S = (CAMmatrixBase*)this;}        //
    else                                // else
    {
     STempFlag = 1;                     // indicate making a temporary
     S = new CAMmatrixBase();           // create a container
     S->initializeReturnArgument(*this);// initialize with structure of the argument
     *S = *this;                        // copy over contents
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
    long  Rows = (S->operator[](1)).getIndexCount();
    long  Cols = A.Structure[2].getIndexCount();

    CAMrange R1((S->operator[](1)).getIndexBase(),
    (S->operator[](1)).getIndexBase() +  Rows  - 1);

    CAMrange R2(A.Structure[2].getIndexBase(),
    A.Structure[2].getIndexBase() +  Cols  - 1);
    
    CAMvectorBase R;
    if(R1.length() == 1)
    {R.initialize(CAMType::typeDouble,R2);}
    else    
    {R.initialize(CAMType::typeDouble,R1);}
//
//   S R = T
//   S : N by N
//   R : N by NRHS
//   T : N by NRHS
//

     char FACT    = 'N';                  // No equilibrate, but factor
    char TRANS   = 'N';                  // No transpose
    long N       =  Rows;                // Rows of S, R, and T
    long NRHS    =  Cols;                // Columns of R  and T

    double* s = (double*)((*S).getDataPointer());
    double* t = (double*)((*T).getDataPointer());
    double* r = (double*)(   R.getDataPointer());

    long  LDS    = N;                // leading dimension of S
    long  LDT    = N;                // leading dimension of T
    long  LDR    = N;                // leading dimension of R


    double*  SF  = new double[N*N];      // factored form of S
    long LDSF    = N;                    // leading dimension of SF

    long* IPIV   = new long[N];          // pivot vector of dimension N

    char  EQUED  = 'B';                  // equilibration flag

    double* RS   = new double[N];        // row and column scale factors
    double* C    = new double[N];        // dimension = N


    double* FERR = new double[NRHS];     // forward error estimates
    double* BERR = new double[NRHS];     // backward error estimates
    double* WORK = new double[4*N];      // double work array
    long*  IWORK = new long[N];          // integer work array

    double RCOND = 0;                    // estimate of reciprocal of
                                         // condition number

    long INFO    = 0;                    // output information

    short f1a = 1;
    short f1b = 1;
    short f1c = 1;

    dgesvx_(&FACT,&TRANS,&N,&NRHS,s,&LDS,SF,&LDSF,IPIV,
           &EQUED,RS,C,t,&LDT,r,&LDR,&RCOND, FERR, BERR, WORK,
           IWORK,&INFO, f1a, f1b, f1c);
//
//  Error Checking
//
   if(INFO != 0)
   {
     if(INFO <= N)
     {
        cerr << "          Matrix Singular " << endl;
        cerr << " LU Factorization Stopped at Step " << INFO << endl;
        cerr << "        No Solution Returned " << endl;
     }
        
     if(INFO ==(N +1))
     {
        cerr << " Matrix Singular or Badly Conditioned " << endl;
        cerr << " Computed Solution May Be Inaccurate "  << endl;
        cerr << " Condition Number = " << 1.0/RCOND << endl;
     }
    }

//
// clean-up
//
    delete []  IWORK;
    delete []   WORK;
    delete []   BERR;
    delete []   FERR;
    delete []      C;
    delete []     RS;
    delete []     SF;
    delete []   IPIV;

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

void CAMmatrixBase::operator+=(const CAMmatrixBase& A)
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
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

void CAMmatrixBase::operator+=(const CAMvectorBase& A)
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//

    CAMbinaryEngine::doubleAplusEqualB(Structure, *DataP, A.Structure, *A.DataP);
}
void CAMmatrixBase::operator-=(const CAMmatrixBase& A)
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//

    CAMbinaryEngine::doubleAminusEqualB(Structure, *DataP, A.Structure, *A.DataP);
}
void CAMmatrixBase::operator-=(const CAMvectorBase& A)
{
    if(Structure.isStrictConformingTo(A.Structure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
//
//  NEED CONVERSION CHECK
//

    CAMbinaryEngine::doubleAminusEqualB(Structure, *DataP, A.Structure, *A.DataP);
}
void CAMmatrixBase::operator*=(const CAMmatrixBase& A)
{
    if((Structure.isMatrixOpConformingTo(A.Structure) != 1)||
    (A.Structure.isMatrixOpConformingTo(Structure) != 1))
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
    (*this) = (*this) * A;
}
void CAMmatrixBase::operator*=(const CAMvectorBase& A)
{
    if((Structure.isMatrixOpConformingTo(A.Structure) != 1)||
    (A.Structure.isMatrixOpConformingTo(Structure) != 1))
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
    (*this) = (*this) * A;
}

void CAMmatrixBase::operator/=(const CAMmatrixBase& A)
{
    if((Structure.isMatrixOpConformingTo(A.Structure) != 1)||
    (A.Structure.isMatrixOpConformingTo(Structure) != 1))
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
    (*this) = (*this)/A;
}

void CAMmatrixBase::operator/=(const CAMvectorBase& A)
{
    if((Structure.isMatrixOpConformingTo(A.Structure) != 1)||
    (A.Structure.isMatrixOpConformingTo(Structure) != 1))
    {CAMmatrixBase::nonConformingMessage(Structure,A.Structure);}
    (*this) = (*this)/A;
}

CAMmatrixBase CAMmatrixBase::transpose() const
{
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S(CAMType::typeDouble,
     _(Structure[2].getIndexBase(),Structure[2].getIndexBound()),
     _(Structure[1].getIndexBase(),Structure[1].getIndexBound()));

    CAMstructureBase  ASubset(Structure);
    CAMstructureBase  BSubset(S.Structure);

    long i;
    for(i  = Structure[1].getIndexBase();
        i <= Structure[1].getIndexBound();i++)
    {
    ASubset.setStructureSubset(i,_);
    BSubset.setStructureSubset(_,i);
    CAMbinaryEngine::doubleAequalToB(BSubset, *S.DataP, ASubset, *DataP);
    }
    S.setTemporaryFlag();
    return S;
}

CAMmatrixBase CAMmatrixBase::operator~() const
{
//  Transpose Operator
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S(CAMType::typeDouble,
     _(Structure[2].getIndexBase(),Structure[2].getIndexBound()),
     _(Structure[1].getIndexBase(),Structure[1].getIndexBound()));

    CAMstructureBase  ASubset(Structure);
    CAMstructureBase  BSubset(S.Structure);

    long i;
    for(i  = Structure[1].getIndexBase();
        i <= Structure[1].getIndexBound();i++)
    {
    ASubset.setStructureSubset(i,_);
    BSubset.setStructureSubset(_,i);
    CAMbinaryEngine::doubleAequalToB(BSubset, *S.DataP, ASubset, *DataP);
    }
    S.setTemporaryFlag();
    return S;
}
//
//*****************************************************************
//                    Operations with Scalers
//*****************************************************************
//
CAMmatrixBase  CAMmatrixBase::operator +(const double value) const
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase AStructure(_(1,1));
    if(Structure.isStrictConformingTo(AStructure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,AStructure);}

    CAMmatrixBase S(*this);
    CAMbinaryEngine::doubleAplusEqualAlpha(S.Structure, *(S.DataP), value);

    S.setTemporaryFlag();
    return S;
}
CAMmatrixBase  operator +(const double value, const CAMmatrixBase& A)
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase  BStructure(_(1,1));
    if(A.Structure.isStrictConformingTo(BStructure) != 1)
    {CAMmatrixBase::nonConformingMessage(A.Structure,BStructure);}

    CAMmatrixBase S(A);
    CAMbinaryEngine::doubleAplusEqualAlpha(S.Structure, *(S.DataP), value);

    S.setTemporaryFlag();
    return S;
}

CAMmatrixBase  CAMmatrixBase::operator -(const double value) const
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase AStructure(_(1,1));
    if(Structure.isStrictConformingTo(AStructure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,AStructure);}

    CAMmatrixBase S(*this);
    CAMbinaryEngine::doubleAminusEqualAlpha(S.Structure, *(S.DataP), value);

    S.setTemporaryFlag();
    return S;
}

CAMmatrixBase  operator -(const double value, const CAMmatrixBase& A)
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase  BStructure(_(1,1));
    if(A.Structure.isStrictConformingTo(BStructure) != 1)
    {CAMmatrixBase::nonConformingMessage(A.Structure,BStructure);}

    CAMmatrixBase S(A);
    CAMbinaryEngine::doubleAminusEqualAlpha(S.Structure, *(S.DataP), value);

    S.setTemporaryFlag();
    return S;
}

void  CAMmatrixBase::operator +=(const double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase AStructure(_(1,1));
    if(Structure.isStrictConformingTo(AStructure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,AStructure);}

    CAMbinaryEngine::doubleAplusEqualAlpha(Structure, *(DataP), value);
}

void  CAMmatrixBase::operator -=(const double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMstructureBase AStructure(_(1,1));
    if(Structure.isStrictConformingTo(AStructure) != 1)
    {CAMmatrixBase::nonConformingMessage(Structure,AStructure);}

    CAMbinaryEngine::doubleAminusEqualAlpha(Structure, *(DataP), value);
}

CAMmatrixBase  CAMmatrixBase::operator*(double value) const
{
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S(*this);
    CAMbinaryEngine::doubleAtimesEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

CAMmatrixBase  operator *(double value, const CAMmatrixBase& A)
{
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S(A);
    CAMbinaryEngine::doubleAtimesEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

CAMmatrixBase  CAMmatrixBase::operator /(double value) const
{
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S(*this);
    CAMbinaryEngine::doubleAdivideEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

CAMmatrixBase  operator /(double value, const CAMmatrixBase& A)
{
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S(A);
    CAMbinaryEngine::doubleAdivideEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

void  CAMmatrixBase::operator *=(double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMbinaryEngine::doubleAtimesEqualAlpha(Structure, *DataP, value);
}

void  CAMmatrixBase::operator /=(double value)
{
    CAMbinaryEngine::doubleAdivideEqualAlpha(Structure, *DataP, value);
}



void  CAMmatrixBase::setToValue(double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMbinaryEngine::doubleAequalToAlpha(Structure, *DataP, value);
}

CAMmatrixBase  CAMmatrixBase::plusValue(double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S(*this);
    CAMbinaryEngine::doubleAplusEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

CAMmatrixBase  CAMmatrixBase::minusValue(double value)
{
//
//  NEED CONVERSION CHECK
//
    CAMmatrixBase S(*this);
    CAMbinaryEngine::doubleAminusEqualAlpha(S.Structure, *S.DataP, value);
    S.setTemporaryFlag();
    return S;
}

//
//*****************************************************************
//            Temporary and Reference Utilities
//*****************************************************************
//
void  CAMmatrixBase::exchangeContentsWith(CAMmatrixBase& B)
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
    long  matrixBaseReferenceCount_temp = matrixBaseReferenceCount;

    Structure.initialize(B.Structure);
    DataP                   = B.DataP;
    typeValue               = B.typeValue;
    referenceFlag           = B.referenceFlag;
    matrixBaseReferenceCount = B.matrixBaseReferenceCount;
//
    B.Structure.initialize(S_temp);
    B.DataP                   = DataP_temp;
    B.typeValue               = typeValue_temp;
    B.referenceFlag           = referenceFlag_temp;
    B.matrixBaseReferenceCount = matrixBaseReferenceCount_temp;
}

void  CAMmatrixBase::initializeReferenceDuplicate(const CAMmatrixBase& B)
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
    matrixBaseReferenceCount = 0;
}
//
//*****************************************************************
//                    CONVERSIONS
//*****************************************************************
//
CAMarrayBase  CAMmatrixBase::asArray() const
{
    CAMarrayBase S;
    if(DataP == 0) return S;

    CAMrange R1(Structure[1].getIndexBase(),Structure[1].getIndexBound());
    CAMrange R2(Structure[2].getIndexBase(),Structure[2].getIndexBound()); 
//
//
    S.initialize(CAMType::typeDouble, R1,R2);
    CAMbinaryEngine::doubleAequalToB(S.Structure, *(S.DataP), Structure, *DataP);
//
//
    S.setTemporaryFlag();
    return S;
}
CAMvectorBase  CAMmatrixBase::asVector() const
{
    CAMvectorBase S;
    if(DataP == 0) return S;

    CAMrange R1;
    long i;
    long dimension = 0;

    for(i = 1; i <= getDimension(); i++)
    {
    if(Structure[i].getIndexCount() != 1)
    {
    dimension++;
    if(dimension == 1)
    R1.initialize(Structure[i].getIndexBase(),Structure[i].getIndexBound());
    }
    }
    switch (dimension)
    {
    case 0 :
    R1.initialize(Structure[1].getIndexBase(),Structure[1].getIndexBound());
    break;

    case 1 :
    break;
    default :
    CAMmatrixBase::objectConversionError(Structure);

    }
//
//
    S.initialize(CAMType::typeDouble, R1);
    CAMbinaryEngine::doubleAequalToB(S.Structure, *(S.DataP), Structure, *DataP);
//
//
    S.setTemporaryFlag();
    return S;
}
//
//*****************************************************************
//                    DIMENSION SELECTION
//*****************************************************************
//
CAMstructureBase&  CAMmatrixBase::operator[](long i)
{
    if((i < 0)||(i > Structure.dataDimension))
    {CAMstructureBase::illegalDimension(i, Structure.dataDimension);}

    Structure.exchangeReferenceIndex(i);

    return  Structure;
}

const CAMstructureBase&  CAMmatrixBase::operator[](long i) const
{
    if((i < 0)||(i > Structure.dataDimension))
    {CAMstructureBase::illegalDimension(i, Structure.dataDimension);}

    Structure.exchangeReferenceIndex(i);

    return  Structure;
}

void*  CAMmatrixBase::getDataPointer(long i1, long i2) const
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

void  CAMmatrixBase::incrementReferenceCount()
{
    if(matrixBaseReferenceCount == 0) CAMmatrixBase::referenceCountError();
    matrixBaseReferenceCount++;
}

void  CAMmatrixBase::referenceCountError()
{
cerr << " Cannot Use Reference Counting on Objects New\'d by the Compiler " << endl;
CAMmvaExit();
}
//
//*****************************************************************
//                    MEMBER_FUNCTIONS
//*****************************************************************
//


void  CAMmatrixBase::indexCheck(const CAMstructureBase &S, long i1, long i2)
{
    if(S.dataDimension != 2)
    {
     cerr << " Error : Incorrect Matrix Array Index Dimension " << endl;
     cerr << " Object Dimension = " << S.dataDimension
          << "--- Dimension Used = "<< 2 << endl;
     CAMmvaExit();
     }
     const long* indexBeginP = S.indexBegin.getDataPointer();
     const long* indexEndP = S.indexEnd.getDataPointer();
     if((i1 < *indexBeginP)||(i1 > *indexEndP))
     {
     CAMmatrixBase::indexErrorMessage(1, *(indexBeginP), *(indexEndP), i1);
     }
     if((i2 < *(indexBeginP +1))||(i2 > *(indexEndP+1)))
     {
     CAMmatrixBase::indexErrorMessage(2, *(indexBeginP+1), *(indexEndP+1), i2);
     }
}





void  CAMmatrixBase::indexErrorMessage(long indexDimension, long base, long bound, long index)
{
     cerr << " Error :  Index " << indexDimension << " Out of Range " << endl;

     cerr << " Current Index Range  :(" << base << ", " << bound << ")"  << endl;
     cerr << " Index Used          : " << index << endl;
     CAMmvaExit();
}
void CAMmatrixBase::nonConformingMessage(const CAMstructureBase& A,  const CAMstructureBase& B)
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
void CAMmatrixBase::doubleConversionError(const CAMstructureBase& A)
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

void CAMmatrixBase::nonSquareMessage()
{
    cerr << endl;
    cerr << "Matrix is not square : dimensions incompatable with matrix solve " << endl << endl;
    CAMmvaExit();
}

void CAMmatrixBase::objectConversionError(const CAMstructureBase& A)
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
void CAMmatrixBase::nullOperandError()
{
    cerr << endl;
    cerr << " Error : Null Object Used As Operand  " << endl;
    CAMmvaExit();
}
void CAMmatrixBase::nullOperandError(char* Operation)
{
    cerr << endl;
    cerr << " Error : Null Object Used As Operand With "<< Operation << endl;
    CAMmvaExit();
}
void CAMmatrixBase::inputSizeError()
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










  

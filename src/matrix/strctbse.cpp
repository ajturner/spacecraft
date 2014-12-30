#include "strctbse.h"

#undef   __IMPEXP__
#ifdef   __BCPLUSPLUS__
#ifdef   __EXPORT_MVASUPPORT_B__
#define  __IMPEXP__ __export
#else
#define  __IMPEXP__
#endif
#else
#define __IMPEXP__
#endif

#ifdef   __STATIC__
#undef   __IMPEXP__
#define  __IMPEXP__
#endif
//
//*****************************************************************
//                    STRCTBSE.CPP
//*****************************************************************
//
//
//*****************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Fri Sep 01 17:09:32 1995
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
CAMstructureBase::CAMstructureBase(): indexBegin(), indexEnd(), indexStride(),
indexBeginBase(), indexEndBase()
{
    dataDimension      = 0;
}

CAMstructureBase::CAMstructureBase(long dimension): indexBegin(dimension ), indexEnd(dimension), indexStride(dimension),
indexBeginBase(dimension), indexEndBase(dimension)
{
    dataDimension      = dimension;
}
CAMstructureBase::CAMstructureBase( const CAMstructureBase& A)
{
    dataDimension       = A.dataDimension;
    indexBegin           = A.indexBegin;
    indexEnd              = A.indexEnd;
    indexStride           = A.indexStride;
    indexBeginBase       = A.indexBeginBase;
    indexEndBase       = A.indexEndBase;
}
CAMstructureBase::CAMstructureBase(const CAMrange& R1, const CAMrange& R2 ,
   const CAMrange& R3 , const CAMrange&R4 ,
   const CAMrange& R5 , const CAMrange&R6 ,
   const CAMrange& R7) : indexBegin(), indexEnd(), indexStride(),
indexBeginBase(), indexEndBase()
{
    if(R1.getNullFlag() == 1)
    { dataDimension = 0;}
    else if(R2.getNullFlag() == 1)
    {dataDimension = 1;}
    else if(R3.getNullFlag() == 1)
    {dataDimension = 2;}
    else if(R4.getNullFlag() == 1)
    {dataDimension = 3;}
    else if(R5.getNullFlag() == 1)
    {dataDimension = 4;}
    else if(R6.getNullFlag() == 1)
    {dataDimension = 5;}
    else if(R7.getNullFlag() == 1)
    {dataDimension = 6;}
    else
    {dataDimension = 7;}

    indexBegin.initialize(dataDimension);
    indexEnd.initialize(dataDimension);
    indexStride.initialize(dataDimension);
    indexBeginBase.initialize(dataDimension);
    indexEndBase.initialize(dataDimension);

    const CAMrange* RangeInput[7];
    RangeInput[0] = &R1;
    RangeInput[1] = &R2;
    RangeInput[2] = &R3;
    RangeInput[3] = &R4;
    RangeInput[4] = &R5;
    RangeInput[5] = &R6;
    RangeInput[6] = &R7;

    int i;
    for(i = 0; i < dataDimension; i++)
    {
    indexBegin[i]      = RangeInput[i]->getBase();
    indexEnd[i]        = RangeInput[i]->getBound();
    indexStride[i]     = RangeInput[i]->getStride();
    indexBeginBase[i]  = indexBegin[i];
    indexEndBase[i]    = indexEnd[i];
    }
}
//
//*****************************************************************
//                    DESTRUCTOR
//*****************************************************************
//
CAMstructureBase::~CAMstructureBase()
{
}

//
//*****************************************************************
//                    OUTPUT
//*****************************************************************
//
ostream&  operator <<(ostream& out_stream, const CAMstructureBase& A)
{
    int i;
    out_stream  << "Structure Dimension = " << A.dataDimension << '\n';

    out_stream  << "indexBegin     = ";
    for(i = 0; i < A.dataDimension; i++)
    out_stream  << " " << A.indexBegin[i];
    out_stream << '\n';

    out_stream  << "indexEnd       = ";
    for(i = 0; i < A.dataDimension; i++)
    out_stream  << " " << A.indexEnd[i];
    out_stream << '\n';

    out_stream  << "indexStride    = ";
    for(i = 0; i < A.dataDimension; i++)
    out_stream  << " " << A.indexStride[i];
    out_stream << '\n';

    out_stream  << "indexBeginBase = ";
    for(i = 0; i < A.dataDimension; i++)
    out_stream  << " " << A.indexBeginBase[i];
    out_stream << '\n';

    out_stream  << "indexEndBase   = ";
    for(i = 0; i < A.dataDimension; i++)
    out_stream  << " " << A.indexEndBase[i];
    out_stream << '\n';


    return(out_stream);
}

//
//*****************************************************************
//                    ASSIGNMENT
//*****************************************************************
//
CAMstructureBase&  CAMstructureBase::operator =( const CAMstructureBase& A)
{
    dataDimension      = A.dataDimension;
    indexBegin            = A.indexBegin;
    indexEnd              = A.indexEnd;
    indexStride            = A.indexStride;
    indexBeginBase        = A.indexBeginBase;
    indexEndBase        = A.indexEndBase;
    return *this;
}

//
//*****************************************************************
//                    MEMBER_FUNCTIONS
//*****************************************************************
//

void      CAMstructureBase::initialize()
{
    indexBegin.initialize();
    indexEnd.initialize();
    indexStride.initialize();
    indexBeginBase.initialize();
    indexEndBase.initialize();
    dataDimension      = 0;
}


void CAMstructureBase::initialize(long dimension)
{
    indexBegin.initialize(dimension);
    indexEnd.initialize(dimension);
    indexStride.initialize(dimension);
    indexBeginBase.initialize(dimension);
    indexEndBase.initialize(dimension);
    dataDimension      = dimension;
}

void CAMstructureBase::initialize(const CAMstructureBase& A)
{
    dataDimension    = A.dataDimension;
    indexBegin.initialize(A.indexBegin);
    indexEnd.initialize(A.indexEnd);
    indexStride.initialize(A.indexStride);
    indexBeginBase.initialize(A.indexBeginBase);
    indexEndBase.initialize(A.indexEndBase);
}
void CAMstructureBase::initialize(const CAMrange& R1, const CAMrange& R2,
   const CAMrange& R3, const CAMrange&R4, const CAMrange& R5,
   const CAMrange&R6, const CAMrange& R7)
{
         if(R1.getNullFlag() == 1){dataDimension = 0;}
    else if(R2.getNullFlag() == 1){dataDimension = 1;}
    else if(R3.getNullFlag() == 1){dataDimension = 2;}
    else if(R4.getNullFlag() == 1){dataDimension = 3;}
    else if(R5.getNullFlag() == 1){dataDimension = 4;}
    else if(R6.getNullFlag() == 1){dataDimension = 5;}
    else if(R7.getNullFlag() == 1){dataDimension = 6;}
    else                     {dataDimension = 7;}

    indexBegin.initialize(dataDimension);
    indexEnd.initialize(dataDimension);
    indexStride.initialize(dataDimension);
    indexBeginBase.initialize(dataDimension);
    indexEndBase.initialize(dataDimension);

    const CAMrange* RangeInput[7];
    RangeInput[0] = &R1;
    RangeInput[1] = &R2;
    RangeInput[2] = &R3;
    RangeInput[3] = &R4;
    RangeInput[4] = &R5;
    RangeInput[5] = &R6;
    RangeInput[6] = &R7;

    int i;
    for(i = 0; i < dataDimension; i++)
    {
    indexBegin[i]      = RangeInput[i]->getBase();
    indexEnd[i]        = RangeInput[i]->getBound();
    indexStride[i]     = RangeInput[i]->getStride();
    indexBeginBase[i]  = indexBegin[i];
    indexEndBase[i]    = indexEnd[i];
    }
}
//
//*****************************************************************
//                    MEMBER_FUNCTIONS
//*****************************************************************
//
int      CAMstructureBase::isConformingTo(const CAMstructureBase& A) const
{
    int returnValue = 0;

    long loopDimension;
    long AloopDimension;

    MVAlongBase  Count(dataDimension);
    MVAlongBase ACount(A.dataDimension);
    long i, ii;

    for(i = 0; i <  dataDimension; i++)
    Count[i] = (( indexEnd[i] - indexBegin[i])/ indexStride[i])  + 1;

    ii = 0;
    for(i = 0; i <  dataDimension; i++)
    { if(Count[i] != 1) {Count[ii]  = Count[i]; ii++;} }

    loopDimension = ii;
    if(loopDimension == 0) loopDimension = 1;


    for(i = 0; i < A.dataDimension; i++)
    ACount[i] = ((A.indexEnd[i] - A.indexBegin[i])/A.indexStride[i])  + 1;

    ii = 0;
    for(i = 0; i < A.dataDimension; i++)
    { if(ACount[i] != 1) {ACount[ii]  = ACount[i]; ii++;} }

    AloopDimension = ii;
    if(AloopDimension == 0) AloopDimension = 1;

    if(loopDimension == AloopDimension)
    {
    returnValue = 1;
    for(i =0; i< loopDimension; i++)
    if(ACount[i] != Count[i]) returnValue =0;
    }

    return returnValue;
}

int      CAMstructureBase::isStrictConformingTo(const CAMstructureBase& A) const
{
    int returnValue = 0;

    MVAlongBase  Count(dataDimension);
    MVAlongBase ACount(A.dataDimension);
    long i;

    for(i = 0; i <  dataDimension; i++)
    Count[i] = (( indexEnd[i] - indexBegin[i])/ indexStride[i])  + 1;

    for(i = 0; i < A.dataDimension; i++)
    ACount[i] = ((A.indexEnd[i] - A.indexBegin[i])/A.indexStride[i])  + 1;

    if(dataDimension == A.dataDimension)
    {
    returnValue = 1;
    for(i =0; i< dataDimension; i++)
    if(ACount[i] != Count[i]) returnValue =0;
    }

    return returnValue;
}

int      CAMstructureBase::isMatrixOpConformingTo(const CAMstructureBase& A) const
{
    if((dataDimension !=2)||(A.dataDimension !=2)) return 0;

    int returnValue = 0;

    long Count2  = ((  indexEnd[1] -   indexBegin[1])/  indexStride[1])  + 1;
    long ACount1 = ((A.indexEnd[0] - A.indexBegin[0])/A.indexStride[0])  + 1;

    if(Count2 == ACount1) returnValue = 1;

    return returnValue;
}

int      CAMstructureBase::isSubset() const
{
//
//  Returns 1 if invoking instance is a subset of it structure
//
    int returnValue = 0;
      for(int i = 0; i < dataDimension; i++)
    returnValue +=   (indexEndBase[i] - indexEnd[i])
                   + (indexBegin[i]   - indexBeginBase[i])
                   + (indexStride[i] - 1);
    if(returnValue > 0) returnValue = 1;
    return returnValue;

}
void  CAMstructureBase::getNormalizedLoops(long& loopDimension, long& Offset, MVAlongBase& Count, MVAlongBase& Stride) const
{
    MVAlongBase localCount(dataDimension);
    MVAlongBase localStride(dataDimension);


    long i;    long M; long i_new;

    for(i = 0; i < dataDimension; i++)
    localCount[i] = ((indexEnd[i] - indexBegin[i])/indexStride[i])  + 1;

    M              = 1;
    Offset         = (indexBegin[0] - indexBeginBase[0])*M;
    localStride[0] = indexStride[0];

    for(i = 1; i < dataDimension; i++)
    {
    M         = M*((indexEndBase[i-1] - indexBeginBase[i-1]) + 1);
    localStride[i] = indexStride[i]*M;
    Offset   += (indexBegin[i] - indexBeginBase[i])*M;
    }
//
//  Collapse loops
//
    i_new = 0;
    for(i = 0; i < dataDimension; i++)
    {
    if(localCount[i] != 1)
    {
    localCount[i_new]  = localCount[i];
    localStride[i_new] = localStride[i];
    i_new++;
    }
    }

    loopDimension = i_new;
    if(loopDimension == 0) loopDimension = 1;

    Count.initialize(loopDimension);
    Stride.initialize(loopDimension);
    for(i = 0; i < loopDimension; i++)
    {
    Count[i]  = localCount[i];
    Stride[i] = localStride[i];
    }

}

void  CAMstructureBase::setStructureSubset(const CAMrange& R1, const CAMrange& R2 ,
   const CAMrange& R3 , const CAMrange&R4 ,
   const CAMrange& R5 , const CAMrange&R6 ,
   const CAMrange& R7)
{
    const CAMrange* RangeInput[7];
    RangeInput[0] = &R1;
    RangeInput[1] = &R2;
    RangeInput[2] = &R3;
    RangeInput[3] = &R4;
    RangeInput[4] = &R5;
    RangeInput[5] = &R6;
    RangeInput[6] = &R7;

    int i;
    for(i = 0; i < dataDimension; i++)
    {
      if(RangeInput[i]->getUnderscoreFlag() == 1)
        {indexStride[i] = 1;}
        else if(RangeInput[i]->getSingleArgumentFlag() == 1)
        {
         indexBegin[i]      = RangeInput[i]->getBound();
         indexEnd[i]        = RangeInput[i]->getBound();

       indexStride[i]     = 1;
       /*** 
       Change 01/29/97    was
         indexStride[i]     = RangeInput[i]->getBound();
       ****/ 
        }
        else
        {
         indexBegin[i]      = RangeInput[i]->getBase();
         indexEnd[i]        = RangeInput[i]->getBound();
         indexStride[i]     = RangeInput[i]->getStride();
        }
    }
     return;

}

long  CAMstructureBase::getFullDataCount() const
{
    if(dataDimension == 0) return 0;

    long fullDataCount = 1;
    for(long i = 0; i <  dataDimension; i++)
    { fullDataCount *= (indexEndBase[i] - indexBeginBase[i]) + 1;}
    return fullDataCount;
}
long  CAMstructureBase::getDataCount() const
{
    if(dataDimension == 0) return 0;

    long dataCount = 1;
    for(long i = 0; i <  dataDimension; i++)
    { dataCount *= ((indexEnd[i] - indexBegin[i])/indexStride[i]) + 1;}
    return dataCount;
}
void CAMstructureBase::initializeMinStructure(CAMstructureBase& A) const
{
    A.dataDimension = dataDimension;
    A.indexBegin.initialize(indexBegin);
    A.indexEnd.initialize(dataDimension);
    A.indexBeginBase.initialize(indexBegin);
    A.indexEndBase.initialize(dataDimension);
    A.indexStride.initialize(dataDimension);

    for(long i = 0; i < dataDimension; i++)
    {
    A.indexEnd[i] = A.indexBegin[i] + ((indexEnd[i] - indexBegin[i])/indexStride[i]);
    A.indexEndBase[i] = A.indexEnd[i];
    A.indexStride[i] = 1;
    }
}
//
//*****************************************************************
//               Coordinate Index Handling
//*****************************************************************
//
long  CAMstructureBase::exchangeReferenceIndex(long i)
{
    static long index = 1;
    long index_return = index;   // take current value
    index = i;                   // give input value
    return index_return ;
}

CAMstructureBase&  CAMstructureBase::operator[](long i)
{
    if((i < 0)||(i > dataDimension))
    {CAMstructureBase::illegalDimension(i, dataDimension);}
    CAMstructureBase::exchangeReferenceIndex(i);

    return  *this;
}

const CAMstructureBase&  CAMstructureBase::operator[](long i) const
{
    if((i < 0)||(i > dataDimension))
    {CAMstructureBase::illegalDimension(i, dataDimension);}
    CAMstructureBase::exchangeReferenceIndex(i);
    return  *this;
}

long  CAMstructureBase::getIndexBase() const
{
    long index = CAMstructureBase::exchangeReferenceIndex(1);
    return  indexBegin[index - 1];
}

long  CAMstructureBase::getIndexBaseBase() const
{
    long index = CAMstructureBase::exchangeReferenceIndex(1);
    return     indexBeginBase[index - 1];
}

long CAMstructureBase::getIndexBound() const
{
    long index = CAMstructureBase::exchangeReferenceIndex(1);
    return indexEnd[index-1];
}


long  CAMstructureBase::getIndexStride() const
{
    long index = CAMstructureBase::exchangeReferenceIndex(1);
    return   indexStride[index - 1];
}

long  CAMstructureBase::getIndexCount() const
{
    long index = CAMstructureBase::exchangeReferenceIndex(1);
    return
    ((indexEnd[index - 1] - indexBegin[index- 1])/indexStride[index -1]) + 1;
}

void  CAMstructureBase::setIndexBase(long i)
{
    long k = CAMstructureBase::exchangeReferenceIndex(1);
    long offset = i - indexBegin[k];
    indexBegin[k]     = indexBegin[k]     + offset;
    indexEnd[k]       = indexEnd[k]       + offset;
    indexBeginBase[k] = indexBeginBase[k] + offset;
    indexEndBase[k]   = indexEndBase[k]   + offset;
}

void  CAMstructureBase::setIndexStride(long i)
{
    long index = CAMstructureBase::exchangeReferenceIndex(1);
    indexStride[index - 1] = i;
}

void  CAMstructureBase::setAllIndexBase(long i)
{
    long offset;

    for(long k = 0; k < dataDimension; k++)
    {
    offset = i - indexBegin[k];
    indexBegin[k]     = indexBegin[k]     + offset;
    indexEnd[k]       = indexEnd[k]       + offset;
    indexBeginBase[k] = indexBeginBase[k] + offset;
    indexEndBase[k]   = indexEndBase[k]   + offset;
    }
}
//
//*****************************************************************
//                     Error Handling
//*****************************************************************
//
void  CAMstructureBase::illegalDimension(long i, long dimension)
{
    cerr << "Argument to Dimension Selection Out of Bounds " << '\n';
    cerr << "Argument Input : " << i << " Acceptable Range : " <<
    "(0, " << dimension << ")" << endl;
    CAMmvaExit();
}
//
//*****************************************************************
//                     CPP File End
//*****************************************************************
//


  

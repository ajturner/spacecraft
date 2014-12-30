//
//******************************************************************************
//                    DARRAY.H
//******************************************************************************
//

#include "strctbse.h"
#include "datahndl.h"
#include "arraybse.h"
#include "range.h"
#include "camtype.h"
#include "under.h"

//
//  
//
//
//********************************************************************************
//
//            Chris Anderson  (C) UCLA
//
//            Thu Nov 02 13:42:45 1995
//
//********************************************************************************
//

#ifndef _CAMDOUBLEARRAY_
#define _CAMDOUBLEARRAY_

#include "mvaimpexp.h"

class __IMPEXP__ CAMdoubleArray : public CAMarrayBase
{

public :

//
//  Constructors
//
    CAMdoubleArray():CAMarrayBase(CAMType::typeDouble){};
    CAMdoubleArray(const CAMdoubleArray& A):CAMarrayBase(*((CAMarrayBase*)&A)){};
    CAMdoubleArray(const CAMarrayBase& A):CAMarrayBase(A){};
    CAMdoubleArray(long n):CAMarrayBase(CAMType::typeDouble, n){};
    CAMdoubleArray(const CAMrange& R1, const CAMrange& R2 = CAMnullRange,
    const CAMrange& R3 = CAMnullRange, const CAMrange&R4 = CAMnullRange,
    const CAMrange& R5 = CAMnullRange, const CAMrange&R6 = CAMnullRange,
    const CAMrange& R7 = CAMnullRange) :
    CAMarrayBase(CAMType::typeDouble,R1, R2, R3, R4, R5, R6, R7){ };
//
//  Assignment
//
    void  operator = (const CAMdoubleArray& A)
    {CAMarrayBase* basePtr = this; const CAMarrayBase* AbasePtr =
    (CAMarrayBase*)&A; basePtr->operator=(*AbasePtr);};
    void  operator =( const CAMarrayBase& A)
    {CAMarrayBase* basePtr = this; basePtr->operator=(A);};
    void  operator = (double value)
    {CAMarrayBase* basePtr = this; basePtr->operator=(value);};
//
//  initialization
//
    void  initialize()
    {CAMarrayBase* basePtr = this; basePtr->initialize(CAMType::typeDouble);};
    void  initialize(const CAMdoubleArray& A)
    {CAMarrayBase* basePtr = this; basePtr->initialize(A);};
    void  initialize(const CAMarrayBase& A)
    {CAMarrayBase* basePtr = this; basePtr->initialize(A);};
    void  initialize(long n)
    {CAMarrayBase* basePtr = this; basePtr->initialize(CAMType::typeDouble, n);};
    void  initialize(const CAMrange& R1, const CAMrange& R2 = CAMnullRange,
    const CAMrange& R3 = CAMnullRange, const CAMrange&R4 = CAMnullRange,
    const CAMrange& R5 = CAMnullRange, const CAMrange&R6 = CAMnullRange,
    const CAMrange& R7 = CAMnullRange){CAMarrayBase* basePtr = this;
    basePtr->initialize(CAMType::typeDouble,R1, R2, R3, R4, R5, R6, R7);};
//
//  Access Functions
//
    inline double&  operator()(long i1)
{
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1);
#endif
    long* beginPtr = Structure.indexBeginBase.getDataPointer();

    double* dataPtr =  (double*)DataP->dataPointer;
    long offset = (i1 - *(beginPtr));
    return *(dataPtr + offset);
};
    inline double&  operator()(long i1, long i2)
{
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2);
#endif
    long* beginPtr = Structure.indexBeginBase.getDataPointer();
    long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer; 
    
    long offset = 
    (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*(i2 - *(beginPtr +1)); 

    return (*(dataPtr + offset));
};
    inline double&  operator()(long i1, long i2, long i3)
{
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2,i3);
#endif
    long* beginPtr = Structure.indexBeginBase.getDataPointer();
    long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset    =  (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*
    ((i2 - *(beginPtr +1)) + 
    ((*(endPtr +1) - *(beginPtr +1)) + 1)*
    (i3 - *(beginPtr + 2)));    
    return (*(dataPtr + offset));
};
    inline double&  operator()(long i1, long i2, long i3, long i4)
{ 
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2,i3,i4);
#endif
    long* beginPtr = Structure.indexBeginBase.getDataPointer();
    long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset    =  (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*
    ( (i2 - *(beginPtr +1)) + 
      ((*(endPtr +1) - *(beginPtr +1)) + 1)*
    ( (i3 - *(beginPtr + 2)) +
      ((*(endPtr +2) - *(beginPtr +2)) + 1)*(i4 - *(beginPtr + 3))));  
    return (*(dataPtr + offset));
};
    inline double&  operator()(long i1, long i2, long i3, long i4, long i5)
{  
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2,i3,i4,i5);
#endif
    long* beginPtr = Structure.indexBeginBase.getDataPointer();
    long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset    =  (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*
    ((i2 - *(beginPtr +1)) + 
    ((*(endPtr +1) - *(beginPtr +1)) + 1)*
    ((i3 - *(beginPtr + 2)) + 
    ((*(endPtr +2) - *(beginPtr +2)) + 1)*
    ((i4 - *(beginPtr + 3)) +
    ((*(endPtr +3) - *(beginPtr +3)) + 1)*(i5 - *(beginPtr + 4)))));   
    return (*(dataPtr + offset));
};
    inline double&  operator()(long i1, long i2, long i3, long i4, long i5, long i6)
{ 
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2,i3,i4,i5,i6);
#endif
    long* beginPtr = Structure.indexBeginBase.getDataPointer();
    long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset    =  (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*
    ((i2 - *(beginPtr +1)) + 
    ((*(endPtr +1) - *(beginPtr +1)) + 1)*
    ((i3 - *(beginPtr + 2)) + 
    ((*(endPtr +2) - *(beginPtr +2)) + 1)*
    ((i4 - *(beginPtr + 3)) +
    ((*(endPtr +3) - *(beginPtr +3)) + 1)*
    ((i5 - *(beginPtr + 4)) +
    ((*(endPtr +4) - *(beginPtr +4)) + 1)*(i6 - *(beginPtr + 5)))))); 
    return (*(dataPtr + offset));
};
    inline double&  operator()(long i1, long i2, long i3, long i4, long i5, long i6, long i7)
{   
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2,i3,i4,i5,i6,i7);
#endif
    long* beginPtr = Structure.indexBeginBase.getDataPointer();
    long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset    =  (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*
    ((i2 - *(beginPtr +1)) + 
    ((*(endPtr +1) - *(beginPtr +1)) + 1)*
    ((i3 - *(beginPtr + 2)) + 
    ((*(endPtr +2) - *(beginPtr +2)) + 1)*
    ((i4 - *(beginPtr + 3)) +
    ((*(endPtr +3) - *(beginPtr +3)) + 1)*
    ((i5 - *(beginPtr + 4)) + 
    ((*(endPtr +4) - *(beginPtr +4)) + 1)*
    ((i6 - *(beginPtr + 5)) +
    ((*(endPtr +5) - *(beginPtr +5)) + 1)*(i7 - *(beginPtr + 6)))))));   
    return (*(dataPtr + offset));
};
    inline const double&  operator()(long i1) const
{
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1);
#endif
    const long* beginPtr = Structure.indexBeginBase.getDataPointer();
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset = (i1 - *(beginPtr));
    return (*(dataPtr + offset));
};
    inline const double&  operator()(long i1, long i2) const
{ 
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2);
#endif
    const long* beginPtr = Structure.indexBeginBase.getDataPointer();
    const long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer; 
    
    long offset = 
    (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*(i2 - *(beginPtr +1)); 
    
    return (*(dataPtr + offset));
};
    inline const double&  operator()(long i1, long i2, long i3) const
{
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2,i3);
#endif
    const long* beginPtr = Structure.indexBeginBase.getDataPointer();
    const long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset    =  (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*
    ((i2 - *(beginPtr +1)) + 
    ((*(endPtr +1) - *(beginPtr +1)) + 1)*
    (i3 - *(beginPtr + 2)));      
    return (*(dataPtr + offset));
};
    inline const double&  operator()(long i1, long i2, long i3, long i4) const
{ 
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2,i3,i4);
#endif
    const long* beginPtr = Structure.indexBeginBase.getDataPointer();
    const long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset    =  (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*
    ( (i2 - *(beginPtr +1)) + 
      ((*(endPtr +1) - *(beginPtr +1)) + 1)*
    ( (i3 - *(beginPtr + 2)) +
      ((*(endPtr +2) - *(beginPtr +2)) + 1)*(i4 - *(beginPtr + 3))));   
    return (*(dataPtr + offset));
};
    inline const double&  operator()(long i1, long i2, long i3, long i4, long i5) const
{ 
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2,i3,i4,i5);
#endif
    const long* beginPtr = Structure.indexBeginBase.getDataPointer();
    const long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset    =  (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*
    ((i2 - *(beginPtr +1)) + 
    ((*(endPtr +1) - *(beginPtr +1)) + 1)*
    ((i3 - *(beginPtr + 2)) + 
    ((*(endPtr +2) - *(beginPtr +2)) + 1)*
    ((i4 - *(beginPtr + 3)) +
    ((*(endPtr +3) - *(beginPtr +3)) + 1)*(i5 - *(beginPtr + 4)))));   
    return (*(dataPtr + offset));
};
    inline const double&  operator()(long i1, long i2, long i3, long i4, long i5, long i6) const
{
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2,i3,i4,i5,i6);
#endif
    const long* beginPtr = Structure.indexBeginBase.getDataPointer();
    const long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset    =  (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*
    ((i2 - *(beginPtr +1)) + 
    ((*(endPtr +1) - *(beginPtr +1)) + 1)*
    ((i3 - *(beginPtr + 2)) + 
    ((*(endPtr +2) - *(beginPtr +2)) + 1)*
    ((i4 - *(beginPtr + 3)) +
    ((*(endPtr +3) - *(beginPtr +3)) + 1)*
    ((i5 - *(beginPtr + 4)) +
    ((*(endPtr +4) - *(beginPtr +4)) + 1)*(i6 - *(beginPtr + 5))))));   
    return (*(dataPtr + offset));
};
    inline const double&  operator()(long i1, long i2, long i3, long i4, long i5, long i6, long i7) const
{
#ifndef _NO_BOUNDS_CHECK_
    CAMarrayBase::indexCheck(Structure,i1,i2,i3,i4,i5,i6,i7);
#endif   
    const long* beginPtr  = Structure.indexBeginBase.getDataPointer();
    const long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset    =  (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*
    ((i2 - *(beginPtr +1)) +
    ((*(endPtr +1) - *(beginPtr +1)) + 1)*
    ((i3 - *(beginPtr + 2)) +
    ((*(endPtr +2) - *(beginPtr +2)) + 1)*
    ((i4 - *(beginPtr + 3)) +
    ((*(endPtr +3) - *(beginPtr +3)) + 1)*
    ((i5 - *(beginPtr + 4)) +
    ((*(endPtr +4) - *(beginPtr +4)) + 1)*
    ((i6 - *(beginPtr + 5)) +
    ((*(endPtr +5) - *(beginPtr +5)) + 1)*(i7 - *(beginPtr + 6)))))));
    return (*(dataPtr + offset));
};
    CAMdoubleArray  operator() (const CAMrange& R1)
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    const CAMdoubleArray  operator()(const CAMrange& R1) const
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    const CAMdoubleArray  operator()(const CAMrange& R1, const CAMrange& R2) const
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    CAMdoubleArray  operator() (const CAMrange& R1, const CAMrange& R2)
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    const CAMdoubleArray  operator()(const CAMrange& R1, const CAMrange& R2,
const CAMrange& R3) const
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2,R3);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    CAMdoubleArray  operator() (const CAMrange& R1, const CAMrange& R2,
const CAMrange& R3)
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2, R3);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    const CAMdoubleArray  operator()(const CAMrange& R1, const CAMrange& R2,
const CAMrange& R3, const CAMrange& R4) const
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2,R3,R4);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    CAMdoubleArray  operator() (const CAMrange& R1, const CAMrange& R2,
const CAMrange& R3, const CAMrange& R4)
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2, R3, R4);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    const CAMdoubleArray  operator()(const CAMrange& R1, const CAMrange& R2,
const CAMrange& R3, const CAMrange& R4, const CAMrange& R5) const
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2,R3,R4, R5);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    CAMdoubleArray  operator() (const CAMrange& R1, const CAMrange& R2,
const CAMrange& R3, const CAMrange& R4, const CAMrange& R5)
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2, R3, R4, R5);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    CAMdoubleArray  operator() (const CAMrange& R1, const CAMrange& R2,
const CAMrange& R3, const CAMrange& R4, const CAMrange& R5,
const CAMrange& R6)
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2, R3, R4, R5, R6);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    const CAMdoubleArray  operator()(const CAMrange& R1, const CAMrange& R2,
const CAMrange& R3, const CAMrange& R4, const CAMrange& R5, const CAMrange& R6) const
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2,R3,R4, R5, R6);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    CAMdoubleArray  operator() (const CAMrange& R1, const CAMrange& R2,
const CAMrange& R3, const CAMrange& R4, const CAMrange& R5,
const CAMrange& R6, const CAMrange& R7)
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2, R3, R4, R5, R6, R7);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    const CAMdoubleArray  operator()(const CAMrange& R1, const CAMrange& R2,
const CAMrange& R3, const CAMrange& R4, const CAMrange& R5, const CAMrange& R6,
const CAMrange& R7) const
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2,R3,R4, R5, R6, R7);
    CAMdoubleArray A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
//
//  data pointer access
//
    double*  getDataPointer() const {return (double*)DataP->getDataPointer();};

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//






  

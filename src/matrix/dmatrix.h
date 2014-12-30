//
//******************************************************************************
//                    DMATRIX.H
//******************************************************************************
//

#include "strctbse.h"
#include "datahndl.h"
#include "matbse.h"
#include "vecbse.h" 
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

#ifndef _CAMDOUBLEMATRIX_
#define _CAMDOUBLEMATRIX_

#include "mvaimpexp.h"

class __IMPEXP__ CAMdoubleMatrix : public CAMmatrixBase
{

public :

//
//  Constructors
//
    CAMdoubleMatrix():CAMmatrixBase(CAMType::typeDouble){};
    CAMdoubleMatrix(const CAMdoubleMatrix& A):CAMmatrixBase(*((CAMmatrixBase*)&A)){};
    CAMdoubleMatrix(const CAMmatrixBase& A):CAMmatrixBase(A){};
    CAMdoubleMatrix(const CAMrange& R1, const CAMrange& R2) 
    : CAMmatrixBase(CAMType::typeDouble,R1, R2){}; 
//
//  Assignment
//
    void  operator = (const CAMdoubleMatrix& A)
    {CAMmatrixBase* basePtr = this; const CAMmatrixBase* AbasePtr =
    (CAMmatrixBase*)&A; basePtr->operator=(*AbasePtr);};
    void  operator =( const CAMmatrixBase& A)
    {CAMmatrixBase* basePtr = this; basePtr->operator=(A);};
     void  operator = (const CAMvectorBase& A) 
 {CAMmatrixBase* basePtr = this; basePtr->operator=(A);};
    void  operator = (double value)
    {CAMmatrixBase* basePtr = this; basePtr->operator=(value);};
//
//  initialization
//
    void  initialize()
    {CAMmatrixBase* basePtr = this; basePtr->initialize(CAMType::typeDouble);};
    void  initialize(const CAMdoubleMatrix& A)
    {CAMmatrixBase* basePtr = this; basePtr->initialize(A);};
    void  initialize(const CAMmatrixBase& A)
    {CAMmatrixBase* basePtr = this; basePtr->initialize(A);};
    void  initialize(const CAMrange& R1, const CAMrange& R2) 
    {CAMmatrixBase* basePtr = this; basePtr->initialize(CAMType::typeDouble,R1, R2);}; 
//
//  Access Functions
//
    inline double&  operator()(long i1, long i2)
{
#ifndef _NO_BOUNDS_CHECK_
    CAMmatrixBase::indexCheck(Structure,i1,i2);
#endif
    long* beginPtr = Structure.indexBeginBase.getDataPointer();
    long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer; 
    
    long offset = 
    (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*(i2 - *(beginPtr +1)); 

    return (*(dataPtr + offset));
};
    inline const double&  operator()(long i1, long i2) const
{ 
#ifndef _NO_BOUNDS_CHECK_
    CAMmatrixBase::indexCheck(Structure,i1,i2);
#endif
    const long* beginPtr = Structure.indexBeginBase.getDataPointer();
    const long* endPtr   = Structure.indexEndBase.getDataPointer();
    
    double* dataPtr =  (double*)DataP->dataPointer; 
    
    long offset = 
    (i1 - *(beginPtr)) + 
    ((*endPtr - *beginPtr) + 1)*(i2 - *(beginPtr +1)); 
    
    return (*(dataPtr + offset));
};
    const CAMdoubleMatrix  operator()(const CAMrange& R1, const CAMrange& R2) const
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2);
    CAMdoubleMatrix A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
};
    CAMdoubleMatrix  operator() (const CAMrange& R1, const CAMrange& R2)
{
    CAMstructureBase Rstructure(Structure);
    Rstructure.setStructureSubset(R1,R2);
    CAMdoubleMatrix A;
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
// 
//  Double Matrix Specific Utility Routines  
//
    static CAMdoubleMatrix identity(long n);

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//




  

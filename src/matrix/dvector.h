//
//******************************************************************************
//                    DVECTOR.H
//******************************************************************************
//

#include "strctbse.h"
#include "datahndl.h"
#include "vecbse.h"
#include "matbse.h" 
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

#ifndef _CAMDOUBLEVECTOR_
#define _CAMDOUBLEVECTOR_

#include "mvaimpexp.h"

class __IMPEXP__ CAMdoubleVector : public CAMvectorBase
{

public :
//
//  Constructors
//
    CAMdoubleVector():CAMvectorBase(CAMType::typeDouble){};
    CAMdoubleVector(const CAMdoubleVector& A):CAMvectorBase(*((CAMvectorBase*)&A)){};
    CAMdoubleVector(const CAMvectorBase& A):CAMvectorBase(A){};
    CAMdoubleVector(long n):CAMvectorBase(CAMType::typeDouble, n){};
    CAMdoubleVector(const CAMrange& R1) 
    : CAMvectorBase(CAMType::typeDouble,R1){}; 
    CAMdoubleVector(const CAMrange& R1,char* RorC)
    : CAMvectorBase(CAMType::typeDouble,R1)
    {if(RorC[0] == 'r') (*this).initialize(this->transpose());};
//
//  Assignment
//
    void  operator = (const CAMdoubleVector& A)
    {CAMvectorBase* basePtr = this; const CAMvectorBase* AbasePtr =
    (CAMvectorBase*)&A; basePtr->operator=(*AbasePtr);};
    void  operator =( const CAMvectorBase& A)
    {CAMvectorBase* basePtr = this; basePtr->operator=(A);};
    void operator = (const CAMmatrixBase& A) 
 {CAMvectorBase* basePtr = this; basePtr->operator=(A);};
    void  operator = (double value)
    {CAMvectorBase* basePtr = this; basePtr->operator=(value);};
//
//  initialization
//
    void  initialize()
    {CAMvectorBase* basePtr = this; basePtr->initialize(CAMType::typeDouble);};
    void  initialize(const CAMdoubleVector& A)
    {CAMvectorBase* basePtr = this; basePtr->initialize(A);};
    void  initialize(const CAMvectorBase& A)
    {CAMvectorBase* basePtr = this; basePtr->initialize(A);};
    void  initialize(long n)
    {CAMvectorBase* basePtr = this; basePtr->initialize(CAMType::typeDouble, n);};
    void  initialize(const CAMrange& R1) 
    {CAMvectorBase* basePtr = this; basePtr->initialize(CAMType::typeDouble,R1);}; 
    inline double&  operator()(long i1)
{
#ifndef _NO_BOUNDS_CHECK_
    long ia, ib;
    if(Structure[1].getIndexCount() != 1)
    {ia = i1; ib = Structure[2].getIndexBase();}
    else
    {ia = Structure[1].getIndexBase(); ib = i1;}
    CAMvectorBase::indexCheck(Structure,ia,ib);
#endif
    long* beginPtr = Structure.indexBeginBase.getDataPointer();

    double* dataPtr =  (double*)DataP->dataPointer;
    long offset = (i1 - *(beginPtr));
    return *(dataPtr + offset);
}
    inline const double&  operator()(long i1) const
{   
#ifndef _NO_BOUNDS_CHECK_
    long ia, ib;
    if(Structure[1].getIndexCount() != 1)
    {ia = i1; ib = Structure[2].getIndexBase();}
    else
    {ia = Structure[1].getIndexBase(); ib = i1;}
    CAMvectorBase::indexCheck(Structure,ia,ib);
#endif
    const long* beginPtr = Structure.indexBeginBase.getDataPointer();
    double* dataPtr =  (double*)DataP->dataPointer;
    long offset = (i1 - *(beginPtr));
    return (*(dataPtr + offset));
};
    CAMdoubleVector  operator() (const CAMrange& R1)
{
    CAMstructureBase Rstructure(Structure);
    CAMrange Ra, Rb;
    if(Structure[1].getIndexCount() != 1)
    {
     Ra = R1;
     Rb.initialize(Structure[2].getIndexBase(),Structure[2].getIndexBase());
    }
    else
    {
     Ra.initialize(Structure[1].getIndexBase(),Structure[1].getIndexBase());
     Rb = R1;
    }
    Rstructure.setStructureSubset(Ra,Rb);
    CAMdoubleVector A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
}
    const CAMdoubleVector  operator()(const CAMrange& R1) const
{
    CAMstructureBase Rstructure(Structure);
    CAMrange Ra, Rb;
    if(Structure[1].getIndexCount() != 1)
    {
     Ra = R1;
     Rb.initialize(Structure[2].getIndexBase(),Structure[2].getIndexBase());
    }
    else
    {
     Ra.initialize(Structure[1].getIndexBase(),Structure[1].getIndexBase());
     Rb = R1;
    }
    Rstructure.setStructureSubset(Ra,Rb);
    CAMdoubleVector A;
    A.Structure.initialize(Rstructure);
    A.DataP = DataP;
    A.DataP->incrementReferenceCount();
    A.DataP->incrementReferenceCount();
    A.referenceFlag = 1;
    return A;
}
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




  

//
//******************************************************************************
//                    BNENGINE.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Sat Feb 03 18:11:18 1996
//
//********************************************************************************
//

#include <iostream.h>
#include "strctbse.h"
#include "datahndl.h"


#ifndef __CAMBINARYENGINE__
#define __CAMBINARYENGINE__

#include "mvaimpexp.h" // C

class __IMPEXP__ CAMbinaryEngine
{

public :

//
//  
//
    static void  doubleAequalToB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata);
    static void  doubleAequalToMinusB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata);
    static void  doubleAplusEqualB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata);
    static void  doubleAminusEqualB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata);
    static void  doubleAtimesEqualB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata);
    static void  doubleAdivideEqualB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata);
    static void  doubleCequalAplusB(const CAMstructureBase &Astructure, const CAMdataHandler &Adata,
    const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata,
    CAMstructureBase &Cstructure, CAMdataHandler &Cdata);
    static void  doubleCequalAminusB(const CAMstructureBase &Astructure, const CAMdataHandler &Adata,
    const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata,
    CAMstructureBase &Cstructure, CAMdataHandler &Cdata);
    static void  doubleCequalAtimesB(const CAMstructureBase &Astructure, const CAMdataHandler &Adata,
    const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata,
    CAMstructureBase &Cstructure, CAMdataHandler &Cdata);
    static void  doubleCequalAdivideB(const CAMstructureBase &Astructure, const CAMdataHandler &Adata,
    const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata,
    CAMstructureBase &Cstructure, CAMdataHandler &Cdata);
    static void  doubleAequalToAlpha(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    double alpha);
    static void  doubleAplusEqualAlpha(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    double alpha);
    static void  doubleAminusEqualAlpha(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    double alpha);
    static void  doubleAtimesEqualAlpha(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    double alpha);
    static void  doubleAdivideEqualAlpha(CAMstructureBase &Astructure, CAMdataHandler &Adata,
    double alpha);
    static void  doubleMaxValue(double* data, long n, double& maxValue);
    static void  doubleMinValue(double* data, long n, double& minValue);
    static void  doubleMaxAbsValue(double* data, long n, double& maxAbsValue);
    static void  doubleMinAbsValue(double* data, long n, double& minAbsValue);
    static void  doublepNorm(double* data, long n, double p, double& pNormValue);

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//


  

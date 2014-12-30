#include "bnengine.h"
#include "strctbse.h"
#include "datahndl.h"
#include "math.h"
#include "blas.h"

void  CAMbinaryEngine::doubleAequalToAlpha(CAMstructureBase &Astructure, CAMdataHandler &Adata,
double alpha)
{
    double* AdataP = (double*)Adata.getDataPointer();

#ifndef __NO_BLAS__
    long strideA;
    long Size;
    long longZero = 0;
#endif

    if(Astructure.isSubset() == 0)
    {
#ifdef __NO_BLAS__
    double* aptr; 
    for(aptr = AdataP; aptr < AdataP + Adata.getDataSize(); aptr++)
    { *aptr = alpha; };
#else
    strideA    = 1;
    Size       = Adata.getDataSize();
    dcopy_(&Size,&alpha,&longZero, AdataP, &strideA);
#endif
    }
    else
    {
//
//  Get Normalized Loops
//
    long AloopDimension;
    long AOffset;
    MVAlongBase ACount;
    MVAlongBase AStride;

    Astructure.getNormalizedLoops(AloopDimension,AOffset, ACount, AStride);

    register long i1, i2, i3, i4, i5, i6, i7;

    double* AOffptr = AdataP + AOffset;

    register double* Ap1;
    register double* Ap2;
    register double* Ap3;
    register double* Ap4;
    register double* Ap5;
    register double* Ap6;

#ifndef __NO_BLAS__
    strideA = AStride[0];
    Size    = ACount[0];
#endif

    switch(AloopDimension)
    {
    case 1 :
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(AOffptr + i1) = alpha;};
#else
    dcopy_(&Size,&alpha,&longZero, AOffptr, &strideA);
#endif

    break;

    case 2 :
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = AOffptr + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) = alpha;};
#else
    dcopy_(&Size,&alpha,&longZero, Ap1, &strideA);
#endif
    };
    break;

    case 3 :
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = AOffptr + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) = alpha;};
#else
    dcopy_(&Size,&alpha,&longZero, Ap1, &strideA);
#endif
    }};
    break;

    case 4 :
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = AOffptr + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) = alpha;};
#else
    dcopy_(&Size,&alpha,&longZero, Ap1, &strideA);
#endif
    }}};
    break;

    case 5 :
    for(i5=0; i5 < ACount[4]*AStride[4]; i5+=AStride[4])
    { Ap4 = AOffptr + i5;
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = Ap4 + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) = alpha;};
#else
    dcopy_(&Size,&alpha,&longZero, Ap1, &strideA);
#endif
    }}}};
    break;

    case 6 :
    for(i6=0; i6 < ACount[5]*AStride[5]; i6+=AStride[5])
    { Ap5 = AOffptr+ i6;
    for(i5=0; i5 < ACount[4]*AStride[4]; i5+=AStride[4])
    { Ap4 = Ap5 + i5;
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = Ap4 + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) = alpha;};
#else
    dcopy_(&Size,&alpha,&longZero, Ap1, &strideA);
#endif
    }}}}};
    break;

    case 7 :
    for(i7=0; i7 < ACount[6]*AStride[6]; i7+=AStride[6])
    { Ap6 = AOffptr + i7;
    for(i6=0; i6 < ACount[5]*AStride[5]; i6+=AStride[5])
    { Ap5 = Ap6 + i6;
    for(i5=0; i5 < ACount[4]*AStride[4]; i5+=AStride[4])
    { Ap4 = Ap5 + i5;
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = Ap4 + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) = alpha;};
#else
    dcopy_(&Size,&alpha,&longZero, Ap1, &strideA);
#endif
    }}}}}};
    break;

    }
}

}


void  CAMbinaryEngine::doubleAplusEqualAlpha(CAMstructureBase &Astructure, CAMdataHandler &Adata,
double alpha)
{
    double* AdataP = (double*)Adata.getDataPointer();

#ifndef __NO_BLAS__
    long strideA;
    long Size;
    long longZero = 0;
    double dOne   = 1.0;
#endif

    if(Astructure.isSubset() == 0)
    {
#ifdef __NO_BLAS__
    double* aptr; 
    for(aptr = AdataP; aptr < AdataP + Adata.getDataSize(); aptr++)
    { *aptr += alpha; };
#else
    strideA    = 1;
    Size       = Adata.getDataSize();
    daxpy_(&Size,&dOne, &alpha,&longZero, AdataP, &strideA);
#endif
    }
    else
    {
//
//  Get Normalized Loops
//
    long AloopDimension;
    long AOffset;
    MVAlongBase ACount;
    MVAlongBase AStride;

    Astructure.getNormalizedLoops(AloopDimension,AOffset, ACount, AStride);

    register long i1, i2, i3, i4, i5, i6, i7;

    double* AOffptr = AdataP + AOffset;

    register double* Ap1;
    register double* Ap2;
    register double* Ap3;
    register double* Ap4;
    register double* Ap5;
    register double* Ap6;

#ifndef __NO_BLAS__
    strideA = AStride[0];
    Size    = ACount[0];
#endif

    switch(AloopDimension)
    {
    case 1 :
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(AOffptr + i1) += alpha;};
#else
    daxpy_(&Size,&dOne,&alpha,&longZero, AOffptr, &strideA);
#endif

    break;

    case 2 :
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = AOffptr + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) += alpha;};
#else
    daxpy_(&Size, &dOne, &alpha,&longZero, Ap1, &strideA);
#endif
    };
    break;

    case 3 :
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = AOffptr + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) += alpha;};
#else
    daxpy_(&Size, &dOne, &alpha,&longZero, Ap1, &strideA);
#endif
    }};
    break;

    case 4 :
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = AOffptr + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) += alpha;};
#else
    daxpy_(&Size, &dOne, &alpha,&longZero, Ap1, &strideA);
#endif
    }}};
    break;

    case 5 :
    for(i5=0; i5 < ACount[4]*AStride[4]; i5+=AStride[4])
    { Ap4 = AOffptr + i5;
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = Ap4 + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) += alpha;};
#else
    daxpy_(&Size, &dOne, &alpha,&longZero, Ap1, &strideA);
#endif
    }}}};
    break;

    case 6 :
    for(i6=0; i6 < ACount[5]*AStride[5]; i6+=AStride[5])
    { Ap5 = AOffptr+ i6;
    for(i5=0; i5 < ACount[4]*AStride[4]; i5+=AStride[4])
    { Ap4 = Ap5 + i5;
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = Ap4 + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1) += alpha;};
#else
    daxpy_(&Size, &dOne, &alpha,&longZero, Ap1, &strideA);
#endif
    }}}}};
    break;

    case 7 :
    for(i7=0; i7 < ACount[6]*AStride[6]; i7+=AStride[6])
    { Ap6 = AOffptr + i7;
    for(i6=0; i6 < ACount[5]*AStride[5]; i6+=AStride[5])
    { Ap5 = Ap6 + i6;
    for(i5=0; i5 < ACount[4]*AStride[4]; i5+=AStride[4])
    { Ap4 = Ap5 + i5;
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = Ap4 + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
#ifdef __NO_BLAS__
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1 ) += alpha;};
#else
    daxpy_(&Size, &dOne, &alpha,&longZero, Ap1, &strideA);
#endif
    }}}}}};
    break;

    }
}

}

void  CAMbinaryEngine::doubleAtimesEqualAlpha(CAMstructureBase &Astructure, CAMdataHandler &Adata,
double alpha)
{
    double* AdataP = (double*)Adata.getDataPointer();

    if(Astructure.isSubset() == 0)
    {
    double* aptr; 
    for(aptr = AdataP; aptr < AdataP + Adata.getDataSize(); aptr++)
    { *aptr *= alpha; };
    }
    else
    {
//
//  Get Normalized Loops
//
    long AloopDimension;
    long AOffset;
    MVAlongBase ACount;
    MVAlongBase AStride;

    Astructure.getNormalizedLoops(AloopDimension,AOffset, ACount, AStride);

    register long i1, i2, i3, i4, i5, i6, i7;

    double* AOffptr = AdataP + AOffset;

    register double* Ap1;
    register double* Ap2;
    register double* Ap3;
    register double* Ap4;
    register double* Ap5;
    register double* Ap6;

    switch(AloopDimension)
    {
    case 1 :
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(AOffptr + i1) *= alpha;};
    break;

    case 2 :
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = AOffptr + i2;
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1 ) *= alpha;};
    };
    break;

    case 3 :
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = AOffptr + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1 ) *= alpha;};
    }};
    break;

    case 4 :
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = AOffptr + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1 ) *= alpha;};
    }}};
    break;

    case 5 :
    for(i5=0; i5 < ACount[4]*AStride[4]; i5+=AStride[4])
    { Ap4 = AOffptr + i5;
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = Ap4 + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1 ) *= alpha;};
    }}}};
    break;

    case 6 :
    for(i6=0; i6 < ACount[5]*AStride[5]; i6+=AStride[5])
    { Ap5 = AOffptr+ i6;
    for(i5=0; i5 < ACount[4]*AStride[4]; i5+=AStride[4])
    { Ap4 = Ap5 + i5;
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = Ap4 + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1 ) *= alpha;};
    }}}}};
    break;

    case 7 :
    for(i7=0; i7 < ACount[6]*AStride[6]; i7+=AStride[6])
    { Ap6 = AOffptr + i7;
    for(i6=0; i6 < ACount[5]*AStride[5]; i6+=AStride[5])
    { Ap5 = Ap6 + i6;
    for(i5=0; i5 < ACount[4]*AStride[4]; i5+=AStride[4])
    { Ap4 = Ap5 + i5;
    for(i4=0; i4 < ACount[3]*AStride[3]; i4+=AStride[3])
    { Ap3 = Ap4 + i4;
    for(i3=0; i3 < ACount[2]*AStride[2]; i3+=AStride[2])
    { Ap2 = Ap3 + i3;
    for(i2=0; i2 < ACount[1]*AStride[1]; i2+=AStride[1])
    { Ap1 = Ap2 + i2;
    for(i1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0])
    {*(Ap1 + i1 ) *= alpha;};
    }}}}}};
    break;

    }
}

}

void  CAMbinaryEngine::doubleAminusEqualAlpha(CAMstructureBase &Astructure, CAMdataHandler &Adata,
double alpha)
{CAMbinaryEngine::doubleAplusEqualAlpha(Astructure, Adata, -alpha);}

void  CAMbinaryEngine::doubleAdivideEqualAlpha(CAMstructureBase &Astructure, CAMdataHandler &Adata,
double alpha)
{CAMbinaryEngine::doubleAtimesEqualAlpha(Astructure, Adata, 1.0/alpha);}

//
//   Array Utilities

void  CAMbinaryEngine::doubleMaxValue(double* data, long n, double& maxValue)
{
    long i;
    maxValue = *data;
    for(i = 1; i < n; i++)
    if(maxValue < *(data + i)) maxValue = *(data + i);
}
void  CAMbinaryEngine::doubleMinValue(double* data, long n, double& minValue)
{
    long i;
    minValue = *data;
    for(i = 1; i < n; i++)
    if(minValue > *(data + i)) minValue = *(data + i);
}
void  CAMbinaryEngine::doubleMaxAbsValue(double* data, long n, double& maxAbsValue)
{
    long i;
    maxAbsValue = fabs(*data);
    for(i = 1; i < n; i++)
    if(maxAbsValue < fabs(*(data + i))) maxAbsValue = fabs(*(data + i));
}
void  CAMbinaryEngine::doubleMinAbsValue(double* data, long n, double& minAbsValue)
{
    long i;
    minAbsValue = fabs(*data);
    for(i = 1; i < n; i++)
    if(minAbsValue > fabs(*(data + i))) minAbsValue = fabs(*(data + i));
}

void CAMbinaryEngine::doublepNorm(double* data, long n, double p, double& pNormValue)
{
    pNormValue = 0.0;
    double* dptr;
    for(dptr = (double*)data; dptr < (double*)data  + n; dptr++)
    pNormValue += ::pow(fabs(*(dptr)),p);

    pNormValue = ::pow(pNormValue,1.0/p);
}
  

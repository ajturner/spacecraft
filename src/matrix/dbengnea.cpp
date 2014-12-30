#include "bnengine.h"
#include "strctbse.h"
#include "datahndl.h"
#include "blas.h"

void  CAMbinaryEngine::doubleAequalToB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata)
{
    double* AdataP = (double*)Adata.getDataPointer();
    double* BdataP = (double*)Bdata.getDataPointer();

    CAMdataHandler Btemporary;
    if(AdataP == BdataP)
    {
    Btemporary.initialize(Bdata);
    BdataP = (double*)Btemporary.getDataPointer();
    }

#ifndef __NO_BLAS__
    long strideA;
    long strideB;
    long Size;
#endif

    if((Astructure.isSubset() == 0)&&(Bstructure.isSubset() == 0))
    {
#ifdef __NO_BLAS__
    register double* aptr; register double* bptr;
    for(aptr = AdataP, bptr = BdataP;
       aptr < AdataP + Adata.getDataSize();
       aptr++, bptr++) { *aptr = *bptr; };
#else
    strideA    = 1;
    strideB    = 1;
    Size       = Adata.getDataSize();

    dcopy_(&Size,BdataP,&strideB, AdataP, &strideA);
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

    long BloopDimension;
    long BOffset;
    MVAlongBase BCount;
    MVAlongBase BStride;

    Astructure.getNormalizedLoops(AloopDimension,AOffset, ACount, AStride);
    Bstructure.getNormalizedLoops(BloopDimension,BOffset, BCount, BStride);

    register long i1, i2, i3, i4, i5, i6, i7;
    register long j1, j2, j3, j4, j5, j6, j7;

    double* AOffptr = AdataP + AOffset;
    double* BOffptr = BdataP + BOffset;

    register double* Ap1; register double* Bp1;
    register double* Ap2; register double* Bp2;
    register double* Ap3; register double* Bp3;
    register double* Ap4; register double* Bp4;
    register double* Ap5; register double* Bp5;
    register double* Ap6; register double* Bp6;

#ifndef __NO_BLAS__
    strideA = AStride[0];
    strideB = BStride[0];
    Size    = ACount[0];
#endif

    switch(AloopDimension)
    {
    case 1 :
#ifdef __NO_BLAS__
    for(i1=0, j1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(AOffptr + i1) = *(BOffptr + j1);
    };
#else
    Bp1 = BOffptr;
    Ap1 = AOffptr;
    dcopy_(&Size,Bp1,&strideB, Ap1, &strideA);
#endif

    break;

    case 2 :
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = AOffptr + i2; Bp1 = BOffptr + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1)= *(Bp1 + j1);
    }
#else
    dcopy_(&Size,Bp1,&strideB, Ap1, &strideA);
#endif
    };
    break;

    case 3 :
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = AOffptr + i3; Bp2 = BOffptr + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2     + i2; Bp1 = Bp2     + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) = *(Bp1 + j1);
    }
#else
    dcopy_(&Size,Bp1,&strideB, Ap1, &strideA);
#endif
    }};
    break;

    case 4 :
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = AOffptr + i4; Bp3 = BOffptr + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) = *(Bp1 + j1);
    }
#else
    dcopy_(&Size,Bp1,&strideB, Ap1, &strideA);
#endif
    }}};
    break;

    case 5 :
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = AOffptr + i5; Bp4 = BOffptr + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) = *(Bp1 + j1);
    }
#else
    dcopy_(&Size,Bp1,&strideB, Ap1, &strideA);
#endif
    }}}};
    break;

    case 6 :
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = AOffptr+ i6; Bp5 = BOffptr + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) = *(Bp1 + j1);
    }
#else
    dcopy_(&Size,Bp1,&strideB, Ap1, &strideA);
#endif
    }}}}};
    break;

    case 7 :
    for(i7=0, j7 = 0; i7 < ACount[6]*AStride[6]; i7+=AStride[6], j7+=BStride[6])
    { Ap6 = AOffptr + i7; Bp6 = BOffptr + j7;
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = Ap6 + i6; Bp5 = Bp6 + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) = *(Bp1 + j1);
    }
#else
    dcopy_(&Size,Bp1,&strideB, Ap1, &strideA);
#endif
    }}}}}};
    break;

    }
}

}

void  CAMbinaryEngine::doubleAequalToMinusB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata)
{
    double* AdataP = (double*)Adata.getDataPointer();
    double* BdataP = (double*)Bdata.getDataPointer();

    CAMdataHandler Btemporary;
    if(AdataP == BdataP)
    {
    Btemporary.initialize(Bdata);
    BdataP = (double*)Btemporary.getDataPointer();
    }

    if((Astructure.isSubset() == 0)&&(Bstructure.isSubset() == 0))
    {
    register double* aptr; register double* bptr;
    for(aptr = AdataP, bptr = BdataP;
       aptr < AdataP + Adata.getDataSize();
       aptr++, bptr++) { *aptr = -(*bptr);};
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

    long BloopDimension;
    long BOffset;
    MVAlongBase BCount;
    MVAlongBase BStride;

    Astructure.getNormalizedLoops(AloopDimension,AOffset, ACount, AStride);
    Bstructure.getNormalizedLoops(BloopDimension,BOffset, BCount, BStride);

    register long i1, i2, i3, i4, i5, i6, i7;
    register long j1, j2, j3, j4, j5, j6, j7;

    double* AOffptr = AdataP + AOffset;
    double* BOffptr = BdataP + BOffset;

    register double* Ap1; register double* Bp1;
    register double* Ap2; register double* Bp2;
    register double* Ap3; register double* Bp3;
    register double* Ap4; register double* Bp4;
    register double* Ap5; register double* Bp5;
    register double* Ap6; register double* Bp6;


    switch(AloopDimension)
    {
    case 1 :
    for(i1=0, j1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(AOffptr + i1) = -(*(BOffptr + j1));
    };

    break;

    case 2 :
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = AOffptr + i2; Bp1 = BOffptr + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1)= -(*(Bp1 + j1));
    }};
    break;

    case 3 :
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = AOffptr + i3; Bp2 = BOffptr + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2     + i2; Bp1 = Bp2     + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) = -(*(Bp1 + j1));
    }}};
    break;

    case 4 :
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = AOffptr + i4; Bp3 = BOffptr + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) =-(*(Bp1 + j1));
    }}}};
    break;

    case 5 :
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = AOffptr + i5; Bp4 = BOffptr + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) = -(*(Bp1 + j1));
    }}}}};
    break;

    case 6 :
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = AOffptr+ i6; Bp5 = BOffptr + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) =-(*(Bp1 + j1));
    }}}}}};
    break;

    case 7 :
    for(i7=0, j7 = 0; i7 < ACount[6]*AStride[6]; i7+=AStride[6], j7+=BStride[6])
    { Ap6 = AOffptr + i7; Bp6 = BOffptr + j7;
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = Ap6 + i6; Bp5 = Bp6 + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) = -(*(Bp1 + j1));
    }}}}}}};
    break;

    }
}
}

void  CAMbinaryEngine::doubleAplusEqualB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata)
{
    double* AdataP = (double*)Adata.getDataPointer();
    double* BdataP = (double*)Bdata.getDataPointer();

    CAMdataHandler Btemporary;
    if(AdataP == BdataP)
    {
    Btemporary.initialize(Bdata);
    BdataP = (double*)Btemporary.getDataPointer();
    }

#ifndef __NO_BLAS__
    long   strideA;
    long   strideB;
    long   Size;
    double dOne = 1.0;
#endif

    if((Astructure.isSubset() == 0)&&(Bstructure.isSubset() == 0))
    {
#ifdef __NO_BLAS__
    double* aptr; double* bptr;
    for(aptr = AdataP, bptr = BdataP;
       aptr < AdataP + Adata.getDataSize();
       aptr++, bptr++) { *aptr += *bptr; };
#else
    strideA    = 1;
    strideB    = 1;
    Size       = Adata.getDataSize();

    daxpy_(&Size,&dOne, BdataP,&strideB, AdataP, &strideA);
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

    long BloopDimension;
    long BOffset;
    MVAlongBase BCount;
    MVAlongBase BStride;

    Astructure.getNormalizedLoops(AloopDimension,AOffset, ACount, AStride);
    Bstructure.getNormalizedLoops(BloopDimension,BOffset, BCount, BStride);

    register long i1, i2, i3, i4, i5, i6, i7;
    register long j1, j2, j3, j4, j5, j6, j7;
    double* AOffptr = AdataP + AOffset;
    double* BOffptr = BdataP + BOffset;

    register double* Ap1; register double* Bp1;
    register double* Ap2; register double* Bp2;
    register double* Ap3; register double* Bp3;
    register double* Ap4; register double* Bp4;
    register double* Ap5; register double* Bp5;
    register double* Ap6; register double* Bp6;

#ifndef __NO_BLAS__
    strideA = AStride[0];
    strideB = BStride[0];
    Size    = ACount[0];
#endif

    switch(AloopDimension)
    {
    case 1 :
#ifdef __NO_BLAS__
    for(i1=0, j1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(AOffptr + i1) +=
    *(BOffptr + j1);
    };
#else
    daxpy_(&Size,&dOne, BOffptr,&strideB, AOffptr, &strideA);
#endif

    break;

    case 2 :
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = AOffptr + i2; Bp1 = BOffptr + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) += *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dOne, Bp1,&strideB, Ap1, &strideA);
#endif
    };
    break;

    case 3 :
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = AOffptr + i3; Bp2 = BOffptr + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2     + i2; Bp1 = Bp2     + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) += *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dOne, Bp1,&strideB, Ap1, &strideA);
#endif
    }};
    break;

    case 4 :
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = AOffptr + i4; Bp3 = BOffptr + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) += *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dOne, Bp1,&strideB, Ap1, &strideA);
#endif
    }}};
    break;

    case 5 :
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = AOffptr + i5; Bp4 = BOffptr + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) += *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dOne, Bp1,&strideB, Ap1, &strideA);
#endif
    }}}};
    break;

    case 6 : 
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = AOffptr+ i6; Bp5 = BOffptr + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) += *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dOne, Bp1,&strideB, Ap1, &strideA);
#endif
    }}}}};
    break;

    case 7 :
    for(i7=0, j7 = 0; i7 < ACount[6]*AStride[6]; i7+=AStride[6], j7+=BStride[6])
    { Ap6 = AOffptr + i7; Bp6 = BOffptr + j7;
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = Ap6 + i6; Bp5 = Bp6 + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) += *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dOne, Bp1,&strideB, Ap1, &strideA);
#endif
    }}}}}};
    break;

    }
}


}



void  CAMbinaryEngine::doubleAminusEqualB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata)
{
    double* AdataP = (double*)Adata.getDataPointer();
    double* BdataP = (double*)Bdata.getDataPointer();

    CAMdataHandler Btemporary;
    if(AdataP == BdataP)
    {
    Btemporary.initialize(Bdata);
    BdataP = (double*)Btemporary.getDataPointer();
    }

#ifndef __NO_BLAS__
    long strideA;
    long strideB;
    long Size;
    double dNegOne = -1.0;
#endif

    if((Astructure.isSubset() == 0)&&(Bstructure.isSubset() == 0))
    {
#ifdef __NO_BLAS__
    double* aptr; double* bptr;
    for(aptr = AdataP, bptr = BdataP;
       aptr < AdataP + Adata.getDataSize();
       aptr++, bptr++) { *aptr -= *bptr; };
#else
    strideA    = 1;
    strideB    = 1;
    Size       = Adata.getDataSize();

    daxpy_(&Size,&dNegOne, BdataP, &strideB, AdataP,&strideA);
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

    long BloopDimension;
    long BOffset;
    MVAlongBase BCount;
    MVAlongBase BStride;

    Astructure.getNormalizedLoops(AloopDimension,AOffset, ACount, AStride);
    Bstructure.getNormalizedLoops(BloopDimension,BOffset, BCount, BStride);

    register long i1, i2, i3, i4, i5, i6, i7;
    register long j1, j2, j3, j4, j5, j6, j7;
    double* AOffptr = AdataP + AOffset;
    double* BOffptr = BdataP + BOffset;

    register double* Ap1; register double* Bp1;
    register double* Ap2; register double* Bp2;
    register double* Ap3; register double* Bp3;
    register double* Ap4; register double* Bp4;
    register double* Ap5; register double* Bp5;
    register double* Ap6; register double* Bp6;

#ifndef __NO_BLAS__
    strideA = AStride[0];
    strideB = BStride[0];
    Size    = ACount[0];
#endif

    switch(AloopDimension)
    {
    case 1 :
#ifdef __NO_BLAS__
    for(i1=0, j1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(AOffptr + i1) -=
    *(BOffptr + j1);
    };
#else
    daxpy_(&Size,&dNegOne, BOffptr, &strideB,  AOffptr, &strideA);
#endif

    break;

    case 2 :
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = AOffptr + i2; Bp1 = BOffptr + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) -= *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dNegOne, Bp1,&strideB, Ap1, &strideA);
#endif
    };
    break;

    case 3 :
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = AOffptr + i3; Bp2 = BOffptr + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2     + i2; Bp1 = Bp2     + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) -= *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dNegOne, Bp1,&strideB, Ap1, &strideA);
#endif
    }};
    break;

    case 4 :
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = AOffptr + i4; Bp3 = BOffptr + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) -= *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dNegOne, Bp1,&strideB, Ap1, &strideA);
#endif
    }}};
    break;

    case 5 :
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = AOffptr + i5; Bp4 = BOffptr + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) -= *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dNegOne, Bp1,&strideB, Ap1, &strideA);
#endif
    }}}};
    break;

    case 6 :
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = AOffptr+ i6; Bp5 = BOffptr + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) -= *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dNegOne, Bp1,&strideB, Ap1, &strideA);
#endif
    }}}}};
    break;

    case 7 :
    for(i7=0, j7 = 0; i7 < ACount[6]*AStride[6]; i7+=AStride[6], j7+=BStride[6])
    { Ap6 = AOffptr + i7; Bp6 = BOffptr + j7;
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = Ap6 + i6; Bp5 = Bp6 + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
#ifdef __NO_BLAS__
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) -= *(Bp1 + j1);
    }
#else
    daxpy_(&Size,&dNegOne, Bp1,&strideB, Ap1, &strideA);
#endif
    }}}}}};
    break;

    }
}


}


void  CAMbinaryEngine::doubleAtimesEqualB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata)
{
    double* AdataP = (double*)Adata.getDataPointer();
    double* BdataP = (double*)Bdata.getDataPointer();

    CAMdataHandler Btemporary;
    if(AdataP == BdataP)
    {
    Btemporary.initialize(Bdata);
    BdataP = (double*)Btemporary.getDataPointer();
    }

    if((Astructure.isSubset() == 0)&&(Bstructure.isSubset() == 0))
    {
    double* aptr; double* bptr;
    for(aptr = AdataP, bptr = BdataP;
       aptr < AdataP + Adata.getDataSize();
       aptr++, bptr++) { *aptr *= *bptr; };
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

    long BloopDimension;
    long BOffset;
    MVAlongBase BCount;
    MVAlongBase BStride;

    Astructure.getNormalizedLoops(AloopDimension,AOffset, ACount, AStride);
    Bstructure.getNormalizedLoops(BloopDimension,BOffset, BCount, BStride);

    register long i1, i2, i3, i4, i5, i6, i7;
    register long j1, j2, j3, j4, j5, j6, j7;
    double* AOffptr = AdataP + AOffset;
    double* BOffptr = BdataP + BOffset;

    register double* Ap1; register double* Bp1;
    register double* Ap2; register double* Bp2;
    register double* Ap3; register double* Bp3;
    register double* Ap4; register double* Bp4;
    register double* Ap5; register double* Bp5;
    register double* Ap6; register double* Bp6;

    switch(AloopDimension)
    {
    case 1 :

    for(i1=0, j1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(AOffptr + i1) *= *(BOffptr + j1);
    };

    break;

    case 2 :
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = AOffptr + i2; Bp1 = BOffptr + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) *= *(Bp1 + j1);
    }
    };
    break;

    case 3 :
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = AOffptr + i3; Bp2 = BOffptr + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2     + i2; Bp1 = Bp2     + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) *= *(Bp1 + j1);
    }
    }};
    break;

    case 4 :
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = AOffptr + i4; Bp3 = BOffptr + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) *= *(Bp1 + j1);
    }
    }}};
    break;

    case 5 :
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = AOffptr + i5; Bp4 = BOffptr + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) *= *(Bp1 + j1);
    }
    }}}};
    break;

    case 6 :

    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = AOffptr+ i6; Bp5 = BOffptr + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) *= *(Bp1 + j1);
    }
    }}}}};
    break;

    case 7 :
    for(i7=0, j7 = 0; i7 < ACount[6]*AStride[6]; i7+=AStride[6], j7+=BStride[6])
    { Ap6 = AOffptr + i7; Bp6 = BOffptr + j7;
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = Ap6 + i6; Bp5 = Bp6 + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) *= *(Bp1 + j1);
    }
    }}}}}};
    break;

    }
}
}


void  CAMbinaryEngine::doubleAdivideEqualB(CAMstructureBase &Astructure, CAMdataHandler &Adata,
const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata)
{
    double* AdataP = (double*)Adata.getDataPointer();
    double* BdataP = (double*)Bdata.getDataPointer();

    CAMdataHandler Btemporary;
    if(AdataP == BdataP)
    {
    Btemporary.initialize(Bdata);
    BdataP = (double*)Btemporary.getDataPointer();
    }

    if((Astructure.isSubset() == 0)&&(Bstructure.isSubset() == 0))
    {
    double* aptr; double* bptr;
    for(aptr = AdataP, bptr = BdataP;
       aptr < AdataP + Adata.getDataSize();
       aptr++, bptr++) { *aptr /= *bptr; };
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

    long BloopDimension;
    long BOffset;
    MVAlongBase BCount;
    MVAlongBase BStride;

    Astructure.getNormalizedLoops(AloopDimension,AOffset, ACount, AStride);
    Bstructure.getNormalizedLoops(BloopDimension,BOffset, BCount, BStride);

    register long i1, i2, i3, i4, i5, i6, i7;
    register long j1, j2, j3, j4, j5, j6, j7;
    double* AOffptr = AdataP + AOffset;
    double* BOffptr = BdataP + BOffset;

    register double* Ap1; register double* Bp1;
    register double* Ap2; register double* Bp2;
    register double* Ap3; register double* Bp3;
    register double* Ap4; register double* Bp4;
    register double* Ap5; register double* Bp5;
    register double* Ap6; register double* Bp6;
    switch(AloopDimension)
    {
    case 1 :

    for(i1=0, j1=0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(AOffptr + i1) /= *(BOffptr + j1);
    };

    break;

    case 2 :
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = AOffptr + i2; Bp1 = BOffptr + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) /= *(Bp1 + j1);
    }
    };
    break;

    case 3 :
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = AOffptr + i3; Bp2 = BOffptr + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2     + i2; Bp1 = Bp2     + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) /= *(Bp1 + j1);
    }
    }};
    break;

    case 4 :
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = AOffptr + i4; Bp3 = BOffptr + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) /= *(Bp1 + j1);
    }
    }}};
    break;

    case 5 :
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = AOffptr + i5; Bp4 = BOffptr + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) /= *(Bp1 + j1);
    }
    }}}};
    break;

    case 6 :
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = AOffptr+ i6; Bp5 = BOffptr + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) /= *(Bp1 + j1);
    }
    }}}}};
    break;

    case 7 :
    for(i7=0, j7 = 0; i7 < ACount[6]*AStride[6]; i7+=AStride[6], j7+=BStride[6])
    { Ap6 = AOffptr + i7; Bp6 = BOffptr + j7;
    for(i6=0, j6 = 0; i6 < ACount[5]*AStride[5]; i6+=AStride[5], j6+=BStride[5])
    { Ap5 = Ap6 + i6; Bp5 = Bp6 + j6;
    for(i5=0, j5 = 0; i5 < ACount[4]*AStride[4]; i5+=AStride[4], j5+=BStride[4])
    { Ap4 = Ap5 + i5; Bp4 = Bp5 + j5;
    for(i4=0, j4 = 0; i4 < ACount[3]*AStride[3]; i4+=AStride[3], j4+=BStride[3])
    { Ap3 = Ap4 + i4; Bp3 = Bp4 + j4;
    for(i3=0, j3 = 0; i3 < ACount[2]*AStride[2]; i3+=AStride[2], j3+=BStride[2])
    { Ap2 = Ap3 + i3; Bp2 = Bp3 + j3;
    for(i2=0, j2 = 0; i2 < ACount[1]*AStride[1]; i2+=AStride[1], j2+=BStride[1])
    { Ap1 = Ap2 + i2; Bp1 = Bp2 + j2;
    for(i1=0, j1 = 0; i1 < ACount[0]*AStride[0]; i1+=AStride[0], j1+=BStride[0])
    {
    *(Ap1 + i1) /= *(Bp1 + j1);
    }
    }}}}}};
    break;

    }
}
}




void  CAMbinaryEngine::doubleCequalAplusB(const CAMstructureBase &Astructure, const CAMdataHandler &Adata,
const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata,
CAMstructureBase &Cstructure, CAMdataHandler &Cdata)
{
    CAMbinaryEngine::doubleAequalToB(Cstructure, Cdata, Astructure, Adata);
    CAMbinaryEngine::doubleAplusEqualB(Cstructure, Cdata, Bstructure, Bdata);
}

void  CAMbinaryEngine::doubleCequalAminusB(const CAMstructureBase &Astructure, const CAMdataHandler &Adata,
const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata,
CAMstructureBase &Cstructure, CAMdataHandler &Cdata)
{
    CAMbinaryEngine::doubleAequalToB(Cstructure, Cdata, Astructure, Adata);
    CAMbinaryEngine::doubleAminusEqualB(Cstructure, Cdata, Bstructure, Bdata);
}

void  CAMbinaryEngine::doubleCequalAtimesB(const CAMstructureBase &Astructure, const CAMdataHandler &Adata,
const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata,
CAMstructureBase &Cstructure, CAMdataHandler &Cdata)
{
    CAMbinaryEngine::doubleAequalToB(Cstructure, Cdata, Astructure, Adata);
    CAMbinaryEngine::doubleAtimesEqualB(Cstructure, Cdata, Bstructure, Bdata);
}

void  CAMbinaryEngine::doubleCequalAdivideB(const CAMstructureBase &Astructure, const CAMdataHandler &Adata,
const CAMstructureBase &Bstructure, const CAMdataHandler &Bdata,
CAMstructureBase &Cstructure, CAMdataHandler &Cdata)
{
    CAMbinaryEngine::doubleAequalToB(Cstructure, Cdata, Astructure, Adata);
    CAMbinaryEngine::doubleAdivideEqualB(Cstructure, Cdata, Bstructure, Bdata);
}

  

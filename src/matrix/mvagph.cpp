//
//******************************************************************************
//                    MVAGPH.CPP
//******************************************************************************
//
#include "mvagph.h"
#include "math.h"
#include "string.h"
#define CAM_PI  3.14159265359
//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 1997
//                       8/1/97
//
// ->Fixed transposed problem 1/2/98 CRA
//******************************************************************************
//
CAMmvaGraphics::CAMmvaGraphics() : CAMgraphicsProcess() {}
//
//******************************************************************************
//******************************************************************************
// Graphics Bindings for CAMvectorBase
//******************************************************************************
//******************************************************************************
//
void CAMmvaGraphics::plot(const CAMvectorBase& V)
{
   int p_arg   = 0;
   int p_style = 0;
   int callType = 0;
    vectorBasePlot(V,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMvectorBase& V, int p_arg)
{
   int p_style = 0;
   int callType = 1;
    vectorBasePlot(V,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMvectorBase& V, int p_arg, int p_style)
{
   int callType = 2;
    vectorBasePlot(V,callType, p_arg, p_style);
}

void CAMmvaGraphics::vectorBasePlot(const CAMvectorBase& V, int callType, int p_arg, int p_style)
{
//
//  Need Conversion Check
//
//
// extract data from vector
//
    long M;
    CAMvectorBase A;
    double* AdataPtr;

    if(V.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(V);
    AdataPtr    = (double*)A.getDataPointer();
    M = A.getIndexCount();
    }
    else
    {
    AdataPtr  = (double*)(V.getDataPointer());
    M = V.getIndexCount();
    }
//
// get reference to the graphics base class
//
   CAMgraphicsProcess& G = *this;
//
// plot
//
   switch(callType)
   {
    case 0 : G.plot(AdataPtr,M); break;
   case 1 : G.plot(AdataPtr,M,p_arg); break;
   case 2 : G.plot(AdataPtr,M,p_arg,p_style); break;
   }
}

void CAMmvaGraphics::plot(const CAMvectorBase& Vx, const CAMvectorBase& Vy)
{
   int p_arg   = 0;
   int p_style = 0;
   int callType = 0;
    vectorBasePlot(Vx,Vy,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMvectorBase& Vx, const CAMvectorBase& Vy, int p_arg)
{
   int p_style = 0;
   int callType = 1;
    vectorBasePlot(Vx,Vy,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMvectorBase& Vx, const CAMvectorBase& Vy, int p_arg, int p_style)
{
   int callType = 2;
    vectorBasePlot(Vx,Vy,callType, p_arg, p_style);
}

void CAMmvaGraphics::vectorBasePlot(const CAMvectorBase& Vx, const CAMvectorBase& Vy,
int callType, int p_arg, int p_style)
{
//
//  Need Conversion Check
//
    long M;

    CAMvectorBase A;
    double* AdataPtr;

    CAMvectorBase O;
    double* OdataPtr;
    long    Ocount;

    if(Vx.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(Vx);
    AdataPtr    = (double*)A.getDataPointer();
    M = A.getIndexCount();
    }
    else
    {
    AdataPtr  = (double*)Vx.getDataPointer();
    M = Vx.getIndexCount();
    }

    if(Vy.Structure.isSubset() == 1)
    {
    O.initializeMinDuplicate(Vy);
    OdataPtr    = (double*)O.getDataPointer();
    Ocount      = O.getIndexCount();
    }
    else
    {
    OdataPtr    = (double*)Vy.getDataPointer();
    Ocount      = Vy.getIndexCount();
    }

    if(M != Ocount)
    {CAMmvaGraphics::ordinateError(Vy.Structure);}
//
// get reference to the graphics base class
//
   CAMgraphicsProcess& G = *this;
//
// plot
//
   switch(callType)
   {
    case 0 : G.plot(AdataPtr,OdataPtr,M); break;
   case 1 : G.plot(AdataPtr,OdataPtr,M,p_arg); break;
   case 2 : G.plot(AdataPtr,OdataPtr,M,p_arg,p_style); break;
   }

}

//
//******************************************************************************
//******************************************************************************
// Graphics Bindings for CAMarrayBase
//******************************************************************************
//******************************************************************************
//

//
//******************************************************************************
//******************************************************************************
//                                  PLOT
//******************************************************************************
//******************************************************************************
//

void CAMmvaGraphics::plot(const CAMarrayBase& V)
{
   int p_arg   = 0;
   int p_style = 0;
   int callType = 0;
    arrayBasePlot(V,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMarrayBase& V, int p_arg)
{
   int p_style = 0;
   int callType = 1;
    arrayBasePlot(V,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMarrayBase& V, int p_arg, int p_style)
{
   int callType = 2;
    arrayBasePlot(V,callType, p_arg, p_style);
}

void CAMmvaGraphics::arrayBasePlot(const CAMarrayBase& V, int callType,
int p_arg, int p_style)
{
//
//  Need Conversion Check
//
//
// extract data from vector
//
    long M;
    CAMarrayBase A;
    double* AdataPtr;

   long dimension;

    if(V.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(V);
   dimension  = A.getDimension();
    AdataPtr    = (double*)A.getDataPointer();
    M = A[1].getIndexCount();
    }
    else
    {
   dimension  = V.getDimension();
    AdataPtr  = (double*)(V.getDataPointer());
    M = V[1].getIndexCount();
    }

   if(dimension != 1) return;
//
// get reference to the graphics base class
//
   CAMgraphicsProcess& G = *this;
//
// plot
//
   switch(callType)
   {
    case 0 : G.plot(AdataPtr,M); break;
   case 1 : G.plot(AdataPtr,M,p_arg); break;
   case 2 : G.plot(AdataPtr,M,p_arg,p_style); break;
   }
}

void CAMmvaGraphics::plot(const CAMarrayBase& Vx, const CAMarrayBase& Vy)
{
   int p_arg   = 0;
   int p_style = 0;
   int callType = 0;
    arrayBasePlot(Vx,Vy,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMarrayBase& Vx, const CAMarrayBase& Vy,
int p_arg)
{
   int p_style = 0;
   int callType = 1;
    arrayBasePlot(Vx,Vy,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMarrayBase& Vx, const CAMarrayBase& Vy,
int p_arg, int p_style)
{
   int callType = 2;
    arrayBasePlot(Vx,Vy,callType, p_arg, p_style);
}

void CAMmvaGraphics::arrayBasePlot(const CAMarrayBase& Vx, const CAMarrayBase& Vy,
int callType, int p_arg, int p_style)
{
//
//  Need Conversion Check
//
   long dimensionX;
   long dimensionY;

    long M;

    CAMarrayBase A;
    double* AdataPtr;

    CAMarrayBase O;
    double* OdataPtr;
    long    Ocount;

    if(Vx.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(Vx);
   dimensionX = A.getDimension();
    AdataPtr    = (double*)A.getDataPointer();
    M = A[1].getIndexCount();
    }
    else
    {
   dimensionX = Vx.getDimension();
    AdataPtr  = (double*)Vx.getDataPointer();
    M = Vx[1].getIndexCount();
    }

    if(Vy.Structure.isSubset() == 1)
    {
    O.initializeMinDuplicate(Vy);
   dimensionY = O.getDimension();
    OdataPtr    = (double*)O.getDataPointer();
    Ocount      = O[1].getIndexCount();
    }
    else
    {
   dimensionY  = Vy.getDimension();
    OdataPtr    = (double*)Vy.getDataPointer();
    Ocount      = Vy[1].getIndexCount();
    }

    if(M != Ocount)
    {CAMmvaGraphics::ordinateError(Vy.Structure);}

   
   if((dimensionX != 1)||(dimensionY != 1)) return;

//
// get reference to the graphics base class
//
   CAMgraphicsProcess& G = *this;
//
// plot
//
   switch(callType)
   {
    case 0 : G.plot(AdataPtr,OdataPtr,M); break;
   case 1 : G.plot(AdataPtr,OdataPtr,M,p_arg); break;
   case 2 : G.plot(AdataPtr,OdataPtr,M,p_arg,p_style); break;
   }

}
//
//******************************************************************************
//******************************************************************************
//                             CONTOUR
//******************************************************************************
//******************************************************************************
//
void CAMmvaGraphics::arrayBaseContour(const CAMarrayBase& V, int callType,
int nCntr, double cIncr, double lVal, double hVal, const CAMarrayBase* contourValues)
{
//
//  Need Conversion Check
//
//
// Unpack data
//
    long M;  long N;
    CAMarrayBase A;
    double* AdataPtr;

   long dimension;

    if(V.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(V);
   dimension  = A.getDimension();
    AdataPtr    = (double*)A.getDataPointer();
   if(dimension != 2) return;
    M = A[1].getIndexCount();
   N = A[2].getIndexCount();
    }
    else
    {
   dimension  = V.getDimension();
    AdataPtr  = (double*)(V.getDataPointer());
   if(dimension != 2) return;
    M = V[1].getIndexCount();
   N = V[2].getIndexCount();
    }
//
// Unpack contour values if required
//
   long Ncntr;
    CAMarrayBase cntrVal;
    double* cntrValDataPtr;

   if(contourValues != 0)
   {
    if((*contourValues).Structure.isSubset() == 1)
    {
    cntrVal.initializeMinDuplicate(V);
    cntrValDataPtr    = (double*)cntrVal.getDataPointer();
    Ncntr = cntrVal[1].getIndexCount();
    }
    else
    {
    cntrValDataPtr  = (double*)((*contourValues).getDataPointer());
    Ncntr = (*contourValues)[1].getIndexCount();
    }
   }
//
// get reference to the graphics base class
//
//
// Contour Plot
//
    double* Cdata = new double[M*N];
    long i; long j;
    for(i = 0; i < M; i++)
    {
    for(j = 0; j < N; j++)
    {
    *(Cdata + j + i*N) = *(AdataPtr + i + j*M);
    }}
    CAMgraphicsProcess& G = *this;
   switch(callType)
    {
    case 0 : G.contour(Cdata,M,N); break;
    case 1 : G.contour(Cdata,M,N,nCntr); break;
    case 2 : G.contour(Cdata,M,N,cIncr); break;
    case 3 : G.contour(Cdata,M,N,lVal,hVal); break;
    case 4 : G.contour(Cdata,M,N,nCntr,lVal,hVal); break;
    case 5 : G.contour(Cdata,M,N,cIncr,lVal,hVal); break;
    case 6 : G.contour(Cdata,M,N,cntrValDataPtr,Ncntr); break;
    }
    delete [] Cdata;
}

void  CAMmvaGraphics::contour(const CAMarrayBase& V)
{
 int callType                = 0;
 int nCntr                   = 0;
 double cIncr                = 0.0;
 double lVal                 = 0.0;
 double hVal                 = 0.0;
 CAMarrayBase* contourValues = 0;

 arrayBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);

}
void  CAMmvaGraphics::contour(const CAMarrayBase& V, int    nContour)
{
 int callType                = 1;
 int nCntr                   = nContour;
 double cIncr                = 0.0;
 double lVal                 = 0.0;
 double hVal                 = 0.0;
 CAMarrayBase* contourValues = 0;

 arrayBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);

}

void  CAMmvaGraphics::contour(const CAMarrayBase& V, long   nContour)
{
 int callType                = 1;
 int nCntr                   = (int)nContour;
 double cIncr                = 0.0;
 double lVal                 = 0.0;
 double hVal                 = 0.0;
 CAMarrayBase* contourValues = 0;

 arrayBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);
}

void  CAMmvaGraphics::contour(const CAMarrayBase& V, double increment)
{
 int callType                = 2;
 int nCntr                   = 0;
 double cIncr                = increment;
 double lVal                 = 0.0;
 double hVal                 = 0.0;
 CAMarrayBase* contourValues = 0;

 arrayBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);
}

void  CAMmvaGraphics::contour(const CAMarrayBase& V, double low_value,
double high_value)
{
 int callType                = 3;
 int nCntr                   = 0;
 double cIncr                = 0.0;
 double lVal                 = low_value;
 double hVal                 = high_value;
 CAMarrayBase* contourValues = 0;

 arrayBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);


}
void  CAMmvaGraphics::contour(const CAMarrayBase& V, int nContour,
double low_value, double high_value)
{
 int callType                = 4;
 int nCntr                   = nContour;
 double cIncr                = 0.0;
 double lVal                 = low_value;
 double hVal                 = high_value;
 CAMarrayBase* contourValues = 0;

 arrayBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);

}
void  CAMmvaGraphics::contour(const CAMarrayBase& V, long nContour,
double low_value, double high_value)
{

 int callType                = 4;
 int nCntr                   = (int)nContour;
 double cIncr                = 0.0;
 double lVal                 = low_value;
 double hVal                 = high_value;
 CAMarrayBase* contourValues = 0;

 arrayBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);
}
void  CAMmvaGraphics::contour(const CAMarrayBase& V, double increment,
double low_value, double high_value)
{
 int callType                = 5;
 int nCntr                   = 0;
 double cIncr                = increment;
 double lVal                 = low_value;
 double hVal                 = high_value;
 CAMarrayBase* contourValues = 0;

 arrayBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);
}

void  CAMmvaGraphics::contour(const CAMarrayBase& V, const CAMarrayBase& cValues)
{
 int callType                = 6;
 int nCntr                   = 0;
 double cIncr                = 0.0;
 double lVal                 = 0.0;
 double hVal                 = 0.0;
 const CAMarrayBase* contourValues = &cValues;

 arrayBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);
}
//
//******************************************************************************
//******************************************************************************
//                             SURFACE
//******************************************************************************
//******************************************************************************
//
void CAMmvaGraphics::arrayBaseSurface(const CAMarrayBase& V, int callType,
const CAMarrayBase* x, const CAMarrayBase* y)
{
//
//  Need Conversion Check
//
//
// Unpack data
//
    long M;  long N;
    CAMarrayBase A;
    double* AdataPtr;

   long dimension;

    if(V.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(V);
   dimension  = A.getDimension();
    AdataPtr    = (double*)A.getDataPointer();
   if(dimension != 2) return;
    M = A[1].getIndexCount();
   N = A[2].getIndexCount();
    }
    else
    {
   dimension  = V.getDimension();
    AdataPtr  = (double*)(V.getDataPointer());
   if(dimension != 2) return;
    M = V[1].getIndexCount();
   N = V[2].getIndexCount();
    }
//
// Unpack axis values if required
//
   long Nx; long Ny;
    CAMarrayBase xB;
   CAMarrayBase yB;
    double* xBDataPtr;
   double* yBDataPtr;

   if((x != 0)&&(y != 0))
   {

    if((*x).Structure.isSubset() == 1)
    {
    xB.initializeMinDuplicate(*x);
    xBDataPtr    = (double*)xB.getDataPointer();
    Nx = xB[1].getIndexCount();
    }
    else
    {
    xBDataPtr  = (double*)((*x).getDataPointer());
    Nx = (*x)[1].getIndexCount();
    }

   if((*y).Structure.isSubset() == 1)
    {
    yB.initializeMinDuplicate(*y);
    yBDataPtr    = (double*)yB.getDataPointer();
    Ny = yB[1].getIndexCount();
    }
    else
    {
    yBDataPtr  = (double*)((*y).getDataPointer());
    Ny = (*y)[1].getIndexCount();
    }

   if(M != Nx)
    {CAMmvaGraphics::ordinateError(x->Structure);}

    if(N != Ny)
    {CAMmvaGraphics::ordinateError(y->Structure);}


    }

    double* Cdata = new double[M*N];
    long i; long j;
    for(i = 0; i < M; i++)
    {
    for(j = 0; j < N; j++)
    {
    *(Cdata + j + i*N) = *(AdataPtr + i + j*M);
    }}

    CAMgraphicsProcess& G = *this;
   switch(callType)
    {
    case 0 : G.surface(Cdata,M,N); break;
    case 1 : G.surface(Cdata,M,N,xBDataPtr, yBDataPtr); break;
    }
    delete [] Cdata;
}

void  CAMmvaGraphics::surface(const CAMarrayBase& V)
{
  int callType     = 0;
  CAMarrayBase* xP = 0;
  CAMarrayBase* yP = 0;
  arrayBaseSurface(V, callType, xP, yP);
}
void  CAMmvaGraphics::surface(const CAMarrayBase& V,const CAMarrayBase& x,
const CAMarrayBase& y)
{
  int callType     = 1;
  const CAMarrayBase* xP = &x;
  const CAMarrayBase* yP = &y;
  arrayBaseSurface(V, callType, xP, yP);
}





//
//******************************************************************************
//******************************************************************************
// Graphics Bindings for CAMmatrixBase
//******************************************************************************
//******************************************************************************
//

//
//******************************************************************************
//******************************************************************************
//                                  PLOT
//******************************************************************************
//******************************************************************************
//

void CAMmvaGraphics::plot(const CAMmatrixBase& V)
{
   int p_arg   = 0;
   int p_style = 0;
   int callType = 0;
    matrixBasePlot(V,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMmatrixBase& V, int p_arg)
{
   int p_style = 0;
   int callType = 1;
    matrixBasePlot(V,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMmatrixBase& V, int p_arg, int p_style)
{
   int callType = 2;
    matrixBasePlot(V,callType, p_arg, p_style);
}

void CAMmvaGraphics::matrixBasePlot(const CAMmatrixBase& V, int callType,
int p_arg, int p_style)
{
//
//  Need Conversion Check
//
//
// extract data from vector
//
    long M;
    CAMmatrixBase A;
    double* AdataPtr;

   long dimension;

    if(V.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(V);
   dimension  = A.getDimension();
    AdataPtr    = (double*)A.getDataPointer();
    M = A[1].getIndexCount();
    }
    else
    {
   dimension  = V.getDimension();
    AdataPtr  = (double*)(V.getDataPointer());
    M = V[1].getIndexCount();
    }

   if(dimension != 1) return;
//
// get reference to the graphics base class
//
   CAMgraphicsProcess& G = *this;
//
// plot
//
   switch(callType)
   {
    case 0 : G.plot(AdataPtr,M); break;
   case 1 : G.plot(AdataPtr,M,p_arg); break;
   case 2 : G.plot(AdataPtr,M,p_arg,p_style); break;
   }
}

void CAMmvaGraphics::plot(const CAMmatrixBase& Vx, const CAMmatrixBase& Vy)
{
   int p_arg   = 0;
   int p_style = 0;
   int callType = 0;
    matrixBasePlot(Vx,Vy,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMmatrixBase& Vx, const CAMmatrixBase& Vy,
int p_arg)
{
   int p_style = 0;
   int callType = 1;
    matrixBasePlot(Vx,Vy,callType, p_arg, p_style);
}

void CAMmvaGraphics::plot(const CAMmatrixBase& Vx, const CAMmatrixBase& Vy,
int p_arg, int p_style)
{
   int callType = 2;
    matrixBasePlot(Vx,Vy,callType, p_arg, p_style);
}

void CAMmvaGraphics::matrixBasePlot(const CAMmatrixBase& Vx, const CAMmatrixBase& Vy,
int callType, int p_arg, int p_style)
{
//
//  Need Conversion Check
//
   long dimensionX;
   long dimensionY;

    long M;

    CAMmatrixBase A;
    double* AdataPtr;

    CAMmatrixBase O;
    double* OdataPtr;
    long    Ocount;

    if(Vx.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(Vx);
   dimensionX = A.getDimension();
    AdataPtr    = (double*)A.getDataPointer();
    M = A[1].getIndexCount();
    }
    else
    {
   dimensionX = Vx.getDimension();
    AdataPtr  = (double*)Vx.getDataPointer();
    M = Vx[1].getIndexCount();
    }

    if(Vy.Structure.isSubset() == 1)
    {
    O.initializeMinDuplicate(Vy);
   dimensionY = O.getDimension();
    OdataPtr    = (double*)O.getDataPointer();
    Ocount      = O[1].getIndexCount();
    }
    else
    {
   dimensionY  = Vy.getDimension();
    OdataPtr    = (double*)Vy.getDataPointer();
    Ocount      = Vy[1].getIndexCount();
    }

    if(M != Ocount)
    {CAMmvaGraphics::ordinateError(Vy.Structure);}

   
   if((dimensionX != 1)||(dimensionY != 1)) return;

//
// get reference to the graphics base class
//
   CAMgraphicsProcess& G = *this;
//
// plot
//
   switch(callType)
   {
    case 0 : G.plot(AdataPtr,OdataPtr,M); break;
   case 1 : G.plot(AdataPtr,OdataPtr,M,p_arg); break;
   case 2 : G.plot(AdataPtr,OdataPtr,M,p_arg,p_style); break;
   }

}
//
//******************************************************************************
//******************************************************************************
//                             CONTOUR
//******************************************************************************
//******************************************************************************
//
void CAMmvaGraphics::matrixBaseContour(const CAMmatrixBase& V, int callType,
int nCntr, double cIncr, double lVal, double hVal, const CAMmatrixBase* contourValues)
{
//
//  Need Conversion Check
//
//
// Unpack data (transfrom to doubleArray so I can use _ notation)
//
    long M;  long N;
   double* AdataPtr;

    CAMdoubleMatrix B = V;
   CAMdoubleMatrix A = V;

    M = A[1].getIndexCount();
   N = A[2].getIndexCount();

   long i;
   for(i = 1; i <= M; i++)
   {A(i,_) = B(M - (i-1),_);}

   AdataPtr = A.getDataPointer();
//
// Repack the data so that the (1,1) element is the upper left; not the
// lower left
//

//
// Unpack contour values if required
//
   long Ncntr;
    CAMmatrixBase cntrVal;
    double* cntrValDataPtr;

   if(contourValues != 0)
   {
    if((*contourValues).Structure.isSubset() == 1)
    {
    cntrVal.initializeMinDuplicate(V);
    cntrValDataPtr    = (double*)cntrVal.getDataPointer();
    Ncntr = cntrVal[1].getIndexCount();
    }
    else
    {
    cntrValDataPtr  = (double*)((*contourValues).getDataPointer());
    Ncntr = (*contourValues)[1].getIndexCount();
    }
   }
//
// get reference to the graphics base class
//
//
// Contour Plot
//
   CAMgraphicsProcess& G = *this;
   switch(callType)
   {
    case 0 : G.contour(AdataPtr,N,M); break;
   case 1 : G.contour(AdataPtr,N,M,nCntr); break;
   case 2 : G.contour(AdataPtr,N,M,cIncr); break;
   case 3 : G.contour(AdataPtr,N,M,lVal,hVal); break;
   case 4 : G.contour(AdataPtr,N,M,nCntr,lVal,hVal); break;
   case 5 : G.contour(AdataPtr,N,M,cIncr,lVal,hVal); break;
   case 6 : G.contour(AdataPtr,N,M,cntrValDataPtr,Ncntr); break;
   }

}

void  CAMmvaGraphics::contour(const CAMmatrixBase& V)
{
 int callType                = 0;
 int nCntr                   = 0;
 double cIncr                = 0.0;
 double lVal                 = 0.0;
 double hVal                 = 0.0;
 CAMmatrixBase* contourValues = 0;

 matrixBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);

}
void  CAMmvaGraphics::contour(const CAMmatrixBase& V, int    nContour)
{
 int callType                = 1;
 int nCntr                   = nContour;
 double cIncr                = 0.0;
 double lVal                 = 0.0;
 double hVal                 = 0.0;
 CAMmatrixBase* contourValues = 0;

 matrixBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);

}

void  CAMmvaGraphics::contour(const CAMmatrixBase& V, long   nContour)
{
 int callType                = 1;
 int nCntr                   = (int)nContour;
 double cIncr                = 0.0;
 double lVal                 = 0.0;
 double hVal                 = 0.0;
 CAMmatrixBase* contourValues = 0;

 matrixBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);
}

void  CAMmvaGraphics::contour(const CAMmatrixBase& V, double increment)
{
 int callType                = 2;
 int nCntr                   = 0;
 double cIncr                = increment;
 double lVal                 = 0.0;
 double hVal                 = 0.0;
 CAMmatrixBase* contourValues = 0;

 matrixBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);
}

void  CAMmvaGraphics::contour(const CAMmatrixBase& V, double low_value,
double high_value)
{
 int callType                = 3;
 int nCntr                   = 0;
 double cIncr                = 0.0;
 double lVal                 = low_value;
 double hVal                 = high_value;
 CAMmatrixBase* contourValues = 0;

 matrixBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);


}
void  CAMmvaGraphics::contour(const CAMmatrixBase& V, int nContour,
double low_value, double high_value)
{
 int callType                = 4;
 int nCntr                   = nContour;
 double cIncr                = 0.0;
 double lVal                 = low_value;
 double hVal                 = high_value;
 CAMmatrixBase* contourValues = 0;

 matrixBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);

}
void  CAMmvaGraphics::contour(const CAMmatrixBase& V, long nContour,
double low_value, double high_value)
{

 int callType                = 4;
 int nCntr                   = (int)nContour;
 double cIncr                = 0.0;
 double lVal                 = low_value;
 double hVal                 = high_value;
 CAMmatrixBase* contourValues = 0;

 matrixBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);
}
void  CAMmvaGraphics::contour(const CAMmatrixBase& V, double increment,
double low_value, double high_value)
{
 int callType                = 5;
 int nCntr                   = 0;
 double cIncr                = increment;
 double lVal                 = low_value;
 double hVal                 = high_value;
 CAMmatrixBase* contourValues = 0;

 matrixBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);
}

void  CAMmvaGraphics::contour(const CAMmatrixBase& V, const CAMmatrixBase& cValues)
{
 int callType                = 6;
 int nCntr                   = 0;
 double cIncr                = 0.0;
 double lVal                 = 0.0;
 double hVal                 = 0.0;
 const CAMmatrixBase* contourValues = &cValues;

 matrixBaseContour(V, callType, nCntr, cIncr, lVal, hVal, contourValues);
}
//
//******************************************************************************
//******************************************************************************
//                             SURFACE
//******************************************************************************
//******************************************************************************
//
void CAMmvaGraphics::matrixBaseSurface(const CAMmatrixBase& V, int callType,
const CAMmatrixBase* x, const CAMmatrixBase* y)
{
//
//  Need Conversion Check
//
//
// Unpack data
//
    long M;  long N;
    CAMmatrixBase A;
    double* AdataPtr;

   long dimension;

    if(V.Structure.isSubset() == 1)
    {
    A.initializeMinDuplicate(V);
   dimension  = A.getDimension();
    AdataPtr    = (double*)A.getDataPointer();
   if(dimension != 2) return;
    M = A[1].getIndexCount();
   N = A[2].getIndexCount();
    }
    else
    {
   dimension  = V.getDimension();
    AdataPtr  = (double*)(V.getDataPointer());
   if(dimension != 2) return;
    M = V[1].getIndexCount();
   N = V[2].getIndexCount();
    }
//
// Unpack axis values if required
//
   long Nx; long Ny;
    CAMmatrixBase xB;
   CAMmatrixBase yB;
    double* xBDataPtr;
   double* yBDataPtr;

   if((x != 0)&&(y != 0))
   {

    if((*x).Structure.isSubset() == 1)
    {
    xB.initializeMinDuplicate(*x);
    xBDataPtr    = (double*)xB.getDataPointer();
    Nx = xB[1].getIndexCount();
    }
    else
    {
    xBDataPtr  = (double*)((*x).getDataPointer());
    Nx = (*x)[1].getIndexCount();
    }

   if((*y).Structure.isSubset() == 1)
    {
    yB.initializeMinDuplicate(*y);
    yBDataPtr    = (double*)yB.getDataPointer();
    Ny = yB[1].getIndexCount();
    }
    else
    {
    yBDataPtr  = (double*)((*y).getDataPointer());
    Ny = (*y)[1].getIndexCount();
    }

   if(M != Nx)
    {CAMmvaGraphics::ordinateError(x->Structure);}

    if(N != Ny)
    {CAMmvaGraphics::ordinateError(y->Structure);}


   }
//
// get reference to the graphics base class
//
//
// Contour Plot
//
   CAMgraphicsProcess& G = *this;
   switch(callType)
   {
    case 0 : G.surface(AdataPtr,N,M); break;
    case 1 : G.surface(AdataPtr,N,M,xBDataPtr, yBDataPtr); break;
   }
}

void  CAMmvaGraphics::surface(const CAMmatrixBase& V)
{
  int callType     = 0;
  CAMmatrixBase* xP = 0;
  CAMmatrixBase* yP = 0;
  matrixBaseSurface(V, callType, xP, yP);
}
void  CAMmvaGraphics::surface(const CAMmatrixBase& V,const CAMmatrixBase& x,
const CAMmatrixBase& y)
{
  int callType     = 1;
  const CAMmatrixBase* xP = &x;
  const CAMmatrixBase* yP = &y;
  matrixBaseSurface(V, callType, xP, yP);
}

void CAMmvaGraphics::ordinateError(const CAMstructureBase & A)
{
    long i;
   cerr << endl;
    cerr << "    Ordinates in Plot Command Incorrectly Specified " << endl << endl;
    cerr << " Error in Number of Ordinates or Ordinate Array Dimension  " << endl;
    cerr << " Ordinates Size :     ";
    cerr << A[1].getIndexCount();
    for(i = 2; i <= A.dataDimension; i++)
    cerr <<  " x " << A[i].getIndexCount() ;
    cerr << endl << endl;
    CAMmvaExit();
}









  

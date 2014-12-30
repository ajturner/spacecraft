//
//******************************************************************************
//                   MVAGPH.H
//******************************************************************************
//
#include "cammva.h"
#include "gprocess.h"
#include "mvaimpexp.h"
//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 1997
//                       8/1/97
//
//
//******************************************************************************
//

#ifndef __CAM_MVA_GRAPHICS__
#define __CAM_MVA_GRAPHICS__
class __IMPEXP__ CAMmvaGraphics : public CAMgraphicsProcess
{
public :

   CAMmvaGraphics();
//
// Routines for CAMdoubleVector
//
   void plot(const CAMvectorBase& V);
   void plot(const CAMvectorBase& V, int p_arg);
   void plot(const CAMvectorBase& V, int p_arg, int p_style);

   void plot(const CAMvectorBase& Vx, const CAMvectorBase& Vy);
   void plot(const CAMvectorBase& Vx, const CAMvectorBase& Vy, int p_arg);
   void plot(const CAMvectorBase& Vx, const CAMvectorBase& Vy, int p_arg, int p_style);
//
// CAMdoubleArray
//
   void plot(const CAMarrayBase& V);
   void plot(const CAMarrayBase& V, int p_arg);
   void plot(const CAMarrayBase& V, int p_arg, int p_style);

   void plot(const CAMarrayBase& Vx, const CAMarrayBase& Vy);
   void plot(const CAMarrayBase& Vx, const CAMarrayBase& Vy, int p_arg);
   void plot(const CAMarrayBase& Vx, const CAMarrayBase& Vy, int p_arg, int p_style);

   void  contour(const CAMarrayBase& V);
   void  contour(const CAMarrayBase& V, int    nContour);
   void  contour(const CAMarrayBase& V, long   nContour) ;
   void  contour(const CAMarrayBase& V, double increment);
   void  contour(const CAMarrayBase& V, double low_value, double high_value);
   void  contour(const CAMarrayBase& V, int nContour, double low_value, double high_value);
   void  contour(const CAMarrayBase& V, long nContour, double low_value, double high_value);
   void  contour(const CAMarrayBase& V, double increment, double low_value, double high_value);
   void  contour(const CAMarrayBase& V, const CAMarrayBase& contourValues);

   void  surface(const CAMarrayBase& V);
   void  surface(const CAMarrayBase& V,const CAMarrayBase& x, const CAMarrayBase& y);
//
// Routines for CAMdoubleMatrix
//
   void plot(const CAMmatrixBase& V);
   void plot(const CAMmatrixBase& V, int p_arg);
   void plot(const CAMmatrixBase& V, int p_arg, int p_style);

   void plot(const CAMmatrixBase& Vx, const CAMmatrixBase& Vy);
   void plot(const CAMmatrixBase& Vx, const CAMmatrixBase& Vy, int p_arg);
   void plot(const CAMmatrixBase& Vx, const CAMmatrixBase& Vy, int p_arg, int p_style);

   void  contour(const CAMmatrixBase& V);
   void  contour(const CAMmatrixBase& V, int    nContour);
   void  contour(const CAMmatrixBase& V, long   nContour) ;
   void  contour(const CAMmatrixBase& V, double increment);
   void  contour(const CAMmatrixBase& V, double low_value, double high_value);
   void  contour(const CAMmatrixBase& V, int nContour, double low_value, double high_value);
   void  contour(const CAMmatrixBase& V, long nContour, double low_value, double high_value);
   void  contour(const CAMmatrixBase& V, double increment, double low_value, double high_value);
   void  contour(const CAMmatrixBase& V, const CAMmatrixBase& contourValues);

   void  surface(const CAMmatrixBase& V);
   void  surface(const CAMmatrixBase& V,const CAMmatrixBase& x, const CAMmatrixBase& y);


private :

    void vectorBasePlot(const CAMvectorBase& V, int callType, int p_arg, int p_style);
   void vectorBasePlot(const CAMvectorBase& Vx, const CAMvectorBase& Vy, int callType, int p_arg, int p_style);

   void arrayBasePlot(const CAMarrayBase& V, int callType, int p_arg, int p_style);
   void arrayBasePlot(const CAMarrayBase& Vx, const CAMarrayBase& Vy, int callType, int p_arg, int p_style);
   void arrayBaseContour(const CAMarrayBase& V, int callType, int nCntr, double cIncr,
   double lVal, double hVal, const CAMarrayBase* contourValues);
   void arrayBaseSurface(const CAMarrayBase& V, int callType, const CAMarrayBase* x,
   const CAMarrayBase* y);


   void matrixBasePlot(const CAMmatrixBase& V, int callType, int p_arg, int p_style);
   void matrixBasePlot(const CAMmatrixBase& Vx, const CAMmatrixBase& Vy, int callType, int p_arg, int p_style);
   void matrixBaseContour(const CAMmatrixBase& V, int callType, int nCntr, double cIncr,
   double lVal, double hVal, const CAMmatrixBase* contourValues);
   void matrixBaseSurface(const CAMmatrixBase& V, int callType, const CAMmatrixBase* x,
   const CAMmatrixBase* y);

   void ordinateError(const CAMstructureBase & A);

};
#endif
  

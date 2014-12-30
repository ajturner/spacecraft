//
//  Prototypes for BLAS Routines and Selected External Routines
//
#ifndef __FORTRAN_CALLS__
//
// 
//
#include "blasimpexp.h"

extern "C" __IMPEXP__ int icopy_(long* n, int* ix, long* incx, int* iy, long* incy);
extern "C" __IMPEXP__ int lcopy_(long* n, long* ix, long* incx, long* iy, long* incy);
extern "C" __IMPEXP__ int scopy_(long* n, float* ix, long* incx, float* iy, long* incy);
extern "C" __IMPEXP__ int iscal_(long* n, int* ia, int* ix, long* incx);
extern "C" __IMPEXP__ int lscal_(long* n, long* la, long* ix, long* incx);
extern "C" __IMPEXP__ int sscal_(long* n, float* sa, float* ix, long* incx);
extern "C" __IMPEXP__ int iaxpy_(long* n, int* ia, int* ix, long* incx, int* iy, long* incy);
extern "C" __IMPEXP__ int laxpy_(long* n, long* la, long* ix, long* incx, long* iy, long* incy);
extern "C" __IMPEXP__ int saxpy_(long* n, float* sa, float* ix, long* incx, float* iy, long* incy);
//
// Double versions translated from Fortran to C using f2c translation
//
extern "C" int  __IMPEXP__ dcopy_(long* n, double* ix, long* incx, double* iy, long* incy);
extern "C" int  __IMPEXP__ dscal_(long* n, double* da, double* ix, long* incx);
extern "C" int  __IMPEXP__ daxpy_(long* n, double* da, double* ix, long* incx, double* iy, long* incy);
//
// Matrix routines (f2c translations of Linpack routines)
//
extern  "C"  double dnrm2_(long* n, double* dx, long* incx);

extern  "C"    int dgemm_(char* transa, char* transb, long* m, long* n, long* k,
                          double* alpha, double* a, long* lda, double* b, long* ldb,
                          double* beta, double* c, long* ldc, short f1, short f2);

extern  "C"    int dgesvx_(char* fact, char* trans, long* n, long* nrhs,
                           double* a, long* lda, double* af, long* ldaf, long* ipiv,
                           char* equed, double* r, double* c, double* b, long* ldb,
                           double* x, long* ldx, double* rcond, double* ferr, double* berr,
                           double*  work, long*  iwork,  long* info,
                           short fact_len, short trans_len, short equed_len);
#endif

  

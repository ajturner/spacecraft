#include "blas.h"
//
// C++ implementations of level 1 Blas --- selectively replaced by
// other implementations at link time
//
int icopy_(long* n, int* ix, long* incx, int* iy, long* incy)
{
    register int* ixp;
    register int* iyp;
    register long i;
    for(i = 1, ixp = ix, iyp = iy; i <= *n; i++, ixp+=(*incx), iyp+=(*incy))
    *iyp = *ixp;

    return 0;
}
int  lcopy_(long* n, long* ix, long* incx, long* iy, long* incy)
{
    register long* ixp;
    register long* iyp;
    register long i;
    for(i = 1, ixp = ix, iyp = iy; i <= *n;i++, ixp+=(*incx), iyp+=(*incy))
        *iyp = *ixp;
    return 0;
};
int  scopy_(long* n, float* ix, long* incx, float* iy, long* incy)
{
    register float* ixp;
    register float* iyp;
    register long i;
    for(i = 1, ixp = ix, iyp = iy; i <= *n;i++, ixp+=(*incx), iyp+=(*incy))
       *iyp = *ixp;
    return 0;
};



int iscal_(long* n, int* ia, int* ix, long* incx)
{
    register int* ixp;
    register int a = *ia;
    register long i;
    for(i = 1, ixp = ix; i <= *n; i++ , ixp+=(*incx))
    *ixp *= a;
    return 0;
}
int lscal_(long* n, long* la, long* ix, long* incx)
{
    register long* ixp;
    register long  a = *la;
    register long i;
    for(i = 1, ixp = ix; i <= *n; i++ , ixp+=(*incx))
    *ixp *= a;
    return 0;
};
int sscal_(long* n, float* sa, float* ix, long* incx)
{
    register float* ixp;
    register float a = *sa;
    register long i;
    for(i = 1, ixp = ix; i <= *n; i++ , ixp+=(*incx))
    *ixp *= a;
    return 0;
};


int iaxpy_(long* n, int* ia, int* ix, long* incx, int* iy, long* incy)
{
    register int* ixp;
    register int* iyp;
    register int a = *ia;
    register long i;
    for(i = 1, ixp = ix, iyp = iy; i  <= *n; i++, ixp+=(*incx), iyp+=(*incy))
    *iyp += a*(*ixp);
    return 0;
}
int laxpy_(long* n, long* la, long* ix, long* incx, long* iy, long* incy)
{
    register long* ixp;
    register long* iyp;
    register long a = *la;
    register long i;
    for(i = 1, ixp = ix, iyp = iy; i  <= *n; i++, ixp+=(*incx), iyp+=(*incy))
    *iyp += a*(*ixp);
    return 0;
};
int saxpy_(long* n, float* sa, float* ix, long* incx, float* iy, long* incy)
{
    register float* ixp;
    register float* iyp;
    register float a = *sa;
    register long i;
    for(i = 1, ixp = ix, iyp = iy; i  <= *n; i++, ixp+=(*incx), iyp+=(*incy))
        *iyp += a*(*ixp);
    return 0;
};

//
// The following have been replaced by ftc translations of LINPACK
// routines.
//
/*
extern "C" int dscal_(long* n, double* da, double* ix, long* incx)
{
    register double* ixp;
    register double a = *da;
    register long i;
    for(i = 1, ixp = ix; i <= *n; i++ , ixp+=(*incx))
    *ixp *= a;
};
*/

/*
extern "C"  int  dcopy_(long* n, double* ix, long* incx, double* iy, long* incy)
{

    register double* ixp;
    register double* iyp;
    register long i;
    for(i = 1, ixp = ix, iyp = iy; i <= *n; i++, ixp+=(*incx), iyp+=(*incy))
    *iyp = *ixp;

};
*/

/*
extern "C" int daxpy_(long* n, double* da, double* ix, long* incx, double* iy, long* incy)
{
    register double* ixp;
    register double* iyp;
    register double a = *da;
    register long i;
    for(i = 1, ixp = ix, iyp = iy; i  <= *n;i++, ixp+=(*incx), iyp+=(*incy))
        *iyp += a*(*ixp);
};
*/


  

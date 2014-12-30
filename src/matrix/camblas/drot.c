/* DROT.F -- translated by f2c (version 19941215).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"
#include "cblasimpexp.h"

/* DECK DROT */
/* Subroutine */ int __IMPEXP__ drot_(n, dx, incx, dy, incy, dc, ds)
integer *n;
doublereal *dx;
integer *incx;
doublereal *dy;
integer *incy;
doublereal *dc, *ds;
{
    /* Initialized data */

    static doublereal zero = 0.;
    static doublereal one = 1.;

    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer i;
    static doublereal w, z;
    static integer kx, ky, nsteps;

/* ***BEGIN PROLOGUE  DROT */
/* ***DATE WRITTEN   791001   (YYMMDD) */
/* ***REVISION DATE  861211   (YYMMDD) */
/* ***CATEGORY NO.  D1A8 */
/* ***KEYWORDS  LIBRARY=SLATEC(BLAS), */
/*             TYPE=DOUBLE PRECISION(SROT-S DROT-D CSROT-C), */
/*             GIVENS ROTATION,GIVENS TRANSFORMATION,LINEAR ALGEBRA, */
/*             PLANE ROTATION,VECTOR */
/* ***AUTHOR  LAWSON, C. L., (JPL) */
/*           HANSON, R. J., (SNLA) */
/*           KINCAID, D. R., (U. OF TEXAS) */
/*           KROGH, F. T., (JPL) */
/* ***PURPOSE  APPLY d.p. Givens rotation */
/* ***DESCRIPTION */

/*                B L A S  Subprogram */
/*    Description of Parameters */

/*     --Input-- */
/*        N  number of elements in input vector(s) */
/*       DX  double precision vector with N elements */
/*     INCX  storage spacing between elements of DX */
/*       DY  double precision vector with N elements */
/*     INCY  storage spacing between elements of DY */
/*       DC  D.P. element of rotation matrix */
/*       DS  D.P. element of rotation matrix */

/*     --Output-- */
/*       DX  rotated vector (unchanged if N .LE. 0) */
/*       DY  rotated vector (unchanged if N .LE. 0) */

/*     Multiply the 2 X 2 matrix  ( DC DS) times the 2 X N matrix (DX**T) 
*/
/*                                (-DS DC)                        (DY**T) 
*/
/*     where **T indicates transpose.  The elements of DX are in */
/*     DX(LX+I*INCX), I = 0 to N-1, where LX = 1 if INCX .GE. 0, else */
/*     LX = (-INCX)*N, and similarly for DY using LY and INCY. */
/* ***REFERENCES  LAWSON C.L., HANSON R.J., KINCAID D.R., KROGH F.T., */
/*                 *BASIC LINEAR ALGEBRA SUBPROGRAMS FOR FORTRAN USAGE*, 
*/
/*                 ALGORITHM NO. 539, TRANSACTIONS ON MATHEMATICAL */
/*                 SOFTWARE, VOLUME 5, NUMBER 3, SEPTEMBER 1979, 308-323 
*/
/* ***ROUTINES CALLED  (NONE) */
/* ***END PROLOGUE  DROT */

    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
/* ***FIRST EXECUTABLE STATEMENT  DROT */
    if (*n <= 0 || *ds == zero && *dc == one) {
	goto L40;
    }
    if (! (*incx == *incy && *incx > 0)) {
	goto L20;
    }

    nsteps = *incx * *n;
    i__1 = nsteps;
    i__2 = *incx;
    for (i = 1; i__2 < 0 ? i >= i__1 : i <= i__1; i += i__2) {
	w = dx[i];
	z = dy[i];
	dx[i] = *dc * w + *ds * z;
	dy[i] = -(*ds) * w + *dc * z;
/* L10: */
    }
    goto L40;

L20:
    kx = 1;
    ky = 1;

    if (*incx < 0) {
	kx = 1 - (*n - 1) * *incx;
    }
    if (*incy < 0) {
	ky = 1 - (*n - 1) * *incy;
    }

    i__2 = *n;
    for (i = 1; i <= i__2; ++i) {
	w = dx[kx];
	z = dy[ky];
	dx[kx] = *dc * w + *ds * z;
	dy[ky] = -(*ds) * w + *dc * z;
	kx += *incx;
	ky += *incy;
/* L30: */
    }
L40:

    return 0;
} /* drot_ */


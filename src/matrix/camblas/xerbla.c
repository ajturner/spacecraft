/* XERBLA.F -- translated by f2c (version 19941215).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"
#include "cblasimpexp.h"

/* Subroutine */ int __IMPEXP__ xerbla_(srname, info, srname_len)
char *srname;
integer *info;
ftnlen srname_len;
{
/*     ..    Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  XERBLA  is an error handler for the Level 2 BLAS routines. */

/*  It is called by the Level 2 BLAS routines if an input parameter is */
/*  invalid. */

/*  Installers should consider modifying the STOP statement in order to */
/*  call system-specific exception-handling facilities. */

/*  Parameters */
/*  ========== */

/*  SRNAME - CHARACTER*6. */
/*           On entry, SRNAME specifies the name of the routine which */
/*           called XERBLA. */

/*  INFO   - INTEGER. */
/*           On entry, INFO specifies the position of the invalid */
/*           parameter in the parameter-list of the calling routine. */


/*  Auxiliary routine for Level 2 Blas. */

/*  Written on 20-July-1986. */

/*     .. Executable Statements .. */

/*      WRITE (*,99999) SRNAME, INFO */

/*      STOP */


/*     End of XERBLA. */

/* L99999: */
} /* xerbla_ */


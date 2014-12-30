/* DGERFS.F -- translated by f2c (version 19941215).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b15 = -1.;
static doublereal c_b17 = 1.;

/* Subroutine */ int dgerfs_(trans, n, nrhs, a, lda, af, ldaf, ipiv, b, ldb, 
	x, ldx, ferr, berr, work, iwork, info, trans_len)
char *trans;
integer *n, *nrhs;
doublereal *a;
integer *lda;
doublereal *af;
integer *ldaf, *ipiv;
doublereal *b;
integer *ldb;
doublereal *x;
integer *ldx;
doublereal *ferr, *berr, *work;
integer *iwork, *info;
ftnlen trans_len;
{
    /* System generated locals */
    integer a_dim1, a_offset, af_dim1, af_offset, b_dim1, b_offset, x_dim1, 
	    x_offset, i__1, i__2, i__3;
    doublereal d__1, d__2, d__3;

    /* Local variables */
    static integer kase;
    static doublereal safe1, safe2;
    static integer i, j, k;
    static doublereal s;
    extern logical lsame_();
    extern /* Subroutine */ int dgemv_(), dcopy_(), daxpy_();
    static integer count;
    extern doublereal dlamch_();
    extern /* Subroutine */ int dlacon_();
    static doublereal xk;
    static integer nz;
    static doublereal safmin;
    extern /* Subroutine */ int xerbla_(), dgetrs_();
    static logical notran;
    static char transt[1];
    static doublereal lstres, eps;


/*  -- LAPACK routine (version 1.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd., */
/*     Courant Institute, Argonne National Lab, and Rice University */
/*     March 31, 1993 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGERFS improves the computed solution to a system of linear */
/*  equations and provides error bounds and backward error estimates for 
*/
/*  the solution. */

/*  Arguments */
/*  ========= */

/*  TRANS   (input) CHARACTER*1 */
/*          Specifies the form of the system of equations: */
/*          = 'N':  A * X = B     (No transpose) */
/*          = 'T':  A**T * X = B  (Transpose) */
/*          = 'C':  A**H * X = B  (Conjugate transpose = Transpose) */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  NRHS    (input) INTEGER */
/*          The number of right hand sides, i.e., the number of columns */
/*          of the matrices B and X.  NRHS >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The original N-by-N matrix A. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,N). */

/*  AF      (input) DOUBLE PRECISION array, dimension (LDAF,N) */
/*          The factors L and U from the factorization A = P*L*U */
/*          as computed by DGETRF. */

/*  LDAF    (input) INTEGER */
/*          The leading dimension of the array AF.  LDAF >= max(1,N). */

/*  IPIV    (input) INTEGER array, dimension (N) */
/*          The pivot indices from DGETRF; for 1<=i<=N, row i of the */
/*          matrix was interchanged with row IPIV(i). */

/*  B       (input) DOUBLE PRECISION array, dimension (LDB,NRHS) */
/*          The right hand side matrix B. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B.  LDB >= max(1,N). */

/*  X       (input/output) DOUBLE PRECISION array, dimension (LDX,NRHS) */
/*          On entry, the solution matrix X, as computed by DGETRS. */
/*          On exit, the improved solution matrix X. */

/*  LDX     (input) INTEGER */
/*          The leading dimension of the array X.  LDX >= max(1,N). */

/*  FERR    (output) DOUBLE PRECISION array, dimension (NRHS) */
/*          The estimated forward error bounds for each solution vector */
/*          X(j) (the j-th column of the solution matrix X). */
/*          If XTRUE is the true solution, FERR(j) bounds the magnitude */
/*          of the largest entry in (X(j) - XTRUE) divided by */
/*          the magnitude of the largest entry in X(j).  The quality of */
/*          the error bound depends on the quality of the estimate of */
/*          norm(inv(A)) computed in the code; if the estimate of */
/*          norm(inv(A)) is accurate, the error bound is guaranteed. */

/*  BERR    (output) DOUBLE PRECISION array, dimension (NRHS) */
/*          The componentwise relative backward error of each solution */
/*          vector X(j) (i.e., the smallest relative change in */
/*          any entry of A or B that makes X(j) an exact solution). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (3*N) */

/*  IWORK   (workspace) INTEGER array, dimension (N) */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  Internal Parameters */
/*  =================== */

/*  ITMAX is the maximum number of steps of iterative refinement. */

/*  ===================================================================== 
*/

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;
    af_dim1 = *ldaf;
    af_offset = af_dim1 + 1;
    af -= af_offset;
    --ipiv;
    b_dim1 = *ldb;
    b_offset = b_dim1 + 1;
    b -= b_offset;
    x_dim1 = *ldx;
    x_offset = x_dim1 + 1;
    x -= x_offset;
    --ferr;
    --berr;
    --work;
    --iwork;

    /* Function Body */
    *info = 0;
    notran = lsame_(trans, "N", 1L, 1L);
    if (! notran && ! lsame_(trans, "T", 1L, 1L) && ! lsame_(trans, "C", 1L, 
	    1L)) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*nrhs < 0) {
	*info = -3;
    } else if (*lda < max(1,*n)) {
	*info = -5;
    } else if (*ldaf < max(1,*n)) {
	*info = -7;
    } else if (*ldb < max(1,*n)) {
	*info = -10;
    } else if (*ldx < max(1,*n)) {
	*info = -12;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGERFS", &i__1, 6L);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *nrhs == 0) {
	i__1 = *nrhs;
	for (j = 1; j <= i__1; ++j) {
	    ferr[j] = 0.;
	    berr[j] = 0.;
/* L10: */
	}
	return 0;
    }

    if (notran) {
	*(unsigned char *)transt = 'T';
    } else {
	*(unsigned char *)transt = 'N';
    }

/*     NZ = maximum number of nonzero entries in each row of A, plus 1 */

    nz = *n + 1;
    eps = dlamch_("Epsilon", 7L);
    safmin = dlamch_("Safe minimum", 12L);
    safe1 = nz * safmin;
    safe2 = safe1 / eps;

/*     Do for each right hand side */

    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {

	count = 1;
	lstres = 3.;
L20:

/*        Loop until stopping criterion is satisfied. */

/*        Compute residual R = B - op(A) * X, */
/*        where op(A) = A, A**T, or A**H, depending on TRANS. */

	dcopy_(n, &b[j * b_dim1 + 1], &c__1, &work[*n + 1], &c__1);
	dgemv_(trans, n, n, &c_b15, &a[a_offset], lda, &x[j * x_dim1 + 1], &
		c__1, &c_b17, &work[*n + 1], &c__1, 1L);

/*        Compute componentwise relative backward error from formula 
*/

/*        max(i) ( abs(R(i)) / ( abs(op(A))*abs(X) + abs(B) )(i) ) */

/*        where abs(Z) is the componentwise absolute value of the matr
ix */
/*        or vector Z.  If the i-th component of the denominator is le
ss */
/*        than SAFE2, then SAFE1 is added to the i-th components of th
e */
/*        numerator and denominator before dividing. */

	i__2 = *n;
	for (i = 1; i <= i__2; ++i) {
	    work[i] = (d__1 = b[i + j * b_dim1], abs(d__1));
/* L30: */
	}

/*        Compute abs(op(A))*abs(X) + abs(B). */

	if (notran) {
	    i__2 = *n;
	    for (k = 1; k <= i__2; ++k) {
		xk = (d__1 = x[k + j * x_dim1], abs(d__1));
		i__3 = *n;
		for (i = 1; i <= i__3; ++i) {
		    work[i] += (d__1 = a[i + k * a_dim1], abs(d__1)) * xk;
/* L40: */
		}
/* L50: */
	    }
	} else {
	    i__2 = *n;
	    for (k = 1; k <= i__2; ++k) {
		s = 0.;
		i__3 = *n;
		for (i = 1; i <= i__3; ++i) {
		    s += (d__1 = a[i + k * a_dim1], abs(d__1)) * (d__2 = x[i 
			    + j * x_dim1], abs(d__2));
/* L60: */
		}
		work[k] += s;
/* L70: */
	    }
	}
	s = 0.;
	i__2 = *n;
	for (i = 1; i <= i__2; ++i) {
	    if (work[i] > safe2) {
/* Computing MAX */
		d__2 = s, d__3 = (d__1 = work[*n + i], abs(d__1)) / work[i];
		s = max(d__2,d__3);
	    } else {
/* Computing MAX */
		d__2 = s, d__3 = ((d__1 = work[*n + i], abs(d__1)) + safe1) / 
			(work[i] + safe1);
		s = max(d__2,d__3);
	    }
/* L80: */
	}
	berr[j] = s;

/*        Test stopping criterion. Continue iterating if */
/*           1) The residual BERR(J) is larger than machine epsilon, a
nd */
/*           2) BERR(J) decreased by at least a factor of 2 during the
 */
/*              last iteration, and */
/*           3) At most ITMAX iterations tried. */

	if (berr[j] > eps && berr[j] * 2. <= lstres && count <= 5) {

/*           Update solution and try again. */

	    dgetrs_(trans, n, &c__1, &af[af_offset], ldaf, &ipiv[1], &work[*n 
		    + 1], n, info, 1L);
	    daxpy_(n, &c_b17, &work[*n + 1], &c__1, &x[j * x_dim1 + 1], &c__1)
		    ;
	    lstres = berr[j];
	    ++count;
	    goto L20;
	}

/*        Bound error from formula */

/*        norm(X - XTRUE) / norm(X) .le. FERR = */
/*        norm( abs(inv(op(A)))* */
/*           ( abs(R) + NZ*EPS*( abs(op(A))*abs(X)+abs(B) ))) / norm(X
) */

/*        where */
/*          norm(Z) is the magnitude of the largest component of Z */
/*          inv(op(A)) is the inverse of op(A) */
/*          abs(Z) is the componentwise absolute value of the matrix o
r */
/*             vector Z */
/*          NZ is the maximum number of nonzeros in any row of A, plus
 1 */
/*          EPS is machine epsilon */

/*        The i-th component of abs(R)+NZ*EPS*(abs(op(A))*abs(X)+abs(B
)) */
/*        is incremented by SAFE1 if the i-th component of */
/*        abs(op(A))*abs(X) + abs(B) is less than SAFE2. */

/*        Use DLACON to estimate the infinity-norm of the matrix */
/*           inv(op(A)) * diag(W), */
/*        where W = abs(R) + NZ*EPS*( abs(op(A))*abs(X)+abs(B) ))) */

	i__2 = *n;
	for (i = 1; i <= i__2; ++i) {
	    if (work[i] > safe2) {
		work[i] = (d__1 = work[*n + i], abs(d__1)) + nz * eps * work[
			i];
	    } else {
		work[i] = (d__1 = work[*n + i], abs(d__1)) + nz * eps * work[
			i] + safe1;
	    }
/* L90: */
	}

	kase = 0;
L100:
	dlacon_(n, &work[(*n << 1) + 1], &work[*n + 1], &iwork[1], &ferr[j], &
		kase);
	if (kase != 0) {
	    if (kase == 1) {

/*              Multiply by diag(W)*inv(op(A)**T). */

		dgetrs_(transt, n, &c__1, &af[af_offset], ldaf, &ipiv[1], &
			work[*n + 1], n, info, 1L);
		i__2 = *n;
		for (i = 1; i <= i__2; ++i) {
		    work[*n + i] = work[i] * work[*n + i];
/* L110: */
		}
	    } else {

/*              Multiply by inv(op(A))*diag(W). */

		i__2 = *n;
		for (i = 1; i <= i__2; ++i) {
		    work[*n + i] = work[i] * work[*n + i];
/* L120: */
		}
		dgetrs_(trans, n, &c__1, &af[af_offset], ldaf, &ipiv[1], &
			work[*n + 1], n, info, 1L);
	    }
	    goto L100;
	}

/*        Normalize error. */

	lstres = 0.;
	i__2 = *n;
	for (i = 1; i <= i__2; ++i) {
/* Computing MAX */
	    d__2 = lstres, d__3 = (d__1 = x[i + j * x_dim1], abs(d__1));
	    lstres = max(d__2,d__3);
/* L130: */
	}
	if (lstres != 0.) {
	    ferr[j] /= lstres;
	}

/* L140: */
    }

    return 0;

/*     End of DGERFS */

} /* dgerfs_ */


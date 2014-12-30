#include "cammva.h"
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//
//######################################################################
//
//  CAMmva Test Program #3
//
//  This program demonstrates the use of sub-matrix and sub-vector access,
//  and index range access, by implementing a naive Gaussian elimination routine
//  and a Gaussian elimination routine with partial pivoting.
//
//  Chris Andersion (C) UCLA 1997
//######################################################################
//
int main()
{

    long N = 5;

    CAMdoubleMatrix M(N,N);
    CAMdoubleVector B(N);
    CAMdoubleVector X(N);

//
//  Initialize a test matrix and right hand side
//
    long i,j;
    for(i=1; i<= N; i++)
    for(j=1; j<= N; j++)
    {
     M(i,j)=1.0/(double(i) + double(j));
    }
    
    for(i=1; i<=N; i++)
    {
     B(i)=double(i);
    }

    cout << " Test Matrix " << endl;
    cout << M << endl;
    cout << " Test Right Hand Side " << endl;
    cout << B << endl;
//
//  Standard Gaussian Elimination (without pivoting)
//
    CAMdoubleMatrix A(N,N+1);
    CAMdoubleMatrix Z(1,N+1);

    A(_(1,N),_(1,N))   =M;
    A(_,N+1)           =B;

    for(j=1;   j<=N-1; j++)
    {
    for(i=j+1; i<=N; i++)
    {
    A(i,_) = A(i,_) - (A(i,j)/A(j,j))*A(j,_);
    }}
//
//   Back Solve
//
    X(N) = A(N,N+1)/A(N,N);

    for(i=N-1; i>= 1; i--)
    {
    X(i) = A(i,N+1)/A(i,i);
    for(j=i+1; j<= N; j++)
    {
    X(i) = X(i) -(A(i,j)/A(i,i))*X(j);
    }}

    cout << "Residual with standard Gaussian elimination " << endl;
    cout << M*X - B << endl;

//
//  Partial Pivoting
//

    A(1,_(1,N))        = M(3,_);
    A(2,_(1,N))        = M(2,_);
    A(3,_(1,N))        = M(1,_);
    A(1,N+1)           = B(3);
    A(2,N+1)           = B(2);
    A(3,N+1)           = B(1);

    CAMdoubleMatrix TMP(1,N+1);

    double pmax;
    long   imax;

    for(j=1;   j<=N-1; j++)
    {

    pmax = fabs(A(j,j));
    imax = j;
    for(i = j+1; i <=N; i++)
    {
    if(fabs(A(i,j)) > pmax){pmax = A(i,j); imax = i;}
    }
    TMP = A(j,_);
    A(j,_) = A(imax,_);
    A(imax,_) = TMP;

    for(i=j+1; i<=N; i++)
    {
    A(i,_) = A(i,_) - (A(i,j)/A(j,j))*A(j,_);
    }}
//
//   Back Solve
//
    X(N) = A(N,N+1)/A(N,N);

    for(i=N-1; i>= 1; i--)
    {
    X(i) = A(i,N+1)/A(i,i);
    for(j=i+1; j<= N; j++)
    {
    X(i) = X(i) -(A(i,j)/A(i,i))*X(j);
    }}

    cout << "Residual with Gaussian elimination and pivoting " << endl;
    cout << M*X - B << endl;


    cout << M/B - X << endl;

    cout << M*(M/B) - B << endl;

    cout << " Program End : Hit Any Key to Terminate " << endl;
    getchar();
    return 0;
}

  

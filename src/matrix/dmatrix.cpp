//
//                    DMATRIX.CPP
//
//          Chris Anderson (C) UCLA 1995
//
#include "dmatrix.h" 

CAMdoubleMatrix CAMdoubleMatrix::identity(long n)
{
    CAMdoubleMatrix I(n,n);
    for(long i = 1; i <= n; i++)
    I(i,i) = 1.0;
    I.setTemporaryFlag();
    return I;
}


  

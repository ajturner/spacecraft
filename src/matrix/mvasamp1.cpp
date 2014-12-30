#include "cammva.h"
#include <stdio.h>
#include <iostream.h>
//
//######################################################################
//
// CAMmva Test Program #1
//
// This program sets up a and solves a linear system of equations.
//
//
// Chris Anderson (C) UCLA 1997
//######################################################################
//
int main(){

  CAMdoubleMatrix A(3,3);           // declare a matrix
  CAMdoubleVector b(3);             // declare vectors
  CAMdoubleVector x(3);  
  CAMdoubleVector residual(3);              
    
  long i,j;                         // variables for loop index
    
    
  for(i=1; i<= 3; i++)              // nested do-loop for initializing
  for(j=1; j<= 3; j++)              // the matrix A.
  {
    A(i,j)=1.0/(double(i) + double(j)); 
  }
    
  for(i=1; i<=3; i++)               // initialize b
  {
    b(i)=double(i);
  }
    
  x=A/b;                            // solve the system A*x=b for x
  residual=A*x - b;                 // compute the residual
    
                                    // set scientific notation output 
                                    // format

  cout.setf(ios::scientific, ios::floatfield); 

  cout << " The matrix A " << endl;
  cout << A;
  cout << " The vector b " << endl;
  cout << b;
  cout << " The solution of A*x=b " << endl;
  cout << x;
  cout << " The residual " << endl;
  cout << residual;

  cout << " Program End : Hit Any Key to Terminate " << endl;
  getchar();
  return 0;
}

  

#include "cammva.h"
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
//
//######################################################################
//
// CAMmva Test Program #2
//
// This program demonstrates file input/output by constructing a matrix and
// a vector, writing it to a file, and then reading it back in. The program
// then solves the linear system represented by the matrix and the vector.
//
// Chris Andersion (C) UCLA 1997
//######################################################################
//
int main(){

  CAMdoubleMatrix A(3,3);            // declare a matrix
  CAMdoubleMatrix M(3,3);
  CAMdoubleVector b(3);              // declare vectors
  CAMdoubleVector rhs(3);
  CAMdoubleVector x(3);
  CAMdoubleVector residual(3);
//
//   Open a file and write out a matrix and a right hand side
//
  ofstream OutFile;                  // declare an output file stream
  OutFile.open("Test.dat",ios::out);   //

  long i,j;                         // variables for loop index
    
    
  for(i=1; i<= 3; i++)              // nested do-loop for initializing
  for(j=1; j<= 3; j++)              // the matrix M.
  {
    M(i,j)=1.0/(double(i) + double(j));
  }
    
  for(i=1; i<=3; i++)               // initialize rhs
  {
    rhs(i)=double(i);
  }
  OutFile << M;
  OutFile << rhs;
  OutFile.close();
//
// Open file and read back in the matrix and solve the system
//
  ifstream InFile;                   // declare an input file stream    
    
                                     // connect the file stream with                                     
  InFile.open("Test.dat",ios::in);   // the external file tinput
  if (!InFile ) 
  {cerr <<  " Error in Opening input File "; exit(1); }
    
  InFile >> A;                       // read in the matrix A
  InFile >> b;                       // read in the vector b

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

  

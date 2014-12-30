//
//######################################################################
//            CAMrange Sample Program  #1
//
// Chris Andersion (C) UCLA 1997                                8/18/97
//######################################################################
//
/*
   This program demonstrates the use of CAMrange constructors and member
   functions. 
*/
#include "access.h"
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   cout << "CAMrange Object _(1,3) : " << _(1,3)  << endl;
   cout << endl;

   CAMrange R(-1,1);

   cout << "CAMrange Object R   : " << R   << endl;
   cout << "CAMrange Object R+2 : " << R+2 << endl;
   cout << "CAMrange Object R-2 : " << R-2 << endl;
   cout << "CAMrange Object R++ : " << R++ << endl;
   cout << "CAMrange Object R-- : " << R-- << endl;
   cout << "R.getCount()        = " << R.getCount() << endl;
   cout << "R.length()          = " << R.length()   << endl;

   cout << endl;

   R.initialize(-2,2,2);
   cout << "R.initialize(-2,2,2) : " << R  << endl;
   cout << "CAMrange Object R    : " << R   << endl;
   cout << "CAMrange Object R-2  : " << R-2 << endl;
   cout << "CAMrange Object R++  : " << R++ << endl;
   cout << "CAMrange Object R--  : " << R-- << endl;
   cout << "R.getCount()         = " << R.getCount() << endl;
   cout << "R.length()           = " << R.length()   << endl;

   cout << " Program End : Hit Any Key to Terminate " << endl;
   getchar();
   return 0;
}
  

#include "cammva.h"
#include "mvagph.h"
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x,double y)
{
return (3*(1-x)*(1-x)*(exp(-x*x - (y+1)*(y+1)))
          -10*(x/5 - x*x*x - y*y*y*y*y)*(exp(-x*x - y*y))
          -(1/3.0)*(exp(-(x+1)*(x+1) - y*y)));

};

int main()
{

	long N = 5;
	CAMdoubleVector B(N);
    CAMdoubleVector X(N);

    CAMmvaGraphics      Mgraphics;            // set up for mva graphics process
	CAMpostScriptDriver PSdriver("graph.ps"); // set up output driver
	Mgraphics.attachDriver(PSdriver);         // attach driver
//
// Initialize a test matrix and right hand side
//
   long i;  long j;
   for(i=1; i<=N; i++)
   {
    B(i)=double(i);
    X(i)=double(i)*.25;
   }
   B(3) = -1;

/*

   Mgraphics.plot(B);
   Mgraphics.frame();
   Mgraphics.plot(B,'G');
   Mgraphics.frame();
   Mgraphics.plot(B,'H',CAMgraphicsProcess::CURVE_AND_POINTS);
   Mgraphics.frame();
   Mgraphics.plot(X,B);
   Mgraphics.frame();
   Mgraphics.plot(X,B,'G');
   Mgraphics.frame();
   Mgraphics.plot(X,B,'H',CAMgraphicsProcess::CURVE_AND_POINTS);
   Mgraphics.frame();

*/

   long m; long n;

   m = 10;
   n = 40;
   CAMdoubleArray A(m,n);
   CAMdoubleArray XP(n);
   for(i= 1; i <= m; i++)
   {
   for(j = 1; j <=n; j++)
   {
     A(i,j) = cos(double(i)*3.14159*2.0*double(j-1)*(1.0)/double(n-1));
   }}

   for(j = 1; j <= n; j++)
   {
     XP(j) = double(j-1)/double(n-1);
   }

   /*
   Mgraphics.plot(A(1,_));
   Mgraphics.frame();
   Mgraphics.plot(A(2,_),CAMgraphicsProcess::CURVE_AND_POINTS);
   Mgraphics.frame();
   Mgraphics.plot(A(3,_),'+');
   Mgraphics.frame();

   Mgraphics.plot(XP,A(1,_));
   Mgraphics.frame();
   Mgraphics.plot(XP,A(2,_),CAMgraphicsProcess::CURVE_AND_POINTS);
   Mgraphics.frame();
   Mgraphics.plot(XP,A(3,_),'+');
   Mgraphics.frame();
   */

    m = 30;
    n = 30;

    CAMdoubleMatrix C(m,n);

    double a  = -3.0;                     // create data for contour plot
    double b  =  3.0;
    double c  = -3.0;
    double d =   3.0;


    double hx  = (b-a)/double(m-1);
    double hy  = (d-c)/double(n-1);

    for(i =1; i <= m; i++)
    {
    for(j =1; j <=n; j++)
    {
    C(i,j) = f(a + double(i-1)*hx, c + double(j-1)*hy);
    C(i,j) = 0.0;
    }}

    C(5,5)   = 1.0;
    C(n-3,n-3) = 1.0;

    Mgraphics.contour(C);
    Mgraphics.frame();
/*
    Mgraphics.contour(C,10);
    Mgraphics.frame();
    Mgraphics.contour(C,.1);
    Mgraphics.frame();
    Mgraphics.contour(C,0.0,1.0);
    Mgraphics.frame();
    Mgraphics.contour(C,10,0.0,1.0);
    Mgraphics.frame();
    Mgraphics.contour(C,XP);
*/
    Mgraphics.surface(C);
    Mgraphics.frame();


   cout << " Program End : Hit Any Key to Terminate " << endl;
   getchar();
   return 0;
}

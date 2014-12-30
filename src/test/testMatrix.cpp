//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file testDynamics.cpp
*  \brief Test program for trying out rigid body dynamics.
*  \author $Author: simpliciter $
*  \version $Revision: 1.3 $
*  \date    $Date: 2003/06/17 19:53:18 $
//////////////////////////////////////////////////////////////////////////////////////////////////
*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include "Matrix.h"
using namespace O_SESSAME;

int main()
{
    Matrix MOI = eye(3);
	cout << "Initialization Finished." << endl;
	
	cout << MOI << endl;

	Matrix I(3,3);
	cout << I << endl;
    return 0;
}

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: testMatrix.cpp,v $
*	Revision 1.3  2003/06/17 19:53:18  simpliciter
*	Added namespace call.
*	
*	Revision 1.2  2003/04/23 16:30:59  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/03/25 02:26:00  nilspace
*	initial submission of test files.
*
******************************************************************************/

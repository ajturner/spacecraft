//******************************************************************************
//                    MVAEXIT.CPP
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1997
//            7/31/97
//
//
//********************************************************************************
//
#include "mvaexit.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "iostream.h"
#ifndef __BCPLUSPLUS__
void CAMmvaExit()
{
    cerr << " Fatal Error : Program Stopped " << endl;
    exit(1);
};
void CAMmvaExit(char* ErrorMessage)
{
    cerr << ErrorMessage << endl << endl << endl;
    cerr << " Fatal Error " << endl;
    exit(1);
};
#else
void CAMmvaExit()
{
    cerr << endl << endl;
    cerr << "Hit return to Exit " << endl << endl;
    getchar();
    throw CAMmvaException("Error In CAM mvametric entity Classes");
};
void CAMmvaExit(char* ErrorMessage)
{
     throw CAMmvaException(ErrorMessage);
};
CAMmvaException::CAMmvaException()
{
    errorMessage = new char[1];
    errorMessage[0] = '\0';
}
CAMmvaException::CAMmvaException(char* Emessage)
{
    errorMessage = new char[strlen(Emessage) + 1];
    strcpy(errorMessage, Emessage);
}
CAMmvaException::CAMmvaException(const CAMmvaException& C)
{
    errorMessage = new char[strlen(C.errorMessage) + 1];
    strcpy(errorMessage, C.errorMessage);
}
CAMmvaException::~CAMmvaException()
{
    delete [] errorMessage;
}
#endif

  

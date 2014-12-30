//******************************************************************************
//                    MVAEXIT.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1997
//            7/30/97
//
//
//********************************************************************************
//
#ifndef __CAMMVAEXIT__
#define __CAMMVAEXIT__

#include "mvaimpexp.h"

void __IMPEXP__ CAMmvaExit();
void __IMPEXP__ CAMmvaExit(char* ErrorMessage);

#ifdef __BCPLUSPLUS__

class __IMPEXP__ CAMmvaException
{
    public :

    CAMmvaException();
    CAMmvaException(const CAMmvaException& C);
    CAMmvaException(char* msg);
    ~CAMmvaException();
    
    char* getMessage() const {return errorMessage;};

    private :

    char* errorMessage;
};
#endif
#endif

  

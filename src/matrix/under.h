//
//******************************************************************************
//                    UNDER.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Mon Sep 25 11:52:15 1995
//
//********************************************************************************
//

#include "range.h"


#ifndef __CAMUNDERSCORE__
#define __CAMUNDERSCORE__

#include "mvaimpexp.h" 

class __IMPEXP__  CAMunderscore
{

public :

//
//  Constructors
//
    CAMunderscore();
//
//  destructor
//
      ~CAMunderscore();
//
//  Public Member Functions
//
    CAMrange      operator()(long inputSize);
    CAMrange      operator()(long inputBase, long inputBound);
    CAMrange      operator()(long inputBase, long inputBound, long inputStride);

};
#endif
//
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//


  

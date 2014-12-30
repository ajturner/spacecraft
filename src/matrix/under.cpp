#include "under.h"
//
//******************************************************************************
//                    UNDER.CPP
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Fri Sep 01 17:52:03 1995
//
//********************************************************************************
//
// Defintion of _ as an instance of the CAMunderscore class
//
//CAMunderscore __IMPEXP__  _;
//
//  Constructors
//
CAMunderscore::CAMunderscore(){};
//
//  destructor
//
CAMunderscore::~CAMunderscore(){};
//
//  Public Member Functions
//
CAMrange    CAMunderscore::operator()(long inputSize)
            {return CAMrange(inputSize);};
CAMrange      CAMunderscore::operator()(long inputBase, long inputBound)
            {return CAMrange(inputBase, inputBound);};
CAMrange      CAMunderscore::operator()(long inputBase, long inputBound, long inputStride)
            {return CAMrange(inputBase, inputBound, inputStride);};
//
//
//********************************************************************************
//                     CPP File End
//********************************************************************************
//


  

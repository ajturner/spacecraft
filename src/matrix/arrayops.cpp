#include "arraybse.h"
#include "bnengine.h"
//
//******************************************************************************
//                    ARRAYOPS.CPP
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson
//
//            Mon Sep 11 12:49:20 1995
//
void  CAMarrayBase::initializeReturnArgument(const CAMarrayBase& A)
{
	A.Structure.initializeMinStructure(Structure);
	DataP = new CAMdataHandler(Structure.getFullDataCount(),A.DataP->getDataType());
	DataP->setReferenceCount(1);
}
//
//********************************************************************************
//                    Operator +
//********************************************************************************
//
CAMarrayBase CAMarrayBase::operator+(const CAMarrayBase& A) const
{
	if(Structure.isConformingTo(A.Structure) != 1)
	{CAMarrayBase::nonConformingMessage(Structure,A.Structure);}

	CAMarrayBase S;
	S.initializeReturnArgument(A);

	CAMbinaryEngine::doubleCequalAplusB(Structure, *DataP, A.Structure, *A.DataP,
	S.Structure, *S.DataP);

	S.setTemporaryFlag();
    return S;
}

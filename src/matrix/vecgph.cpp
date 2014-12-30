#include "vecbse.h"
//
//******************************************************************************
//                    VECGPH.CPP
//******************************************************************************
//
//        BINDINGS TO THE UC GRAHPICS CLASSES
//
//********************************************************************************
//
//            Chris Anderson  (C) UCLA
//
//            Tue Sep 26 14:40:00 1995
//
//********************************************************************************
//

//
// Graphics Bindings
//
void  CAMvectorBase::plot() const
{
//
//  Need Conversion Check
//
	long M;

	CAMvectorBase A;
	double* AdataPtr;

	if(Structure.isSubset() == 1)
	{
	A.initializeMinDuplicate(*this);
	AdataPtr    = (double*)A.getDataPointer();
	M = A.getIndexCount();
	}
	else
	{
	AdataPtr  = (double*)getDataPointer();
	M = getIndexCount();
	}

	CAMgraphics::plot(AdataPtr,M);
}

void  CAMvectorBase::plot(int p_arg) const
{
	char point_type_save = CAMgraphics::getPointType();
	int  plot_style_save = CAMgraphics::getPlotStyle();
    if(p_arg < 32) 
	{ CAMgraphics::setPlotStyle(p_arg);}
    else
	{ CAMgraphics::setPointType(char(p_arg));
	  CAMgraphics::setPlotStyle(CAMgraphics::POINTS);
	}

	this->plot();

	CAMgraphics::setPointType(point_type_save);
	CAMgraphics::setPlotStyle(plot_style_save);
}
void  CAMvectorBase::plot(int p_style, int p_arg) const
{
	char point_type_save = CAMgraphics::getPointType();
	int  plot_style_save = CAMgraphics::getPlotStyle();
	CAMgraphics::setPointType(char(p_arg));
	CAMgraphics::setPlotStyle(p_style);

	this->plot();

	CAMgraphics::setPointType(point_type_save);
	CAMgraphics::setPlotStyle(plot_style_save);
}


void  CAMvectorBase::plot(const CAMvectorBase& Ordinates) const
{
//
//  Need Conversion Check
//
	long M;

	CAMvectorBase A;
	double* AdataPtr;

	CAMvectorBase O;
	double* OdataPtr;
	long    Ocount;

	if(Structure.isSubset() == 1)
	{
	A.initializeMinDuplicate(*this);
	AdataPtr    = (double*)A.getDataPointer();
	M = A.getIndexCount();
	}
	else
	{
	AdataPtr  = (double*)getDataPointer();
	M = getIndexCount();
	}

	if(Ordinates.Structure.isSubset() == 1)
	{
	O.initializeMinDuplicate(Ordinates);
	OdataPtr    = (double*)O.getDataPointer();
	Ocount      = O.getIndexCount();
	}
	else
	{
	OdataPtr    = (double*)Ordinates.getDataPointer();
	Ocount      = Ordinates.getIndexCount();
	}

	if(M != Ocount)
	{CAMvectorBase::ordinateError(Ordinates.Structure);}

	CAMgraphics::plot(OdataPtr,AdataPtr,M);
}
void  CAMvectorBase::plot(const CAMvectorBase& Ordinates, int p_arg) const
{
	char point_type_save = CAMgraphics::getPointType();
	int  plot_style_save = CAMgraphics::getPlotStyle();
    if(p_arg < 32) 
	{ CAMgraphics::setPlotStyle(p_arg);}
    else
	{ CAMgraphics::setPointType(char(p_arg));
	  CAMgraphics::setPlotStyle(CAMgraphics::POINTS);
	}

	this->plot(Ordinates);

	CAMgraphics::setPointType(point_type_save);
	CAMgraphics::setPlotStyle(plot_style_save);
}

void  CAMvectorBase::plot(const CAMvectorBase& Ordinates, int p_arg, int p_style) const
{
	char point_type_save = CAMgraphics::getPointType();
	int  plot_style_save = CAMgraphics::getPlotStyle();
	CAMgraphics::setPointType(char(p_arg));
	CAMgraphics::setPlotStyle(p_style);

	this->plot(Ordinates);

	CAMgraphics::setPointType(point_type_save);
	CAMgraphics::setPlotStyle(plot_style_save);
}

void CAMvectorBase::ordinateError(const CAMstructureBase & A) 
{
	long i;
    cerr << endl;
	cerr << "    Ordinates in Plot Command Incorrectly Specified " << endl << endl;
	cerr << " Error in Number of Ordinates or Ordinate Array Dimension  " << endl;
	cerr << " Ordinates Size : 	";
	cerr << A[1].getIndexCount();
	for(i = 2; i <= A.dataDimension; i++)
	cerr <<  " x " << A[i].getIndexCount() ;
	cerr << endl << endl;
	CAMmvaExit();
}
void CAMvectorBase::plotDimensionError(const CAMstructureBase& A)
{
	long i;
    cerr << endl;
	cerr << "Error :  Object Dimensions not Compatable with Plot Operation " << endl << endl;
	cerr << "    Operand Dimensions :   ";
	cerr << A[1].getIndexCount();
	for(i = 2; i <= A.dataDimension; i++)
	cerr <<  " x " << A[i].getIndexCount() ;
	cerr << endl << endl;
	CAMmvaExit();
}
//
//********************************************************************************
//                     CPP File End 
//********************************************************************************
//

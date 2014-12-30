#include "arraybse.h"
//
//******************************************************************************
//                    ARRAYGPH.CPP
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

void  CAMarrayBase::plot() const
{
//
//  Need Conversion Check
//
	long dimension;
	long M,N;

	const CAMarrayBase* InputPtr;
	CAMarrayBase A;

	double* AdataPtr; double* BdataPtr;

	long j; int autoFlag;
	double x_min, x_max, y_min, y_max;

	if(Structure.isSubset() == 1)
	{
	A.initializeMinDuplicate(*this);
	dimension   = A.getDimension();
	AdataPtr    = (double*)A.getDataPointer();
	if(dimension >= 1) M = A[1].getIndexCount();
	if(dimension == 2) N = A[2].getIndexCount();
	InputPtr = &A;
	}
	else
	{
	dimension = getDimension();
	AdataPtr  = (double*)getDataPointer();
	if(dimension >= 1) M = Structure[1].getIndexCount();
	if(dimension == 2) N = Structure[2].getIndexCount();
	InputPtr =  this;
	}

	switch (dimension)
	{
	case 1  :
	CAMgraphics::plot(AdataPtr,M);

	break;

	case 2  :
	autoFlag = CAMgraphics::getAutoScaleFlag();
	x_min = 1;
	x_max = M;
	y_min = InputPtr->min();
	y_max = InputPtr->max();
	CAMgraphics::axis(x_min,x_max,y_min,y_max);
	for(j = 1; j <= N; j++)
	{
	BdataPtr = AdataPtr + (j-1)*M;
	CAMgraphics::plot(BdataPtr,M);
	}
	CAMgraphics::axis(autoFlag);

	break;
	default :
	CAMarrayBase::plotDimensionError(A.Structure);
	}

}

void  CAMarrayBase::plot(int p_arg) const
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
void  CAMarrayBase::plot(int p_style, int p_arg) const
{
	char point_type_save = CAMgraphics::getPointType();
	int  plot_style_save = CAMgraphics::getPlotStyle();
	CAMgraphics::setPointType(char(p_arg));
	CAMgraphics::setPlotStyle(p_style);

	this->plot();

	CAMgraphics::setPointType(point_type_save);
	CAMgraphics::setPlotStyle(plot_style_save);
}
void  CAMarrayBase::plot(const CAMarrayBase& Ordinates) const
{
//
//  Need Conversion Check
//
	long dimension;
	long M,N;

	CAMarrayBase A;
	const CAMarrayBase* InputPtr;
	double* AdataPtr; double* BdataPtr;

	long j; int autoFlag;
	double x_min, x_max, y_min, y_max;

	CAMarrayBase O;
    double* OdataPtr;
	long    Odimension;
	long    Ocount;
//
	if(Structure.isSubset() == 1)
	{
	A.initializeMinDuplicate(*this);
	dimension   = A.getDimension();
	AdataPtr    = (double*)A.getDataPointer();
	if(dimension >= 1) M = A[1].getIndexCount();
	if(dimension == 2) N = A[2].getIndexCount();
	InputPtr = &A;
	}
	else
	{
	dimension = getDimension();
	AdataPtr  = (double*)getDataPointer();
	if(dimension >= 1) M = Structure[1].getIndexCount();
	if(dimension == 2) N = Structure[2].getIndexCount();
	InputPtr = this;
	}

	if(Ordinates.Structure.isSubset() == 1)
	{
	O.initializeMinDuplicate(Ordinates);
	Odimension  = O.getDimension();
	OdataPtr    = (double*)O.getDataPointer();
	Ocount      = O[1].getIndexCount();
	}
	else
	{
	Odimension  = Ordinates.getDimension();
	OdataPtr    = (double*)Ordinates.getDataPointer();
	Ocount      = Ordinates[1].getIndexCount();
	}

	if(Odimension != 1)
	{CAMarrayBase::ordinateError(Ordinates.Structure);}

	if(M != Ocount)
	{CAMarrayBase::ordinateError(Ordinates.Structure);}

	switch (dimension)
	{
	case 1  :
	CAMgraphics::plot(OdataPtr,AdataPtr,M);

	break;

	case 2  :

	autoFlag = CAMgraphics::getAutoScaleFlag();
	x_min = *OdataPtr;
	x_max = *(OdataPtr +(M-1));
	y_min = InputPtr->min();
	y_max = InputPtr->max();
	CAMgraphics::axis(x_min,x_max,y_min,y_max);
	for(j = 1; j <= N; j++)
	{
	BdataPtr = AdataPtr + (j-1)*M;
	CAMgraphics::plot(OdataPtr, BdataPtr,M);
	}
	CAMgraphics::axis(autoFlag);

	break;
	default :
	CAMarrayBase::plotDimensionError(A.Structure);
	}

}

void  CAMarrayBase::plot(const CAMarrayBase& Ordinates, int p_arg) const
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

void  CAMarrayBase::plot(const CAMarrayBase& Ordinates, int p_arg, int p_style) const
{
	char point_type_save = CAMgraphics::getPointType();
	int  plot_style_save = CAMgraphics::getPlotStyle();
	CAMgraphics::setPointType(char(p_arg));
	CAMgraphics::setPlotStyle(p_style);

	this->plot(Ordinates);

	CAMgraphics::setPointType(point_type_save);
	CAMgraphics::setPlotStyle(plot_style_save);
}

void  CAMarrayBase::contour() const
{
//
//  Need Conversion Check
//
	CAMarrayBase A;
	double* AdataPtr;

	long dimension;
	long M,N;
	int  Fflag;

	if(Structure.isSubset() == 1)
	{
	A.initializeMinDuplicate(*this);
	dimension   = A.getDimension();
	AdataPtr    = (double*)A.getDataPointer();
	if(dimension >= 1) M = A[1].getIndexCount();
	if(dimension == 2) N = A[2].getIndexCount();
	}
	else
	{
	dimension = getDimension();
	AdataPtr  = (double*)getDataPointer();
	if(dimension >= 1) M = Structure[1].getIndexCount();
	if(dimension == 2) N = Structure[2].getIndexCount();
	}

	if(dimension == 2)
	{
	Fflag = CAMgraphics::getFortranArrayFlag();
	CAMgraphics::fortranArrayFlagOn();
	CAMgraphics::contour(AdataPtr,M,N);
	if(Fflag == 0) CAMgraphics::fortranArrayFlagOff();
	}
	else
	{CAMarrayBase::plotDimensionError(A.Structure);}

}

void  CAMarrayBase::contour(int nContour)  const
{
	CAMgraphics::setContourLevel(nContour);
	this->contour();
}

void  CAMarrayBase::contour(long nContour)  const
{
	CAMgraphics::setContourLevel(nContour);
	this->contour();
}
void  CAMarrayBase::contour(double increment) const
{
	CAMgraphics::setContourLevel(increment);
	this->contour();
}

void  CAMarrayBase::contour(double low_value, double high_value) const
{
	CAMgraphics::setContourLevel(low_value, high_value);
	this->contour();
}

void  CAMarrayBase::contour(long nContour, double low_value, double high_value) const
{
	CAMgraphics::setContourLevel(nContour, low_value, high_value);
	this->contour();
}

void  CAMarrayBase::contour(int nContour, double low_value, double high_value) const
{
	CAMgraphics::setContourLevel(nContour, low_value, high_value);
	this->contour();
}

void  CAMarrayBase::contour(double increment, double low_value, double high_value) const
{
	CAMgraphics::setContourLevel(increment, low_value, high_value);
	this->contour();
}

void  CAMarrayBase::contour(const CAMarrayBase& contourValues) const
{
//
//  Need Conversion Check
//
	CAMarrayBase A;
	double* AdataPtr;

	long dimension;
	long M,N;
	int  Fflag;

	CAMarrayBase CV;
	double* CVdataPtr;
	long    CVdimension;
	long    CVcount;

	if(Structure.isSubset() == 1)
	{
	A.initializeMinDuplicate(*this);
	dimension   = A.getDimension();
	AdataPtr    = (double*)A.getDataPointer();
	if(dimension >= 1) M = A[1].getIndexCount();
	if(dimension == 2) N = A[2].getIndexCount();
	}
	else
	{
	dimension = getDimension();
	AdataPtr  = (double*)getDataPointer();
	if(dimension >= 1) M = Structure[1].getIndexCount();
	if(dimension == 2) N = Structure[2].getIndexCount();
	}

	if(contourValues.Structure.isSubset() == 1)
	{
	CV.initializeMinDuplicate(contourValues);
	CVdimension  = CV.getDimension();
	CVdataPtr    = (double*)CV.getDataPointer();
	CVcount      = CV[1].getIndexCount();
	}
	else
	{
	CVdimension  = contourValues.getDimension();
	CVdataPtr    = (double*)contourValues.getDataPointer();
	CVcount      = contourValues[1].getIndexCount();
	}


	if(CVdimension != 1)
	{CAMarrayBase::ordinateError(contourValues.Structure);}

	if(dimension == 2)
	{
	Fflag = CAMgraphics::getFortranArrayFlag();
	CAMgraphics::fortranArrayFlagOn();
	CAMgraphics::contour(AdataPtr,M,N,CVdataPtr,CVcount);
	if(Fflag == 0) CAMgraphics::fortranArrayFlagOff();
	}
	else
	{CAMarrayBase::plotDimensionError(A.Structure);}

}

void  CAMarrayBase::surface() const
{
//
//  Need Conversion Check
//
	CAMarrayBase A;
	double* AdataPtr;

	long dimension;
	long M,N;
	int  Fflag;


	if(Structure.isSubset() == 1)
	{
	A.initializeMinDuplicate(*this);
	dimension   = A.getDimension();
	AdataPtr    = (double*)A.getDataPointer();
	if(dimension >= 1) M = A[1].getIndexCount();
	if(dimension == 2) N = A[2].getIndexCount();
	}
	else
	{
	dimension = getDimension();
	AdataPtr  = (double*)getDataPointer();
	if(dimension >= 1) M = Structure[1].getIndexCount();
	if(dimension == 2) N = Structure[2].getIndexCount();
	}

	if(dimension == 2)
	{
	Fflag = CAMgraphics::getFortranArrayFlag();
	CAMgraphics::fortranArrayFlagOn();
	CAMgraphics::surface(AdataPtr,M,N);
	if(Fflag == 0) CAMgraphics::fortranArrayFlagOff();
	}
	else
	{CAMarrayBase::plotDimensionError(A.Structure);}
}

void  CAMarrayBase::surface(const CAMarrayBase& x, const CAMarrayBase& y) const
{
//
//  Need Conversion Check
//
	CAMarrayBase A;
	double* AdataPtr;

	long dimension;
	long M,N;
	int  Fflag;

	CAMarrayBase XC;
	double* XCdataPtr;
	long    XCdimension;
	long    XCcount;

	CAMarrayBase YC;
	double* YCdataPtr;
	long    YCdimension;
	long    YCcount;

	if(Structure.isSubset() == 1)
	{
	A.initializeMinDuplicate(*this);
	dimension   = A.getDimension();
	AdataPtr    = (double*)A.getDataPointer();
	if(dimension >= 1) M = A[1].getIndexCount();
	if(dimension == 2) N = A[2].getIndexCount();
	}
	else
	{
	dimension = getDimension();
	AdataPtr  = (double*)getDataPointer();
	if(dimension >= 1) M = Structure[1].getIndexCount();
	if(dimension == 2) N = Structure[2].getIndexCount();
	}

	if(x.Structure.isSubset() == 1)
	{
	XC.initializeMinDuplicate(x);
	XCdimension  = x.getDimension();
	XCdataPtr    = (double*)x.getDataPointer();
	XCcount      = x[1].getIndexCount();
	}
	else
	{
	XCdimension  = x.getDimension();
	XCdataPtr    = (double*)x.getDataPointer();
	XCcount      = x[1].getIndexCount();
	}

	if(y.Structure.isSubset() == 1)
	{
	YC.initializeMinDuplicate(y);
	YCdimension  = y.getDimension();
	YCdataPtr    = (double*)y.getDataPointer();
	YCcount      = y[1].getIndexCount();
	}
	else
	{
	YCdimension  = y.getDimension();
	YCdataPtr    = (double*)y.getDataPointer();
	YCcount      = y[1].getIndexCount();
	}

	if(XCdimension != 1)
	{CAMarrayBase::ordinateError(x.Structure);}

	if(YCdimension != 1)
	{CAMarrayBase::ordinateError(y.Structure);}

	if(M != XCcount)
	{CAMarrayBase::ordinateError(x.Structure);}

	if(N != YCcount)
	{CAMarrayBase::ordinateError(y.Structure);}


	if(dimension == 2)
	{
	Fflag = CAMgraphics::getFortranArrayFlag();
	CAMgraphics::fortranArrayFlagOn();
	CAMgraphics::surface(AdataPtr,M, N, XCdataPtr, YCdataPtr);
	if(Fflag == 0) CAMgraphics::fortranArrayFlagOff();
	}
	else
	{CAMarrayBase::plotDimensionError(A.Structure);}

}

void CAMarrayBase::ordinateError(const CAMstructureBase & A) 
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
void CAMarrayBase::plotDimensionError(const CAMstructureBase& A)
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


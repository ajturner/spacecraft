//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Plot.cpp
*  \brief Implementation of the Plot class.
*  \author $Author: rsharo $
*  \version $Revision: 1.4 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Plot.h"
namespace O_SESSAME {

Plot::Plot()
{
    m_pipeVar = popen("gnuplot","w");
        
    char tmpname[L_tmpnam];
    m_dataFilename = tmpnam(tmpname);
    
    return;
}
Plot::~Plot()
{
    // delete data file
    pclose(m_pipeVar); // close pipe when you are finished with plotting
    return;
}
Plot::Plot(const Matrix &_data)
{
    Plot();
    AddPlot(_data);
    return;
}
Plot::Plot(const Matrix &_data, int _cols[], const int &_numCols)
{
    Plot();
    AddPlot(_data, _cols, _numCols);
}

void Plot::AddPlot(const Matrix &_data)
{
	std::ofstream ofile;
    ofile.open(m_dataFilename);
    ofile << _data;
    ofile.close();
    
    fprintf(m_pipeVar, "plot '%s' with linespoints\n", m_dataFilename);
    fflush(m_pipeVar);
    for(int ii = MatrixIndexBase+2;ii < MatrixIndexBase + _data[MatrixColsIndex].getIndexBound();++ii)
    {
        fprintf(m_pipeVar, "replot '%s' using 1:%i with linespoints\n", m_dataFilename, ii);
        fflush(m_pipeVar);
    }
    fflush(m_pipeVar); // pipes are buffered, so flush buffer after you are finished
    return;
}

void Plot::AddPlot(const Matrix &_data, int _cols[], const int &_numCols)
{
    for(int ii = 0;ii < _numCols;++ii)
    {
        fprintf(m_pipeVar, "replot '%s' using 1:%i with linespoints\n", m_dataFilename, ii);
        fflush(m_pipeVar);
    }    
    return;
}

void Plot::Title(const char *_titleString)
{
    fprintf(m_pipeVar, "set title '%s' \n", _titleString);
    fflush(m_pipeVar);
    return;
}

void Plot::Set(const char *_parameterName, const char *_values)
{
    return;
}
void Plot::Command(const char *_stringCommand)
{
    return;
}
} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Plot.cpp,v $
*	Revision 1.4  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.3  2003/05/13 18:58:27  nilspace
*	Cleaned up comments.
*	
*	Revision 1.2  2003/04/27 22:04:34  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.1  2003/04/08 22:31:25  nilspace
*	Initial Submission.
*	
*	
*
******************************************************************************/

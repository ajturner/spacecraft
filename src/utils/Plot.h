//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Plot.h
*  \brief Interface to GNUPLOT (http://www.gnuplot.org)
*  \author $Author: rsharo $
*  \version $Revision: 1.6 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
* \todo figure out if this can be done w/ 1 instance of gnuplot
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __PLOT_H__
#define __PLOT_H__
#include <string.h>
#include <stdio.h>
#include <fstream>
#include "Matrix.h"
namespace O_SESSAME {

/*! \brief A Plot object is used to display data in a 2-D or 3-D plot.
* \ingroup Utilities
*
* \detail Using GnuPlot, this class is a C++ interface to plotting. 
* for a list of GnuPlot commands, visit: http://www.duke.edu/~hpgavin/gnuplot.html or
* http://www.cs.uni.edu/Help/gnuplot/
* \todo Finish documenting API
*/
class Plot
{
public:
    Plot();
    virtual ~Plot();
    Plot(const Matrix &_data);
    Plot(const Matrix &_data, int _cols[], const int &_numCols);
    void AddPlot(const Matrix &_data);
    void AddPlot(const Matrix &_data, int _cols[], const int &_numCols);

    void Title(const char *_titleString);
    void Set(const char *_parameterName, const char *_values);
    void Command(const char *_stringCommand);
private:
    FILE* m_pipeVar;
    char* m_dataFilename;

};

/** Use GnuPlot to plot the data in a matrix
    * @param _data Matrix of data, the first column is x, and each of the other columns will be plotted on the y-axis
    */
static void Plot2D(const Matrix &_data)
{
    FILE* pipeVar;
    pipeVar = popen("gnuplot","w");
	std::ofstream ofile;
    char tmpname[L_tmpnam];
    char *filename;
    filename = tmpnam(tmpname);
    ofile.open(filename);
    ofile << _data;
    ofile.close();
    
    fprintf(pipeVar, "plot '%s' with linespoints\n", filename);
    fflush(pipeVar);
    for(int ii = MatrixIndexBase+2;ii < MatrixIndexBase + _data[MatrixColsIndex].getIndexBound();++ii)
    {
        fprintf(pipeVar, "replot '%s' using 1:%i with linespoints\n", filename, ii);
        fflush(pipeVar);
    }
    fflush(pipeVar); // pipes are buffered, so flush buffer after you are finished
	cout << "Press enter to continue." << flush;
        char dummy;
	cin >> dummy;
	pclose(pipeVar); // close pipe when you are finished with plotting
    return;
}

static void Plot3D(const Matrix &_data)
{
    FILE* pipeVar = popen("gnuplot","w");
	std::ofstream ofile;

    char tmpname[L_tmpnam];
    char *filename;
    filename = tmpnam(tmpname);
    ofile.open(filename);
    ofile << _data;
    ofile.close();
    
    fprintf(pipeVar, "splot '%s' with lines\n",filename);
    fflush(pipeVar); // pipes are buffered, so flush buffer after you are finished
	
        cout << "Enter a key and press enter to continue..." << flush;
        char dummy;
	cin >> dummy;
	
    pclose(pipeVar); // close pipe when you are finished with plotting
    return;
}
} // close namespace O_SESSAME

#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Plot.h,v $
*	Revision 1.6  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.5  2003/05/13 18:58:27  nilspace
*	Cleaned up comments.
*	
*	Revision 1.4  2003/05/01 20:28:19  nilspace
*	Added stdio.h to includes.
*	
*	Revision 1.3  2003/04/27 22:04:34  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.2  2003/04/23 16:28:38  nilspace
*	Added functionality to general plot functions.
*	
*	Revision 1.1  2003/04/08 22:31:25  nilspace
*	Initial Submission.
*	
*	
*
******************************************************************************/

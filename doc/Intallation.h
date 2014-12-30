/*! \page InstallationPage Installation Instructions
\ref TableOfContents : \ref IntroductionPage

  This page contains installation instructions for \ref LinuxInstall, \ref WindowsInstall, \ref EmbeddedComputersInstall, 
  and \ref InstallingLibraries.
  \par
  For more info see section \ref TroubleshootingInstallation.
  
  \section Requirements 
  The following programs are required or suggested for using and developing with the Open-Sessame Framework:
    - <a href="http://www.doxygen.org">Doxygen</a>
        - <a href="http://www.research.att.com/sw/tools/graphviz/">GraphViz</a> (<a href="http://www.graphviz.org/">Another</a>)
    - <a href="http://gcc.gnu.org/">GNU GCC</a>
    - <a href="http://www.gnuplot.org/">GnuPlot</a>
    - <a href="http://www.cvshome.org">CVS</a>
    
  \section Building Building the libraries
  \subsection LinuxInstall Linux
  -# Grab the current software via 2 methods, CVS or a bundled ZIP file:
    -# CVS
        - Make sure that <a href="http://www.cvshome.org">CVS</a> (Concurrent Versioning System) is installed on your system.
        - Run the following command from the directory where you want to store the project files: \verbatim cvs -z3 -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/spacecraft co spacecraft \endverbatim
        - If you receive an error like: "cvs [checkout aborted]: recv() from server cvs.sourceforge.net" just keep trying to checkout, the anonymous server is over-worked.
    -# ZIP File
        - Download the source bunde from <a href="http://sourceforge.net/projects/spacecraft" target=_new>Files</a>.
        - Unzip the bundle or source file: \verbatim gunzip OpenSessame-##_bundle.zip \endverbatim (where ## is the current version number)
  -# Change to the spacecraft root directory: \verbatim cd spacecraft/ \endverbatim
  -# Run the make file to compile the libraries: \verbatim make \endverbatim
        - If you see the following error: \begin{verbatim}make[2]: *** No rule to make target `/mkspecs/linux-g++/qmake.conf', needed by `Makefile'.  Stop.\end{verbatim} it means
        you don't have QT or qmake installed or the environment variable set. Make sure QT is installed and then type the following at the command line: 
        \begin{verbatim}export QTDIR="/usr/share/qt"\end{verbatim}
  -# Compile the documentation: \verbatim make doc \endverbatim
  -# Change to the test directory: \verbatim cd src/test/ \endverbatim
  -# Build a test file: \verbatim make testPropagation \endverbatim
  -# Run the test program. If it runs okay, your installation is finished: \verbatim ./testPropagation \endverbatim
  \subsection WindowsInstall Windows
  This section is forthcoming: Developer XB70
  \todo Document Windows installation
  
  \subsection EmbeddedComputersInstall Embedded Computers
  This section is forthcoming, but should be similar to \ref LinuxInstall
  
  \section InstallingLibraries Installing Libraries
 \todo Document Library installation
*/

/*! \page TroubleshootingInstallation Troubleshooting Installation
  Troubleshooting information forthcoming.
*/
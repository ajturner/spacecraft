/** @page IntroductionPage Introduction to the Open-Sessame Framework

@authors Andrew Turner

\ref TableOfContents

@section intro Introduction
The goal of this project is to develop an Open-Source, Extensible Spacecraft Simulation 
And Modeling Environment (Open-SESSAME) framework that can serve as a basis for satellite 
modeling and analysis. The entire collection of code provides most of the tools, libraries 
and structure necessary for simulating a wide-range of spacecraft while also allowing easy 
extension for any further desired functionality. Also, by being open-source users are able 
to investigate the design and operating of the code to reassure themselves of the validity 
of the simulator. The Open-SESSAME framework is also an active project of the large and rapidly 
growing open-source community. This allows new functionality to be disseminated to all current 
and future users of the framework as it continues to grow and mature. 


\section rationale Rationale
Many students and researchers of satellite dynamics and control must independently 
develop a software simulations each time a new research project begins. These simulations 
are typically built specifically for the research task at hand and not easily adaptable to 
future projects. Furthermore, many students have little experience developing simulations, 
and may not know where to begin, what to be concerned with, and how to best implement 
components so they can be resuable between projects and other students and engineers. 
The Open-Sessame framework addresses these issues by providing a common groundwork upon 
which students can learn how simulators are implemented and develop their own components 
for use in the framework for their own research. 

The <a href="http://www.aoe.vt.edu/research/groups/sssl/" target="new">Space Systems Simulation Laboratory</a>
(SSSL) at <a href="http://www.vt.edu" target="new">Virginia Tech</a> in Blacksburg, Virginia is working on a 
number of projects that work to develop new methodologies for the simulation and analysis of 
spacecraft and their associated systems.
These projects include both hardware and software simulation techniques that are used in 
conjuction to better understand the interplay of satellite dynamics with novel control \& 
sensing strategies. As a result of the various unique requirements of many of the projects, 
a single commercial software package has not yet fulfilled the needs of the lab. An open-source 
and extensible simulation framework creates a reusable basis for any future simulation projects 
while also allowing the students and researchers the capacity to configure the simulation to 
their unique specifications. Furthermore, they are able to interface the simulation software 
with any other analysis package they may require for their research. 

\section using Using the Framework

Here is the suggested path for using the Open-Sessame Framework.
-# If you haven't already, download the latest source and documentation from the Sourceforge 
repository at <a href="http://sourceforge.net/projects/spacecraft" target="new">http://sourceforge.net/projects/spacecraft</a>.
Download either the newest bundle (under @em Files), or click on the link to @em CVS and follow the basic instructions to get the 
most up-to-date release. 
-# Scroll through the <a href="Open-Sessame_Primer_Presentation.pdf" target=_new>Primer Presentation</a> which gives an 
introduction and overview of some of the main concepts.
-# Read the \ref UsingOpenSESSAME documentation about the general usage of the framework.
-# Build \& install the libraries by following the \ref InstallationPage.
-# Follow the \ref TutorialsPage
-# Check out the forums at the <a href="http://sourceforge.net/projects/spacecraft" target="new">Sourceforge website</a> 
for discussion on development, useful links, tutorials, etc. There is a user base out there, use it.
-# Begin contributing by checking out the todo list or talking to other uses in the forums.

@section installSection Installation
See the \ref InstallationPage ["Installation Page"] for instructions on building \& installing 
the Open-Sessame framework libraries. 

* \section ToDo To Do Items
    
To help in development, as well as learning the framework, here is a current (5/12/03) list of major 
todo implementation items. These consist of larger scale new feature and add-on implementation items 
that have been identified by the development team, which differe from the bug-fixes and small todo items 
found on the 'todo' page. While the small items need to be completed, if you're up to learning more about 
C++ coding and the framework, it is suggested you look at one of these problems.
 
* @todo 
-# A better, faster, powerful matrix/vector library. Should handle all typical linear algebra 
functionality (matrix mult, vector mult, matrix*vector mult, inverse, transpose, norm, etc). Error handling 
would be nice with options for command line debugging (outputting the type/size of matrix, characterization 
of error (wrong mult sizes, singular) and possibly where the error occured (function, code line).
-# More force functions: solar radiation pressure, advanced atmospheric model, higher-order 
gravity model
-# More torque functions: magnetic field, higher-order gravity gradient, micrometeorites
-# Need to implement frames, both orbit \& attitude.
-# A store and restore mechanism. Needs to be cross-platform, prefer something like XML formatting. Also need to be able to export/import with MatLab, Satellite ToolKit (STK), Excel (CSV), and others.

* <hr>
* @section notes Release Notes
* release.notes
* <hr>
* @section Requirements Requirements
* @verbinclude requirements
* <hr>
<a href="http://sourceforge.net/projects/spacecraft">\image html sflogo.png</a>

*/
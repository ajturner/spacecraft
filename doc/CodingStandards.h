/*! \page CodingStandardsPage Coding Standards 
\ref mainpage

\verbatim
    
#ifndef CLASSTEMPLATE_H
#define CLASSTEMPLATE_H

// [C Headers]
extern "C" {
}

// [C++ Header files]
#include "SomeClass.h"

// [forward declarations]
class AnotherClass;

%/** 
* @class ClassTemplate
*
* @brief This is an example class.
*
* This comment block is @e required for all class declarations.
* Please remove comments that are bracketed by [..]. These comments are there 
* to provide instructions to developers while writing their code. 
* Obvious member variables and functions, such as get and set routines and 
* default constructors and destructors, should not be documented as this 
* clutters the files. Use standard C++ comments for those comments you wish 
* Doxygen to ignore. If the class has many members - you may consider 
* providing separate public, protected, private sections for member functions
* and member variables to improve readability. In addition it may be useful to
* form member groups preceded by a header as shown below.
*
* Please note that the \$Header\$ keyword specified below is a RCS keyword, 
* and will inflate into the version, name, etc for this file.
* 
* @author Some Body
* 
* $Header $
*/

class ClassTemplate {

public:
ClassTemplate();
~ClassTemplate();

int getIntMember() { return m_intMember; };
void setIntMember(const int i) { m_intMember = i; };

%/**
* Provide detailed desciption of this function
* @param parmeter1 Describe this parameter

* Here is an example of inserting a mathematical formula into the text:
* The distance is computed as /f$\sqrt{ (x_2-x_1)^2 + (y_2 - y_1)^2 }/f$
* If we wanted to insert the formula centered on a separate line:
* /f[
* \sqrt{ (x_2-x_1)^2 + (y_2 - y_1)^2 }
* /f]
* Please note that all formulas must be valid LaTeX math-mode commands. 
* Additionally, to be processed by Doxygen, the machine used must have 
* LaTeX installed. Please see the Doxygen manual for more information 
* about installing LaTeX locally.
*/
void publicMemberFunction(int parameter1);

%/**
* Provide a detailed description of this function.
* @return Describe the return values.
*/
bool anotherPublcMemberFunction();

static int getStaticIntMember() { return s_staticIntMember; };

%/** @name Header for Group1
* [ Description of Group1 ]
*/
//@{
// [ members of Group1]
bool yetAnotherFunction1();
int yetAnotherFunction2();
//@}

private:

/// Provide a description of this class member 
/// [note that the m_ prefix is not used for static members]
static int s_staticIntMember;
/// Provide a description of this class member
int m_intMember;
/// Provide a description of this class member
float m_floatMember;

}

#endif // CLASSTEMPLATE_H 
/*! 
\endverbatim
*/
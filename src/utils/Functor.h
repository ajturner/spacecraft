//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Functor.h
*  \brief Implementation of a Functor class for vectors.
*  \author $Author: rsharo $
*  \version $Revision: 1.10 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_FUNCTOR_H__
#define __SSF_FUNCTOR_H__

#include <Matrix.h>
#include "utils/Time.h"
#include "OrbitState.h"
#include "AttitudeState.h"

namespace O_SESSAME {

/*! \brief Abstract class to hold the pointer to an force calculating functor.
* \ingroup IntegrationLibrary
* \ingroup EnvironmentToolkit
*
* A @em Function @em Object, or @em Functor (the two terms are synonymous) is simply 
any object that can be called as if it is a function. It is used to define a call-back function that evaluates 
any algorithm that takes the defined inputs and returns a vector of values. Examples of usage include 
evaluating a disturbance force or torque given the current time, orbit state, and attitude state. The returned 
vector will then be the 3 forces (or torques). 

\par Examples:
The simplest functor is a placeholder that can be set to just return a vector of zeros:
\code
Vector NullFunctor(const ssfTime& _pSSFTime, const OrbitState& _pOrbitState, const AttitudeState& _pAttitudeState)
{
    return Vector(3);
}
\endcode
This isn't very useful, but may be necessary for filling out a parameter list such as for \sa Integrator that 
requests a Functor call-back function. The Functor object is created as follows:
\code 
SpecificFunctor AttitudeForcesFunctor(&NullFunctor);
\endcode
SpecificFunctor is used since it is only a function that was used, and not a member function of a class. For that 
case, an ObjectFunctor is required which stores the type (or class) of the function as well as the pointer to 
the function itself. 

\par
An ObjectFunctor may be assigned from an Environment object (@em pEarthEnv) where the function is @em GetForces:
\code
ObjectFunctor<Environment> OrbitForcesFunctor(pEarthEnv, &Environment::GetForces);
\endcode
To review, we are creating an ObjectFunctor that will hold a call-back function to the Environment class (hence 
the template argument <Environment>). The function, @em OrbitForcesFunctor, needs a pointer to the instance 
of the class we are using (@em pEarthEnv), and the reference to the function (@em &Environment::GetForces). The 
@em \& is required to specify that it is a @em reference, and the @em Environment:: defines the scope of the 
function @em GetForces. It is also important to note that the @em GetForces function conforms to the ObjectFunctor 
interface. (\sa Environment::GetForces).

* \todo make Functors for variety of function types 
*/
class Functor
{
public:

      // two possible functions to call member function. virtual cause derived
      // classes will use a pointer to an object and a pointer to a member function
      // to make the function call
      virtual Vector Call(const ssfTime&, const OrbitState&, const AttitudeState&) const =0;        // call using function
};

/*! \brief derived template class
* \ingroup IntegrationLibrary
* \ingroup EnvironmentToolkit
*
*/
class SpecificFunctor : public Functor
{
private:
      Vector (*fpt)(const ssfTime&, const OrbitState&, const AttitudeState&);   	// pointer to member function

public:

      // constructor - takes pointer to a Function
      SpecificFunctor(Vector(*_fpt)(const ssfTime&, const OrbitState&, const AttitudeState&)):fpt(_fpt) {};

      // override function "Call"
      virtual Vector Call(const ssfTime &_ssfTime, const OrbitState &_orbState, const AttitudeState &_attState) const { return (*fpt)(_ssfTime, _orbState, _attState);};             // execute member function
};

/*! \brief derived template class
* \ingroup IntegrationLibrary
* \ingroup EnvironmentToolkit
*
*/
template <class TClass> class ObjectFunctor : public Functor
{
private:
      TClass* pt2Object;                  	/*!< pointer to object */
      Vector (TClass::*fpt)(const ssfTime&, const OrbitState&, const AttitudeState&);   	/*!< pointer to member function */

public:

      /*! constructor - takes pointer to an object and pointer to a member and stores
      * them in two private variables */
      ObjectFunctor(TClass* _pt2Object, Vector(TClass::*_fpt)(const ssfTime&, const OrbitState&, const AttitudeState&)): pt2Object(_pt2Object),  fpt(_fpt) {};
      ObjectFunctor(): pt2Object(NULL),  fpt(NULL) {};
      void Set(TClass* _pt2Object, Vector(TClass::*_fpt)(const ssfTime&, const OrbitState&, const AttitudeState&)){ pt2Object = _pt2Object;  fpt=_fpt; };
      
      // override function "Call"
      virtual Vector Call(const ssfTime &_ssfTime, const OrbitState &_orbState, const AttitudeState &_attState) const { return (*pt2Object.*fpt)(_ssfTime, _orbState, _attState);};             // execute member function
};
} // close namespace O_SESSAME

#endif /* __SSF_FUNCTOR_H__ */

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Functor.h,v $
*	Revision 1.10  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.9  2003/05/21 19:52:22  nilspace
*	Updated comments.
*	
*	Revision 1.8  2003/05/20 17:44:20  nilspace
*	Updated comments.
*	
*	Revision 1.7  2003/05/13 18:58:04  nilspace
*	Cleaned up comments.
*	
*	Revision 1.6  2003/04/27 22:04:34  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.5  2003/04/25 18:55:45  nilspace
*	Implemented ObjectFunctor body (empty), and moved constructor assignments to inline with constructor.
*	
*	Revision 1.4  2003/04/25 13:45:53  nilspace
*	const'd Get() functions.
*	
*	Revision 1.3  2003/04/24 20:00:10  nilspace
*	Made all Call() functions const to prevent warnings.
*	
*	Revision 1.2  2003/04/24 13:51:10  nilspace
*	Added a Set function for setting the object & function afterwards, or by using the default constructor.
*	
*	Revision 1.1  2003/04/08 22:33:06  nilspace
*	Initial Submission
*	
*
******************************************************************************/

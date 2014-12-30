//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file NumericPropagator.h
*  \brief Interface to the Numeric Propagator class.
*  \author $Author: rsharo $
*  \version $Revision: 1.8 $
*  \date    $Date: 2003/10/18 21:37:27 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* \todo Finish documentation
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OSESSAME_NUMERIC_PROPAGATOR_H__
#define __OSESSAME_NUMERIC_PROPAGATOR_H__

#include "Matrix.h"
#include "Rotation.h"
#include "utils/Integrator.h"
#include "Propagator.h"

namespace O_SESSAME {

/*! \brief Numeric Propagation of orbit & attitude using a numeric integrator.
* \ingroup PropagatorToolkit
*
* 
* \example testDynamics.cpp
*/
class NumericPropagator : public Propagator
{
public:
    /*! Default Constructor */
    NumericPropagator();
    /*! Default Deconstructor */
    virtual ~NumericPropagator();
    
    /*! Propagates the dynamics forward through time
        * @param _propTime vector of ssfTime values specifying beginning, ending times of propagation as well as time step [initialTime, timeStep, finalTime] (s)
        * @param _orbitInitConditions initial conditions of the orbit integration.
        * @param _attInitConditions initial conditions of the attitude integration.
        */
    virtual void Propagate(const vector<ssfTime> &_propTime, const Vector &_orbitInitConditions, const Vector &_attInitConditions);
    
protected:
   
private:

};
} // close namespace O_SESSAME

#endif
/*****************************************************************************
*	$Log: NumericPropagator.h,v $
*	Revision 1.8  2003/10/18 21:37:27  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.7  2003/05/22 21:02:16  nilspace
*	Updated comments.
*	
*	Revision 1.6  2003/05/20 17:55:35  nilspace
*	Updated comments, also now use derived CombinedNumericProp.
*	
*	Revision 1.5  2003/05/13 18:54:04  nilspace
*	Fixed comments & various propagate functions.
*	
*	Revision 1.4  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.3  2003/04/25 13:43:52  nilspace
*	Updated to actually work. Still needs verification.
*	
*	Revision 1.2  2003/04/23 16:30:58  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/04/08 22:49:56  nilspace
*	Initial Submission.
*
******************************************************************************/

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file AnalyticPropagator.h
*  \brief Interface to the Analytic Propagator class.
*  \author $Author: nilspace $
*  \version $Revision: 1.5 $
*  \date    $Date: 2003/05/13 18:54:14 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* \todo Finish documentation
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ANALYTIC_PROPAGATOR_H__
#define __SSF_ANALYTIC_PROPAGATOR_H__

#include "Rotation.h"

namespace O_SESSAME {

/*! \brief Encapsulation of the propagation of the spacecraft dynamics (attitude, orbital, etc.)
* \ingroup PropagatorToolkit
*
* \detail The propagator is used to tie together the various spacecraft dynamics that are desired to be 
* propagated. The user has the ability to set the time derivative equations, integrators, parameters,
* etc. as necessary. Furthermore, the Propagator class can be derived for more functionality.
*/
class AnalyticPropagator : public Propagator
{
public:
    /** Default Constructor */
    AnalyticPropagator();
    
    /** Propagates the dynamics forward through time
        * @param _propTime STL vector of values specifying beginning, ending times of propagation as well as time step [initialTime, timeStep, finalTime] (s)
        */
    virtual void Propagate(const vector<ssfTime> &_propTime);
    
private:

};
}
#endif
/*****************************************************************************
*	$Log: AnalyticPropagator.h,v $
*	Revision 1.5  2003/05/13 18:54:14  nilspace
*	Fixed comments.
*	
*	Revision 1.4  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.3  2003/04/25 13:43:51  nilspace
*	Updated to actually work. Still needs verification.
*	
*	Revision 1.2  2003/04/23 16:30:58  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/04/08 22:51:58  nilspace
*	Initial submission. Only a template, needs to be implemented.
*
******************************************************************************/

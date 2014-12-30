//////////////////////////////////////////////////////////////////////////////////////////////////
/*!\file RungeKuttaIntegrator.h
*  \brief Runge-Kutta integrator.
*  \author $Author: nilspace $
*  \version $Revision: 1.8 $
*  \date    $Date: 2003/05/22 02:59:15 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  \todo Add test cases
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_RUNGEKUTTA_INTEGRATOR_H__
#define __SSF_RUNGEKUTTA_INTEGRATOR_H__

#include "Matrix.h"
#include "Integrator.h"
namespace O_SESSAME {

/*! \class RungeKuttaIntegrator 
* \brief Implementation of a Runge-Kutta (Fourth Order) %Integrator. 
* \ingroup IntegrationLibrary
* 
* \copydoc Integrator 
* \todo document algorithm 
* \example testAttitudeIntegration.cpp
* \example testOrbitIntegration.cpp
*/
class RungeKuttaIntegrator : public Integrator 
{
public:
    RungeKuttaIntegrator();
    
    Matrix Integrate(const vector<ssfTime>& _propTime, odeFunctor _odeFunctorPtr, const Vector& _initialConditions, Orbit* _Orbit, Attitude* _Attitude, const Matrix& _constants, const Functor& _functorPtr);

    /*! Standard Integration Function */
//    Matrix Integrate(const Vector &_propTime, odeFunc _FuncPtr, const Vector &_initialConditions, const Matrix &_constants, vectorFuncPtr _vectorFuncPtr);

    /*! \brief Set the number of integration steps 
        * @param _numSteps number of steps to include between integration timesteps
        */
    void SetNumSteps(const int &_numSteps) 	{ m_NumSteps = _numSteps; return; }
    
    /*! \brief Return the number of integration steps
        * @return current number of integration steps performed b/w every timestep 
        */
    int GetNumSteps() 				{ return m_NumSteps; }
private:
    int m_NumSteps;	/*!< \brief number of integration steps performed b/w every timestep */
};
} // close namespace O_SESSAME

#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: RungeKuttaIntegrator.h,v $
*	Revision 1.8  2003/05/22 02:59:15  nilspace
*	Updated comments. Changed to pass in pointers to Orbit & Attitude objects.
*	
*	Revision 1.7  2003/05/21 19:52:47  nilspace
*	Updated comments.
*	
*	Revision 1.6  2003/05/20 17:44:21  nilspace
*	Updated comments.
*	
*	Revision 1.5  2003/05/13 18:58:27  nilspace
*	Cleaned up comments.
*	
*	Revision 1.4  2003/04/27 22:04:34  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.3  2003/04/25 13:45:55  nilspace
*	const'd Get() functions.
*	
*	Revision 1.2  2003/04/23 16:30:59  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/04/08 22:29:55  nilspace
*	Initial submission. Made a subclass of Integrator.
*	
******************************************************************************/

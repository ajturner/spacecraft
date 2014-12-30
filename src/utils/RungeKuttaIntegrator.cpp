//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file RungeKuttaIntegrator.cpp
*  \brief Implementation of the Runge-Kutta Fourth Order integrator.
*  \author $Author: nilspace $
*  \version $Revision: 1.7 $
*  \date    $Date: 2003/05/22 02:59:15 $
//////////////////////////////////////////////////////////////////////////////////////////////////
*  \todo Add test cases
*/
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "RungeKuttaIntegrator.h"
namespace O_SESSAME {

/*! \brief Creates a default, unitialized RK-integrator.
    */
RungeKuttaIntegrator::RungeKuttaIntegrator()
{
    m_NumSteps = 1;
}

/** \todo pull out RungeKuttaIntegrator::Step function */
/*
Matrix RungeKuttaIntegrator::Integrate(const Vector &_propTime, odeFunc _FuncPtr, const Vector &_initialConditions, const Matrix &_constants, vectorFuncPtr _vectorFuncPtr)
{
        double timeInitial = _propTime(VectorIndexBase);
	double t = timeInitial;
        double h = (_propTime(VectorIndexBase + 1) - t) / m_NumSteps;

	int numEqs = _initialConditions.getIndexCount();
	Vector inputs = _initialConditions;
	Vector K1(numEqs);
	Vector K2(numEqs);
	Vector K3(numEqs);
	Vector K4(numEqs);

	Matrix output(m_NumSteps + 1, numEqs + 1);

	output(MatrixIndexBase,MatrixIndexBase) = timeInitial;
	output(MatrixIndexBase,_(MatrixIndexBase+1,MatrixIndexBase+numEqs)) = ~_initialConditions;

	Vector temp(numEqs);
        for (int ii = 1; ii <= m_NumSteps; ++ii)
        {
            K1 = h * _FuncPtr(t, inputs, _constants, _vectorFuncPtr);
            temp = inputs + K1 / 2.0;
            K2 = h * _FuncPtr(t + h/2, temp, _constants, _vectorFuncPtr);
            temp = inputs + K2 / 2.0;
            K3 = h * _FuncPtr(t + h/2, temp, _constants, _vectorFuncPtr);
            temp = inputs + K3;
            K4 = h * _FuncPtr(t + h, temp, _constants, _vectorFuncPtr);
            for (int jj = MatrixIndexBase; jj < MatrixIndexBase + numEqs; ++jj)
            {
                inputs(jj) += (K1(jj)
                                 + 2.0 * K2(jj)
                                 + 2.0 * K3(jj)
                                 + K4(jj)) / 6.0;
            }
            t = timeInitial + ii * h;
            output(MatrixIndexBase + ii,MatrixIndexBase) = t;
            output(MatrixIndexBase + ii,_(MatrixIndexBase+1,MatrixIndexBase+numEqs)) = ~inputs;	
	}
	return output;
}
*/

    /*! \brief Integrates the Right-Hand Side (RHS) equation using a Runge-Kutta 4th Order %integrator.
        * 
        * This function will integrate an equation of the form \f$\dot{\bf x} = f(t,{\bf x})\f$ from \f$t_0\f$ to \f$t_f\f$ given 
        * initial conditions, an orbit and attitude object (or empty references if not required), a matrix of constants, and an 
        * external call-back function. 
        *
        * @param _propTime This input variable specifies the list of integration times, from the starting value (first time) to the ending integration (last time) with the specified intervals.
        *	If no specific intervals are required (and can be interpolated later), the user needs to just specify the beginning and end times of integration.
        *	This vector is built by creating ssfTime object, and "push_back" them onto the vector list:
            * \code
            * vector<ssfTime> integrationTimes;
            * ssfTime begin(0);
            * ssfTime end(begin + 20);
            * integrationTimes.push_back(begin);
            * integrationTimes.push_back(end);
            * \endcode
        * @param _FunctorPtr This is the reference (odeFunctor) to the Right-Hand side (RHS) of the integration equation. It should be a single function that computes the time derivative 
        *	of the state given the time, current state, and other parameters.
        * @param _initialConditions The vector of initial conditions of the state being integrated. It can be any sized.
        * @param _pOrbit This is a pointer to an Orbit object. It will be passed directly to the RHS and may be used for evaluating the dynamics or disturbance torque/forces. 
        *	However, if no orbit is required, or used, the user should only pass a NULL pointer and the orbit object shouldn't be used in the user's RHS function.
        * @param _pAttitude This is a pointer to an Attitude object. It behaves much the same way as _Orbit above. It will be passed directly to the RHS function for use in 
        * 	evaluation, but if not used, the user should only pass a NULL pointer, and the attitude object not used in the RHS function. 
        * @param _constants This is a matrix of constants that is required by the RHS function. The constants are passed to each evaluation of the RHS, and may be any size, and 
        *	store any values the user requires. Examples include Moments of Inertia, ballistic coefficients, mass, etc.
        * @param _functorPtr The Functor is a call-back function that the RHS can use to evaluate an external function call. The prototype of the _functorPtr must correspond to the Functor 
        *	definition, but other than that, may perform any calculations required by the user in the RHS function.
        * @return The output of the integration function is a matrix of calculated integration times (meshpoints), and integrated state values at each of the meshpoints.
            * \f[
            * \begin{bmatrix}
            * t_0 & x_{1,0} & x_{2,0} & ...\\
            * t_1 & x_{1,1} & x_{2,1} & ...\\
            * t_2 & x_{1,2} & x_{2,2} & ...\\
            * . & . & . & . \\
            * t_{final} & x_{1,f} & x_{2,f} & ...
            * \end{bmatrix}
            * \f]
            * where /f$t_T/f$ is the time at step T, and /f$x_{i,T}/f$ is the state value of element i, at time step T.
        */
Matrix RungeKuttaIntegrator::Integrate(const vector<ssfTime>& _propTime, odeFunctor _odeFunctorPtr, const Vector& _initialConditions, Orbit* _pOrbit, Attitude* _pAttitude, const Matrix& _constants, const Functor& _functorPtr)
{
        vector<ssfTime> propTime = _propTime; // need to create copy to prevent the stl .begin() and .end() from discarding the const-ness
        vector<ssfTime>::iterator timeIterator = propTime.begin();

        ssfTime timeInitial = (*timeIterator);
	ssfTime t = timeInitial;
        timeIterator = propTime.end() - 1;
        double h = ((*timeIterator).GetSeconds() - timeInitial.GetSeconds()) / m_NumSteps; // Calculation step size (seconds)
	int numEqs = _initialConditions.getIndexCount();
	Vector inputs = _initialConditions;
	Vector K1(numEqs);
	Vector K2(numEqs);
	Vector K3(numEqs);
	Vector K4(numEqs);

	Matrix output(m_NumSteps + 1, numEqs + 1);

	output(MatrixIndexBase,MatrixIndexBase) = timeInitial.GetSeconds();
	output(MatrixIndexBase,_(MatrixIndexBase+1,MatrixIndexBase+numEqs)) = ~_initialConditions;
        ssfTime tTemp;
	Vector temp(numEqs);
        for (int ii = 1; ii <= m_NumSteps; ++ii)
        {
            K1 = h * _odeFunctorPtr(t, inputs, _pOrbit, _pAttitude, _constants, _functorPtr);
            temp = inputs + K1 / 2.0; 		tTemp = t + h/2; 	
            K2 = h * _odeFunctorPtr(tTemp, temp, _pOrbit, _pAttitude, _constants, _functorPtr);
            temp = inputs + K2 / 2.0;				
            K3 = h * _odeFunctorPtr(tTemp, temp, _pOrbit, _pAttitude, _constants, _functorPtr);
            temp = inputs + K3; 	tTemp = t + h;		
            K4 = h * _odeFunctorPtr(tTemp, temp, _pOrbit, _pAttitude, _constants, _functorPtr);
            for (int jj = MatrixIndexBase; jj < MatrixIndexBase + numEqs; ++jj)
            {
                inputs(jj) += (K1(jj)
                                 + 2.0 * K2(jj)
                                 + 2.0 * K3(jj)
                                 + K4(jj)) / 6.0;
            }
            t = timeInitial + ii * h;
            output(MatrixIndexBase + ii,MatrixIndexBase) = t.GetSeconds();
            output(MatrixIndexBase + ii,_(MatrixIndexBase+1,MatrixIndexBase+numEqs)) = ~inputs;	
	}
	return output;
}
} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: RungeKuttaIntegrator.cpp,v $
*	Revision 1.7  2003/05/22 02:59:15  nilspace
*	Updated comments. Changed to pass in pointers to Orbit & Attitude objects.
*	
*	Revision 1.6  2003/05/13 18:58:27  nilspace
*	Cleaned up comments.
*	
*	Revision 1.5  2003/04/27 22:04:34  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.4  2003/04/25 14:15:06  nilspace
*	Created a temporary vectro<ssfTime> to prevent the STL .begin() and .end() functions from discarding the const-ness of _propTime in Integrate().
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
*	
*
******************************************************************************/

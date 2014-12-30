//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file RungeKutta.h
*  \brief Runge-Kutta integrator.
*  \author $Author: rsharo $
*  \version $Revision: 1.4 $
*  \date    $Date: 2003/10/18 21:37:28 $
//////////////////////////////////////////////////////////////////////////////////////////////////
*  \todo Add test cases
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef RUNGEKUTTA_H
#define RUNGEKUTTA_H

#include <Matrix.h>

/*! defines a pointer to a Runge-Kutta right-hand side (RHS) function */
typedef Vector(*ptr2RKFunc)(const double &_time, const Vector &_states, const Matrix &_params);

/** 
* Integrate an equation of the form \f$\dot{y} = f\left(t,x\right)\f$ using the Runge-Kutta integration method.
* \detail The Runge-Kutta integrator uses a right-hand side equation, \f$f\left(t,x\right)\f$ to compute the integration of the function over the specified time interval, given initial conditions, constants of integration, and number of steps desired (since this is a fixed step integrator).
* @param odeFunc Pointer to the right-hand side (RHS) equation
*	@param timeInput time of current step to RHS file function
*	@param stateInput vector of state inputs at current step to RHS file function
*	@param constantsInput vector of constants that are not integrated and passed to the RHS function
* @param _initialConditions vector of initial conditions of the state
* @param _constants matrix of constants that should be passed to the RHS function
* @param _timeInitial initial time of integration
* @param _timeFinal final time of integration
* @param _numSteps number of steps to integrate over (therefore timeStep = _timeFinal - _timeInitial / _numSteps)
* @return matrix of integrated state outputs from the initial to final times. Format:
/f[
    \begin{bmatrix}
    t_0 & x_{1,0} & x_{2,0} & ...\\
    t_1 & x_{1,1} & x_{2,1} & ...\\
    t_2 & x_{1,2} & x_{2,2} & ...\\
    . & . & . & . \\
    t_final & x_{1,f} & x_{2,f} & ...
    \end{bmatrix}
/f]
where /f$t_T/f$ is the time at step T, and /f$x_{i,T}/f$ is the state value of element i, at time step T.
*/
inline Matrix RungeKuttaSolve(Vector (*odeFunc)(const double &timeInput, const Vector &stateInput, const Matrix &constantsInput), const Vector &_initialConditions, const Matrix &_constants, const double &_timeInitial, const double &_timeFinal, const int &_numSteps)
{
	double h = (_timeFinal - _timeInitial) / _numSteps;
	double t = _timeInitial;
	int numEqs = _initialConditions.getIndexCount();
	Vector inputs(numEqs); inputs = _initialConditions;
	Vector K1(numEqs);
	Vector K2(numEqs);
	Vector K3(numEqs);
	Vector K4(numEqs);

	Matrix output(_numSteps + 1, numEqs + 1);

	output(MatrixIndexBase,MatrixIndexBase) = _timeInitial;
	output(MatrixIndexBase,_(MatrixIndexBase+1,MatrixIndexBase+numEqs)) = ~_initialConditions;

	Vector temp(numEqs);
        for (int ii = 1; ii <= _numSteps; ++ii)
        {
            K1 = h * odeFunc(t, inputs, _constants);
            temp = inputs + K1 / 2.0;
            K2 = h * odeFunc(t + h/2, temp, _constants);
            temp = inputs + K2 / 2.0;
            K3 = h * odeFunc(t + h/2, temp, _constants);
            temp = inputs + K3;
            K4 = h * odeFunc(t + h, temp, _constants);
            for (int jj = MatrixIndexBase; jj < MatrixIndexBase + numEqs; ++jj)
            {
                inputs(jj) += (K1(jj)
                                 + 2.0 * K2(jj)
                                 + 2.0 * K3(jj)
                                 + K4(jj)) / 6.0;			
            }
            t = _timeInitial + ii * h;
            output(MatrixIndexBase + ii,MatrixIndexBase) = t;
            output(MatrixIndexBase + ii,_(MatrixIndexBase+1,MatrixIndexBase+numEqs)) = ~inputs;	
	}
	return output;
}


#endif /* RungeKutta */

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: RungeKutta.h,v $
*	Revision 1.4  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.3  2003/04/23 16:30:59  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.2  2003/03/26 16:38:58  nilspace
*	Updated comments to better work with Doxygen.
*	
*	Revision 1.1  2003/03/05 20:41:04  nilspace
*	Initial submission of example source code file.
*	
*
******************************************************************************/

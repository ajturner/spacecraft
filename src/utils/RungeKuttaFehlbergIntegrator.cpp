//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file RungeKuttaFehlbergIntegrator.cpp
*  \brief Implementation of the Runge-Kutta-Fehlberg Fourth Order integrator.
*  \author $Author: nilspace $
*  \version $Revision: 1.5 $
*  \date    $Date: 2003/06/05 20:30:52 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \warning NOT VERIFIED
*  \todo Add test cases
*/
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "RungeKuttaFehlbergIntegrator.h"
namespace O_SESSAME {

RungeKuttaFehlbergIntegrator::RungeKuttaFehlbergIntegrator() : m_Tolerance(0.00001), m_minStepSize(0.01), m_maxStepSize(0.25)
{
}

Matrix RungeKuttaFehlbergIntegrator::Integrate(const vector<ssfTime>& _propTime, odeFunctor _odeFunctorPtr, const Vector& _initialConditions, Orbit* _pOrbit, Attitude* _pAttitude, const Matrix& _constants, const Functor& _functorPtr)
{
        vector<ssfTime>::const_iterator timeIterator = _propTime.begin();

        ssfTime timeInitial = (*timeIterator);
        timeIterator = _propTime.end() - 1;
        ssfTime timeFinal = (*timeIterator);
        ssfTime t = timeInitial;
        double h = m_maxStepSize;
        double delta;
        bool hAccepted = false;
        
	int numEqs = _initialConditions.getIndexCount();
	Vector inputs = _initialConditions;
        Vector tempVector = inputs;
        Vector Error(numEqs);
	Vector K1(numEqs);
	Vector K2(numEqs);
	Vector K3(numEqs);
	Vector K4(numEqs);
	Vector K5(numEqs);	
        Vector K6(numEqs);
	vector<Vector> output; // state + time
        output.reserve(floor((timeFinal-timeInitial) / m_maxStepSize));
    
        output.push_back(Vector(numEqs+1));
	output[0](MatrixIndexBase) = timeInitial.GetSeconds();
	output[0](_(MatrixIndexBase+1,MatrixIndexBase+numEqs)) = _initialConditions;

        ssfTime tTemp;
	Vector temp(numEqs);
        int ii = 1;
        while (t.GetSeconds() < timeFinal.GetSeconds())
        {
            hAccepted = true;
            K1 = h * _odeFunctorPtr(t, inputs, _pOrbit, _pAttitude, _constants, _functorPtr);
            tTemp = t + h / 4.;		temp = inputs + K1 / 4.0; 
            K2 = h * _odeFunctorPtr(tTemp, temp, _pOrbit, _pAttitude, _constants, _functorPtr);
            tTemp = t + 3/8. * h;	temp = inputs + (3/32. * K1 + 9/32. * K2); 		 	
            K3 = h * _odeFunctorPtr(tTemp, temp, _pOrbit, _pAttitude, _constants, _functorPtr);
            tTemp = t + 12/13. * h;	temp = inputs + (1932. * K1 - 7200. * K2 + 7296. * K3) / 2197.; 		 	
            K4 = h * _odeFunctorPtr(tTemp, temp, _pOrbit, _pAttitude, _constants, _functorPtr);
            tTemp = t + h;		temp = inputs + (439/216. * K1 - 8. * K2 +3680/513. * K3 - 845/4104. * K4); 		 	
            K5 = h * _odeFunctorPtr(tTemp, temp, _pOrbit, _pAttitude, _constants, _functorPtr);
            tTemp = t + h / 2;		temp = inputs - 8/27. * K1 +2. * K2 - 3544/2565. * K3 + 1859/4104. * K4 - 11/40./*0.275*/* K5; 
            K6 = h * _odeFunctorPtr(tTemp, temp, _pOrbit, _pAttitude, _constants, _functorPtr);

            // Check that all the variables are within tolerance
            for (int jj = MatrixIndexBase; jj < MatrixIndexBase + numEqs; ++jj)
            {
                //  If error <= tolerance, calculate integral & output
                Error(jj) = 1/h * abs(K1(jj)/360. - 128/4275. * K3(jj) - 2197/75240. * K4(jj) + K5(jj)/50. + K6(jj)/27.5);

//	Could be used for testing
//                wTilda = 16/135*K1(jj) + 6656/12825 * K3(jj) + 28561/56430 * K4(jj) - 9/50 * K5(jj) + 2/55*K6(jj);
//                w = 25/216 * K1(jj) + 1408/2565 * K3(jj) + 2197/4104 * K4(jj) - 0.2* K5(jj);
//                Error(jj) = abs(wTilda - w);
                
                if((Error(jj) <= m_Tolerance) || (h < m_minStepSize))
                {
                        tempVector(jj) = inputs(jj) + 25/216. * K1(jj) + 1408/2565. * K3(jj) + 2197/4104. * K4(jj) - 0.2* K5(jj);
                }
                else
                {// if error > tolerance, calc new step size, and re-integrate this step
                    hAccepted = false;
                    delta = 0.84 * pow((m_Tolerance / Error(jj)), 0.25);
                    if(delta <= 0.1)
                        h = 0.1*h;
                    else if(delta > 4)
                        h = 4*h;
                    else
                        h = delta * h;
                    if (h > m_maxStepSize)
                        h = m_maxStepSize;
                    break;
                }
            }
            // if all variables are within tolerance, then save output and step forward
            if(hAccepted)
            {
                t = t + h;
                inputs = tempVector;
                output.push_back(Vector(numEqs+1));
                output[ii](MatrixIndexBase) = t.GetSeconds();
                output[ii](_(MatrixIndexBase+1,MatrixIndexBase+numEqs)) = inputs;
                ++ii;
                
                if(t.GetSeconds() + h > timeFinal.GetSeconds())
                    h = timeFinal - t;
            }

	}
    
        // Because we used a dynamic vector<Vector>, we need to move this a Matrix    
        Matrix outputMatrix(output.size(), numEqs + 1);
            
        for(ii = 0; ii < output.size(); ++ii)
        {
            outputMatrix(MatrixIndexBase + ii,_) = ~output[ii](_); 
        }
	return outputMatrix;
}
} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: RungeKuttaFehlbergIntegrator.cpp,v $
*	Revision 1.5  2003/06/05 20:30:52  nilspace
*	Removed testing cout commands.
*	
*	Revision 1.4  2003/06/05 20:09:14  nilspace
*	Finished implementation and verified against a short 2 second integration.
*	
*	Revision 1.3  2003/05/22 02:59:15  nilspace
*	Updated comments. Changed to pass in pointers to Orbit & Attitude objects.
*	
*	Revision 1.2  2003/04/25 13:45:55  nilspace
*	const'd Get() functions.
*	
*	Revision 1.1  2003/04/23 15:08:28  nilspace
*	Initial submission of RKF integrator.
*	
*	
******************************************************************************/



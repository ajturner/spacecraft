//////////////////////////////////////////////////////////////////////////////////////////////////
/*!\file RungeKuttaFehlbergIntegrator.h
*  \brief Runge-Kutta-Fehlberg integrator.
*  \author $Author: nilspace $
*  \version $Revision: 1.5 $
*  \date    $Date: 2003/06/05 20:09:14 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*   
* \todo Add test cases
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_RUNGEKUTTAFEHLBERG_INTEGRATOR_H__
#define __SSF_RUNGEKUTTAFEHLBERG_INTEGRATOR_H__

#include "Matrix.h"
#include "Integrator.h"
namespace O_SESSAME {
/*! \brief Runge-Kutta-Fehlberg integrator 
* \ingroup IntegrationLibrary
*
* \warning Implementation not complete!
* \todo document algorithm 
*/
class RungeKuttaFehlbergIntegrator : public Integrator 
{
public:
    RungeKuttaFehlbergIntegrator();
    
     /*! Specific Orbit/Attitude simulation integration function 
     * 
     */
    Matrix Integrate(const vector<ssfTime>& _propTime, odeFunctor _odeFunctorPtr, const Vector& _initialConditions, Orbit* _pOrbit, Attitude* _pAttitude, const Matrix& _constants, const Functor& _functorPtr);

    /*! \brief Set the tolerance of the integration.
        * @param _numSteps number of steps to include between integration timesteps
        */
    void SetTolerance(const double& _Tolerance) 	{ m_Tolerance = _Tolerance; return; }
    
    /*! \brief Return the tolerance of the integration
        * @return tolerance of the integration 
        */
    double GetTolerance() 				{ return m_Tolerance; }
    
    /*! \brief Set the minimum and maximum step-sizes.
        * @param _minStepSize minimum step-size between integration meshpoints.
        * @param _maxStepSize maximum step-size between integration meshpoints.
        */
    void SetStepSizes(const double& _minStepSize, const double& _maxStepSize) 	{ m_minStepSize = _minStepSize; m_maxStepSize = _maxStepSize; return; }
    
private:
    double m_Tolerance;	 /*!< Desired tolerance of the integration between timesteps */
    double m_minStepSize; /*!< minimum step-size between integration calculation meshpoints */
    double m_maxStepSize; /*!< maximum step-size between integration calculation meshpoints */
};
} // close namespace O_SESSAME

#endif 
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: RungeKuttaFehlbergIntegrator.h,v $
*	Revision 1.5  2003/06/05 20:09:14  nilspace
*	Finished implementation and verified against a short 2 second integration.
*	
*	Revision 1.4  2003/05/22 02:59:15  nilspace
*	Updated comments. Changed to pass in pointers to Orbit & Attitude objects.
*	
*	Revision 1.3  2003/05/13 18:58:27  nilspace
*	Cleaned up comments.
*	
*	Revision 1.2  2003/04/25 13:45:55  nilspace
*	const'd Get() functions.
*	
*	Revision 1.1  2003/04/23 15:08:28  nilspace
*	Initial submission of RKF integrator.
*	
*	
******************************************************************************/

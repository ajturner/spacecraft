#include "Time.h"
#include "RungeKuttaFehlbergIntegrator.h"
#include "RungeKuttaIntegrator.h"
#include "Matrix.h"
#include <iostream>

using namespace std;
using namespace O_SESSAME;
// Torque function that will be called each timestep
Vector NullFunctor(const ssfTime& _pSSFTime, const OrbitState& _pOrbitState, const AttitudeState& _pAttitudeState)
{
    return Vector(3);
}

Vector testRKFunc(const ssfTime &_time, const Vector& _integratingState, Orbit *_Orbit, Attitude *_Attitude, const Matrix &_parameters, const Functor &_forceFunctorPtr)
{
    static Vector returnVal(1);
    returnVal(1) = _integratingState(1) - pow(_time.GetSeconds(),2) + 1;
    return returnVal;
}
Vector testRKFunc2(const ssfTime &_time, const Vector& _integratingState, Orbit *_Orbit, Attitude *_Attitude, const Matrix &_parameters, const Functor &_forceFunctorPtr)
{
    static Vector returnVal(1);
    returnVal(1) = _integratingState(1) - pow(_time.GetSeconds(),3) + 1;
    return returnVal;
}
int main()
{
    //////////////////////////////////////////////////
    // Setup an integrator and any special parameters
    RungeKuttaIntegrator myRK4Integrator; 
    myRK4Integrator.SetNumSteps(10);
    
    // Integration times
    vector<ssfTime> integrationTimes;
    ssfTime begin(0);
    ssfTime end(begin + 2);
    integrationTimes.push_back(begin);
    integrationTimes.push_back(end);

    SpecificFunctor NothingFunctor(&NullFunctor);
    Matrix Parameters(1,1);
    
    Vector initConditions(1);
    initConditions(1) = 0.5;
        
    //////////////////////////////////////////////////
    // Setup an integrator and any special parameters
    RungeKuttaFehlbergIntegrator myRK5Integrator; 
    myRK5Integrator.SetTolerance(0.0001);

    // Integration times
    
    ///////////////////////////////////////////////
    // Integrate over the desired time interval
    tick();
    Matrix RK5History = myRK5Integrator.Integrate(
                            integrationTimes, 		// seconds
                            &testRKFunc, 
                            initConditions,
                            NULL,
                            NULL,
                            Parameters,
                            NothingFunctor
                        );
    cout << "finished propagating in " << tock() << " seconds." << endl;
                            
                        
                        
    cout << "RK-4(5) output: " << endl << setprecision(15) <<RK5History;
    
    
    
    ///////////////////////////////////////////////
    // Integrate over the desired time interval
    tick();
    Matrix RK4History = myRK4Integrator.Integrate(
                            integrationTimes, 		// seconds
                            &testRKFunc, 
                            initConditions,
                            NULL,
                            NULL,
                            Parameters,
                            NothingFunctor
                        );
    cout << "finished propagating in " << tock() << " seconds." << endl;
                            
                        
     ///////////////////////////////////////////////
    // Integrate over the desired time interval
    tick();
    Matrix RK4History2 = myRK4Integrator.Integrate(
                            integrationTimes, 		// seconds
                            &testRKFunc2, 
                            initConditions,
                            NULL,
                            NULL,
                            Parameters,
                            NothingFunctor
                        );
    cout << "finished propagating in " << tock() << " seconds." << endl;                       
    cout << "RK-4 output: " << endl << setprecision(15) << RK4History;
    cout << "RK-4 output2: " << endl << setprecision(15) << RK4History2;

    return 0;
}


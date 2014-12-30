//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file testEnvironment.cpp
*  \brief Sample of an orbit integration and an Environment object using components of the SSF.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/08/24 20:59:13 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "orbitmodels/TwoBodyDynamics.h"
#include "Matrix.h"
#include "RungeKuttaIntegrator.h"
#include "PositionVelocity.h"
#include "Plot.h"
#include "Environment.h"
#include "OrbitStateRepresentation.h"
#include "EarthCentralBody.h"
#include "OrbitState.h"
#include "orbitframes/OrbitFrameIJK.h"

// Force function that will be called each timestep
Vector GravityForceFunction(ssfTime* _currentTime, OrbitState* _currentOrbitState, AttitudeState* _currentAttitudeState, EnvFuncParamaterType _parameterList)
{
    Vector state = _currentOrbitState->GetState();
    Vector Forces(3);
    Vector Position(3); Position(_) = state(_(VectorIndexBase,VectorIndexBase+2));
    Forces = -398600.441 / pow(norm2(Position),3) * Position;
    return Forces;
}

Vector DragForceFunction(ssfTime* _currentTime, OrbitState* _currentOrbitState, AttitudeState* _currentAttitudeState, EnvFuncParamaterType _parameterList)
{
    Vector Forces(3);
    double BC = *(reinterpret_cast<double*>(_parameterList[1]));
    Vector Vrel(3); Vrel = _currentOrbitState->GetState()(_(VectorIndexBase+3,VectorIndexBase+5));
    double Vrel_mag = norm2(Vrel);
    Forces = -1/2 *1 / BC * pow(Vrel_mag,2) * Vrel / Vrel_mag; 
    return Forces;
}

int main()
{
    // Setup an integrator and any special parameters
    RungeKuttaIntegrator myIntegrator; 
        int numOrbits = 10;
        int numSteps = 100;
  
    cout << "Number of Orbits: " << flush;
    cin >> numOrbits;
    cout << "Number of Integration Steps: "<< flush;
    cin >> numSteps;

    myIntegrator.SetNumSteps(numSteps);
    
    // Create & initialize an orbit type
    OrbitState myOrbit;
    myOrbit.SetStateRepresentation(new PositionVelocity);
    myOrbit.SetOrbitFrame(new OrbitFrameIJK);
    Vector initPV(6);
        initPV(VectorIndexBase+0) = -5776.6; // km/s
        initPV(VectorIndexBase+1) = -157; // km/s        
        initPV(VectorIndexBase+2) = 3496.9; // km/s    
        initPV(VectorIndexBase+3) = -2.595;  // km/s
        initPV(VectorIndexBase+4) = -5.651;  // km/s        
        initPV(VectorIndexBase+5) = -4.513; // km/s
    myOrbit.SetState(initPV);
    
    AttitudeState myAttitude;
    myAttitude.SetRotation(Rotation(Quaternion(0,0,0,1)));
    
    // Create the matrix of parameters needed for the RHS
    Matrix Parameters(1,1);
    Parameters(MatrixIndexBase,MatrixIndexBase) = 398600.441; //km / s^2

    
    // ENVIRONMENT TESTING
    Environment* pEarthEnv = new Environment;
    EarthCentralBody *pCBEarth = new EarthCentralBody;
    pEarthEnv->SetCentralBody(pCBEarth);
    cout << "Filling Parameters" << endl;
    EnvFunction TwoBodyGravity(&GravityForceFunction);
    pEarthEnv->AddForceFunction(TwoBodyGravity);
    EnvFunction DragForce(&DragForceFunction);
    double BC = 200;
    DragForce.AddParameter(reinterpret_cast<void*>(&BC), 1);
    pEarthEnv->AddForceFunction(DragForce);
    cout << "Finished Setting up Earth Environment" << endl;


    vector<ssfTime> integrationTimes;
    ssfTime begin(Now());
    ssfTime end(begin + 92*60*numOrbits);
    integrationTimes.push_back(begin);
    integrationTimes.push_back(end);
    cout << "PropTime = " << begin.GetSeconds() << " s -> " << end.GetSeconds() << " s" << endl;
    cout << "Orbit State: " << ~myOrbit.GetState() << endl;

    ObjectFunctor<Environment> OrbitForcesFunctor(pEarthEnv, &Environment::GetForces);
    // Integrate over the desired time interval
    tick();
    Matrix history = myIntegrator.Integrate(
                            integrationTimes, 		// seconds
                            &TwoBodyDynamics, 
                            myOrbit.GetState(),
                            NULL,
                            NULL,
                            Parameters,
                            OrbitForcesFunctor
                        );

    cout << "finished propagating in " << tock() << " seconds." << endl;                                 
    // Output the flight history
    //cout << history;
    Matrix plotting = history(_,_(MatrixIndexBase+1,MatrixIndexBase+3));

    Plot3D(plotting);
    delete pEarthEnv;
    
    return 0;
                            
}

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: testEnvironment.cpp,v $
*	Revision 1.2  2003/08/24 20:59:13  nilspace
*	Updated.
*	
*	Revision 1.1  2003/04/08 23:06:26  nilspace
*	Initial Submission.
*	
*
******************************************************************************/

                        

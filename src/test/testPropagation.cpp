//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file testPropagation.cpp
*  \brief Sample of an orbit and attitude propagation using components of the SSF.
*  \author $Author: nilspace $
*  \version $Revision: 1.4 $
*  \date    $Date: 2003/05/27 17:47:13 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "Matrix.h"
#include "Rotation.h"
#include "Attitude.h"
#include "Orbit.h"
#include "CombinedNumericPropagator.h"
#include "RungeKuttaIntegrator.h"
#include "orbitmodels/TwoBodyDynamics.h"
#include "EarthCentralBody.h"
#include "OrbitState.h"
#include "AttitudeState.h"
#include "orbitstaterep/PositionVelocity.h"
#include "orbitframes/OrbitFrameIJK.h"
#include "Plot.h"
using namespace O_SESSAME;

NumericPropagator* SetupPropagator();
Environment* SetupEnvironment();
Orbit* SetupOrbit();
Attitude* SetupAttitude();
void myOrbitStateConvFunc(const Matrix &_meshPoint, OrbitState &_convertedOrbitState);
void myAttitudeStateConvFunc(const Matrix &_meshPoint, AttitudeState &_convertedAttitudeState);

int main()
{
    cout << "Calling SetupOrbit()" << endl;
    Orbit* myOrbit = SetupOrbit();
    cout << "Calling SetupAttitude()" << endl;
    Attitude* myAttitude = SetupAttitude();
    
    // Setup Propagator
    cout << "Calling SetupPropagator()" << endl;
    NumericPropagator* myPropagator = SetupPropagator();
    myOrbit->SetPropagator(myPropagator);
    myAttitude->SetPropagator(myPropagator);

    // Setup external environment
    cout << "Calling SetupEnvironment()" << endl;
    Environment* myEnvironment = SetupEnvironment();
    myOrbit->SetEnvironment(myEnvironment);
    myAttitude->SetEnvironment(myEnvironment);

    // Integration Times
    double numOrbits = 1/10.0;
    cout << "Number of Orbits: " << flush;
//        cin >> numOrbits;
    vector<ssfTime> integrationTimes;
    ssfTime begin(0);
    ssfTime end(begin + 92*60*numOrbits);
    integrationTimes.push_back(begin);
    integrationTimes.push_back(end);
    cout << "PropTime = " << begin.GetSeconds() << " s -> " << end.GetSeconds() << " s" << endl;
    cout << "Orbit State: " << ~myOrbit->GetStateObject().GetState() << endl;
    cout << "Attitude State: " << ~myAttitude->GetStateObject().GetState() << endl;

    // Integrate over the desired time interval
    tick();
    myPropagator->Propagate(integrationTimes, myOrbit->GetStateObject().GetState(), myAttitude->GetStateObject().GetState());
    ssfSeconds calcTime = tock();
    cout << "finished propagating in " << calcTime << " seconds." << endl;                                 

for (int ii = 0; ii < 2 ; ++ii)
{
    // Integrate again
    integrationTimes[0] = integrationTimes[1];
    integrationTimes[1] = integrationTimes[0] + 92*60*numOrbits;
    cout << integrationTimes[0] << " -> " << integrationTimes[1] << endl;
    myPropagator->Propagate(integrationTimes, myOrbit->GetStateObject().GetState(), myAttitude->GetStateObject().GetState());
}

    Matrix orbitHistory = myOrbit->GetHistory().GetHistory();
    Matrix orbitPlotting = orbitHistory(_,_(MatrixIndexBase+1,MatrixIndexBase+3));
    Matrix attitudeHistory = myAttitude->GetHistory().GetHistory();
    Matrix attitudePlotting = attitudeHistory(_,_(MatrixIndexBase,MatrixIndexBase+4));


    Plot3D(orbitPlotting);
//    Plot attitudePlot(attitudePlotting);
    Plot2D(attitudePlotting);
   
    // Store the output to file
    ofstream ofile;
    ofile.open("OrbitHistory.dat");
    ofile << myOrbit->GetHistory().GetHistory();
    ofile.close();
    
    ofile.open("AttitudeHistory.dat");
    ofile << myAttitude->GetHistory().GetHistory();
    ofile.close();

    return 0;
                            
}

// *************************
// ****** ENVIRONMENT ****** 
// *************************
// Force function that will be called each timestep
Vector GravityForceFunction(const ssfTime &_currentTime, const OrbitState  &_currentOrbitState, const AttitudeState &_currentAttitudeState, const EnvFuncParamaterType &_parameterList)
{
//    Vector state = _currentOrbitState.GetState();
    static Vector Forces(3);
//    Vector Position(3); Position(_) = state(_(VectorIndexBase,VectorIndexBase+2));
    static Vector Position(3); Position(_) = _currentOrbitState.GetState()(_(VectorIndexBase,VectorIndexBase+2));
    Forces = -398600.441 / pow(norm2(Position),3) * Position;
    return Forces;
}

Vector DragForceFunction(const ssfTime &_currentTime, const OrbitState &_currentOrbitState, const AttitudeState &_currentAttitudeState, const EnvFuncParamaterType &_parameterList)
{
    static Vector Forces(3);
    double BC = *(reinterpret_cast<double*>(_parameterList[0]));
    static Vector Vrel(3); Vrel(_) = _currentOrbitState.GetState()(_(VectorIndexBase+3,VectorIndexBase+5));
    double Vrel_mag = norm2(Vrel);
    double rho = *(reinterpret_cast<double*>(_parameterList[1]));
    Forces = -1/2 * rho / BC * pow(Vrel_mag,2) * Vrel / Vrel_mag; 
    return Forces;
}

Environment* SetupEnvironment()
{
    // ENVIRONMENT TESTING
    Environment* pEarthEnv = new Environment;
    EarthCentralBody *pCBEarth = new EarthCentralBody;
    pEarthEnv->SetCentralBody(pCBEarth);
    
    // Add Gravity force function
    cout << "Filling Parameters" << endl;
    EnvFunction TwoBodyGravity(&GravityForceFunction);
    pEarthEnv->AddForceFunction(TwoBodyGravity);
    
    // Add Drag Force Function
    EnvFunction DragForce(&DragForceFunction);
    double *BC = new double(200);
    DragForce.AddParameter(reinterpret_cast<void*>(BC), 1);
    double *rho = new double(1.13 * pow(static_cast<double>(10), static_cast<double>(-12))); // kg/m^3
    DragForce.AddParameter(reinterpret_cast<void*>(rho), 2);
    pEarthEnv->AddForceFunction(DragForce);
    
    cout << "Finished Setting up Earth Environment" << endl;
    return pEarthEnv;
}

// *************************
// ****** PROPAGATOR ******* 
// ************************* 
NumericPropagator* SetupPropagator()
{
    CombinedNumericPropagator* myProp = new CombinedNumericPropagator;
    
    // Create & setup the integator
        // Setup an integrator and any special parameters
    RungeKuttaIntegrator* orbitIntegrator = new RungeKuttaIntegrator; 
    RungeKuttaIntegrator* attitudeIntegrator = new RungeKuttaIntegrator; 

    orbitIntegrator->SetNumSteps(100);
    myProp->SetOrbitIntegrator(orbitIntegrator);
    attitudeIntegrator->SetNumSteps(1000);
    myProp->SetAttitudeIntegrator(attitudeIntegrator);
    
    myProp->SetOrbitStateConversion(&myOrbitStateConvFunc);
    myProp->SetAttitudeStateConversion(&myAttitudeStateConvFunc);
    return myProp;
}

// *************************
// ********* ORBIT ********* 
// ************************* 
void myOrbitStateConvFunc(const Matrix &_meshPoint, OrbitState &_convertedOrbitState)
{
    static Vector tempVector(_meshPoint[MatrixColsIndex].getIndexBound() - 1);
    tempVector(_) = ~_meshPoint(_,_(MatrixIndexBase+1, _meshPoint[MatrixColsIndex].getIndexBound()));
    _convertedOrbitState.SetState(tempVector);
    return;
}

Orbit* SetupOrbit()
{
    Orbit* myOrbit = new Orbit;
    
    // Create & initialize the orbit
    OrbitState myOrbitState;
    myOrbitState.SetStateRepresentation(new PositionVelocity);
    myOrbitState.SetOrbitFrame(new OrbitFrameIJK);
    Vector initPV(6);
        // Space station
        initPV(VectorIndexBase+0) = -5776.6; // km
        initPV(VectorIndexBase+1) = -157; // km       
        initPV(VectorIndexBase+2) = 3496.9; // km    
        initPV(VectorIndexBase+3) = -2.595;  // km/s
        initPV(VectorIndexBase+4) = -5.651;  // km/s        
        initPV(VectorIndexBase+5) = -4.513; // km/s
    myOrbitState.SetState(initPV);
    myOrbit->SetStateObject(myOrbitState);
    
    myOrbit->SetDynamicsEq(&TwoBodyDynamics);
    
    // Setup Parameters (ie mass, etc)
    Matrix Parameters(1,1);
    Parameters(MatrixIndexBase,MatrixIndexBase) = 398600.441; //km / s^2
    myOrbit->SetParameters(Parameters);
    return myOrbit;
}


// *************************
// ******* ATTITUDE ******** 
// ************************* 
void myAttitudeStateConvFunc(const Matrix &_meshPoint, AttitudeState &_convertedAttitudeState)
{
    static Vector tempQ(4); tempQ(_) = ~_meshPoint(_,_(2, 5));
    static Vector tempVector(3); tempVector(_) = ~_meshPoint(1, _(6, 8));
    _convertedAttitudeState.SetState(Rotation(Quaternion(tempQ)), tempVector);
    return;
}
static Vector AttituteDynamics(const ssfTime &_time, const Vector& _integratingState, Orbit *_Orbit, Attitude *_Attitude, const Matrix &_parameters, const Functor &_forceFunctorPtr)
{
    static Vector stateDot(7);
    static Matrix bMOI(3,3); 
    static Matrix qtemp(4,3); 
    static Matrix Tmoment(3,1);
    static Vector qIn(4); 
    static Vector wIn(3);
    qIn = _integratingState(_(VectorIndexBase,VectorIndexBase + 3));
    wIn = _integratingState(_(VectorIndexBase + 4,VectorIndexBase + 6));
    qIn /= norm2(qIn);

//    _attitudeState->SetState(Rotation(Quaternion(qIn)), wIn);  // Need to speed up in some way
    qtemp(_(VectorIndexBase+0,VectorIndexBase+2),_(VectorIndexBase+0,VectorIndexBase+2)) = skew(qIn(_(VectorIndexBase+0,VectorIndexBase+2))) + qIn(VectorIndexBase+3) * eye(3);
    qtemp(VectorIndexBase+3, _(VectorIndexBase+0,VectorIndexBase+2)) = -(~qIn(_(VectorIndexBase+0,VectorIndexBase+2)));
    qtemp(_,MatrixIndexBase) = 0.5 * qtemp * wIn;

    bMOI = _parameters(_(MatrixIndexBase+0,MatrixIndexBase+2),_(MatrixIndexBase+0,MatrixIndexBase+2));
    Tmoment(_,_) = (_forceFunctorPtr.Call(_time, _Orbit->GetStateObject(), _Attitude->GetStateObject()))(_);
    Tmoment = (bMOI.inverse() * (Tmoment - skew(wIn) * (bMOI * wIn)));
    
    stateDot(_(VectorIndexBase,VectorIndexBase + 3)) = qtemp(_,MatrixIndexBase);
    stateDot(_(VectorIndexBase + 4,VectorIndexBase + 6)) = Tmoment(_,MatrixIndexBase);

    return stateDot;
}

Attitude* SetupAttitude()
{
    Attitude* myAttitude = new Attitude;
    
    AttitudeState myAttitudeState;
    myAttitudeState.SetRotation(Rotation(Quaternion(0,0,0,1)));
    Vector initAngVelVector(3);
        initAngVelVector(1) = 0.1;
    myAttitudeState.SetAngularVelocity(initAngVelVector);

    myAttitude->SetStateObject(myAttitudeState);
    myAttitude->SetDynamicsEq(&AttituteDynamics);
    myAttitude->SetParameters(eye(3));
    
    return myAttitude;
    
}

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: testPropagation.cpp,v $
*	Revision 1.4  2003/05/27 17:47:13  nilspace
*	Updated example to have seperate orbit & attitude integrators.
*	
*	Revision 1.3  2003/05/20 19:24:43  nilspace
*	Updated.
*	
*	Revision 1.2  2003/05/13 18:57:32  nilspace
*	Clened up to work with new Propagators.
*	
*	Revision 1.1  2003/05/01 02:42:47  nilspace
*	New propagation test file.
*	
*
******************************************************************************/

                        

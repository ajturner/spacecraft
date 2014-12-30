//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file testInterface.cpp
*  \brief Uses a text-based user interface to step through running a simulation.
*  \author $Author: nilspace $
*  \version $Revision: 1.5 $
*  \date    $Date: 2003/10/18 13:58:02 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*!  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "Matrix.h"
#include "Rotation.h"
#include "Attitude.h"
#include "Orbit.h"
#include "CombinedNumericPropagator.h"
#include "RungeKuttaFehlbergIntegrator.h"
#include "orbitmodels/TwoBodyDynamics.h"
#include "CentralBody/EarthCentralBody.h"
#include "OrbitState.h"
#include "AttitudeState.h"
#include "orbitstaterep/PositionVelocity.h"
#include "orbitframes/OrbitFrameIJK.h"
#include "Disturbances/GravityFunctions.h"
#include "Disturbances/SimpleAerodynamicDisturbances.h"
#include "Plot.h"
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace O_SESSAME;

// Global Variables
static Orbit* myOrbit = NULL;
static Attitude* myAttitude = NULL;
static Environment* myEnvironment = NULL;
static CombinedNumericPropagator* myPropagator = NULL;
static RungeKuttaFehlbergIntegrator* orbitIntegrator = NULL; 
static RungeKuttaFehlbergIntegrator* attitudeIntegrator = NULL; 
static vector<ssfTime> propTimes;

void SetupPropagator();
void SetupEnvironment();
void SetupOrbit();
void SetupAttitude();

void ChangePropagator();
void ChangeEnvironment();
void ChangeOrbit();
void ChangeOrbitIntegrator();
void ChangeAttitude();
void ChangeAttitudeIntegrator();

void Propagate(); 
void Plot();

Vector SimpleController(const ssfTime &_currentTime, const OrbitState &_currentOrbitState, const AttitudeState &_currentAttitudeState, const EnvFuncParamaterType &_parameterList);
void myOrbitStateConvFunc(const Matrix &_meshPoint, OrbitState &_convertedOrbitState);
void myAttitudeStateConvFunc(const Matrix &_meshPoint, AttitudeState &_convertedAttitudeState);

void DisplayOrbit()
{
    if(myOrbit->IsIntegrateable())
        cout << "Orbit State (km, km/s): " << ~myOrbit->GetStateObject().GetStateRepresentation()->GetPositionVelocity() << endl;
    else
        cout << "Orbit State: [ uninitialized ]" << endl;
    return;
}

void DisplayAttitude()
{
    if(myAttitude->IsIntegrateable())
        cout << "Attitude State: (-, rad/s)" << ~myAttitude->GetStateObject().GetState() << endl;
    else
        cout << "Attitude State: [ uninitialized ]" << endl;
    return;
}
void DisplayPropagator()
{
    if(myPropagator)
        cout << "Propagate times: [" << propTimes[0] << " -> " << propTimes[1] <<  "] (s)" << endl;
    else
        cout << "Propagate State: [ uninitialized ]" << endl;
    return;
}
int DisplayMenu()
{
    DisplayOrbit();
    DisplayAttitude();
    DisplayPropagator();
    cout << endl;
    cout << "[1] Setup Orbit" << endl;
    cout << "[2] Setup Orbit Integrator" << endl;
    cout << "[3] Setup Attitude" << endl;
    cout << "[4] Setup Attitude Integrator" << endl;
    cout << "[5] Setup Environment" << endl;
    cout << "[6] Setup Propagator" << endl;
    cout << "[7] Propagate" << endl;
    cout << "[8] Plot" << endl;
    cout << "[0] Exit" << endl;
    cout << endl << "Selection: " << flush;
    
    int selection;
    cin >> selection;
    return selection;
}

void Select()
{
    switch(DisplayMenu())
    {
        case 1: // ChangeOrbit
            ChangeOrbit();
            break;
        case 2:
            ChangePropagator();
            //ChangeOrbitIntegrator();
            break;
        case 3: 
            ChangeAttitude();
            break;
        case 4:
            ChangePropagator();
            //ChangeAttitudeIntegrator();
            break;
        case 5:
            ChangeEnvironment();
            break;
        case 6:
            ChangePropagator();
            break;
        case 7:
            Propagate();
            break;
        case 8:
            ::Plot();
            break;
        case 0:
            return;
            break;
        default:
            cout << "Incorrect Selection." << endl;
            break;
    }
    Select();

}
int main()
{
    SetupOrbit();
    SetupAttitude();
    SetupPropagator();
    myOrbit->SetPropagator(myPropagator);
    myAttitude->SetPropagator(myPropagator);

    SetupEnvironment();
    myOrbit->SetEnvironment(myEnvironment);
    myAttitude->SetEnvironment(myEnvironment);
   
   Select(); 
    // Store the output to file
    ofstream ofile;
    
    double requestTime;
    cout << "Output requested time (s): " << flush;
    cin >> requestTime;
    
    if(myOrbit)
        if (myOrbit->IsIntegrateable())
        {
            cout << "Orbit State (km, km/s): " << ~myOrbit->GetHistoryObject().GetState(requestTime).GetStateRepresentation()->GetPositionVelocity() << endl;
            ofile.open("OrbitHistory.dat");
            ofile << setprecision(15) << myOrbit->GetHistoryObject().GetHistory();
            ofile.close();
        }
    
    if(myAttitude)
        if (myAttitude->IsIntegrateable())
        {
            cout << "Attitude State: (-, rad/s)" << ~myAttitude->GetHistoryObject().GetState(requestTime).GetState() << endl;

            ofile.open("AttitudeHistory.dat");
            ofile << setprecision(15) << myAttitude->GetHistoryObject().GetHistory();
            ofile.close();
        }
    return 0;
                            
}

void Plot()
{
    if(myOrbit)
        if (myOrbit->IsIntegrateable())
        {
            Matrix orbitHistory = myOrbit->GetHistoryObject().GetHistory();
            Matrix orbitPlotting = orbitHistory(_,_(MatrixIndexBase+1,MatrixIndexBase+3));
            Plot3D(orbitPlotting);
        }
    if(myAttitude)
        if (myAttitude->IsIntegrateable())
        {
            Matrix attitudeHistory = myAttitude->GetHistoryObject().GetHistory();
            Matrix attitudePlotting = attitudeHistory(_,_(MatrixIndexBase,MatrixIndexBase+4));
            Plot2D(attitudePlotting);
        }

}

void Propagate()
{

    cout << "PropTime = " << propTimes[0].GetSeconds() << " s -> " << propTimes[1].GetSeconds() << " s" << endl;
    Vector orbInitState(6);
    Vector attInitState(7);
    if(myOrbit->IsIntegrateable())
    {
        orbInitState = myOrbit->GetStateObject().GetState();
        cout << "Orbit State: " << ~orbInitState << endl;
    }
    if(myAttitude->IsIntegrateable())
    {
        attInitState = myAttitude->GetStateObject().GetState();
        cout << "Attitude State: " << ~attInitState << endl;
    }
    // Integrate over the desired time interval
    tick();
    myPropagator->Propagate(propTimes, orbInitState, attInitState);
    ssfSeconds calcTime = tock();
    cout << "finished propagating in " << calcTime << " seconds." << endl;
}
// *************************
// ****** ENVIRONMENT ****** 
// *************************
void SetupEnvironment()
{
    // ENVIRONMENT TESTING
    myEnvironment = new Environment;
    EarthCentralBody *pCBEarth = new EarthCentralBody;
    myEnvironment->SetCentralBody(pCBEarth);

    return;
}
void ChangeEnvironment()
{
    // Add Gravity force function
    cout << "Filling Parameters" << endl;
    EnvFunction TwoBodyGravity(&GravityForceFunction);
    myEnvironment->AddForceFunction(TwoBodyGravity);
    
    cout << "Add Drag? (y or n): " << flush;
    char answer;
    cin >> answer;
    if(answer == 'y')
    {
        // Add Drag Force Function
        EnvFunction DragForce(&SimpleAerodynamicDragForce);
        double *BC = new double(200);
        DragForce.AddParameter(reinterpret_cast<void*>(BC), 1);
        double *rho = new double(1.13 * pow(static_cast<double>(10), static_cast<double>(-12))); // kg/m^3
        DragForce.AddParameter(reinterpret_cast<void*>(rho), 2);
        myEnvironment->AddForceFunction(DragForce);
    }
    cout << "Finished Setting up Earth Environment" << endl;

    // Adds a controller
    
    EnvFunction Controller(&SimpleController);
    Vector* Gains = new Vector(3);
    cout << "Input Control gains: "<< flush;
    cin >> (*Gains)(1);
    cin >> (*Gains)(2);
    cin >> (*Gains)(3);
    
    Controller.AddParameter(reinterpret_cast<void*>(Gains),1);
    myEnvironment->AddTorqueFunction(Controller);    
    
    return;
}

// *************************
// ****** PROPAGATOR ******* 
// ************************* 
void SetupPropagator()
{
    myPropagator = new CombinedNumericPropagator;
    orbitIntegrator = new RungeKuttaFehlbergIntegrator;
    attitudeIntegrator = new RungeKuttaFehlbergIntegrator;
        
    myPropagator->SetOrbitIntegrator(orbitIntegrator);
    myPropagator->SetAttitudeIntegrator(attitudeIntegrator);
        
    // Integration Times
    double intTime = 1;
    ssfTime begin(0);
    ssfTime end(begin + intTime);
    propTimes.push_back(begin);
    propTimes.push_back(end);
    return;
}

void ChangePropagator()
{
    DisplayPropagator();
    
    // Create & setup the integator
        // Setup an integrator and any special parameters
    int stepSize = 1;

    // Integration Times
    double intTime = 1;
    cout << "Integration duration (s): " << flush;
    cin >> intTime;
      /*
    cout << "Orbit Integration Stepsize (s): "<< flush;
    cin >> stepSize;
    orbitIntegrator->SetNumSteps(floor(intTime/stepSize));

    cout << "Attitude Integration Stepsize(s): "<< flush;
    cin >> stepSize;
    attitudeIntegrator->SetNumSteps(floor(intTime/stepSize));
    */
    double tolerance;
    orbitIntegrator->SetStepSizes(1, 300);
    cout << "Orbit Tolerance: " << flush;
    cin >> tolerance;
    orbitIntegrator->SetTolerance(tolerance);
    attitudeIntegrator->SetStepSizes(0.01, 5);
    cout << "Attitude Tolerance: " << flush;
    cin >> tolerance;
    attitudeIntegrator->SetTolerance(tolerance);
    ssfTime begin(0);
    ssfTime end(begin + intTime);
    propTimes[0] = begin;
    propTimes[1] = end;
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

void ChangeOrbit()
{
    DisplayOrbit();
    
    // Create & initialize the orbit
    OrbitState myOrbitState;
    myOrbitState.SetStateRepresentation(new PositionVelocity);
    myOrbitState.SetOrbitFrame(new OrbitFrameIJK);
    Vector initPV(6);
    //-5776.6 -157 3496.9
    // -2.595 -5.651 -4.513
        cout << "Enter the position vector (km): " << flush;
        cin >> initPV(VectorIndexBase+0); // km
        cin >> initPV(VectorIndexBase+1); // km
        cin >> initPV(VectorIndexBase+2); // km
        cout << "Enter the velocity vector (km): " << flush;
        cin >> initPV(VectorIndexBase+3); // km
        cin >> initPV(VectorIndexBase+4); // km
        cin >> initPV(VectorIndexBase+5); // km
    myOrbitState.SetState(initPV);
    myOrbit->SetStateObject(myOrbitState);
    
//    cout << "Choose the dynamics equation: " << flush;
    myOrbit->SetDynamicsEq(&TwoBodyDynamics);
    myOrbit->SetStateConversion(&myOrbitStateConvFunc);

    // Setup Parameters (ie mass, etc)
    return;
}
void SetupOrbit()
{
    myOrbit = new Orbit;
    return;
}


// *************************
// ******* ATTITUDE ******** 
// ************************* 
void myAttitudeStateConvFunc(const Matrix &_meshPoint, AttitudeState &_convertedAttitudeState)
{
    static Vector tempQ(4); tempQ(_) = ~_meshPoint(_,_(2, 5));
    static Vector tempVector(3); tempVector(_) = ~_meshPoint(_, _(6, 8));
    _convertedAttitudeState.SetState(Rotation(Quaternion(tempQ)), tempVector);
    return;
}
static Vector AttituteDynamics(const ssfTime &_time, const Vector& _integratingState, Orbit *_Orbit, Attitude *_Attitude, const Matrix &_parameters, const Functor &_forceFunctorPtr)
{
    static Vector stateDot(7);
    static Matrix bMOI(3,3); 
    static Matrix qtemp(4,3); 
    static Vector Tmoment(3);
    static Vector qIn(4); 
    static Vector wIn(3);

    qIn = _integratingState(_(VectorIndexBase,VectorIndexBase + 3));
    wIn = _integratingState(_(VectorIndexBase + 4,VectorIndexBase + 6));
    qIn /= norm2(qIn);

    qtemp(_(VectorIndexBase+0,VectorIndexBase+2),_) = skew(qIn(_(VectorIndexBase+0,VectorIndexBase+2))) + qIn(VectorIndexBase+3) * eye(3);
    qtemp(VectorIndexBase+3, _) = -(~qIn(_(VectorIndexBase+0,VectorIndexBase+2)));

    bMOI = _parameters(_(MatrixIndexBase+0,MatrixIndexBase+2),_(MatrixIndexBase+0,MatrixIndexBase+2));
    Tmoment = _forceFunctorPtr.Call(_time, _Orbit->GetStateObject(), _Attitude->GetStateObject());
    
    stateDot(_(VectorIndexBase,VectorIndexBase + 3)) = 0.5 * qtemp * wIn;
    stateDot(_(VectorIndexBase + 4,VectorIndexBase + 6)) = (bMOI.inverse() * (Tmoment - skew(wIn) * (bMOI * wIn)));

    return stateDot;
}

void ChangeAttitude()
{
    DisplayAttitude();
    double q1,q2,q3,q4;
    cout << "Enter Attitude quaternion: " << flush;
    cin >> q1 >> q2 >> q3 >> q4;
    
    AttitudeState myAttitudeState;
    myAttitudeState.SetRotation(Rotation(Quaternion(q1,q2,q3,q4)));

    cout << "Enter Attitude angular velocity (rad/s): " << flush;
    cin >> q1 >> q2 >> q3;
    Vector initAngVelVector(3);
        initAngVelVector(1) = q1;
        initAngVelVector(2) = q2;
        initAngVelVector(3) = q3;
        
    myAttitudeState.SetAngularVelocity(initAngVelVector);

    myAttitude->SetStateObject(myAttitudeState);
    myAttitude->SetDynamicsEq(&AttituteDynamics);
    myAttitude->SetStateConversion(&myAttitudeStateConvFunc);
    cout << "Enter Principle Moments of Inertia: " << flush;
    Matrix MOI = eye(3);
    cin >> MOI(1,1);
    cin >> MOI(2,2);
    cin >> MOI(3,3);
    myAttitude->SetParameters(MOI);
    
    return;
}
void SetupAttitude()
{
    myAttitude = new Attitude;
    
    return;
    
}
Vector SimpleController(const ssfTime &_currentTime, const OrbitState &_currentOrbitState, const AttitudeState &_currentAttitudeState, const EnvFuncParamaterType &_parameterList)
{
    static Vector Torques(3);
    Torques(1) = (*reinterpret_cast<Vector*>(_parameterList[0]))(1) * sin(_currentTime.GetSeconds());
    Torques(2) = (*reinterpret_cast<Vector*>(_parameterList[0]))(2) * cos(_currentTime.GetSeconds());
    Torques(3) = (*reinterpret_cast<Vector*>(_parameterList[0]))(3);
    return Torques;
}
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: testInterface.cpp,v $
*	Revision 1.5  2003/10/18 13:58:02  nilspace
*	Updated for final testing.
*	
*	Revision 1.4  2003/08/24 20:59:13  nilspace
*	Updated.
*	
*	Revision 1.3  2003/06/05 20:31:54  nilspace
*	Changed integrator to Runge-Kutta Fehlberg.
*	
*	Revision 1.2  2003/05/29 21:12:21  nilspace
*	Asks if the user wants to include drag.
*	
*	Revision 1.1  2003/05/26 21:23:21  nilspace
*	Initial submission.
*	
*
******************************************************************************/

                        

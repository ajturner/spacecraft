//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file HokieSatSimulation.cpp
*  \brief Demonstrates the use of Open-SESSAME for simulating HokieSat.
*  \author $Author: nilspace $
*  \version $Revision: 1.5 $
*  \date    $Date: 2003/08/24 20:59:13 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*!  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "HokieSatSimulation.h"

/** @brief Main operating function for HokieSat simulation. 
* @author Andrew Turner
*
* Breaks down all object initializations into seperate functions. 
*/
int main()
{
    Orbit* pHokiesatOrbit = SetupOrbit();
    Attitude* pHokiesatAttitude = SetupAttitude();
    
    // Setup Propagator
        NumericPropagator* pHokiesatPropagator = SetupPropagator();
        pHokiesatOrbit->SetPropagator(pHokiesatPropagator);
        pHokiesatAttitude->SetPropagator(pHokiesatPropagator);

    // Setup external environment
        Environment* pEarthEnv = SetupEnvironment(pHokiesatAttitude);
        pHokiesatOrbit->SetEnvironment(pEarthEnv);
        pHokiesatAttitude->SetEnvironment(pEarthEnv);

    // Integration Times
        double propTime = 20; // mins
            cout << "Propagation time (mins): " << flush;
            cin >> propTime;
        double propStep = 60; // s
            cout << "Propagation step (secs): " << flush;
            cin >> propStep;
        vector<ssfTime> integrationTimes;
        ssfTime begin(0);
        ssfTime end(begin + propStep);
        integrationTimes.push_back(begin);
        integrationTimes.push_back(end);
        
    // Output the current state properties
        cout << "PropTime = " << begin.GetSeconds() << " s -> " << end.GetSeconds() << " s" << endl;
        cout << "Orbit State: " << ~pHokiesatOrbit->GetStateObject().GetStateRepresentation()->GetPositionVelocity();
        cout << "Attitude State: " << ~pHokiesatAttitude->GetStateObject().GetState() << endl;

    // Integrate over the desired time interval
        tick();
        pHokiesatPropagator->Propagate(integrationTimes, pHokiesatOrbit->GetStateObject().GetStateRepresentation()->GetPositionVelocity(), pHokiesatAttitude->GetStateObject().GetState());                            

        for (int ii = 0; ii < propTime*60/propStep ; ++ii)
        {
            // Integrate again
            integrationTimes[0] = integrationTimes[1];
            integrationTimes[1] = integrationTimes[0] + propStep;
            //cout << integrationTimes[0] << " -> " << integrationTimes[1] << endl;
            pHokiesatPropagator->Propagate(integrationTimes, pHokiesatOrbit->GetStateObject().GetStateRepresentation()->GetPositionVelocity(), pHokiesatAttitude->GetStateObject().GetState());
            if((ii % 100) < 5)
                cout << integrationTimes[0].GetSeconds() << ", ";
        }
        cout << endl;
        ssfSeconds calcTime = tock();
        cout << "finished propagating " << propTime*60 << " sim-seconds in " << calcTime << " real-seconds." << endl;     
    // Plot the state history
        Matrix orbitHistory = pHokiesatOrbit->GetHistoryObject().GetHistory();
        Matrix orbitPlotting = orbitHistory(_,_(MatrixIndexBase+1,MatrixIndexBase+3));
        Matrix attitudeHistory = pHokiesatAttitude->GetHistoryObject().GetHistory();
        Matrix attitudePlotting = attitudeHistory(_,_(MatrixIndexBase,MatrixIndexBase+4));

        Plot3D(orbitPlotting);
        Plot2D(attitudePlotting);
   
    // Store the output to file
        ofstream ofile;
        ofile.open("OrbitHistory.dat");
        ofile << pHokiesatOrbit->GetHistoryObject().GetHistory();
        ofile.close();
    
        ofile.open("AttitudeHistory.dat");
        ofile << pHokiesatAttitude->GetHistoryObject().GetHistory();
        ofile.close();

    return 0;
                            
}

// *************************
// ****** ENVIRONMENT ****** 
// *************************
Environment* SetupEnvironment(Attitude* pSatAttitude)
{
    // ENVIRONMENT TESTING
    Environment* pEarthEnv = new Environment;
    EarthCentralBody *pCBEarth = new EarthCentralBody;
    pEarthEnv->SetCentralBody(pCBEarth);
    
    // Add Gravity force function
        EnvFunction TwoBodyGravity(&GravityForceFunction);
        double *mu = new double(pCBEarth->GetGravitationalParameter());
        TwoBodyGravity.AddParameter(reinterpret_cast<void*>(mu), 1);
        pEarthEnv->AddForceFunction(TwoBodyGravity);
    
    cout << "Add Drag? (y or n): " << flush;
    char answer;
    cin >> answer;
    if(answer == 'y')
    {
        // Add Drag Force Function
        EnvFunction DragForce(&SimpleAerodynamicDragForce);
        double *BC = new double(2);
        DragForce.AddParameter(reinterpret_cast<void*>(BC), 1);
        double *rho = new double(1.13 * pow(static_cast<double>(10), static_cast<double>(-12))); // kg/m^3
        DragForce.AddParameter(reinterpret_cast<void*>(rho), 2);
        pEarthEnv->AddForceFunction(DragForce);
    }
    // Add Gravity torque function
    
        EnvFunction GGTorque(&GravityGradientTorque);
        Matrix *MOI = new Matrix(pSatAttitude->GetParameters()(_(1,3),_));
        GGTorque.AddParameter(reinterpret_cast<void*>(MOI), 1);
        GGTorque.AddParameter(reinterpret_cast<void*>(mu), 2);
        pEarthEnv->AddTorqueFunction(GGTorque);
    
    // Assign Magnetic Model
        pCBEarth->SetMagneticModel(new TiltedDipoleMagneticModel);
    return pEarthEnv;
}

// *************************
// ****** PROPAGATOR ******* 
// ************************* 
NumericPropagator* SetupPropagator()
{
    CombinedNumericPropagator* pSatProp = new CombinedNumericPropagator;
    
    // Create & setup the integator
        // Setup an integrator and any special parameters
    RungeKuttaFehlbergIntegrator* orbitIntegrator = new RungeKuttaFehlbergIntegrator; 
    RungeKuttaFehlbergIntegrator* attitudeIntegrator = new RungeKuttaFehlbergIntegrator; 

    orbitIntegrator->SetTolerance(pow(10.,-7.));
    orbitIntegrator->SetStepSizes(0.01, 300);
    pSatProp->SetOrbitIntegrator(orbitIntegrator);
    attitudeIntegrator->SetTolerance(pow(10.,-7.));
    attitudeIntegrator->SetStepSizes(0.01, 5);
    pSatProp->SetAttitudeIntegrator(attitudeIntegrator);
    
    return pSatProp;
}

// *************************
// ********* ORBIT ********* 
// ************************* 
Orbit* SetupOrbit()
{
    Orbit* pSatOrbit = new Orbit;
    
    // Create & initialize the orbit
    OrbitState SatOrbitState;
    SatOrbitState.SetStateRepresentation(new PositionVelocity);
    SatOrbitState.SetOrbitFrame(new OrbitFrameIJK);
    Vector initPV(6);
        // Space station
        initPV(VectorIndexBase+0) = -5776.6; // km
        initPV(VectorIndexBase+1) = -157; // km       
        initPV(VectorIndexBase+2) = 3496.9; // km    
        initPV(VectorIndexBase+3) = -2.595;  // km/s
        initPV(VectorIndexBase+4) = -5.651;  // km/s        
        initPV(VectorIndexBase+5) = -4.513; // km/s
    SatOrbitState.SetState(initPV);
    pSatOrbit->SetStateObject(SatOrbitState);
    
    pSatOrbit->SetDynamicsEq(&TwoBodyDynamics);
    pSatOrbit->SetStateConversion(&PositionVelocityConvFunc);

    return pSatOrbit;
}


// *************************
// ******* ATTITUDE ******** 
// ************************* 
Attitude* SetupAttitude()
{
    Attitude* pSatAttitude = new Attitude;
    
    AttitudeState SatAttState;
    SatAttState.SetRotation(Rotation(Quaternion(0,0,0,1)));
    Vector initAngVelVector(3);
        initAngVelVector(1) = 0;
    SatAttState.SetAngularVelocity(initAngVelVector);

    pSatAttitude->SetStateObject(SatAttState);
    pSatAttitude->SetDynamicsEq(&AttituteDynamics_QuaternionAngVel);
    pSatAttitude->SetStateConversion(&QuaternionAngVelConvFunc);

    // Create the matrix of parameters needed for the RHS
    Matrix MOI(3,3);
        MOI(1,1) =  0.4084; MOI(1,2) =  0.0046; MOI(1,3) = 0.0;
        MOI(2,1) =  0.0046; MOI(2,2) =  0.3802; MOI(2,3) = 0.0;
        MOI(3,1) =  0.0;    MOI(3,2) =  0.0;    MOI(3,3) = 0.4530;

    MOI = eye(3);
        MOI(1,1) = 2; MOI(2,2) = 2; MOI(3,3) = 10;
    Matrix params(6,3);
        params(_(1,3),_) = MOI;
        params(_(4,6),_) = MOI.inverse();
    
    pSatAttitude->SetParameters(params);
    
    return pSatAttitude;
    
}

Vector ControlTorques(const ssfTime &_currentTime, const OrbitState  &_currentOrbitState, const AttitudeState &_currentAttitudeState, const EnvFuncParamaterType &_parameterList) // HYK
{
  /* This function takes the current and desired attitudes (orbital to body)
   * and returns the needed control torque (in N-m)
   */
   /*
  static Matrix Kp(3,3);        // gain on quaternion
  static Matrix Kd(3,3);        // gain on angular velocity
  static Matrix qCurrent(4,1);  // current quaternion (orbital to body)
  static Matrix qDesired(4,1);  // desired quaternion (orbital to body)
  static Matrix wCurrent(3,1);  // current angular velocity (orbital to body, rad/s)
  static Matrix wDesired(3,1);  // desired angular velocity (orbital to body, rad/s)
  static Matrix qError(4,1);    // the error quaternion (desired to body)
  static Matrix qErrAxis(3,1);  // Euler axis for desired to body rotation
  static double qError4;         // fourth entry of error quaternion
  static Matrix wError;          // Angular Velocity error
  static Matrix sigma(3,1);     // scaled error quaternion

  static Matrix Inertia(3,3);    // Moments of inertia, kg-m^2



  qCurrent = CurrentAttState[mslice(0,0,4,1)];
  qDesired = DesAttState[mslice(0,0,4,1)]; //HYKIM Oct 15
  wCurrent = CurrentAttState[mslice(4,0,3,1)];
  wDesired = DesAttState[mslice(4,0,3,1)];

  qError = ATT_qMult(qCurrent, qDesired);

  wError = wCurrent - wDesired;
  qErrAxis = qError[mslice(0,0,3,1)];
  qError4 = qError(3,0);

  Kd = .02*eye(3);
  Kp = 0.0006*eye(3);

  Matrix Torque_r(3,1);


      sigma = qErrAxis / (1 + qError4);
      Torque_r = -Kp * sigma* (eye(1) + ~sigma * sigma) - Kd * wError;

  Matrix B(3,1);
  B = ATT1_CalcG(epoch, count);  // HYK
  //B = B / B.norm2();
  //Torque = Torque_r - (~Torque_r*B)*B;
  Matrix K(3,6);

 K(1,1) =  0.040424; K(1,2) =  0.000065; K(1,3) =  0.000110; K(1,3) =  30.393883; K(1,4) = -0.671557;  K(1,5) = -0.233840; 
 K(2,1) = -0.000724; K(2,2) =  0.030161; K(2,3) = -0.022378; K(2,3) = -1.024919;  K(2,4) =  34.678584; K(2,5) = -10.027221; 
 K(3,1) = -0.000370; K(3,2) =  0.020404; K(3,3) =  0.019692; K(3,3) = -0.326869;  K(3,4) = -1.073717;  K(3,5) =  24.430588;

  Matrix dx(6,1), gm(6,1), Gt(6,3);



  dx[mslice(0,0,3,1)] = qErrAxis;
  dx[mslice(3,0,3,1)] = wError; 

	Matrix Rto(3,3), qbt(4,1), wbt(3,1) ;
  	Matrix temp5(3,1);
	Rto = ATT_q2R(qDesired);
	qbt = ATT_itzhackR2q(ATT_q2R(qCurrent)*~Rto);

  	temp5=  qbt[mslice(0,0,3,1)];
	//cout<<"up="<<dx<<endl;
  	dx[mslice(0,0,3,1)] = temp5;
  	dx[mslice(3,0,3,1)] = wCurrent; 
	//cout<<"down="<<dx<<endl;

  Gt[mslice(3,0,3,3)] = -(1.0 / B.norm2()) * skew(B) * skew(B);
  gm = -Gt * K * dx;
  Torque  = gm[mslice(3,0,3,1)];
//  Torque = ATT_q2R(qCurrent) * Torque;



  if (Torque.norm2() > MAXTORQUE)
    {
      Torque = Torque / Torque.norm2() * MAXTORQUE;
    }

  return ATT_TORQUE_VALID;
*/
    return Vector(3);
}
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: HokieSatSimulation.cpp,v $
*	Revision 1.5  2003/08/24 20:59:13  nilspace
*	Updated.
*	
*	Revision 1.4  2003/06/12 23:05:55  nilspace
*	Works.
*	
*	Revision 1.3  2003/06/12 21:01:48  nilspace
*	Fixed GG torque MOI parameter.
*	
*	Revision 1.2  2003/06/12 20:48:10  nilspace
*	Asks user for times.
*	
*	Revision 1.1  2003/06/12 18:06:06  nilspace
*	Initial submission.
*	
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

                        

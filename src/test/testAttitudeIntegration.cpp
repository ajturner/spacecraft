//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file testAttitudeIntegration.cpp
*  \brief Sample of an attitude integration using components of the SSF.
*  \author $Author: nilspace $
*  \version $Revision: 1.6 $
*  \date    $Date: 2003/08/24 20:59:13 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Matrix.h"
#include "RungeKuttaIntegrator.h"
#include "LinearInterpolator.h"
#include "Plot.h"
#include "Attitude.h"
#include "AttitudeState.h"
#include <vector.h>
using namespace std;


// Torque function that will be called each timestep
Vector NullFunctor(const ssfTime& _pSSFTime, const OrbitState& _pOrbitState, const AttitudeState& _pAttitudeState)
{
    return Vector(3);
}
/*
static Vector EugeneDynamics(const ssfTime &_time, const Vector& _integratingState, Orbit *_Orbit, Attitude *_Attitude, const Matrix &_parameters, const Functor &_forceFunctorPtr)
{
    //function statedot=test1_rhs(t,state)
    static Vector h = _integratingState(_(1,3)); 	//h=state(1:3);
    static double T = _integratingState(4);		//T=state(4);

    Matrix I(3,3);				//I=[100 0 0;0 200 0;0 0 150];
        I(1,1) = 100;
        I(2,2) = 200;
        I(3,3) = 150;
    static Vector w = I.inverse() * h;			//w=inv(I)*h;
    Vector ge(3);				//ge=[0 0 0]';
    
    static Vector hdot = skew(w) * h + ge;		//hdot=-cr(w)*h+ge;
    static Vector wdot = I.inverse() * hdot;		//wdot=inv(I)*hdot;
    static Matrix temp = (~ge * wdot);			//Tdot=ge'*wdot;
    double Tdot = temp(1,1);
    
    static Vector statedot(hdot.getIndexBound() + 1);
        statedot(_(1, hdot.getIndexBound())) = hdot(_);
        statedot(hdot.getIndexBound()+1) = Tdot;
        
    return statedot;				//statedot=[hdot; Tdot];

}*/

/*! \brief Dynamic and Kinematic attitude equations using quaternion and angular velocities. 
*/
static Vector AttituteDynamics(const ssfTime &_time, const Vector& _integratingState, Orbit *_pOrbit, Attitude *_pAttitude, const Matrix &_parameters, const Functor &_forceFunctorPtr)
{
    // Initialize the vectors used in the calculation.
    // 	made static, which causes the memory to be allocated the first time the function is called
    //  and then left in memory during the program to speed up computation.
    static Vector stateDot(7);
    static Matrix bMOI(3,3); 
    static Matrix qtemp(4,3); 
    static Matrix Tmoment(3,1);
    static Vector qIn(4); 
    static Vector wIn(3);
    
    // Retrieve the current integration states to a quaternion and angular velocity vector
    qIn = _integratingState(_(VectorIndexBase,VectorIndexBase + 3));
    wIn = _integratingState(_(VectorIndexBase + 4,VectorIndexBase + 6));
    qIn /= norm2(qIn);

    // Calculate qDot
    qtemp(_(VectorIndexBase+0,VectorIndexBase+2),_(VectorIndexBase+0,VectorIndexBase+2)) = skew(qIn(_(VectorIndexBase+0,VectorIndexBase+2))) + qIn(VectorIndexBase+3) * eye(3);
    qtemp(VectorIndexBase+3, _(VectorIndexBase+0,VectorIndexBase+2)) = -(~qIn(_(VectorIndexBase+0,VectorIndexBase+2)));
    qtemp(_,MatrixIndexBase) = 0.5 * qtemp * wIn;

    // Get the moments of inertia and calculate the omegaDot
    bMOI = _parameters(_(MatrixIndexBase+0,MatrixIndexBase+2),_(MatrixIndexBase+0,MatrixIndexBase+2));
    Tmoment = (bMOI.inverse() * (Tmoment - skew(wIn) * (bMOI * wIn)));
    
    // Combine the qDot and omegaDot into a stateDot vector
    stateDot(_(VectorIndexBase,VectorIndexBase + 3)) = qtemp(_,MatrixIndexBase);
    stateDot(_(VectorIndexBase + 4,VectorIndexBase + 6)) = Tmoment(_,MatrixIndexBase);

    cout << 0.5 * ~wIn * (bMOI * wIn);
    return stateDot;
}

int main()
{
    //////////////////////////////////////////////////
    // Setup an integrator and any special parameters
    RungeKuttaIntegrator myIntegrator; 
    myIntegrator.SetNumSteps(1000);
    // Integration times
    vector<ssfTime> integrationTimes;
    ssfTime begin(0);
    ssfTime end(begin + 20);
    integrationTimes.push_back(begin);
    integrationTimes.push_back(end);
    
    // Create the initial attitude state
    AttitudeState myAttitudeState;
    myAttitudeState.SetRotation(Rotation(Quaternion(0,0,0,1)));
    Vector initAngVelVector(3);
        initAngVelVector(1) = 0.1;
    myAttitudeState.SetAngularVelocity(initAngVelVector);
    SpecificFunctor AttitudeForcesFunctor(&NullFunctor);
    
    // Create the matrix of parameters needed for the RHS - MOI
    Matrix Parameters = eye(3);
    
    Matrix I(3,3);				//I=[100 0 0;0 200 0;0 0 150];
        I(1,1) = 100;
        I(2,2) = 200;
        I(3,3) = 150;
    Vector h(3);
        h(1) = 10;
        h(2) = 20;
        h(3) = 30;

    Vector w = I.inverse() * h;
    Matrix Tmat = 0.5 * (~w * (I * w));
    Vector initEugeneState(4);
	initEugeneState(_(1,3)) = h(_(1,3));
        initEugeneState(4) = Tmat(1,1);

 
    cout << "PropTime = " << begin.GetSeconds() << " s -> " << end.GetSeconds() << " s" << endl;
    cout << "Attitude State: " << ~myAttitudeState.GetState() << endl;
    ///////////////////////////////////////////////
    // Integrate over the desired time interval
    tick();
    Matrix history = myIntegrator.Integrate(
                            integrationTimes, 		// seconds
                            &AttituteDynamics, 
                            myAttitudeState.GetState(),
                            NULL,
                            NULL,
                            Parameters,
                            AttitudeForcesFunctor
                        );

    cout << "finished propagating in " << tock() << " seconds." << endl;                                 
    // Output the flight history
    //cout << history;
    Matrix plotting = history(_,_(MatrixIndexBase,MatrixIndexBase+4));

//    Plot2D(plotting);
    
    ///////////////////////////////////////////////
    // Create & populate an AttitudeHistory object
    AttitudeHistory myAttHistory;
    myAttHistory.SetInterpolator(new LinearInterpolator);
    Vector AngVel(3);
    Vector Quat(4);
    Rotation myRot;
    for(int jj = 1;jj <= history[MatrixRowsIndex].getIndexBound(); ++jj)
    {
        AngVel = ~(history(jj, _(6,8)));
        Quat = ~(history(jj,_(2,5)));
        myRot.Set(Quaternion(Quat));
        myAttHistory.AppendHistory(history(jj,1), myRot, AngVel);
    }
    
    /////////////////////////////////////////////////
    // Output the attitude state at a requested time    
    double requestTime;
    cout << "Output attitude state at time (s): " << flush;
    cin >> requestTime;
    ssfTime myTime(requestTime);
    myAttHistory.GetState(myTime, myRot, AngVel);
    cout << myTime.GetSeconds() << " : " << ~myRot.GetQuaternion() << endl;

    /*
    // Verifying the energy
    Matrix calcHistory = history;
    for(int ii = 1; ii <= history[MatrixRowsIndex].getIndexBound(); ++ii)
    {
        h = ~(history(ii,_(2,4)));
        w = I.inverse() * h;
        Tmat = 0.5 * (~w * (I * w)); 
        calcHistory(ii,5) = Tmat(1,1);
    }
    Plot2D(calcHistory);*/
    
    /////////////////////////////////////////////////
    // Store the output to file
    ofstream ofile;
    ofile.open("AttitudeHistory.dat");
    ofile << history;
    ofile.close();

    return 0;
                            
}
// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: testAttitudeIntegration.cpp,v $
*	Revision 1.6  2003/08/24 20:59:13  nilspace
*	Updated.
*	
*	Revision 1.5  2003/05/22 14:48:11  nilspace
*	It works, for now. Changed so integrator just takes NULL pointers to Attitude & Orbit.
*	
*	Revision 1.4  2003/05/22 03:02:52  nilspace
*	Pass pointers to Orbit & Attitude in integrator (pointers to NULL).
*	
*	Revision 1.3  2003/05/19 19:19:55  nilspace
*	Updated to include Eugene's "test case". Also made the RHS dynamic equation variables declared as static.
*	
*	Revision 1.2  2003/05/13 18:55:50  nilspace
*	Fixed to work with the new integrator, eugene's functions, History, and interpolation.
*	
*	Revision 1.1  2003/05/10 01:53:37  nilspace
*	Initial submission. Works, but needs to be refined.
*	
*
******************************************************************************/

                        

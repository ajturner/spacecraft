//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file HokiesatAttitudeSim.cpp
*  \brief Implementation of a HokieSat Attitude Simulation using the Open-SESSAME Framework.
*  \author $Author: nilspace $
*  \version $Revision: 1.2 $
*  \date    $Date: 2003/08/24 20:59:13 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Matrix.h"
#include "RungeKuttaIntegrator.h"
#include "AttitudeState.h"
#include <vector.h>
using namespace std;

#include "SSFComm.h"



Vector ControlTorques(Matrix CurrentAttState, Matrix DesAttState, double epoch, double count) // HYK
{
  /* This function takes the current and desired attitudes (orbital to body)
   * and returns the needed control torque (in N-m)
   */
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
  /* smaller torque */
 //    Kd = .05*eye(3);
 //   Kp = 0.0005*eye(3);

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

}

int AttitudeServer()
{
    // Setup an integrator and any special parameters
    RungeKuttaIntegrator myIntegrator; 
        int numSteps = 10;
        myIntegrator.SetNumSteps(numSteps);
        vector<ssfTime> integrationTimes;
        ssfTime begin(0);
        ssfTime end(begin + 1);
        integrationTimes.push_back(begin);
        integrationTimes.push_back(end);
        simTimeData.simTime.Set(0);

   // Create & initialize an orbit type
    OrbitState myOrbit;
    
    // Setup the initial attitude
    AttitudeState myAttitude;
        myAttitude.SetRotation(Quaternion(0.5,0.5,0.5,0.5));
        Vector AngularVelocity(3);
//	AngularVelocity(2) = 0.03;
        myAttitude.SetAngularVelocity(AngularVelocity);
//    	myAttitude.SetAttitudeFrame(new AttitudeFrameBI);
    
    
    // Create the matrix of parameters needed for the RHS
    Matrix MOI(3,3);
        MOI(1,2) =  0.4084; MOI(1,3) =  0.0046; MOI(1,3) = 0.0;
        MOI(2,2) =  0.0046; MOI(2,3) =  0.3802; MOI(2,3) = 0.0;
        MOI(3,2) =  0.0;    MOI(3,3) =  0.0;    MOI(3,3) = 0.4530;
            
    SpecificFunctor AttitudeForcesFunctor(&AttitudeForcesFunction);

    // Setup Communications 
    int server_fifo_fd, client_fifo_fd;
        TimeData simTimeData;
        AttitudeData attitudeState;
        int read_res;
        char client_fifo[256];
    
    // Create the pipe 
    mkfifo(SERVER_FIFO_NAME, 0777);
    server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);
    if (server_fifo_fd == -1)
    {
        fprintf(stderr, "Server fifo failure\n");
        exit(EXIT_FAILURE);
    }
    //sleep(5); // lets clients queue
    int ii = 0;
     while ((simTimeData.simTime.GetSeconds() <= 25) && ii < 5) 
     {
        read_res = read(server_fifo_fd, &simTimeData, sizeof(simTimeData));
        sprintf(client_fifo, CLIENT_FIFO_NAME, simTimeData.client_pid);

        if (read_res > 0)
        {
            // Set the final integration time to the requested time
            integrationTimes[1] = simTimeData.simTime;
                
            cout << "PropTime = " << integrationTimes[0].GetSeconds() << " s -> " << integrationTimes[1].GetSeconds() << " s" << endl;

            // Integrate over the desired time interval
            Matrix history = myIntegrator.Integrate(
                            integrationTimes, 		// seconds
                            &AttituteDynamics, 
                            myAttitude.GetState(),
                            myOrbit,
                            myAttitude,
                            MOI,
                            AttitudeForcesFunctor
                        );
            // on the next pass, the specified time will be the beginning time
            integrationTimes[0] = simTimeData.simTime;
            attitudeState.time = simTimeData.simTime.GetSeconds();
            attitudeState.q1 = (myAttitude.GetState())(1);
            attitudeState.q2 = (myAttitude.GetState())(2);
            attitudeState.q3 = (myAttitude.GetState())(3);
            attitudeState.q4 = (myAttitude.GetState())(4);
            attitudeState.w1 = (myAttitude.GetState())(5);
            attitudeState.w2 = (myAttitude.GetState())(6);
            attitudeState.w3 = (myAttitude.GetState())(7);
            
            // write out to pipe
            client_fifo_fd = open(client_fifo, O_WRONLY);
            if(client_fifo_fd != -1)
            {
                cout << "sending : " << attitudeState.time << " [ " << attitudeState.q1 << ", " 
                                                        << attitudeState.q2 << ", "
                                                        << attitudeState.q3 << ", "
                                                        << attitudeState.q4 << " : "
                                                        << attitudeState.w1 << ", "
                                                        << attitudeState.w2 << ", "
                                                        << attitudeState.w3 << " ]" << endl;
                write(client_fifo_fd, &attitudeState, sizeof(attitudeState));
                close(client_fifo_fd);
            }
            else
                cout << "Could not open Client FIFO FD" << endl;
        }
        else
	{
            cout << "Server has nothing to read." << endl;
	    ++ii;
	}
    }
    cout << "Closing Attitude Server" << endl;
    close(server_fifo_fd);
    unlink (SERVER_FIFO_NAME);
    exit(EXIT_SUCCESS);
    
        
    return 0;
                            
}

void DeviceRun()
{
            sleep(2);
            cout << "Running Device Model" << endl;
            SetupSSFComm();
            for (int ii = 0; ii < 5; ++ii)
            {
                cout << "Run " << ii << ": " << endl;
                SSFGetAttitude();
            }
            StopSSFComm();
}

// Starts up the processes
int main()
{
    pid_t new_pid;
    new_pid = fork();
    switch(new_pid)
    {
        case 0 : // child
            cout << "Running Attitude Server" << endl;
            AttitudeServer();
            break;
            
        default : // parent
            DeviceRun();
            break;
        }

    return 0;
        
}

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: AttitudeSimulatorServer.cpp,v $
*	Revision 1.2  2003/08/24 20:59:13  nilspace
*	Updated.
*	
*	Revision 1.1  2003/05/01 15:29:59  nilspace
*	First commit.
*	
*
******************************************************************************/

                        


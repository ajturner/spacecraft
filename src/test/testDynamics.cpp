//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file testDynamics.cpp
*  \brief Test program for trying out rigid body dynamics.
*  \author $Author: nilspace $
*  \version $Revision: 1.4 $
*  \date    $Date: 2005/06/30 11:24:18 $
//////////////////////////////////////////////////////////////////////////////////////////////////
*  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include "rotation/Rotation.h"
#include "dynamics/QuaternionDynamics.h"
#include "kinematics/QuaternionKinematics.h"
#include "attitude/Attitude.h"
#include "environment/Environment.h"
#include "environment/CentralBody/EarthCentralBody.h"
#include "environment/Disturbances/GravityFunctions.h"
//#include "utils/Units.h"

Environment* SetupEnvironment(Attitude &_SpacecraftAttitude)
{
    Environment *pEarthEnv = new Environment;
    EarthCentralBody *pCBEarth = new EarthCentralBody;
    pEarthEnv->SetCentralBody(pCBEarth);
    EnvFunction GGTorque(GravityGradientTorque);
    cout << "Filling Parameters" << endl;
    GGTorque.AddParameter((void*)&(_SpacecraftAttitude.GetAttitude()), 1);
    GGTorque.AddParameter((void*)&(_SpacecraftAttitude.GetMOI()), 2);
    GGTorque.AddParameter((void*)&(pCBEarth->GetWc(500000)),3);
    pEarthEnv->AddTorqueFunction(GGTorque);
    return pEarthEnv;
}

int main()
{
    Attitude testAttitude;
    Rotation rotInit(Quaternion(0.01,0,0,.8));
    
    testAttitude.SetAttitude(rotInit);
    Vector AngularVelocity(3);
    Vector ControlTorques(3);
    AngularVelocity(VectorIndexBase) = 0.1;
    ControlTorques(VectorIndexBase) = 0.0;
        
    Matrix MOI = eye(3);
    Vector time(2); 
    time(VectorIndexBase + 0) = 0;
    time(VectorIndexBase + 2) = 100;
    
    // End user specified parameters
    testAttitude.SetAngularVelocity(AngularVelocity);
    testAttitude.SetControlTorques(ControlTorques);
    testAttitude.SetMOI(MOI);
    
    testAttitude.SetKinematicsEq(&QuaternionKinematics);
    testAttitude.SetDynamicsEq(&QuaternionDynamics);
    Environment* pEarth = SetupEnvironment(testAttitude);
    testAttitude.SetEnvironment(pEarth);
/*    
    cout << ~testAttitude.GetAttitude().GetRotation(Quaternion_Type) << endl;
    cout << ~testAttitude.GetAttitude().GetRotation(DCM_Type) << endl;
    cout << ~testAttitude.GetAttitude().GetRotation(EulerAngle_Type) << endl;
    cout << ~testAttitude.GetAttitude().GetRotation(EulerAxisAngle_Type) << endl;
*/
    cout << "Propagating..." << endl;
    testAttitude.Propagate(time);
    
    cout << "History: "<< endl << testAttitude.GetHistory();

    delete pEarth;
    return 0;
}

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: testDynamics.cpp,v $
*	Revision 1.4  2005/06/30 11:24:18  nilspace
*	Fixed some of the include file names - still several errors due to function name changes.
*	
*	Revision 1.3  2003/04/23 16:30:59  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.2  2003/03/27 02:47:29  nilspace
*	Updated to propagate a satellite forward for 10 seconds and return the history.
*	
*	Revision 1.1  2003/03/25 02:26:00  nilspace
*	initial submission of test files.
*	
*	
*
******************************************************************************/

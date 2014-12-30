//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file testOrbitIntegration.cpp
*  \brief Example of orbit integration using Open-Sessame.
*  \author $Author: nilspace $
*  \version $Revision: 1.4 $
*  \date    $Date: 2003/08/24 20:59:13 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*!  
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "orbitmodels/TwoBodyDynamics.h"
#include "Matrix.h"
#include "RungeKuttaFehlbergIntegrator.h"
#include "OrbitState.h"
#include "Plot.h"
#include "orbitframes/OrbitFrameIJK.h"
#include "orbitstaterep/PositionVelocity.h"
#include "LinearInterpolator.h"

#include <vector.h>
using namespace std;
using namespace O_SESSAME;

/*! \brief Force function that will be called each timestep */
Vector OrbitForcesFunctor(const ssfTime& _pSSFTime, const OrbitState& _pOrbitState, const AttitudeState& _pAttitudeState)
{
    Vector Forces;
    Vector Position(3); Position(_) = _pOrbitState.GetStateRepresentation()->GetPositionVelocity()(_(VectorIndexBase,VectorIndexBase+2));
    Forces = -398600.4418 / pow(norm2(Position),3) * Position;
    return Forces;
}

Vector OrbitForcesWithDragFunctor(const ssfTime& _pSSFTime, const OrbitState& _pOrbitState, const AttitudeState& _pAttitudeState)
{
    Vector Forces;
    Vector Position(3); Position(_) = _pOrbitState.GetStateRepresentation()->GetPositionVelocity()(_(VectorIndexBase,VectorIndexBase+2));
            
    double BC = 0.5;
    Vector Vrel(3); Vrel = _pOrbitState.GetStateRepresentation()->GetPositionVelocity()(_(VectorIndexBase+3,VectorIndexBase+5));
    double Vrel_mag = norm2(Vrel);
    Forces = -398600.4418 / pow(norm2(Position),3) * Position;
    
    Forces += -1/2 *1/BC * pow(Vrel_mag,2) * Vrel / Vrel_mag; 
    return Forces;
}

int main()
{
    /////////////////////////////////////////////////
    // Setup an integrator and any special parameters
    RungeKuttaFehlbergIntegrator myIntegrator; 
        int numOrbits = 1;
        int numSteps = 100;
    cout << "Number of Orbits: " << flush;
    cin >> numOrbits;
    cout << "Number of Integration Steps: "<< flush;
    cin >> numSteps;
    //myIntegrator.SetNumSteps(numSteps);
    
    vector<ssfTime> integrationTimes;
    ssfTime begin(0);
    ssfTime end(begin + 92*60*numOrbits);
    integrationTimes.push_back(begin);
    integrationTimes.push_back(end);
    
    /////////////////////////////////////////////////
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
    myOrbit.GetStateRepresentation()->SetPositionVelocity(initPV);

    SpecificFunctor OrbitForcesFunctor(&OrbitForcesWithDragFunctor);

    /////////////////////////////////////////////////
    // Create the matrix of parameters needed for the RHS
    Matrix Parameters(1,1);
    Parameters(MatrixIndexBase,MatrixIndexBase) = 398600.4418; //km / s^2


    /////////////////////////////////////////////////
    cout << "PropTime = " << begin.GetSeconds() << " s -> " << end.GetSeconds() << " s" << endl;
    cout << "Orbit State: " << ~myOrbit.GetStateRepresentation()->GetPositionVelocity() << endl;

    // Integrate over the desired time interval
    tick();
    Matrix history = myIntegrator.Integrate(
                            integrationTimes, 		// seconds
                            &TwoBodyDynamics, 
                            myOrbit.GetStateRepresentation()->GetPositionVelocity(),
                            NULL,
                            NULL,
                            Parameters,
                            OrbitForcesFunctor
                        );

    cout << "finished propagating in " << tock() << " seconds." << endl;
    
    /////////////////////////////////////////////////
    // Plot the flight history
    //cout << history;
    Matrix plotting = history(_,_(MatrixIndexBase+1,MatrixIndexBase+3));

    Plot3D(plotting);
    
    /////////////////////////////////////////////////
    // Store the output to file
    ofstream ofile;
    ofile.open("OrbitHistory.dat");
    ofile << history;
    ofile.close();
    
    //////////////////////////////////////////////////////////////
    // Create an OrbitHistory object (uses a LinearInterpolator)
    OrbitHistory myOrbHistory;
    myOrbHistory.SetInterpolator(new LinearInterpolator);
    Vector PosVel(6);
    for(int jj = 1;jj <= history[MatrixRowsIndex].getIndexBound(); ++jj)
    {
        PosVel(_) = ~history(jj,_(2,7));
        myOrbit.GetStateRepresentation()->SetPositionVelocity(PosVel);
        myOrbHistory.AppendHistory(history(jj,1), myOrbit);
    }
    
    ///////////////////////////////////////////////////////////
    // Ask the user for a specified time to inspect the state.
    double inspectTime;
    cout << "Output state at time (s): " << flush;
    cin >> inspectTime;
    ssfTime myTime(inspectTime);
    myOrbHistory.GetState(myTime, myOrbit);
    cout << myTime.GetSeconds() << " : " << ~myOrbit.GetStateRepresentation()->GetPositionVelocity() << endl;

    return 0;
}


// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: testOrbitIntegration.cpp,v $
*	Revision 1.4  2003/08/24 20:59:13  nilspace
*	Updated.
*	
*	Revision 1.3  2003/05/13 18:56:15  nilspace
*	Fixed to work with new integrators, History, and interpolation.
*	
*	Revision 1.2  2003/04/23 16:30:59  nilspace
*	Various bugfixes & uploading of all changed code for new programmers.
*	
*	Revision 1.1  2003/04/08 23:05:58  nilspace
*	Initial submission.
*	
*
******************************************************************************/

                        

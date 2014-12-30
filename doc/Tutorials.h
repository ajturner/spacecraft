/*! \page TutorialsPage Tutorials
  \ref TableOfContents : \ref IntroductionPage : \ref TutorialAnswersPage

    The following sections are sets of tutorials meant to lead the user through the basics of using the Open-Sessame Framework
all the way to creating a full spacecraft simulation application. Each section is a listing of a textual 
description of the problem to be solved, followed by a reference to the answer sheet. Don't cheat! Following the 
successful completion of each lesson, the user should move onto the next lesson until all the tutorials are complete.

\par Running Tutorials:
    To build and run a tutorial, (after writing your file, e.g. myFile.cpp) follow the following instructions:
    -# Put the @em .cpp file in the @em spacecraft/src/test directory:
        \verbatim cp myFile.cpp spacecraft/src/test 
            cd spacecraft/src/test\endverbatim
        or use whatever method you choose for getting it there (ftp, sftp, scp, drag -n- drop, mv, etc.)
    -# Build the program by running the generalized makefile with the target of your source file, minus the @em cpp extension:
        \verbatim make myFile \endverbatim
    -# Run the program in the same directory (the executable will be the same as the source file minus the extension):
        \verbatim ./myFile \endverbatim
    -# Debug the code (unless your implementation was perfect, then check your answers)
        - If you need help check the suggested \ref ProgrammingTroubleshooting
        
  \section RotationTutorials Rotation Tutorials
-# Create a Quaternion that has the initial parameters (0.5,0.5,0.5,0.5).
-# Output this quaternion to the console in both quaternion and Modified Rodriguez Parameters (MRP) form.
-# Create a Direction Cosine Matrix corresponding to a 321 rotation with angles: 10, -30, 150 degrees.
-# Create 2 "Rotation"s that are intialized by the quaternion and Direction Cosine Matrix.
-# Determine the successive rotation of these two rotations and output to the console in DCM form.
-# Verify that the answer you got was the correct (expected) one.

\ref TutorialAnswersPage

\section UtilityTutorials Utility Tutorials
-# Create an ssfTime object, set the epoch to the current real time, and the stored 'current' time to 50 seconds later. Output both of these in DateTime and JulianDate format to the console.
-# Plot a Matrix of values corresponding to the \f$ f(x)=\sin{x}\f$ for \f$x=0:2\pi \f$ using the Open-Sessame GnuPlot interface.
-# Create a linear interpolation of the \f$\sin{}\f$ function using a step-size of 0.1

\ref TutorialAnswersPage

  \section AttitudeTutorials Attitude Tutorials
-# Create an AttitudeState object instance that is initialized to an aligned rotation in the Orbit-Inertial Frame (attitudeframe not yet implemented fully).
-# Integrate an attitude for 50 seconds using the following conditions:
    - Quaternion Kinematics
    - Euler's equations of motion
    - Gravity-gradient torque disturbance
    - Initial conditions of: \f$\bar{\bf q}_0 = [0,0,0,1]^{T}\f$ and \f$\omega_{0} = [0,0.1, -0.05]^{T} \frac{rad}{s}\f$.
    - Principle Moments of Inertia: \f$[100, 300, 150]\f$
-# Store the attitude to a text file.
-# Plot the attitude history using GnuPlot.
-# Store the attitude in DirectionCosineMatrix format in a MatLab file.

\ref AttitudeTutorialAnswer

  \section OrbitTutorials Orbit Tutorials
-# Create an OrbitState object instance that is initialized to the current state of the spacestation in inertial coordinates.
-# Convert to ECEF coordinates and output to the console. 
-# Integrate an orbit for 2 orbits using the following conditions:
    - 2-body force function above the Earth (mass = 200 kg).
    - Solar-radiation pressure force disturbance (assume constant \f$Area=20 m^2\f$).
    - Initial conditions of: \f${\bf r}=[-5776.6, -157, 3496.9]^{T}\f$ (km) and \f${\bf v} = [-2.595, -5.651, -4.513]^{T}\f$ (km/s).
-# Store the position and velocity to a text file.
-# Plot the orbit position vector using GnuPlot.
-# Store the orbit Keplerian parameters in a MatLab file.

\ref OrbitTutorialAnswer

\section CoupledTutorials Coupled Attitude & Orbit Tutorials
-# Create an Environment object of the Earth using the above (Orbit \& Attitude) disturbance force \& torque functions.
-# Create a Propagator that will propagate the above Orbit \& Attitude objects and using the Environment object.
    - Use a linear interpolator for the OrbitHistory.
    - Use loose coupling (orbit independent of attitude, but attitude dependent on position).
-# Propagate the orbit and attitude for 2 orbits.
-# Plot the position and attitude using gnuplot.
-# Propagate another 2 orbits.
-# Add the new states to the previously made plots.

\ref CoupledTutorialAnswer
*/

/*! \page TutorialAnswersPage Tutorial Answers Page
  \ref TableOfContents : \ref IntroductionPage : \ref TutorialsPage

\section RotationTutorialAnswer Rotation Tutorial Answer

\code
// Create a Quaternion that has the initial parameters (0.5,0.5,0.5,0.5).
Quaternion myQuat(0.5, 0.5, 0.5, 0.5);

// Output this quaternion to the console in both quaternion and MRP form
cout << myQuat;
cout << myQuat.GetMRP();

// Create a Direction Cosine Matrix corresponding to a 321 rotation with angles: 10, -30, 150 degrees.
DirectionCosineMatrix myDCM(10*RPD, -30*RPD, 150*RPD, 321);

// Create 2 "Rotation"s that are intialized by the quaternion and Direction Cosine Matrix.
Rotation myRot1(myQuat);
Rotation myRot2(myDCM);

// Determine the successive rotation of these two rotations and output to the console in DCM form.
cout << (myRot1 * myRot2).GetDCM();

// Verify that the answer you got was the correct (expected) one. 
Matrix Answer(3,3);

\endcode

Back to: \ref RotationTutorials
<hr>

\section UtilityTutorialAnswer Utility Tutorial Answer
-# Create an ssfTime object, set the epoch to the current real time, and the stored 'current' time to 50 seconds later. Output both of these in DateTime and JulianDate format to the console.
\code
ssfTime myTime;
myTime.SetEpoch(Now());
myTime.Set(myTime.GetEpoch() + 50);
cout << myTime.GetDateTime().tm_mon << "/" << myTime.GetDateTime().tm_mday << "/" << myTime.GetDateTime().tm_year << endl;
cout << myTime.GetJulianDate() << endl;
\endcode

-# Plot a Matrix of values corresponding to the \f$ f(x)=\sin{x}\f$ for \f$x=0:2\pi \f$ using the Open-Sessame GnuPlot interface.
\code
int stepsize = 0.1;
Matrix datavec(2*M_PI / stepsize,2);
for (int jj = 1; jj <= datavec[MatrixRowsIndex].getIndexBound();  ++jj)
{
    datavec(jj,1) = jj * stepsize;
    datavec(jj,2) = sin(jj * stepsize);
}
Plot2D(datavec);
\endcode
-# Create a linear interpolation of the \f$\sin{}\f$ function using a step-size of 0.1
\code
int stepsize = 0.1;
Vector timeVec(2*M_PI / stepsize);
Matrix dataMat(timeVec[MatrixRowsIndex].getIndexBound(), 1);
for (int jj = 1; jj < timeVec[MatrixRowsIndex].getIndexBound();  ++jj)
{
    timeVec(jj) = jj * stepsize;
    dataMat(jj,1) = sin(jj * stepsize);
}

LinearInterpolator interp(timeVec,dataMat);
Vector chk = interp.Evaluate(0.25);
cout <<  timevec << endl << datavec << endl << sin(0.25) << " = " << chk << endl;
\endcode
Back to: \ref UtilityTutorials
<hr>

\section AttitudeTutorialAnswer Attitude Tutorial Answer
-# Create an AttitudeState object instance that is initialized to an aligned rotation in the Orbit-Inertial Frame (attitudeframe not yet implemented fully).
\code
AttitudeState myAttState(Rotation(), new AttitudeFrameOI);
\endcode

-# Integrate an attitude for 50 seconds using the following conditions:

First setup the kinematics equation:
\code
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

    return stateDot;
}
\endcode

Then setup the driver code to run the above dynamics equation:
\code
// Setup an integrator and any special parameters
RungeKuttaIntegrator myIntegrator; 
myIntegrator.SetNumSteps(1000);
// Integration times
vector<ssfTime> integrationTimes;
ssfTime begin(0);
ssfTime end(begin + 50);
integrationTimes.push_back(begin);
integrationTimes.push_back(end);

// Create the initial attitude state
AttitudeState myAttitudeState;
myAttitudeState.SetRotation(Rotation(Quaternion(0,0,0,1)));
Vector initAngVelVector(3);
    initAngVelVector(1) = 0;
    initAngVelVector(2) = 0.1;
    initAngVelVector(2) = -0.5;
myAttitudeState.SetAngularVelocity(initAngVelVector);
SpecificFunctor AttitudeForcesFunctor(&NullFunctor);

// Create the matrix of parameters needed for the RHS - MOI
Matrix Parameters = eye(3);
    Parameters(1) = 100;
    Parameters(2) = 300;
    Parameters(3) = 150;
    
// Integrate over the desired time interval
Matrix history = myIntegrator.Integrate(
                            integrationTimes, 		// seconds
                            &AttituteDynamics, 
                            myAttitudeState.GetState(),
                            NULL,
                            NULL,
                            Parameters,
                            AttitudeForcesFunctor
                        );
\endcode
-# Store the attitude to a text file.
\code
ofstream ofile;
ofile.open("AttitudeHistory.dat");
ofile << history;
ofile.close();
\endcode

-# Plot the attitude history using GnuPlot.
\code
Matrix plotting = history(_,_(MatrixIndexBase,MatrixIndexBase+4));
Plot2D(plotting);
\endcode

-# Store the attitude in DirectionCosineMatrix format in a MatLab file.

Back to: \ref AttitudeTutorials
<hr>

\section OrbitTutorialAnswer Orbit Tutorial Answer
Setup the dynamic equations:
\code
static Vector TwoBodyDynamics(const ssfTime &_time, const Vector& _integratingState, Orbit *_Orbit, Attitude *_Attitude, const Matrix &_parameters, const Functor &_forceFunctorPtr)
{
    static Vector Forces(3);
    static Vector Velocity(3);
    static Vector stateDot(6);
    static AttitudeState tempAttState; // don't need this except to pass an empty one if there is no attitude
    static OrbitState orbState(new PositionVelocity);

    orbState.GetStateRepresentation()->SetPositionVelocity(_integratingState);

    if(_Attitude)
        Forces = _forceFunctorPtr.Call(_time, orbState, _Attitude->GetStateObject());
    else 
        Forces = _forceFunctorPtr.Call(_time, orbState, tempAttState);

    Velocity(_) = _integratingState(_(VectorIndexBase+3,VectorIndexBase+5));
    

    stateDot(_(VectorIndexBase, VectorIndexBase+2)) = Velocity(_);
    stateDot(_(VectorIndexBase+3, VectorIndexBase+5)) = Forces(_);
    return stateDot;
}
\endcode
The force functions are setup as follows (using drag instead of solar radiation pressure):
\code
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
\endcode

Finally create the driver program and call the integration:
\code
// Setup an integrator and any special parameters
RungeKuttaIntegrator myIntegrator; 
    int numOrbits = 2;
    int numSteps = 100;
myIntegrator.SetNumSteps(numSteps);
    
vector<ssfTime> integrationTimes;
ssfTime begin(0);
ssfTime end(begin + 92*60*numOrbits);
integrationTimes.push_back(begin);
integrationTimes.push_back(end);
    
OrbitState myOrbitState;
myOrbitState.SetStateRepresentation(new PositionVelocity);
myOrbitState.SetOrbitFrame(new OrbitFrameIJK);
Vector initPV(6);
    initPV(VectorIndexBase+0) = -5776.6; // km/s
    initPV(VectorIndexBase+1) = -157; // km/s        
    initPV(VectorIndexBase+2) = 3496.9; // km/s    
    initPV(VectorIndexBase+3) = -2.595;  // km/s
    initPV(VectorIndexBase+4) = -5.651;  // km/s        
    initPV(VectorIndexBase+5) = -4.513; // km/s
myOrbitState.GetStateRepresentation()->SetPositionVelocity(initPV);

Matrix history = myIntegrator.Integrate(
                            integrationTimes, 		// seconds
                            &TwoBodyDynamics, 
                            myOrbit.GetStateRepresentation()->GetPositionVelocity(),
                            NULL,
                            NULL,
                            Parameters,
                            OrbitForcesFunctor
                        );
\endcode

-# Store the position and velocity to a text file.
\code
ofstream ofile;
ofile.open("OrbitHistory.dat");
ofile << history;
ofile.close();
\endcode

-# Plot the orbit position vector using GnuPlot.
\code
// Create the plot using Columns 2:4
Matrix orbitHistory = myOrbit->GetHistory().GetHistory();
Matrix orbitPlotting = orbitHistory(_,_(2,4));
Plot3D(orbitPlotting);
\endcode
Here is a check for your answer (without solar radiation pressure):
\verbatim
[ time, r1, r2, r3, v1, v2, v3]
[ 5400, -5386.654,  562.845,  4034.074, -3.518027, -5.617977, -3.890888 ] 
\endverbatim

-# Store the orbit Keplerian parameters in a MatLab file.

Back to: \ref OrbitTutorials

\section CoupledTutorialAnswer Coupled Tutorial Answers
-# Create an Environment object of the Earth using the above (Orbit \& Attitude) disturbance force \& torque functions.

-# Create a Propagator that will propagate the above Orbit \& Attitude objects and using the Environment object.
    - Use a linear interpolator for the OrbitHistory.
    - Use loose coupling (orbit independent of attitude, but attitude dependent on position).

-# Propagate the orbit and attitude for 2 orbits.

-# Plot the position and attitude using gnuplot.

-# Propagate another 2 orbits.

-# Add the new states to the previously made plots.

Back to: \ref CoupledTutorials

*/

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file HokieSatSimulation.h
*  \brief Include files and function prototypes for HokieSat attitude simulation example.
*  \author $Author: nilspace $
*  \version $Revision: 1.3 $
*  \date    $Date: 2003/08/24 20:59:13 $
*//////////////////////////////////////////////////////////////////////////////////////////////////


// Standard includes
#include "Matrix.h"
#include "Rotation.h"

// Dynamics includes
#include "CombinedNumericPropagator.h"
#include "RungeKuttaFehlbergIntegrator.h"

// Orbit Includes
#include "Orbit.h"
#include "OrbitState.h"
#include "orbitmodels/TwoBodyDynamics.h"
#include "orbitstaterep/PositionVelocity.h"
#include "orbitframes/OrbitFrameIJK.h"

// Attitude includes
#include "Attitude.h"
#include "AttitudeState.h"
#include "AttitudeModels/QuaternionAngVelDynamics.h"

// Environment Includes
#include "CentralBody/EarthCentralBody.h"
#include "CentralBody/Models/TiltedDipoleMagneticModel.h"
#include "Disturbances/GravityFunctions.h"
#include "Disturbances/SimpleAerodynamicDisturbances.h"

// Utility Includes
#include "Plot.h"
#include "MathUtils.h"

using namespace O_SESSAME;

/** @brief Sets up a combined numeric propagator, RK4(5) integrator and tolerances. */
NumericPropagator* SetupPropagator();
/** @brief Creates an Earth environment with point-mass, two-body gravity, gravity-gradient torque, 
    * and a tilted-dipole magnetic field model. */
Environment* SetupEnvironment(Attitude* pSatAttitude);

/** @brief Creates an initial orbit read in from a file. */
Orbit* SetupOrbit();

/** @brief Creates an initial attitude read in from a file. */
Attitude* SetupAttitude();

/** @brief HokieSat magnetic controller algoritm.
    * @author Hye-Young Kim
    */
Vector ControlTorques(Matrix CurrentAttState, Matrix DesAttState, double epoch, double count);

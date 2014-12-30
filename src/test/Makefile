# Spacecraft Simulation Framework
# Testing Makefile
#
# $Author: nilspace $
# $Revision: 1.13 $
# $Date: 2006/07/14 02:51:45 $

# Which compiler to use
CC      = gcc
CFLAGS 		= -g -Wall $(INCLUDE)

INCLUDE 	= -I../ -I../matrix -I../rotation \
		-I../kinematics -I../dynamics -I../utils \
		-I../datahandling -I../orbit -I../environment \
		-I../attitude -I../orbit/orbitstaterep -I../environment/CentralBody
LIBDIR		= ../../lib/
 
LDFLAGS 	= -L$(LIBDIR) \
		-losessame_rotation -losessame_matrix \
		-losessame_attitude \
		-losessame_environment \
		-losessame_dynamics -losessame_utils \
		-losessame_datahandling -losessame_orbit -losessame_math \
		-L/usr/lib -lstdc++ 

all: working

working: testMatrix testIntegration testEnvironment testOrbitIntegration testAttitudeIntegration 
nonworking: testPropagation testRotation testDynamic testHokieSatSimulation

math: testMatrix testRotation testIntegration
eng: testPropagation testDynamics
complex: testOrbitIntegration testEnvironment testAttitudeIntegration HokieSatSimulation

SimServer.o: SimServer.cpp 
	c++ -DNETXX_NO_INET6 $(CFLAGS) $(INCLUDE) -I'/Users/aturner/Projects/OSS_Packages/comm/Netxx/include' -g -c SimServer.cpp

SimServer: SimServer.o
	c++ -o SimServer SimServer.o '/Users/aturner/Projects/OSS_Packages/comm/Netxx/src/libNetxx.a' ${LDFLAGS}
	
%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $*.cpp

.cpp : FORCE clean
	$(CC) $(CFLAGS) $(INCLUDE) -c $<
	$(CC) -o $* $*.o ${LDFLAGS}
.o : FORCE $<
	$(CC) -o $* $*.o ${LDFLAGS} 
clean:
	-rm *.o

# /*****************************************************************************
# *	$Log: Makefile,v $
# *	Revision 1.13  2006/07/14 02:51:45  nilspace
# *	Cleaned up Makefile to build the currently working tests by default
# *	
# *	Revision 1.12  2003/08/24 20:59:13  nilspace
# *	Updated.
# *	
# *	Revision 1.11  2003/05/21 13:57:08  nilspace
# *	Updated to call correct libraries.
# *	
# *	Revision 1.10  2003/05/21 13:54:46  nilspace
# *	Updated libraries to be prefixed by osessame_
# *	
# *	Revision 1.9  2003/05/20 19:24:43  nilspace
# *	Updated.
# *	
# *	Revision 1.8  2003/05/19 19:20:50  nilspace
# *	Removed all the old targets and made a single target that is generalized to build any .cpp requested by 'make myfile.cpp'. Builds with the entire Open-Sessame framework which may be inefficient.
# *	
# *	Revision 1.7  2003/05/13 18:56:49  nilspace
# *	Cleaned up the build targets a little bit.
# *	
# *	Revision 1.6  2003/05/01 15:30:18  nilspace
# *	Updated to work with AttitudeSimulatorServer
# *	
# *	Revision 1.5  2003/04/29 20:57:48  nilspace
# *	Updated to work with Propagator.
# *	
# *	Revision 1.4  2003/04/27 22:04:33  nilspace
# *	Created the namespace O_SESSAME.
# *	
# *	Revision 1.3  2003/04/23 16:30:59  nilspace
# *	Various bugfixes & uploading of all changed code for new programmers.
# *	
# *	Revision 1.2  2003/04/08 22:52:39  nilspace
# *	Updated to work with Orbit Integration and Environment tests.
# *	
# *	Revision 1.1  2003/03/25 02:26:20  nilspace
# *	initial submission of test makefile.
# *	
# *	Revision 1.2  2003/03/05 20:39:42  nilspace
# *	Now creates librotation.a in the src/rotation directory.
# *	
# *	Revision 1.1  2003/03/05 20:21:44  nilspace
# *	New Makefile for making the rotation library. Prelminary version, need to add linking into a library.
# *	
# *
# ******************************************************************************/


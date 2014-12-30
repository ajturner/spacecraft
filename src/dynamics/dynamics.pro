#
# $Id: dynamics.pro,v 1.3 2003/10/18 21:37:28 rsharo Exp $
#
# Copyright (C) 2002-2003 by Andrew J. Turner.
#
# Permission to use, copy, modify, and distribute this software and its
# documentation under the terms of the GNU General Public License is hereby 
# granted. No representations are made about the suitability of this software 
# for any purpose. It is provided "as is" without express or implied warranty.
# See the GNU General Public License for more details.

HEADERS  	= 	Propagator.h NumericPropagator.h \
			 CombinedNumericPropagator.h
SOURCES	 	=	Propagator.cpp NumericPropagator.cpp \
			 CombinedNumericPropagator.cpp
TARGET	 	= 	osessame_dynamics
VERSION  	= 	1.0
DESTDIR		=	../../lib/
INCLUDEPATH	=	../matrix/ ../rotation ../attitude \
			../orbit ../datahandling ../dynamics \
			../environment ..
CONFIG 		= 	console staticlib warn_on debug
TEMPLATE 	= 	lib
OBJECTS_DIR 	= 	../../objects
DEPENDPATH  	= 	../matrix/ ../rotation ../attitude \
			../orbit ../datahandling ../dynamics \
			../environment ../utils

#
# $Id: matrix.pro,v 1.3 2003/12/05 15:43:30 rsharo Exp $
#
# Copyright (C) 2002-2003 by Andrew J. Turner.
#
# Permission to use, copy, modify, and distribute this software and its
# documentation under the terms of the GNU General Public License is hereby 
# granted. No representations are made about the suitability of this software 
# for any purpose. It is provided "as is" without express or implied warranty.
# See the GNU General Public License for more details.

HEADERS  	= 	*.h camblas/*.h camlapack/*.h
SOURCES	 	=	arraybse.cpp\
        		arrayutl.cpp\
        		datahndl.cpp\
        		dbengnea.cpp\
        		dbengneb.cpp\
        		dmatrix.cpp\
        		matbse.cpp\
        		matutl.cpp\
        		mvaexit.cpp\
        		mvalngbase.cpp\
        		range.cpp\
        		strctbse.cpp\
        		under.cpp\
        		vecbse.cpp\
        		vecutl.cpp \
			camblas/*.c camblas/*.cpp \
			camlapack/*.c

TARGET	 	= 	osessame_matrix
VERSION  	= 	1.0
DESTDIR		=	../../lib/
INCLUDEPATH 	= 	camblas/ camlapack/
CONFIG 		= 	console staticlib warn_on debug
TEMPLATE 	= 	lib
OBJECTS_DIR 	= 	../../objects
DEPENDPATH  	= 	

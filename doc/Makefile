# Spacecraft Simulation Framework
# Makefile
#
# $Author: nilspace $
# $Revision: 1.2 $
# $Date: 2003/09/01 23:03:04 $

# Which compiler to use
CC      = gcc

all: doxyfile 
	doxygen doxyfile

archive: doxyfile 
	pushd html; tar -cvf OpenSessameDoc.tar *; mv *.tar ../; popd;
	gzip OpenSessameDoc.tar;

clean:
	rm -rf html/
	rm -f doxygen.error


FORCE:
# /*****************************************************************************
# *	$Log: Makefile,v $
# *	Revision 1.2  2003/09/01 23:03:04  nilspace
# *	Updating to do a recursive build.
# *	
# *	Revision 1.1  2003/05/21 03:47:54  nilspace
# *	New documentation makefile.
# *	
# *	Revision 1.7  2003/05/20 19:12:54  nilspace
# *	Updated to call qmake.
# *	
# *	Revision 1.6  2003/05/15 20:48:51  simpliciter
# *	removed explicit gcc-3.1 call
# *	
# *	Revision 1.5  2003/05/15 19:49:20  simpliciter
# *	Passing CFLAGS to sub-Makefiles.
# *	
# *	Revision 1.4  2003/05/15 19:47:07  simpliciter
# *	Added -Wno-deprecated to CFLAGS line to suppress error messages.
# *	
# *	Revision 1.3  2003/05/15 19:38:21  simpliciter
# *	Sub-Makefiles will be called with the CC identified at the top of this file.
# *	
# *	Revision 1.2  2003/05/15 18:41:39  nilspace
# *	Updated the clean: target.
# *	
# *	Revision 1.1  2003/05/01 15:02:12  nilspace
# *	New makefile for building the Open-SESSAME libraries and documentation.
# *	
# *
# ******************************************************************************/

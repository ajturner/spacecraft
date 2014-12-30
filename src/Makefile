# Spacecraft Simulation Framework
# Makefile
#
# $Author: nilspace $
# $Revision: 1.3 $
# $Date: 2003/05/22 03:07:26 $

QMAKE		= qmake

ROTATIONDIR 	= rotation/
MATRIXDIR 	= matrix/
ENVDIR		= environment/
ORBDIR		= orbit/
MATHDIR		= utils/
ATTDIR		= attitude/
DATADIR		= datahandling/
DYNDIR		= dynamics/
UTILDIR		= utils/

all:
	$(MAKE) -C ${MATRIXDIR}   all
	$(MAKE) -C ${ROTATIONDIR} all
	$(MAKE) -C ${ENVDIR} 	  all
	$(MAKE) -C ${ORBDIR} 	  all
	$(MAKE) -C ${MATHDIR} 	  all
	$(MAKE) -C ${ATTDIR} 	  all
	$(MAKE) -C ${DATADIR} 	  all
	$(MAKE) -C ${DYNDIR} 	  all
	$(MAKE) -C ${UTILDIR} -f Makefile.math all
	$(MAKE) -C ${UTILDIR} -f Makefile.utils all


qmake:
	cd ${MATRIXDIR}	  ; $(QMAKE) 
	cd ${ROTATIONDIR} ; $(QMAKE)
	cd ${ENVDIR} 	  ; $(QMAKE)
	cd ${ORBDIR} 	  ; $(QMAKE)
	cd ${MATHDIR} 	  ; $(QMAKE)
	cd ${ATTDIR} 	  ; $(QMAKE)
	cd ${DATADIR} 	  ; $(QMAKE)
	cd ${DYNDIR} 	  ; $(QMAKE)
	cd ${UTILDIR} 	  ; $(QMAKE) utils.pro -o Makefile.utils
	cd ${UTILDIR} 	  ; $(QMAKE) math.pro -o Makefile.math


clean:
	$(MAKE) -C  $(MATRIXDIR)   clean
	$(MAKE) -C  ${ROTATIONDIR} clean
	$(MAKE) -C  ${ENVDIR} 	   clean
	$(MAKE) -C  ${ORBDIR} 	   clean
	$(MAKE) -C  ${MATHDIR} 	   clean
	$(MAKE) -C  ${ATTDIR} 	   clean
	$(MAKE) -C  ${DATADIR} 	   clean
	$(MAKE) -C  ${DYNDIR} 	   clean
	$(MAKE) -C  ${UTILDIR} 	   clean

archive: clean
	tar zcvf dx`date +%y%m%d`.tgz doc src Makefile INSTALL LICENSE VERSION packages

FORCE:
# /*****************************************************************************
# *	$Log: Makefile,v $
# *	Revision 1.3  2003/05/22 03:07:26  nilspace
# *	Uncommented the matrix qmake target.
# *	
# *	Revision 1.2  2003/05/21 03:46:13  nilspace
# *	Updated to work.
# *	
# *	Revision 1.1  2003/05/20 18:15:37  nilspace
# *	Initial Submission of src/ makefile.
# *	
# *	Revision 1.2  2003/05/15 18:41:39  nilspace
# *	Updated the clean: target.
# *	
# *	Revision 1.1  2003/05/01 15:02:12  nilspace
# *	New makefile for building the Open-SESSAME libraries and documentation.
# *	
# *
# ******************************************************************************/

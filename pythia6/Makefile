main :
	cons

CERNDIR  = /cern/pro
CERNLIB  = -L${CERNDIR}/lib 

FOR      = gfortran
FOROPT   = -m32 -O -g -u -extend_source -Wno-unused ${DEFINES} -lgfortran -xf77-cpp-input -I.

LD       = ./gxint
LDOPT	 = -m -d Motif $(CERNLIB) -L/usr/X11R6/lib -lX11 -lc -lm

objects := $(patsubst %.f,%.o,$(wildcard *.f))
incs    := $(wildcard *.inc)
srcs    := $(wildcard *.f)
     
ip2 : $(objects) $(incs) Makefile	
	$(LD) $(LDOPT) -o ip2 $(objects) 

.f.o:  $(incs)
	$(FOR) -c $(FOROPT) $<

depend: $(srcs)
	makedepend $(incs) $^

clean :
	rm -f *.o ip2

# DO NOT DELETE

uhit.o: max.inc ugeom.inc
untp.o: max.inc
gfpd.o: geant321/gctrak.inc ugeom.inc uswitch.inc rhsys.inc
guhadr.o: uswitch.inc
gukine.o: geant321/gcflag.inc geant321/gckine.inc geant321/gcscan.inc
gukine.o: heppart.inc grndm.inc uswitch.inc
guout.o: geant321/gcflag.inc geant321/gcscan.inc uswitch.inc
gustep.o: geant321/gckine.inc geant321/gcking.inc geant321/gckmax.inc
gustep.o: geant321/gctmed.inc geant321/gcvolu.inc geant321/gctrak.inc
gustep.o: geant321/gcscan.inc geant321/gcsets.inc geant321/gcflag.inc
gustep.o: uswitch.inc uhit.inc max.inc ugeom.inc
gutrev.o: uswitch.inc uhit.inc max.inc ugeom.inc
pgeom.o: geant321/gctrak.inc ugeom.inc uswitch.inc
ugeom.o: geant321/gctrak.inc ugeom.inc uswitch.inc rhsys.inc
uginit.o: uswitch.inc
uglast.o: uswitch.inc grndm.inc
uhist.o: ugeom.inc digi.inc uhit.inc max.inc untp.inc
untp.o: geant321/gcflag.inc untp.inc max.inc uswitch.inc heppart.inc
untp.o: geant321/gcnum.inc geant321/gckine.inc digi.inc uhit.inc ugeom.inc
uscank.o: geant321/pilot.h geant321/gcbank.inc geant321/gclink.inc
uscank.o: geant321/gcscal.inc geant321/gcscan.inc geant321/gcflag.inc
uscank.o: geant321/gconsp.inc

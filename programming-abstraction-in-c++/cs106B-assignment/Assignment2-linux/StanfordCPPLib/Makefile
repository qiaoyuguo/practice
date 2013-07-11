# Makefile for StanfordCPPLib
#****************************************************************

OBJECTS = \
    console.o \
    direction.o \
    error.o \
    filelib.o \
    gevents.o \
    ginteractors.o \
    gmath.o \
    gobjects.o \
    gtimer.o \
    gtypes.o \
    gwindow.o \
    hashmap.o \
    lexicon.o \
    main.o \
    platform.o \
    point.o \
    random.o \
    simpio.o \
    sound.o \
    startup.o \
    strlib.o \
    thread.o \
    tplatform.o \
    tokenscanner.o

CPPOPTIONS = -fvisibility-inlines-hidden


# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: libStanfordCPPLib.a

libStanfordCPPLib.a: $(OBJECTS)
	ar cr libStanfordCPPLib.a $(OBJECTS)
	ranlib libStanfordCPPLib.a

console.o: console.cpp console.h platform.h
	g++ -c $(CPPOPTIONS) console.cpp

direction.o: direction.cpp direction.h
	g++ -c $(CPPOPTIONS) direction.cpp

error.o: error.cpp error.h
	g++ -c $(CPPOPTIONS) error.cpp

filelib.o: filelib.cpp filelib.h foreach.h strlib.h vector.h
	g++ -c $(CPPOPTIONS) filelib.cpp

gevents.o: gevents.cpp error.h gevents.h gtypes.h
	g++ -c $(CPPOPTIONS) gevents.cpp

ginteractors.o: ginteractors.cpp gevents.h ginteractors.h gobjects.h \
                gtypes.h gwindow.h platform.h
	g++ -c $(CPPOPTIONS) ginteractors.cpp

gmath.o: gmath.cpp gmath.h gtypes.h
	g++ -c $(CPPOPTIONS) gmath.cpp

gobjects.o: gobjects.cpp gobjects.h gtypes.h vector.h
	g++ -c $(CPPOPTIONS) gobjects.cpp

gtimer.o: gtimer.cpp platform.h
	g++ -c $(CPPOPTIONS) gtimer.cpp

gtypes.o: gtypes.cpp error.h gtypes.h strlib.h
	g++ -c $(CPPOPTIONS) gtypes.cpp

gwindow.o: gwindow.cpp gmath.h gwindow.h gtypes.h map.h platform.h stack.h \
           strlib.h vector.h
	g++ -c $(CPPOPTIONS) gwindow.cpp

hashmap.o: hashmap.cpp hashmap.h
	g++ -c $(CPPOPTIONS) hashmap.cpp

lexicon.o: lexicon.cpp error.h lexicon.h strlib.h
	g++ -c $(CPPOPTIONS) lexicon.cpp

main.o: main.cpp
	g++ -c $(CPPOPTIONS) main.cpp

platform.o: platform.cpp error.h platform.h stack.h vector.h
	g++ -c $(CPPOPTIONS) platform.cpp

point.o: point.cpp point.h strlib.h
	g++ -c $(CPPOPTIONS) point.cpp

random.o: random.cpp private/randompatch.h random.h
	g++ -c $(CPPOPTIONS) random.cpp

simpio.o: simpio.cpp simpio.h
	g++ -c $(CPPOPTIONS) simpio.cpp

sound.o: sound.cpp error.h sound.h
	g++ -c $(CPPOPTIONS) sound.cpp

startup.o: startup.cpp error.h
	g++ -c $(CPPOPTIONS) startup.cpp

strlib.o: strlib.cpp error.h strlib.h
	g++ -c $(CPPOPTIONS) strlib.cpp

thread.o: thread.cpp map.h private/tplatform.h
	g++ -c $(CPPOPTIONS) thread.cpp

tplatform.o: tplatform.cpp map.h private/tplatform.h
	g++ -c $(CPPOPTIONS) tplatform.cpp

tokenscanner.o: tokenscanner.cpp error.h stack.h strlib.h tokenscanner.h
	g++ -c $(CPPOPTIONS) tokenscanner.cpp


# ***************************************************************
# Standard entries to remove files from the directories
#    tidy  -- eliminate unwanted files
#    clean -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAM)

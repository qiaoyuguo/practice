TOPDIR = ../../../
INCDIR = ../../../StanfordCPPLib
LIBDIR = $(INCDIR)

CXX=g++
CXXFLAGS=-g

PROGRAM = KarelGoesHome 
OBJECTS = KarelGoesHome.o 

CPPOPTIONS = -I$(INCDIR) -fvisibility-inlines-hidden
LDOPTIONS = -L$(LIBDIR)
LIB = -lStanfordCPPLib

all: $(PROGRAM)

$(PROGRAM):$(OBJECTS)
	rm -rf spl.jar
	ln -s $(LIBDIR)/spl.jar .
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $(CPPOPTIONS) $< -o $@
clean:
	rm -rf *.o *.a $(PROGRAM) *.jar

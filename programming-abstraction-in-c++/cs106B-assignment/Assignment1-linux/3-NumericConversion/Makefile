TOPDIR = ../../../
INCDIR = ../../../StanfordCPPLib
LIBDIR = $(INCDIR)

CXX=g++

PROGRAM = NumericConversion 
OBJECTS = NumericConversion.o

CPPOPTIONS = -I$(INCDIR) -fvisibility-inlines-hidden
LDOPTIONS = -L$(LIBDIR)
LIB = -lStanfordCPPLib

all: $(PROGRAM)

$(PROGRAM):$(OBJECTS)
	rm -rf spl.jar
	ln -s $(LIBDIR)/spl.jar .
	$(CXX) -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

%.o:%.cpp
	$(CXX) -c $(CPPOPTIONS) $< -o $@
clean:
	rm -rf *.o *.a $(PROGRAM) *.jar

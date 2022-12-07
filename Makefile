CXX=c++ #$(CXXFLAGS)
#CXXFLAGS=-Wall # Enable all warnings

ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS=$(shell root-config --libs)

CFLAGS =
LFLAGS =

RCXX=$(CFLAGS) $(ROOTCFLAGS)
RLXX=$(LFLAGS) $(ROOTLIBS)

SRC= Analysis.o Muon.o

%.o: %.C
		$(CXX) $(RCXX) -c $<

all: run

run.o: run.C Analysis.h
		$(CXX) $(RCXX) -c $<

run: $(SRC) run.o
		$(CXX) $(SRC) run.o $(RLXX) -o run


clean:
	-rm -f *.o run
	-rm analysis.root
	-rm *.pdf

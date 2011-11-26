#
# Makefile for non-Microsoft compilers
#

## Linux  (uncomment the 2 lines below for compilation on Linux)
#CXXFLAGS += -std=c++98 -Wall -ggdb
#LDFLAGS += 

## CygWin (uncomment the 2 lines below for compilation on CygWin)
#CXXFLAGS += -Wall
#LDFLAGS += 

all: netinf
 
opt: CXXFLAGS += -O4
opt: LDFLAGS += -O4
opt: netinf

debug: CXXFLAGS += -g
debug: LDFLAGS += -g
debug: netinf

# COMPILE

netinf: netinf.cpp Snap.o
	g++ $(LDFLAGS) -o netinf netinf.cpp cascinf.cpp Snap.o -I./glib -I./snap
	
Snap.o: 
	g++ -c $(CXXFLAGS) ./snap/Snap.cpp -I./glib -I./snap

clean:
	rm -rf   netinf *.dSYM 

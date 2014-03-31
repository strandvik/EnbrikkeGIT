export LD_LIBRARY_PATH=/usr/local/systemc230/lib-linux64:$LD_LIBRARY_PATH
CC     = g++
OPT    = -O3
DEBUG  = -g
OTHER  = -Wno-deprecated -fpermissive
#CFLAGS = $(OPT) $(OTHER)
CFLAGS = $(DEBUG) $(OTHER)

MODULE = run
SRCS = statemachine.cpp top.cpp
OBJS = $(SRCS:.cpp=.o)

all: run.x

statemachine.o: if.h statemachine.h statemachine.cpp

topp.o: if.h statemachine.h top.cpp

ifneq (, $(realpath $(HOME)/systemc/Makefile.defs))
include ~/systemc/Makefile.defs
else ifneq (, $(realpath ../Makefile.defs))
include ../Makefile.defs
else
$(error "Cannot find Makefile.defs")
endif

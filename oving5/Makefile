CC     = g++
OPT    = -O3
DEBUG  = -g
OTHER  = -Wno-deprecated -fpermissive
#CFLAGS = $(OPT) $(OTHER)
CFLAGS = $(DEBUG) $(OTHER)

MODULE = run
SRCS = button.cpp control.cpp top.cpp
OBJS = $(SRCS:.cpp=.o)

all: run.x


topp.o: top.cpp

ifneq (, $(realpath $(HOME)/systemc/Makefile.defs))
include ~/systemc/Makefile.defs
else ifneq (, $(realpath ../Makefile.defs))
include ../Makefile.defs
else
$(error "Cannot find Makefile.defs")
endif

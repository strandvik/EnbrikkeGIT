CC     = g++
OPT    = -O3
DEBUG  = -g
OTHER  = -Wno-deprecated -fpermissive
CFLAGS = $(OPT) $(OTHER)
# CFLAGS = $(DEBUG) $(OTHER)

MODULE = run
SRCS = processor.cpp top.cpp
OBJS = $(SRCS:.cpp=.o)

all: run.x

processor.o: if.h processor.h processor.cpp
top.o: if.h processor.h top.cpp

ifneq (, $(realpath ~/systemc/Makefile.defs))
include ~/systemc/Makefile.defs
else ifneq (, $(realpath ../Makefile.defs))
include ../Makefile.defs
else
$(error "Cannot find Makefile.defs")
endif

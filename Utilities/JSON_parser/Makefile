#########################################################################
# Makefile																#
# Author: Jeffrey McDaniel												#
# Description: Makefile for the architecture and application model data #
# structures															#
#########################################################################
# Release: 1/27/2014													#
# Revision History:														#
# Author   | Date      | Description									#
# Jeffrey  | MM/DD/YY  | Short Description								#
# 																		#
#########################################################################

SHELL=/bin/sh

.SUFFIXES:
.SUFFIXES: .cc .h .ypp .lex

PRG=json_parse
LIB=json_parser.so

OBJS=json_value.o\
	 json_file.o\
	 json_object.o\
	 json_name_value.o\
	 json_parser_bison.o\
	 json_parser.o\
	 json_parser_lex.o

TESTFN=partition_test.json

# C++ compiler
CXXFLAGS=-Wall -ansi -pedantic 
LIBFLAGS=-shared
CXXLIB=-fPIC
CXXINC=-I$(INC) -I../Headers/ -I./ 
CXXOBJS=-c
CXXRN=-o
# Archive
AR=ar
# bison++ compiler
PRE=json
YFN=json_parser_bison.cc
YPP=/usr/bin/bison
YPFLGS=-d 
YRN=-p
YEXT=.ypp
# flex compiler
FPP=flex
FFN=json_parser_lex.cc
FPFLGS=
FRN=-P

# Path variables
INC=Headers/
SRC=Source/
vpath %.cc  $(SRC)
vpath %.h   $(INC)
vpath %.ypp $(SRC)
vpath %.lex $(SRC)

all: $(LIB)

# -------------------------------------------------------------------------

$(LIB): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) $(CXXRN) $(LIB) $(OBJS) $(COMMON)

.PHONY: tester test
tester: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(CXXRN) json_parse $^

test: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(CXXRN) json_parse $^
	./json_parse $(TESTFN)

# -------------------------------------------------------------------------

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CXXLIB) $(CXXINC) $(CXXOBJS) $^
	
%_bison.cc: %.ypp
	@echo Compiling $^
	$(YPP)	 $(YPFLGS) $(YRN)$(PRE) -o $(YFN) $^

%_lex.cc: %.lex
	@echo Compiling $^
	$(FPP) $(FPFLGS) $(FRN)$(PRE) -o$(FFN) $^

clean:
	@echo Removing $(LIB)...
	@rm -f $(LIB)
	@echo Removing all object files...
	@rm -f *.o
	@echo Removing json_parse...
	@rm -f json_parse


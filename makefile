CXX=clang++
LD=ld
CFLAGS=-O0 -g -std=c++14

all: program

program: main.o parse_sexpr.o structure_io.o lisp_eval.o
	$(CXX) $^ -o $@

parse_sexpr.o: parse_sexpr.cpp sexpr_parser.hpp

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


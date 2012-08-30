#
#  Olli's C++ Library
#  examples/Makefile
#  (c) 2012 Oliver Michel
#

INC_DIR=../include
LIB_DIR=../lib

CXXFLAGS=-I$(INC_DIR) -L$(LIB_DIR) -Wall
CXXPOSTFIX=-lom

.PHONY: all
all: bin/ex_tun_device

bin/ex_tun_device:
	$(CXX) $(CXXFLAGS) -o bin/ex_tun_device ex_tun_device.cc $(CXXPOSTFIX)

.PHONY: clean
clean:
	rm -rf bin/*

#
#  Olli's C++ Library
#  examples/Makefile
#  (c) 2012 Oliver Michel
#

INC_DIR=../include
LIB_STATIC_DIR=../lib/static
BIN_DIR=bin

CXXFLAGS=-I$(INC_DIR) -L$(LIB_STATIC_DIR) -Wall
CXXPOSTFIX=-lom

.PHONY: all
all: $(BIN_DIR)/example_tunnel_device $(BIN_DIR)/example_net_addresses

bin/example_tunnel_device: $(BIN_DIR) example_tunnel_device.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_tunnel_device \
			example_tunnel_device.cc $(CXXPOSTFIX)

bin/example_net_addresses: $(BIN_DIR) example_net_addresses.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_net_addresses \
			example_net_addresses.cc $(CXXPOSTFIX)

$(BIN_DIR):
	mkdir -p bin

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)/*

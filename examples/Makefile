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
all: $(BIN_DIR)/example_tunnel_device \
	$(BIN_DIR)/example_net_addresses \
	$(BIN_DIR)/example_raw_socket \
	$(BIN_DIR)/example_net_packing \
	$(BIN_DIR)/example_tools_random \
	$(BIN_DIR)/example_net_stream_client \
	$(BIN_DIR)/example_net_datagram_socket \
	$(BIN_DIR)/example_net_agent \
	$(BIN_DIR)/example_net_stream_listener \
	$(BIN_DIR)/example_net_inotify_handler \
	$(BIN_DIR)/example_tools_file

$(BIN_DIR)/example_tunnel_device: $(BIN_DIR) example_tunnel_device.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_tunnel_device \
			example_tunnel_device.cc $(CXXPOSTFIX)

$(BIN_DIR)/example_net_addresses: $(BIN_DIR) example_net_addresses.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_net_addresses \
			example_net_addresses.cc $(CXXPOSTFIX)

$(BIN_DIR)/example_net_datagram_socket: $(BIN_DIR) example_net_datagram_socket.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_net_datagram_socket \
			example_net_datagram_socket.cc $(CXXPOSTFIX)

$(BIN_DIR)/example_raw_socket: $(BIN_DIR) example_raw_socket.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_raw_socket \
			example_raw_socket.cc $(CXXPOSTFIX)

$(BIN_DIR)/example_net_packing: $(BIN_DIR) example_net_packing.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_net_packing \
			example_net_packing.cc $(CXXPOSTFIX)

$(BIN_DIR)/example_net_agent: $(BIN_DIR) example_net_agent.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_net_agent \
			example_net_agent.cc $(CXXPOSTFIX)

$(BIN_DIR)/example_tools_random: $(BIN_DIR) example_tools_random.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_tools_random \
			example_tools_random.cc $(CXXPOSTFIX)

$(BIN_DIR)/example_net_stream_client: $(BIN_DIR) example_net_stream_client.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_net_stream_client \
			example_net_stream_client.cc $(CXXPOSTFIX)

$(BIN_DIR)/example_net_stream_listener: $(BIN_DIR) example_net_stream_listener.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_net_stream_listener \
			example_net_stream_listener.cc $(CXXPOSTFIX)

$(BIN_DIR)/example_net_inotify_handler: $(BIN_DIR) example_net_inotify_handler.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_net_inotify_handler \
			example_net_inotify_handler.cc $(CXXPOSTFIX)

$(BIN_DIR)/example_tools_file: $(BIN_DIR) example_tools_file.cc
		$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/example_tools_file \
			example_tools_file.cc $(CXXPOSTFIX)

$(BIN_DIR):
	mkdir -p bin

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)/*

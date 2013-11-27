#
#  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
#  examples/Makefile
#  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
#  http://ngn.cs.colorado/~oliver
#

INC_DIR=../
LIB_STATIC_DIR=../

CXXFLAGS=-I$(INC_DIR) -L$(LIB_STATIC_DIR) -Wall -std=c++11
CXXPOSTFIX=-lom-net -lom-tools

.PHONY: all
all: example_tunnel_device \
	example_net_addresses \
	example_raw_socket \
	example_net_packing \
	example_tools_random \
	example_net_stream_client \
	example_net_datagram_socket \
	example_net_agent \
	example_net_stream_listener \
	example_net_inotify_handler \
	example_tools_file

example_tunnel_device: example_tunnel_device.cc
	$(CXX) $(CXXFLAGS) -o example_tunnel_device \
		example_tunnel_device.cc $(CXXPOSTFIX)

example_net_addresses: example_net_addresses.cc
	$(CXX) $(CXXFLAGS) -o example_net_addresses \
		example_net_addresses.cc $(CXXPOSTFIX)

example_net_datagram_socket:  example_net_datagram_socket.cc
	$(CXX) $(CXXFLAGS) -o example_net_datagram_socket \
		example_net_datagram_socket.cc $(CXXPOSTFIX)

example_raw_socket:  example_raw_socket.cc
	$(CXX) $(CXXFLAGS) -o example_raw_socket example_raw_socket.cc $(CXXPOSTFIX)

example_net_packing:  example_net_packing.cc
	$(CXX) $(CXXFLAGS) -o example_net_packing example_net_packing.cc $(CXXPOSTFIX)

example_net_agent:  example_net_agent.cc
	$(CXX) $(CXXFLAGS) -o example_net_agent example_net_agent.cc $(CXXPOSTFIX)

example_tools_random:  example_tools_random.cc
	$(CXX) $(CXXFLAGS) -o example_tools_random \
		example_tools_random.cc $(CXXPOSTFIX)

example_net_stream_client:  example_net_stream_client.cc
	$(CXX) $(CXXFLAGS) -o example_net_stream_client \
		example_net_stream_client.cc $(CXXPOSTFIX)

example_net_stream_listener:  example_net_stream_listener.cc
	$(CXX) $(CXXFLAGS) -o example_net_stream_listener \
		example_net_stream_listener.cc $(CXXPOSTFIX)

example_net_inotify_handler:  example_net_inotify_handler.cc
	$(CXX) $(CXXFLAGS) -o example_net_inotify_handler \
		example_net_inotify_handler.cc $(CXXPOSTFIX)

example_tools_file:  example_tools_file.cc
	$(CXX) $(CXXFLAGS) -o example_tools_file example_tools_file.cc $(CXXPOSTFIX)

.PHONY: clean
clean:
	rm -f example_tunnel_device
	rm -f example_tunnel_device
	rm -f example_net_addresses
	rm -f example_raw_socket
	rm -f example_net_packing
	rm -f example_tools_random
	rm -f example_net_stream_client
	rm -f example_net_datagram_socket
	rm -f example_net_agent
	rm -f example_net_stream_listener
	rm -f example_net_inotify_handler
	rm -f example_tools_file

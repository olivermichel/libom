#
#  Olli's C++ Library
#  Makefile
#  (c) 2013 Oliver Michel
#

CXX = g++
CXXFLAGS = -fPIC -Wall -g

NET_LIB = libom-net.so
TOOLS_LIB = libom-tools.so
LIBS = $(NET_LIB) $(TOOLS_LIB)

NET_NAMES = net \
	agent io_interface socket \
	datagram_socket stream_client stream_listener stream_connection \
	tunnel_device raw_socket \
 	inotify_handler

TOOLS_NAMES = tools \
	logger time random string file


NET_OBJS = $(addprefix src/net/, $(addsuffix .o, $(NET_NAMES)))
TOOLS_OBJS = $(addprefix src/tools/, $(addsuffix .o, $(TOOLS_NAMES)))

all: $(NET_LIB) $(TOOLS_LIB)

$(NET_LIB): $(NET_OBJS)
	$(CXX) -shared -o $@ $(NET_OBJS)

$(TOOLS_LIB): $(TOOLS_OBJS)
	$(CXX) -shared -o $@ $(TOOLS_OBJS)


%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

examples:
	$(MAKE) -C ./examples

clean:
	$(RM) src/net/*.o
	$(RM) src/tools/*.o

spotless: clean
	$(RM) $(LIBS)

.PHONY: all examples clean spotless

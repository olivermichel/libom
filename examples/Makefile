#
#  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
#  examples/Makefile
#  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
#  http://ngn.cs.colorado/~oliver
#

INC_DIR = ../
LIB_STATIC_DIR = ../

CXXFLAGS = $(shell pkg-config --cflags dbus-1) -ldbus-1 -I$(INC_DIR) -L$(LIB_STATIC_DIR) -Wall -std=c++11
CXXPOSTFIX = -lom-net -lom-tools -lom-async -lom-ipc

EXAMPLES_NAMES = example_net_addresses \
	example_net_dbus_adapter \
	example_net_packing \
	example_net_stream_listener \
	example_tools_dir \
	example_tools_file \
	example_tools_random \
	example_async_epoll_wrapper

# example_raw_socket
# example_net_inotify_handler
# example_net_datagram_socket
# example_tunnel_device
# example_net_stream_client
# example_net_agent

all: $(EXAMPLES_NAMES)

%: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $< $(CXXPOSTFIX)

spotless:
	$(RM) $(EXAMPLES_NAMES)

.PHONY: all clean spotless

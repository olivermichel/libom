#
#  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
#  Makefile
#  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
#  http://ngn.cs.colorado/~oliver
#

# shared target names
LIB_NET   = libom-net.so
LIB_TOOLS = libom-tools.so
LIB_ASYNC = libom-async.so
LIB_IPC   = libom_ipc.so

# static target names
AR_NET    = libom-net.a
AR_TOOLS  = libom-tools.a
AR_ASYNC  = libom-async.a
AR_IPC    = libom-ipc.a

# dependency names
NET_NAMES   = net agent io_interface datagram_socket stream_client \
		stream_listener stream_connection inotify_handler tunnel_device \
		dbus_adapter
TOOLS_NAMES = tools logger time random string file dir
ASYNC_NAMES = multiplex_interface epoll_wrapper
IPC_NAMES   = dbus/connection

# external libary flags
DBUS_I = $(shell pkg-config --cflags-only-I dbus-1)
DBUS_L = $(shell pkg-config --libs dbus-1)

# compiler/linker flags
AR       = ar
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -g -I. -fPIC $(DBUS_I)
LDFLAGS  = $(DBUS_L)

# object files
NET_OBJS   = $(addprefix om/net/,   $(addsuffix .o, $(NET_NAMES)))
TOOLS_OBJS = $(addprefix om/tools/, $(addsuffix .o, $(TOOLS_NAMES)))
ASYNC_OBJS = $(addprefix om/async/, $(addsuffix .o, $(ASYNC_NAMES)))
IPC_OBJS   = $(addprefix om/ipc/,   $(addsuffix .o, $(IPC_NAMES)))

# target rules
all: so ar
so: $(LIB_NET) $(LIB_TOOLS) $(LIB_ASYNC) $(LIB_IPC)
ar: $(AR_NET) $(AR_TOOLS) $(AR_ASYNC) $(AR_IPC)

# target dependencies
$(LIB_NET):   $(NET_OBJS)
$(LIB_TOOLS): $(TOOLS_OBJS)
$(LIB_ASYNC): $(ASYNC_OBJS)
$(LIB_IPC):   $(IPC_OBJS)
$(AR_NET):    $(NET_OBJS)
$(AR_TOOLS):  $(TOOLS_OBJS)
$(AR_ASYNC):  $(ASYNC_OBJS)
$(AR_IPC):    $(IPC_OBJS)

# compile/link rules
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

%.so:
	$(CXX) -shared -o $@ $^ $(LDFLAGS)

%.a:
	$(AR) -cvr $@ $^

examples:
	$(MAKE) -C ./examples

clean:
	$(RM) $(NET_OBJS) $(TOOLS_OBJS) $(ASYNC_OBJS) $(IPC_OBJS)

spotless: clean
	$(RM) $(LIB_NET) $(LIB_TOOLS) $(LIB_ASYNC) $(LIB_IPC)
	$(RM) $(AR_NET) $(AR_TOOLS) $(AR_ASYNC) $(AR_IPC)

.PHONY: all ar so examples clean spotless

#
#  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
#  Makefile
#  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
#  http://ngn.cs.colorado/~oliver
#

LIB_NET   = libom-net.so
LIB_TOOLS = libom-tools.so
AR_NET    = libom-net.a
AR_TOOLS  = libom-tools.a

NET_NAMES = net agent io_interface datagram_socket stream_client \
	stream_listener stream_connection inotify_handler tunnel_device \
	dbus_adapter
	# raw_socket

TOOLS_NAMES = tools logger time random string file dir

DBUS_I = $(shell pkg-config --cflags-only-I dbus-1)
DBUS_L = $(shell pkg-config --libs dbus-1)

CXX = g++
CXXFLAGS = $(DBUS_I) -Wall -g -I. -fPIC -std=c++11
LDFLAGS  = $(DBUS_L)

AR = ar

all: ar so

ar: $(AR_NET) $(AR_TOOLS)

so: $(LIB_NET) $(LIB_TOOLS)

NET_OBJS = $(addprefix om/net/, $(addsuffix .o, $(NET_NAMES)))
TOOLS_OBJS = $(addprefix om/tools/, $(addsuffix .o, $(TOOLS_NAMES)))

$(LIB_NET): $(NET_OBJS)
$(LIB_TOOLS): $(TOOLS_OBJS)
$(AR_NET): $(NET_OBJS)
$(AR_TOOLS): $(TOOLS_OBJS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

%.so:
	$(CXX) -shared -o $@ $^ $(LDFLAGS)

%.a:
	$(AR) -cvr $@ $^

examples:
	$(MAKE) -C ./examples

clean:
	$(RM) $(NET_OBJS) $(TOOLS_OBJS) .deps

spotless: clean
	$(RM) $(LIB_NET) $(LIB_TOOLS) $(AR_NET) $(AR_TOOLS)

.PHONY: all ar so examples clean spotless

-include .deps
.deps: $(NET_OBJS:.o=.cc) $(TOOLS_OBJS:.o=.cc)
	for src in $^; do \
		$(CXX) $(CXXFLAGS) -MM -MT $${src/.cc/.o} $$src; \
	done > $@ 2> /dev/null

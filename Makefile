#
#  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
#  Makefile
#  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
#  http://ngn.cs.colorado/~oliver
#

LIB_NET   = libom-net.so
LIB_TOOLS = libom-tools.so
AR_NET    = libom-net.a
AR_TOOLS  = libom-tools.a

NET_NAMES = net agent io_interface socket datagram_socket stream_client \
	stream_listener stream_connection tunnel_device raw_socket inotify_handler

TOOLS_NAMES = tools logger time random string file

CXX = g++
CXXFLAGS = -Wall -g -I. -fPIC -std=c++11
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
	$(CXX) $(CXXFLAGS) -shared -o $@ $^

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

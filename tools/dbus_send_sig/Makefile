#
#  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
#  tools/dbus_send_sig/Makefile
#  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
#  http://ngn.cs.colorado/~oliver
#

INC_DIR = ../../
LIB_STATIC_DIR = ../../

CXXFLAGS = $(shell pkg-config --cflags dbus-1) -ldbus-1 -I$(INC_DIR) -L$(LIB_STATIC_DIR) -Wall -std=c++11
CXXPOSTFIX = -lom-net -lom-tools

all: dbus_send_sig

%: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $< $(CXXPOSTFIX)

spotless:
	$(RM) dbus_send_sig



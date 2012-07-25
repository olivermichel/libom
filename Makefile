
# macro definitions

CXX = g++
VPATH = src:src/net:src/tools:build:bin

ifeq ($(DEBUG), 1)
	CXXFLAGS = -Wall -ggdb
else
	CXXFLAGS = -Wall
endif

BIN_DIR = bin

NET_BUILD_DIR = build/net
NET_SRC_DIR = src/net

TOOLS_BUILD_DIR = build/tools
TOOLS_SRC_DIR = src/tools

NET_OBJS = net.o io_interface.o socket.o datagram_socket.o tunnel_device.o
NET_HEADERS = net.h io_interface.h socket.h datagram_socket.h tunnel_device.h

TOOLS_OBJS = tools.o logger.o time.o
TOOLS_HEADERS = tools.h logger.h time.h

.PHONY: all
all: test_net test_tools

.PHONY: test_net
test_net: $(BIN_DIR) $(NET_BUILD_DIR) build/test_net_main.o \
	$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/test_net \
	$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS)) build/test_net_main.o

.PHONY: test_tools
test_tools: $(BIN_DIR) $(TOOLS_BUILD_DIR) build/test_tools_main.o \
	$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS))
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/test_tools \
	$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) build/test_tools_main.o

build/test_net_main.o: test_net_main.cc $(addprefix $(NET_SRC_DIR)/, $(NET_HEADERS))
	$(CXX) $(CXXFLAGS) -c -o build/test_net_main.o src/test_net_main.cc

build/test_tools_main.o: test_tools_main.cc $(addprefix $(TOOLS_SRC_DIR)/, $(TOOLS_HEADERS))
	$(CXX) $(CXXFLAGS) -c -o build/test_tools_main.o src/test_tools_main.cc

# compile rule for non-library sources

$(NET_BUILD_DIR)/%.o: $(NET_SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c -o $(NET_BUILD_DIR)/$*.o $(NET_SRC_DIR)/$*.cc

$(TOOLS_BUILD_DIR)/%.o: $(TOOLS_SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c -o $(TOOLS_BUILD_DIR)/$*.o $(TOOLS_SRC_DIR)/$*.cc

# directories

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(NET_BUILD_DIR): 
	mkdir -p $(NET_BUILD_DIR)

$(TOOLS_BUILD_DIR): 
	mkdir -p $(TOOLS_BUILD_DIR)

.PHONY: clean
clean:
	rm -f $(NET_BUILD_DIR)/*.o
	rm -f $(TOOLS_BUILD_DIR)/*.o 
	rm -f bin/test_net bin/test_tools
	
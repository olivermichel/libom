
# macro definitions

CXX = g++
VPATH = src:src/net:src/tools:build:bin

ifeq ($(DEBUG), 1)
	CXXFLAGS = -Wall -fPIC -ggdb 
else
	CXXFLAGS = -Wall -fPIC
endif

BIN_DIR = bin
LIB_DIR = lib
SRC_DIR = src

DYNLIB_NAME = om_lib.so

TEST_TOOLS_BIN_NAME = test_tools 
TEST_NET_BIN_NAME = test_net

BUILD_DIR = build

NET_BUILD_DIR = $(BUILD_DIR)/net
NET_SRC_DIR = $(SRC_DIR)/net

TOOLS_BUILD_DIR = $(BUILD_DIR)/tools
TOOLS_SRC_DIR = $(SRC_DIR)/tools

NET_OBJS = net.o io_interface.o socket.o datagram_socket.o tunnel_device.o
NET_HEADERS = net.h io_interface.h socket.h datagram_socket.h tunnel_device.h

TOOLS_OBJS = tools.o logger.o time.o
TOOLS_HEADERS = tools.h logger.h time.h

.PHONY: all
all: $(TEST_TOOLS_BIN_NAME) $(TEST_NET_BIN_NAME) $(DYNLIB_NAME)

.PHONY: $(DYNLIB_NAME)
$(DYNLIB_NAME): $(LIB_DIR) $(NET_BUILD_DIR) $(TOOLS_BUILD_DIR) \
	$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
	$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))
	$(CXX) -shared -fPIC -o $(LIB_DIR)/$(DYNLIB_NAME) \
	$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
	$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))

.PHONY: $(TEST_TOOLS_BIN_NAME)
$(TEST_TOOLS_BIN_NAME): $(BIN_DIR) $(NET_BUILD_DIR) $(BUILD_DIR)/test_net_main.o \
	$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TEST_NET_BIN_NAME) \
	$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS)) $(BUILD_DIR)/test_net_main.o

.PHONY: $(TEST_NET_BIN_NAME)
$(TEST_NET_BIN_NAME): $(BIN_DIR) $(TOOLS_BUILD_DIR) $(BUILD_DIR)/test_tools_main.o \
	$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS))
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TEST_TOOLS_BIN_NAME) \
	$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) $(BUILD_DIR)/test_tools_main.o

$(BUILD_DIR)/test_net_main.o: test_net_main.cc $(addprefix $(NET_SRC_DIR)/, $(NET_HEADERS))
	$(CXX) $(CXXFLAGS) -c -o $(BUILD_DIR)/test_net_main.o $(SRC_DIR)/test_net_main.cc

$(BUILD_DIR)/test_tools_main.o: test_tools_main.cc $(addprefix $(TOOLS_SRC_DIR)/, $(TOOLS_HEADERS))
	$(CXX) $(CXXFLAGS) -c -o $(BUILD_DIR)/test_tools_main.o $(SRC_DIR)/test_tools_main.cc

# compile rule

$(NET_BUILD_DIR)/%.o: $(NET_SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c -o $(NET_BUILD_DIR)/$*.o $(NET_SRC_DIR)/$*.cc

$(TOOLS_BUILD_DIR)/%.o: $(TOOLS_SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c -o $(TOOLS_BUILD_DIR)/$*.o $(TOOLS_SRC_DIR)/$*.cc

# directories

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(NET_BUILD_DIR): 
	mkdir -p $(NET_BUILD_DIR)

$(TOOLS_BUILD_DIR): 
	mkdir -p $(TOOLS_BUILD_DIR)

.PHONY: clean
clean:
	rm -f $(NET_BUILD_DIR)/*.o
	rm -f $(TOOLS_BUILD_DIR)/*.o 
	rm -f $(BIN_DIR)/$(TEST_NET_BIN_NAME) $(BIN_DIR)/$(TEST_TOOLS_BIN_NAME)
	rm -f $(LIB_DIR)/$(DYNLIB_NAME)
	
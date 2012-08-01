
# macro definitions

CXX = g++
VPATH = src:src/net:src/tools:build:bin

CXXFLAGS = -I ./$(SRC_DIR) -Wall 
LDFLAGS = -fPIC

ifeq ($(DEBUG), 1)
	CXXFLAGS += -ggdb
endif

BIN_DIR = bin
LIB_DIR = lib
SRC_DIR = src
BUILD_DIR = build

NET_BUILD_DIR = $(BUILD_DIR)/net
NET_SRC_DIR = $(SRC_DIR)/net

TOOLS_BUILD_DIR = $(BUILD_DIR)/tools
TOOLS_SRC_DIR = $(SRC_DIR)/tools

DYNLIB_NAME = om_lib.so
STATLIB_NAME = om_lib.a

TEST_TOOLS_BIN_NAME = test_tools 
TEST_NET_BIN_NAME = test_net

NET_OBJS = net.o io_interface.o socket.o datagram_socket.o tunnel_device.o \
	agent.o raw_socket.o
NET_HEADERS = net.h io_interface.h socket.h datagram_socket.h tunnel_device.h \
	agent.h raw_socket.h

TOOLS_OBJS = tools.o logger.o time.o random.o
TOOLS_HEADERS = tools.h logger.h time.h random.h

.PHONY: all
all: libs examples

# libraries

.PHONY: libs
libs: $(DYNLIB_NAME) $(STATLIB_NAME)

.PHONY: $(DYNLIB_NAME)
$(DYNLIB_NAME): $(LIB_DIR) $(NET_BUILD_DIR) $(TOOLS_BUILD_DIR) \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
		$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))
	
	$(CXX) $(LDFLAGS) -shared -o $(LIB_DIR)/$(DYNLIB_NAME) \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
		$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))

.PHONY: $(STATLIB_NAME)
$(STATLIB_NAME): $(LIB_DIR) $(NET_BUILD_DIR) $(TOOLS_BUILD_DIR) \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
		$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))

	ar ru $(LIB_DIR)/$(STATLIB_NAME) $(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS)) \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS))
	ranlib $(LIB_DIR)/$(STATLIB_NAME)

# text/example binaries

.PHONY: examples
examples: $(TEST_NET_BIN_NAME) $(TEST_TOOLS_BIN_NAME)

.PHONY: $(TEST_NET_BIN_NAME)
$(TEST_NET_BIN_NAME): $(BIN_DIR) $(TOOLS_BUILD_DIR) $(NET_BUILD_DIR) \
		$(BUILD_DIR)/test_net_main.o $(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS)) \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS))

	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $(BIN_DIR)/$(TEST_NET_BIN_NAME) \
		$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS)) \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
		$(BUILD_DIR)/test_net_main.o

.PHONY: $(TEST_TOOLS_BIN_NAME)
$(TEST_TOOLS_BIN_NAME): $(BIN_DIR) $(TOOLS_BUILD_DIR) $(NET_BUILD_DIR) \
		$(BUILD_DIR)/test_tools_main.o \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
		$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))
	
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $(BIN_DIR)/$(TEST_TOOLS_BIN_NAME) \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
		$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS)) \
		$(BUILD_DIR)/test_tools_main.o

# source files containing main-functions

$(BUILD_DIR)/test_net_main.o: test_net_main.cc \
		$(addprefix $(NET_SRC_DIR)/, $(NET_HEADERS))

	$(CXX) $(LDFLAGS) $(CXXFLAGS) -c -o $(BUILD_DIR)/test_net_main.o \
		$(SRC_DIR)/test_net_main.cc

$(BUILD_DIR)/test_tools_main.o: test_tools_main.cc \
		$(addprefix $(TOOLS_SRC_DIR)/, $(TOOLS_HEADERS))
	
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -c -o $(BUILD_DIR)/test_tools_main.o \
		$(SRC_DIR)/test_tools_main.cc

# compile rule

$(NET_BUILD_DIR)/%.o: $(NET_SRC_DIR)/%.cc
		$(CXX) $(LDFLAGS) $(CXXFLAGS) -c -o $(NET_BUILD_DIR)/$*.o $(NET_SRC_DIR)/$*.cc

$(TOOLS_BUILD_DIR)/%.o: $(TOOLS_SRC_DIR)/%.cc
		$(CXX) $(LDFLAGS) $(CXXFLAGS) -c -o $(TOOLS_BUILD_DIR)/$*.o $(TOOLS_SRC_DIR)/$*.cc

# directories

$(BIN_DIR):
		mkdir -p $(BIN_DIR)

$(LIB_DIR):
		mkdir -p $(LIB_DIR)

$(BUILD_DIR):
		mkdir -p $(BUILD_DIR)

$(NET_BUILD_DIR): 
		mkdir -p $(NET_BUILD_DIR)

$(TOOLS_BUILD_DIR): 
		mkdir -p $(TOOLS_BUILD_DIR)

# etc

.PHONY: clean
clean:
		rm -f $(NET_BUILD_DIR)/*.o
		rm -f $(TOOLS_BUILD_DIR)/*.o 
		rm -f $(BIN_DIR)/$(TEST_NET_BIN_NAME) $(BIN_DIR)/$(TEST_TOOLS_BIN_NAME)
		rm -f $(LIB_DIR)/$(DYNLIB_NAME) $(LIB_DIR)/$(STATLIB_NAME)
	
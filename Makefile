#
#  Olli's C++ Library
#  Makefile
#  (c) 2012 Oliver Michel
#

# vpath

VPATH = include/om/net:include/om/tools:src/net:src/tools:build

# flags

CXXFLAGS = -fPIC -I ./$(INC_DIR) -Wall

ifeq ($(DEBUG), 1)
	CXXFLAGS += -ggdb
endif

# directory specifications

BUILD_DIR = build
INC_DIR = include
LIB_DIR = lib
SRC_DIR = src

NET_BUILD_DIR = $(BUILD_DIR)/net
NET_SRC_DIR = $(SRC_DIR)/net
NET_INC_DIR = $(INC_DIR)/net

TOOLS_BUILD_DIR = $(BUILD_DIR)/tools
TOOLS_SRC_DIR = $(SRC_DIR)/tools
TOOLS_INC_DIR = $(INC_DIR)/tools

DYNLIB_DIR = $(LIB_DIR)/dynamic
STATLIB_DIR = $(LIB_DIR)/static
# lib target names

DYNLIB_NAME = libom.so
STATLIB_NAME = libom.a

# library sources

NET_FILES = net io_interface socket datagram_socket tunnel_device agent \
	raw_socket socket_bindable stream_socket
TOOLS_FILES = tools logger time random string

NET_OBJS = $(addsuffix .o, $(NET_FILES))
TOOLS_OBJS = $(addsuffix .o, $(TOOLS_FILES))

# special targets

.PHONY: all
all: libs

.PHONY: clean
clean:
		rm -f $(NET_BUILD_DIR)/*.o
		rm -f $(TOOLS_BUILD_DIR)/*.o 
		rm -f $(DYNLIB_DIR)/$(DYNLIB_NAME) $(STATLIB_DIR)/$(STATLIB_NAME)

# libraries

.PHONY: libs
libs: $(DYNLIB_NAME) $(STATLIB_NAME)

.PHONY: $(DYNLIB_NAME)
$(DYNLIB_NAME): $(LIB_DIR) $(DYNLIB_DIR) build-dirs \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
		$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))
	
	$(CXX) -shared -o $(DYNLIB_DIR)/$(DYNLIB_NAME) \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
		$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))

.PHONY: $(STATLIB_NAME)
$(STATLIB_NAME): $(LIB_DIR) $(STATLIB_DIR) build-dirs \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS)) \
		$(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS))

	ar ru $(STATLIB_DIR)/$(STATLIB_NAME) $(addprefix $(NET_BUILD_DIR)/, $(NET_OBJS)) \
		$(addprefix $(TOOLS_BUILD_DIR)/, $(TOOLS_OBJS))
	ranlib $(STATLIB_DIR)/$(STATLIB_NAME)

# general compile rule

$(NET_BUILD_DIR)/%.o: $(NET_SRC_DIR)/%.cc
		$(CXX) $(CXXFLAGS) -c -o $(NET_BUILD_DIR)/$*.o $(NET_SRC_DIR)/$*.cc

$(TOOLS_BUILD_DIR)/%.o: $(TOOLS_SRC_DIR)/%.cc
		$(CXX) $(CXXFLAGS) -c -o $(TOOLS_BUILD_DIR)/$*.o $(TOOLS_SRC_DIR)/$*.cc

# directories

$(LIB_DIR):
		mkdir -p $(LIB_DIR)

$(DYNLIB_DIR):
		mkdir -p $(DYNLIB_DIR)

$(STATLIB_DIR):
		mkdir -p $(STATLIB_DIR)

.PHONY: build-dirs
build-dirs:
		mkdir -p $(BUILD_DIR)
		mkdir -p $(NET_BUILD_DIR)
		mkdir -p $(TOOLS_BUILD_DIR)

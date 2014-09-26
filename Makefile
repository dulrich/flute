SRC_DIR = source
OBJ_DIR = object
LUA_LIB = lua5.2

CXX		= $(shell fltk-config --cxx )
DEBUG		= -g
CXXFLAGS	= $(shell fltk-config --use-gl --use-images --cxxflags ) -I./$(SRC_DIR)
LUACFLAGS	= $(shell pkg-config --cflags $(LUA_LIB) )
LUALFLAGS	= $(shell pkg-config --libs $(LUA_LIB) )
LDFLAGS		= $(shell fltk-config --use-gl --use-images --ldflags ) -L./$(OBJ_DIR)
LDSTATIC	= $(shell fltk-config --use-gl --use-images --ldstaticflags ) -L./$(OBJ_DIR)
LINK		= $(CXX)

TARGET = flute
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(SRCS:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

.PHONY: all clean
.SUFFIXES: .o .cc

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) --std=c++0x $(CXXFLAGS) $(LUACFLAGS) $(DEBUG) -o $@ -c $<

all: $(TARGET)
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC) $(LUALFLAGS)

$(TARGET): $(OBJS)

clean:
	rm -f $(OBJ_DIR)/*.o 2> /dev/null
	rm -f $(TARGET) 2> /dev/null

SRC_DIR = source
OBJ_DIR = object

CXX		= $(shell fltk-config --cxx )
DEBUG		= -g
CXXFLAGS	= $(shell fltk-config --use-gl --use-images --cxxflags ) -I./$(SRC_DIR)
LUAFLAGS	= $(shell pkg-config --cflags --libs lua5.2 )
LDFLAGS		= $(shell fltk-config --use-gl --use-images --ldflags ) -L./$(OBJ_DIR)
LDSTATIC	= $(shell fltk-config --use-gl --use-images --ldstaticflags ) -L./$(OBJ_DIR)
LINK		= $(CXX)

TARGET = flute
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(SRCS:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

.PHONY: all clean
.SUFFIXES: .o .cc

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) --std=c++0x $(CXXFLAGS) $(DEBUG) -o $@ -c $<

all: $(TARGET)
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC) $(LUAFLAGS)

$(TARGET): $(OBJS)

clean:
	rm -f $(OBJ_DIR)/*.o 2> /dev/null
	rm -f $(TARGET) 2> /dev/null

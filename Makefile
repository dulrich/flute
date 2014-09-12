CXX		= $(shell fltk-config --cxx )
DEBUG		= -g
CXXFLAGS	= $(shell fltk-config --use-gl --use-images --cxxflags ) -I.
LUAFLAGS	= $(shell pkg-config --cflags --libs lua5.2 )
LDFLAGS		= $(shell fltk-config --use-gl --use-images --ldflags )
LDSTATIC	= $(shell fltk-config --use-gl --use-images --ldstaticflags )
LINK		= $(CXX)

TARGET = flute
SRCS = $(wildcard *.cc)
OBJS = $(SRCS:%.cc=%.o)

.PHONY: all clean
.SUFFIXES: .o .cc

%.o: %.cc
	$(CXX) --std=c++0x $(CXXFLAGS) $(DEBUG) -c $<
	
all: $(TARGET)
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC) $(LUAFLAGS)
	
$(TARGET): $(OBJS)

clean:
	rm -f *.o 2> /dev/null
	rm -f $(TARGET) 2> /dev/null

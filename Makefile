CXX		= $(shell fltk-config --cxx )
DEBUG		= -g
CXXFLAGS	= $(shell fltk-config --use-gl --use-images --cxxflags ) -I.
LDFLAGS		= $(shell fltk-config --use-gl --use-images --ldflags )
LDSTATIC	= $(shell fltk-config --use-gl --use-images --ldstaticflags )
LINK		= $(CXX)

TARGET = flute
OBJS = main.o Flute_Config.o Flute_Window.o Flute_Editor.o Flute_Buffer.o Flute_Buffer_Manager.o Flute_Tree.o
SRCS = main.cc Flute_Config.cc Flute_Window.cc Flute_Editor.cc Flute_Buffer.cc Flute_Buffer_Manager.cc Flute_Tree.cc

.PHONY: all clean
.SUFFIXES: .o .cc

%.o: %.cc
	$(CXX) --std=c++0x $(CXXFLAGS) $(DEBUG) -c $<
	
all: $(TARGET)
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC)
	
$(TARGET): $(OBJS)
Flute_Config.o: Flute_Config.cc Flute_Config.hh

clean: $(TARGET) $(OBJS)
	rm -f *.o 2> /dev/null
	rm -f $(TARGET) 2> /dev/null

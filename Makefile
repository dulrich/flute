CXX		= $(shell fltk-config --cxx)
DEBUG		= -g -Wno-write-strings
CXXFLAGS		= $(shell fltk-config --use-gl --use-images --cxxflags ) -I.
LDFLAGS		= $(shell fltk-config --use-gl --use-images --ldflags )
LDSTATIC		= $(shell fltk-config --use-gl --use-images --ldstaticflags )
LINK		= $(CXX)

TARGET = flute
OBJS = main.o Flute_Config.o Flute_Controller.o
SRCS = main.cc Flute_Config.cc Flute_Controller.cc

.SUFFIXES: .o .cc
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<
	
all: $(TARGET)
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC)
	
$(TARGET): $(OBJS)
Flute_Config.o: Flute_Config.cc Flute_Config.hh
Flute_Controller.o: Flute_Controller.cc Flute_Controller.hh

clean: $(TARGET) $(OBJS)
	rm -f *.o 2> /dev/null
	rm -f $(TARGET) 2> /dev/null
CXX		= $(shell fltk-config --cxx)
DEBUG		= -g
CXXFLAGS		= $(shell fltk-config --use-gl --use-images --cxxflags ) -I.
LDFLAGS		= $(shell fltk-config --use-gl --use-images --ldflags )
LDSTATIC		= $(shell fltk-config --use-gl --use-images --ldstaticflags )
LINK		= $(CXX)

TARGET = flute
OBJS = main.o
SRCS = main.cc

.SUFFIXES: .o .cc
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<
	
all: $(TARGET)
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC)
	
$(TARGET): $(OBJS)

clean: $(TARGET) $(OBJS)
	rm -f *.o 2> /dev/null
	rm -f $(TARGET) 2> /dev/null
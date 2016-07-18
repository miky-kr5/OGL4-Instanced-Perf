CXX = g++
TARGET = instanced vao dlist
OBJECTS = main.o GLSLProgram.o gui.o ogl.o
CXXFLAGS = -ansi -pedantic -Wall -DGLM_FORCE_RADIANS `pkg-config --cflags glew assimp` `fltk-config --cxxflags --use-gl`
LDLIBS =  `pkg-config --libs glew assimp` `fltk-config --ldflags --use-gl`

all: CXXFLAGS += -O3 -DNDEBUG
all: programs

debug: CXXFLAGS += -g
debug: programs

programs:
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o
	$(CXX) -c $(CXXFLAGS) GLSLProgram.cpp -o GLSLProgram.o
	$(CXX) -c $(CXXFLAGS) gui.cpp -o gui.o
	$(CXX) -c $(CXXFLAGS) -DUSE_INSTANCED_RENDERING ogl.cpp -o ogl.o
	$(CXX) -o instanced $(OBJECTS) $(CXXFLAGS) $(LDLIBS)
	$(RM) ogl.o
	$(CXX) -c $(CXXFLAGS) -DUSE_VAO ogl.cpp -o ogl.o
	$(CXX) -o vao $(OBJECTS) $(CXXFLAGS) $(LDLIBS)
	$(RM) ogl.o
	$(CXX) -c $(CXXFLAGS) -DUSE_DISPLAY_LIST ogl.cpp -o ogl.o
	$(CXX) -o dlist $(OBJECTS) $(CXXFLAGS) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJECTS)

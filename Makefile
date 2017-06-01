CXX = g++
TARGET = instanced vao dlist
BASE_OBJECTS = main.o GLSLProgram.o gui.o
BASE_HEADERS = GLSLProgram.hpp gui.hpp
BASE_SOURCES = $(BASE_OBJECTS:.o=.cpp)
GL_OBJECTS = ogl.o
GL_SOURCES = ogl.cpp
GL_HEADERS = ogl.hpp basicObjLoader.hpp tiny_obj_loader.h
OBJECTS = $(BASE_OBJECTS) $(GL_OBJECTS)
CXXFLAGS = -Wall -DGLM_FORCE_RADIANS `pkg-config --cflags glew` `fltk-config --cxxflags --use-gl`
LDLIBS =  `pkg-config --libs glew` `fltk-config --ldflags --use-gl`

.PHONY: all
all: CXXFLAGS += -O3 -DNDEBUG
all: $(TARGET)

.PHONY: debug
debug: CXXFLAGS += -g
debug: $(TARGET)

.PHONY: instanced_debug
instanced_debug: CXXFLAGS += -g
instanced_debug: instanced

.PHONY: vao_debug
vao_debug: CXXFLAGS += -g
vao_debug: vao

.PHONY: dlist_debug
dlist_debug: CXXFLAGS += -g
dlist_debug: dlist

instanced: CXXFLAGS += -DUSE_INSTANCED_RENDERING
instanced: $(BASE_OBJECTS) $(GL_SOURCES) $(GL_HEADERS)
	$(CXX) -c $(CXXFLAGS) $(GL_SOURCES) -o $(GL_OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(CXXFLAGS) $(LDLIBS)

vao: CXXFLAGS += -DUSE_VAO
vao: $(BASE_OBJECTS) $(GL_SOURCES) $(GL_HEADERS)
	$(CXX) -c $(CXXFLAGS) $(GL_SOURCES) -o $(GL_OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(CXXFLAGS) $(LDLIBS)

dlist: CXXFLAGS += -DUSE_DISPLAY_LIST
dlist: $(BASE_OBJECTS) $(GL_SOURCES) $(GL_HEADERS)
	$(CXX) -c $(CXXFLAGS) $(GL_SOURCES) -o $(GL_OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(CXXFLAGS) $(LDLIBS)

$(BASE_OBJECTS): $(BASE_SOURCES) $(BASE_HEADERS)
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o
	$(CXX) -c $(CXXFLAGS) GLSLProgram.cpp -o GLSLProgram.o
	$(CXX) -c $(CXXFLAGS) gui.cpp -o gui.o

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJECTS)

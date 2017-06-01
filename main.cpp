#include <iostream>
#include <cstdlib>
#include <FL/Fl.H>

#include "gui.hpp"
#include "ogl.hpp"

int main(int argc, char** argv)
{
  int rc;

  if(argc > 8) {
    std::cerr << "USAGE: " << argv[0] << " [MODEL [X INSTANCES [Y INSTANCES [X POS [Y POS [STRIDE]]]]]]" << std::endl;
    return EXIT_FAILURE;
  }

  if(argc >= 2) {
    opengl::sModelName = argv[1];
    if(argc >= 3) {
      opengl::xInstances = atof(argv[2]);
      if(argc >= 4) {
	opengl::yInstances = atof(argv[3]);
	if(argc >= 5) {
	  opengl::xInit = atof(argv[4]);
	  if(argc >= 6) {
	    opengl::yInit = atof(argv[5]);
	    if(argc >= 7) {
	      opengl::stride = atof(argv[6]);
	      if(argc == 8)
	      {
	      	opengl::camZ = atof(argv[7]);
	      }
	    }
	  }
	}
      }
    }
  }

  Fl_Window * window = new GlGui(0, 0, opengl::iWidthWindow, opengl::iHeightWindow, opengl::sWindowTitle.c_str());
  window->resizable(window);
  window->end();
  window->show(1, argv);
  window->make_current();
  window->fullscreen();
  rc = Fl::run();
  opengl::destroy();
  return rc;
}

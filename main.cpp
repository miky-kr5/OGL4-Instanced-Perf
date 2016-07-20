#include <FL/Fl.H>

#include "gui.hpp"
#include "ogl.hpp"

int main(int argc, char** argv)
{
  int rc;
  Fl_Window * window = new GlGui(0, 0, opengl::iWidthWindow, opengl::iHeightWindow, opengl::sWindowTitle.c_str());
  window->resizable(window);
  window->end();
  window->show(argc, argv);
  window->make_current();
  rc = Fl::run();
  opengl::destroy();
  return rc;
}

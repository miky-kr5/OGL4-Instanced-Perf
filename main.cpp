#include <FL/Fl.H>

#include "gui.hpp"

int main(int argc, char** argv)
{
  Fl_Window * window = new GlGui(0, 0, opengl::iWidthWindow, opengl::iHeightWindow, opengl::sWindowTitle.c_str());
  window->resizable(window);
  window->end();
  window->show(argc, argv);
  window->make_current();

  return Fl::run();
}

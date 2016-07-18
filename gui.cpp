#include <iostream>
#include <sstream>
#include <cmath>

#include <FL/Fl.H>
#include <FL/gl.h>

#include "gui.hpp"

static void redraw_callback(void * arg) {
  GlGui * window = static_cast<GlGui *>(arg);
  Fl::focus(window);
  window->redraw();
}

GlGui::GlGui(int x, int y, int w, int h, const char * l) : Fl_Gl_Window(x, y, w, h, l) {
  title += l;
  initialized = false;
  Fl::add_idle(redraw_callback, this);
  resizable(this);
}

void GlGui::draw() {
  std::ostringstream oss;

  if(!valid()) {
    if(!initialized) {
      opengl::initialize();
      initialized = true;
    }
    oss << title << " :: OpenGL " << glGetString(GL_VERSION) << " :: " << glGetString(GL_VENDOR);
    label(oss.str().c_str());

    opengl::reshape(w(), h());
  }

  opengl::display();
}

int GlGui::handle(int event) {
  return Fl_Gl_Window::handle(event);
}

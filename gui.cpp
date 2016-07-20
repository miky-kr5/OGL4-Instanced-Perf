#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>

#include <FL/Fl.H>
#include <FL/gl.h>

#include "gui.hpp"
#include "ogl.hpp"

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
  clock_t t1, t2;
  std::ostringstream oss;

  if(!valid()) {
    if(!initialized) {
      opengl::initialize();
      initialized = true;
    }
    opengl::reshape(w(), h());
  }

  t1 = clock();
  opengl::display();
  t2 = clock();

  oss << title << " :: OpenGL " << glGetString(GL_VERSION) << " :: " << glGetString(GL_VENDOR) << " :: ms per frame: " << (((t2 - t1) * 1000000.0f) / CLOCKS_PER_SEC);
  label(oss.str().c_str());
}

int GlGui::handle(int event) {
  return Fl_Gl_Window::handle(event);
}

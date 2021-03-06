#pragma once

#ifndef GUI_HPP
#define GUI_HPP

#include <string>

#include <FL/Fl_Gl_Window.H>

class GlGui : public Fl_Gl_Window {
public:
  GlGui(int x, int y, int w, int h, const char * l);

protected:
  virtual void draw();
  virtual int handle(int);

private:
  std::string title;
  bool initialized;
};

#endif

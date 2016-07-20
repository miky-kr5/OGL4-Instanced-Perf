#pragma once

#ifndef OGL_HPP
#define OGL_HPP

#include <string>

namespace opengl
{
//globals
  extern const std::string sWindowTitle; //name of the window
  extern unsigned int iWidthWindow;
  extern unsigned int iHeightWindow;     //width & height of the viewport
  extern float camZ;

  ///
  /// Function to initialize OGL variables + shader's loading + VAO + VBO
  ///
  void initialize();

  ///
  /// The display OGL function
  ///
  void display();

  ///
  /// The classical resized function in GLUT, including the perspective matrox construction
  ///
  void reshape(int w, int h);

  ///
  /// Function to destroy OGL variables.
  ///
  void destroy();
}

#endif

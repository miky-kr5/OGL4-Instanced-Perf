#pragma once

#ifndef OGL_HPP
#define OGL_HPP

#include <string>

namespace opengl {
  //globals
  extern const std::string sWindowTitle;
  extern unsigned int iWidthWindow;
  extern unsigned int iHeightWindow;
  extern std::string sModelName;
  extern unsigned int xInstances;
  extern unsigned int yInstances;
  extern float xInit;
  extern float yInit;
  extern float stride;
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

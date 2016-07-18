#pragma once

#ifndef OGL_HPP
#define OGL_HPP

#include <string>
#include <FL/Fl_Widget.H>

namespace opengl
{
//globals
  extern const std::string sWindowTitle; //name of the window
  extern unsigned int iWidthWindow;
  extern unsigned int iHeightWindow;     //width & height of the viewport
  extern float geom_param;
  extern float tess_inner;
  extern float tess_outer;
  
  ///
  /// A function to create two triangles based on the quad definition
  ///
  /// @iIndex an integer to access into the vectors (color and points)
  /// @a definition of the 1st index into the </code>vec_position</code> variable
  /// @b definition of the 2nd index into the </code>vec_position</code> variable
  /// @c definition of the 3rd index into the </code>vec_position</code> variable
  /// @d definition of the 4th index into the </code>vec_position</code> variable
  void quad(int& iIndex, int a, int b, int c, int d );

  ///
  /// Simple function to construct <code>iNVertices</code> vertexes over the definition of 6 faces of a cube
  ///
  void colorcube();

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
  /// A FLTK callback that changes the parameter of the Geometry Shader.
  ///
  void geom_callback(Fl_Widget * w, void * data);

  ///
  /// Two FLTK callbacks that change the parameters of the Tessellation Shaders.
  ///
  void tess_callback_inner(Fl_Widget * w, void * data);
  void tess_callback_outer(Fl_Widget * w, void * data);

  ///
  /// Function that toggles normalization on the tessellation shader.
  ///
  void toggle_tess();

  ///
  /// Function that activates/deactivates the lights in the geometry shader.
  ///
  void toggle_light();

  ///
  /// Function that activates/deactivates wireframe rendering.
  ///
  void toggle_lines();
}

#endif

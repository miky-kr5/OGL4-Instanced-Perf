#include <iostream>
#include <cstdlib>
#include <cassert>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "tiny_obj_loader.h"
#include "ogl.hpp"
#include "GLSLProgram.hpp"

#if !defined(USE_INSTANCED_RENDERING) && !defined(USE_VAO) && !defined(USE_DISPLAY_LIST)
#error "Must define USE_INSTANCED_RENDERING or USE_VAO or USE_DISPLAY_LIST"
#elif (defined(USE_INSTANCED_RENDERING) && defined(USE_VAO)) || (defined(USE_INSTANCED_RENDERING) && defined(USE_DISPLAY_LIST)) || (defined(USE_VAO) && defined(USE_DISPLAY_LIST))
#error "Cannot define USE_INSTANCED_RENDERING, USE_VAO and USE_DISPLAY_LIST simultaneously."
#endif

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace opengl {
  //globals
  const std::string sWindowTitle = "OGL Homework";
  unsigned int iWidthWindow = 800, iHeightWindow = 600;

  //constants
  static const float NCP = 0.1f;
  static const float FCP = 150.0f;
  static const float ANGLE = 75.f;

  //variables
  static const glm::vec4 cameraPos = glm::vec4(0.0f, 0.0f, -10.5f, 1.0f);
  static const glm::vec4 lightPos = glm::vec4(1.0f, 1.0f, 1.5f, 1.0f);
  static glm::mat4x4 mProjMatrix, mModelMatrix, mViewMatrix;
  static CGLSLProgram * m_program;
  static float m_fAngle;

#if defined(USE_INSTANCED_RENDERING) || defined(USE_VAO)
  static GLuint m_iIndexVAO;
  static GLuint iIdBuffer;
#elif defined(USE_DISPLAY_LIST)
  static GLuint m_iIndexList;
#endif

  // Model data.
  static std::vector<tinyobj::shape_t> shapes;

  void initialize() {
    std::string err;
    std::vector<tinyobj::material_t> materials;
#ifdef USE_DISPLAY_LIST
    int idx;
#endif

    mModelMatrix = glm::mat4();
    mViewMatrix = glm::mat4();
    m_fAngle = 0.f;
    
    glewInit();	
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    if(!tinyobj::LoadObj(shapes, materials, err, "models/suzane.obj", "models/")) {
      std::cerr << "Error loading model: " << err << std::endl;
      exit(EXIT_FAILURE);
    }

    assert(shapes.size() > 0);
    assert(shapes[0].mesh.indices.size() % 3 == 0);

    if(shapes.size() > 1)
      std::cout << "WARNING: Model has more than 1 mesh. Using mesh 0 only." << std::endl;

    std::cout << shapes[0].mesh.indices.size() << std::endl;
    std::cout << shapes[0].mesh.positions.size() << std::endl;

    m_program = new CGLSLProgram();
#if defined(USE_INSTANCED_RENDERING) || defined(USE_VAO)
    m_program->loadShader("shaders/phong_gl4.vert", CGLSLProgram::VERTEX);
    m_program->loadShader("shaders/phong_gl4.geom", CGLSLProgram::GEOMETRY);
    m_program->loadShader("shaders/phong_gl4.frag", CGLSLProgram::FRAGMENT);
    m_program->create_link();
    m_program->enable(); {
      m_program->addAttribute("vVertex");
      m_program->addAttribute("vNormal");
      m_program->addUniform("mView");
      m_program->addUniform("mProjection");
      m_program->addUniform("mModel");
      m_program->addUniform("bInstanced");
      m_program->addUniform("cameraPos");
      m_program->addUniform("lightPos");
    } m_program->disable();
#elif defined(USE_DISPLAY_LIST)
    m_program->loadShader("shaders/phong_gl2.vert", CGLSLProgram::VERTEX);
    m_program->loadShader("shaders/phong_gl2.frag", CGLSLProgram::FRAGMENT);
    m_program->create_link();
    m_program->enable(); {
      m_program->addUniform("mView");
      m_program->addUniform("mProjection");
      m_program->addUniform("mModel");
      m_program->addUniform("cameraPos");
      m_program->addUniform("lightPos");
    } m_program->disable();
#endif

#ifdef USE_DISPLAY_LIST
    m_iIndexList = glGenLists(1);
    glNewList(m_iIndexList, GL_COMPILE); {
      for(size_t k = 0; k < shapes[0].mesh.indices.size() / 3; k++) {
	glBegin(GL_TRIANGLES); {
	  for(int j = 0; j < 3; j++) {
	    idx = shapes[0].mesh.indices[(3 * k) + j];
	    glVertex3fv(&shapes[0].mesh.positions[3 * idx]);
	    glNormal3fv(&shapes[0].mesh.normals[3 * idx]);
	  }
	} glEnd();
      }
    } glEndList();
#elif defined(USE_INSTANCED_RENDERING) || defined(USE_VAO)
    //VAO
    glGenVertexArrays(1, &m_iIndexVAO);
    glBindVertexArray(m_iIndexVAO); {
      //VBO - create and initialize a buffer object
      glGenBuffers(1, &iIdBuffer);
      glBindBuffer(GL_ARRAY_BUFFER, iIdBuffer); {
	glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.positions.size() * shapes[0].mesh.normals.size() * sizeof(float), NULL, GL_STATIC_DRAW );
	glBufferSubData(GL_ARRAY_BUFFER, 0, shapes[0].mesh.positions.size() * sizeof(float), &shapes[0].mesh.positions[0]);
	glBufferSubData(GL_ARRAY_BUFFER, shapes[0].mesh.positions.size() * sizeof(float), shapes[0].mesh.normals.size() * sizeof(float), &shapes[0].mesh.normals[0]);
	glEnableVertexAttribArray(m_program->getLocation("vVertex"));
	glVertexAttribPointer(m_program->getLocation("vVertex"), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(m_program->getLocation("vNormal"));
	glVertexAttribPointer(m_program->getLocation("vNormal"), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(shapes[0].mesh.positions.size() * sizeof(float)));
      } glBindBuffer(GL_ARRAY_BUFFER, 0);
    } glBindVertexArray(0);
#endif
  }

  void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.15f, 0.15f, 0.15f, 1.f);

    mViewMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -10.5));

    m_program->enable(); {
#ifdef USE_VAO
      for(int i = -9; i <= 9; i += 3) { 
	for(int j = -7.5; j <= 9; j += 3) {
	  mModelMatrix = glm::translate(glm::mat4(), glm::vec3(i, j, 0));
	  mModelMatrix = glm::rotate(mModelMatrix, glm::radians(m_fAngle), glm::vec3(0, 1, 0));
	  glUniformMatrix4fv(m_program->getLocation("mView"), 1, GL_FALSE, glm::value_ptr(mViewMatrix));
	  glUniformMatrix4fv(m_program->getLocation("mModel"), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
	  glUniformMatrix4fv(m_program->getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(mProjMatrix));
	  glUniform1i(m_program->getLocation("bInstanced"), 0);
	  glUniform4fv(m_program->getLocation("cameraPos"), 1, glm::value_ptr(cameraPos));
	  glUniform4fv(m_program->getLocation("lightPos"), 1, glm::value_ptr(lightPos));
	  glBindVertexArray(m_iIndexVAO); {
	    glDrawElements(GL_TRIANGLES, shapes[0].mesh.indices.size(), GL_UNSIGNED_INT, &shapes[0].mesh.indices[0]);
	  } glBindVertexArray(0);
	}
      }
#elif defined(USE_INSTANCED_RENDERING)
      mModelMatrix = glm::rotate(glm::mat4(), glm::radians(m_fAngle), glm::vec3(0, 1, 0));
      glUniformMatrix4fv(m_program->getLocation("mView"), 1, GL_FALSE, glm::value_ptr(mViewMatrix));
      glUniformMatrix4fv(m_program->getLocation("mModel"), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
      glUniformMatrix4fv(m_program->getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(mProjMatrix));
      glUniform1i(m_program->getLocation("bInstanced"), 1);
      glUniform4fv(m_program->getLocation("cameraPos"), 1, glm::value_ptr(cameraPos));
      glUniform4fv(m_program->getLocation("lightPos"), 1, glm::value_ptr(lightPos));
      glBindVertexArray(m_iIndexVAO); {
	glDrawElementsInstanced(GL_TRIANGLES, shapes[0].mesh.indices.size(), GL_UNSIGNED_INT, &shapes[0].mesh.indices[0], 42);
      } glBindVertexArray(0);
#elif defined(USE_DISPLAY_LIST)
      for(int i = -9; i <= 9; i += 3) { 
	for(int j = -7.5; j <= 9; j += 3) {
	  mModelMatrix = glm::translate(glm::mat4(), glm::vec3(i, j, 0));
	  mModelMatrix = glm::rotate(mModelMatrix, glm::radians(m_fAngle), glm::vec3(0, 1, 0));
	  glUniformMatrix4fv(m_program->getLocation("mView"), 1, GL_FALSE, glm::value_ptr(mViewMatrix));
	  glUniformMatrix4fv(m_program->getLocation("mModel"), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
	  glUniformMatrix4fv(m_program->getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(mProjMatrix));
	  glUniform4fv(m_program->getLocation("cameraPos"), 1, glm::value_ptr(cameraPos));
	  glUniform4fv(m_program->getLocation("lightPos"), 1, glm::value_ptr(lightPos));
	  glCallList(m_iIndexList);  
	}
      }
#endif
    } m_program->disable();

    m_fAngle += 0.5f;
    if (m_fAngle > 360.0f)
      m_fAngle -= 360.0f;
  }

  void reshape(int w, int h) {
    if(h == 0)h = 1;
    float fRatio = float(w) / float(h);
    opengl::iWidthWindow = w;
    opengl::iHeightWindow = h;
    glViewport(0, 0, w, h);
    float k = 90;
    opengl::mProjMatrix = glm::perspective(glm::radians(k), fRatio, opengl::NCP, opengl::FCP);
  }

  void destroy() {
    std::cout << "Destroying OpenGL objects." << std::endl;
    delete m_program;
#if defined(USE_VAO) || defined(USE_INSTANCED_RENDERING)
    glDeleteBuffers(1, &iIdBuffer);
    glDeleteVertexArrays(1, &m_iIndexVAO);
#elif defined(USE_DISPLAY_LIST)
    glDeleteLists(m_iIndexList, 1);
#endif
  }
}

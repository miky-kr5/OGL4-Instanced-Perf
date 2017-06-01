#include <iostream>
#include <cstdlib>
#include <cassert>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "basicObjLoader.hpp"
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
  const std::string sWindowTitle = "CG2 Homework";
  unsigned int iWidthWindow = 800, iHeightWindow = 600;
  std::string sModelName = "models/suzane.obj";
  float camZ = -10.5f;
  unsigned int xInstances = 7;
  unsigned int yInstances = 6;
  float xInit = -9.0f;
  float yInit = -7.5f;
  float stride = 3.0f;

  //constants
  static const float NCP = 0.1f;
  static const float FCP = 150.0f;
  static const float ANGLE = 75.f;

  //variables
  static glm::vec4 cameraPos = glm::vec4(0.0f, 0.0f, camZ, 1.0f);
  static const glm::vec4 lightPos = glm::vec4(1.0f, 1.0f, 1.5f, 1.0f);
  static CGLSLProgram * m_program;
  static float m_fAngle;

  BasicObjLoader obj;

#if defined(USE_INSTANCED_RENDERING) || defined(USE_VAO)
  static glm::mat4x4 mProjMatrix, mModelMatrix, mViewMatrix;
  static GLuint m_iIndexVAO;
  static GLuint iIdBuffer;
  static GLuint iElBuffer;
#elif defined(USE_DISPLAY_LIST)
  static GLuint m_iIndexList;
#endif

  void initialize() {
    std::string err;
#ifdef USE_DISPLAY_LIST
    int idx;
#endif

    std::cout << "Using the following parameters:" << std::endl;
    std::cout << "\tModel name:                     " << sModelName << std::endl;
    std::cout << "\tNumber of horizontal instances: " << xInstances << std::endl;
    std::cout << "\tNumber of vertical instances:   " << yInstances << std::endl;
    std::cout << "\tInitial X position:             " << xInit << std::endl;
    std::cout << "\tInitial Y position:             " << yInit << std::endl;
    std::cout << "\tInter-model stride:             " << stride << std::endl;

#if defined(USE_INSTANCED_RENDERING) || defined(USE_VAO)
    mModelMatrix = glm::mat4();
    mViewMatrix = glm::mat4();
#endif
    m_fAngle = 0.f;
    
    glewInit();	
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    if(!obj.loadObj(sModelName.c_str()))
      exit(EXIT_FAILURE);

    assert(obj.triangleType > 1);

    m_program = new CGLSLProgram();
#if defined(USE_INSTANCED_RENDERING) || defined(USE_VAO)
    m_program->loadShader("shaders/phong_gl4.vert", CGLSLProgram::VERTEX);
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
      m_program->addUniform("xInstances");
      m_program->addUniform("yInstances");
      m_program->addUniform("xInit");
      m_program->addUniform("yInit");
      m_program->addUniform("stride");
    } m_program->disable();
#elif defined(USE_DISPLAY_LIST)
    m_program->loadShader("shaders/phong_gl2.vert", CGLSLProgram::VERTEX);
    m_program->loadShader("shaders/phong_gl2.frag", CGLSLProgram::FRAGMENT);
    m_program->create_link();
    m_program->enable(); {
      m_program->addUniform("cameraPos");
      m_program->addUniform("lightPos");
    } m_program->disable();
#endif

#ifdef USE_DISPLAY_LIST
    m_iIndexList = glGenLists(1);
    glNewList(m_iIndexList, GL_COMPILE); {
    int dataPerVertex = obj.dataPerTriangle / 3;
    int triangleIndex = 0;
    for(size_t k = 0; k < obj.Triangles.size() / obj.dataPerTriangle; k++){
        triangleIndex = k * obj.dataPerTriangle;
         glBegin(GL_TRIANGLES); {
            for(int j = 0; j < 3; j++) {
              idx = obj.Triangles[triangleIndex + j * dataPerVertex + 1];
              glNormal3f(obj.vNormals[idx].X, obj.vNormals[idx].Y, obj.vNormals[idx].Z);
              idx = obj.Triangles[triangleIndex + j * dataPerVertex];
              glVertex3f(obj.vPositions[idx].X, obj.vPositions[idx].Y, obj.vPositions[idx].Z);
            }
     } glEnd();
      }
    } glEndList();
#elif defined(USE_INSTANCED_RENDERING) || defined(USE_VAO)
    float * bufferData = obj.generateBufferData();
    //VAO
    glGenVertexArrays(1, &m_iIndexVAO);
    
    //VBO - create and initialize a buffer object
    glGenBuffers(1, &iIdBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, iIdBuffer); {
      glBufferData(GL_ARRAY_BUFFER, (obj.Triangles.size() / obj.dataPerTriangle * 6 * 3) * sizeof(float), bufferData, GL_STATIC_DRAW);
    }

    glBindVertexArray(m_iIndexVAO); {
      glBindBuffer(GL_ARRAY_BUFFER, iIdBuffer); {
        glEnableVertexAttribArray(m_program->getLocation("vVertex"));
        glVertexAttribPointer(m_program->getLocation("vVertex"), 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
        glEnableVertexAttribArray(m_program->getLocation("vNormal"));
        glVertexAttribPointer(m_program->getLocation("vNormal"), 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
      }
    } glBindVertexArray(0); glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete bufferData;
        
#endif
  }

  void display() {
#if defined(USE_DISPLAY_LIST) || defined(USE_VAO)
    GLfloat xOffset, yOffset;
#endif

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.15f, 0.15f, 0.15f, 1.f);

#if defined(USE_INSTANCED_RENDERING) || defined(USE_VAO)
    mViewMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, camZ));
#endif

    m_program->enable(); {
#ifdef USE_VAO
      xOffset = xInit;
      for(unsigned int i = 0; i < xInstances; i++) {
	yOffset = yInit;
	for(unsigned int j = 0; j < yInstances; j++) {
	  mModelMatrix = glm::translate(glm::mat4(), glm::vec3(xOffset, yOffset, 0));
	  mModelMatrix = glm::rotate(mModelMatrix, glm::radians(m_fAngle), glm::vec3(0, 1, 0));
	  glUniformMatrix4fv(m_program->getLocation("mView"), 1, GL_FALSE, glm::value_ptr(mViewMatrix));
	  glUniformMatrix4fv(m_program->getLocation("mModel"), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
	  glUniformMatrix4fv(m_program->getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(mProjMatrix));
	  glUniform1i(m_program->getLocation("bInstanced"), 0);
	  glUniform4fv(m_program->getLocation("cameraPos"), 1, glm::value_ptr(cameraPos));
	  glUniform4fv(m_program->getLocation("lightPos"), 1, glm::value_ptr(lightPos));
	  glBindVertexArray(m_iIndexVAO); {
	     glDrawArrays(GL_TRIANGLES, 0, obj.Triangles.size()/obj.dataPerTriangle * 3);
	  } glBindVertexArray(0);
	  yOffset += stride;
	}
	xOffset += stride;
      }
#elif defined(USE_INSTANCED_RENDERING)
      mModelMatrix = glm::rotate(glm::mat4(), glm::radians(m_fAngle), glm::vec3(0, 1, 0));
      glUniformMatrix4fv(m_program->getLocation("mView"), 1, GL_FALSE, glm::value_ptr(mViewMatrix));
      glUniformMatrix4fv(m_program->getLocation("mModel"), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
      glUniformMatrix4fv(m_program->getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(mProjMatrix));
      glUniform1i(m_program->getLocation("bInstanced"), 1);
      glUniform4fv(m_program->getLocation("cameraPos"), 1, glm::value_ptr(cameraPos));
      glUniform4fv(m_program->getLocation("lightPos"), 1, glm::value_ptr(lightPos));
      glUniform1i(m_program->getLocation("xInstances"), xInstances);
      glUniform1i(m_program->getLocation("yInstances"), yInstances);
      glUniform1f(m_program->getLocation("xInit"), xInit);
      glUniform1f(m_program->getLocation("yInit"), yInit);
      glUniform1f(m_program->getLocation("stride"), stride);
      glBindVertexArray(m_iIndexVAO); {
	       glDrawArraysInstanced(GL_TRIANGLES, 0, obj.Triangles.size()/obj.dataPerTriangle * 3, xInstances * yInstances);
      } glBindVertexArray(0);
#elif defined(USE_DISPLAY_LIST)
      xOffset = xInit;
      for(unsigned int i = 0; i < xInstances; i++) {
	yOffset = yInit;
	for(unsigned int j = 0; j < yInstances; j++) {
	  glLoadIdentity();
	  glTranslatef(xOffset, yOffset, 0.0f);
	  glRotatef(m_fAngle, 0.0f, 1.0f, 0.0f);
	  glUniform4fv(m_program->getLocation("cameraPos"), 1, glm::value_ptr(cameraPos));
	  glUniform4fv(m_program->getLocation("lightPos"), 1, glm::value_ptr(lightPos));
	  glCallList(m_iIndexList);
	  yOffset += stride;
	}
	xOffset += stride;
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
    cameraPos.z = camZ;
#ifdef USE_DISPLAY_LIST
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(k, fRatio, NCP, FCP);
    glTranslatef(0.0f, 0.0f, camZ);
    glMatrixMode(GL_MODELVIEW);
#elif defined(USE_INSTANCED_RENDERING) || defined(USE_VAO)
    opengl::mProjMatrix = glm::perspective(glm::radians(k), fRatio, NCP, FCP);
#endif
  }

  void destroy() {
    std::cout << "Destroying OpenGL objects." << std::endl;
    delete m_program;
#if defined(USE_VAO) || defined(USE_INSTANCED_RENDERING)
    glDeleteBuffers(1, &iIdBuffer);
    glDeleteBuffers(1, &iElBuffer);
    glDeleteVertexArrays(1, &m_iIndexVAO);
#elif defined(USE_DISPLAY_LIST)
    glDeleteLists(m_iIndexList, 1);
#endif
  }
}

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

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace opengl {
  //globals
  const std::string sWindowTitle = "OGL Cube";		//name of the window
  unsigned int iWidthWindow = 800, iHeightWindow = 600;	//width & height of the viewport

  //constants
  static const float NCP = 0.1f;
  static const float FCP = 150.0f;
  static const float ANGLE = 75.f;

  //variables
  static glm::mat4x4 mProjMatrix, mModelMatrix, mViewMatrix;
  static CGLSLProgram * m_program;
  static float m_fAngle;	//this variable is just for spinning the cube

#if defined(USE_INSTANCED_RENDERING) || defined(USE_VAO)
  static GLuint m_iIndexVAO;
  static GLuint iIdBuffer;
#elif defined(USE_DISPLAY_LIST)
#error "Display lists coming soon."
#else
#error "Must define USE_INSTANCED_RENDERING or USE_VAO or USE_DISPLAY_LIST"
#endif

  // Model data.
  static std::vector<tinyobj::shape_t> shapes;

  void initialize() {
    std::string err;
    std::vector<tinyobj::material_t> materials;

    mModelMatrix = glm::mat4();
    mViewMatrix = glm::mat4();
    m_fAngle = 0.f;
    
    glewInit();	
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_program = new CGLSLProgram();
    m_program->loadShader("shaders/basic.vert", CGLSLProgram::VERTEX);
    m_program->loadShader("shaders/basic.geom", CGLSLProgram::GEOMETRY);
    m_program->loadShader("shaders/basic.frag", CGLSLProgram::FRAGMENT);
    m_program->create_link();
    m_program->enable(); {
      m_program->addAttribute("vVertex");
      m_program->addAttribute("vNormal");
      m_program->addUniform("mView");
      m_program->addUniform("mProjection");
      m_program->addUniform("mModel");
    } m_program->disable();

    if(!tinyobj::LoadObj(shapes, materials, err, "models/suzane.obj", "models/")) {
      std::cerr << "Error loading model: " << err << std::endl;
      exit(EXIT_FAILURE);
    }

    assert(shapes.size() > 0);
    assert(shapes[0].mesh.indices.size() % 3 == 0);

    if(shapes.size() > 1)
      std::cout << "WARNING: Model has more than 1 mesh. Using mesh 0 only." << std::endl;

#if defined(USE_DISPLAY_LIST)
#error "Display lists coming soon."
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
	glVertexAttribPointer(m_program->getLocation("vVertex"), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)); //Vertex
	glEnableVertexAttribArray(m_program->getLocation("vNormal"));
	glVertexAttribPointer(m_program->getLocation("vNormal"), 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(shapes[0].mesh.positions.size() * sizeof(float)));
      } glBindBuffer(GL_ARRAY_BUFFER, 0);
    } glBindVertexArray(0);
#endif
  }

  void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.15f, 0.15f, 0.15f, 1.f);

    mViewMatrix = glm::translate(glm::mat4(), glm::vec3(0,0,-1.5));
    mModelMatrix = glm::rotate(glm::mat4(), glm::radians(m_fAngle), glm::vec3(0,1,0));

#if defined(USE_VAO)
    m_program->enable(); {
      glUniformMatrix4fv(m_program->getLocation("mView"), 1, GL_FALSE, glm::value_ptr(mViewMatrix));
      glUniformMatrix4fv(m_program->getLocation("mModel"), 1, GL_FALSE, glm::value_ptr(mModelMatrix));
      glUniformMatrix4fv(m_program->getLocation("mProjection"), 1, GL_FALSE, glm::value_ptr(mProjMatrix));
      glBindVertexArray(m_iIndexVAO); {
	glDrawElements(GL_TRIANGLES, shapes[0].mesh.indices.size(), GL_UNSIGNED_INT, &shapes[0].mesh.indices[0]);
      } glBindVertexArray(0);
    } m_program->disable();
#elif defined(USE_INSTANCED_RENDERING)
#error "Instanced rendering coming soon."
#elif defined(USE_DISPLAY_LIST)
#error "Display lists coming soon."
#endif

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
    glDeleteBuffers(1, &iIdBuffer);
    glDeleteVertexArrays(1, &m_iIndexVAO);
  }
}

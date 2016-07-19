#version 400

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;

uniform mat4 mView, mProjection, mModel;

out vec3 vNormalVs;

void main() {
  vNormalVs = vNormal;
  gl_Position = mProjection * mView * mModel * vec4(vVertex, 1.0);
}

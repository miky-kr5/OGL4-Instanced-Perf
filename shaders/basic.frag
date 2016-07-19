#version 400

layout(location = 0) out vec4 vFragColor;

in vec3 vVertexNormal;

void main(void) {
  vFragColor = vec4(abs(vVertexNormal), 1.0);
}

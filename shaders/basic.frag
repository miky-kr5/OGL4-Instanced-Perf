#version 400

layout(location = 0) out vec4 vFragColor;

in vec4 vVertexColor;

void main(void) {
  vFragColor = vVertexColor;
}

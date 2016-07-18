#version 400

layout(location = 0) out vec4 vFragColor;

in vec4 vColorVs;

void main(void) {
  vFragColor = vColorVs;
}

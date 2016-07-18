#version 400

layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec4 vColor;

out vec4 vColorVs;
out vec4 vPosition;

void main() {
  vColorVs = vColor;
  vPosition = vVertex;
}

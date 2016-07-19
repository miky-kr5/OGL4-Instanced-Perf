#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 vNormalVs[];
out vec3 vVertexNormal;

void main() {
  for(int i = 0; i < gl_in.length(); i++) {
    gl_Position = gl_in[i].gl_Position;
    vVertexNormal = vNormalVs[i];
    EmitVertex();
  }

  EndPrimitive();
}

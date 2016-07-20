#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec4 vNormalVs[];
in vec4 vViewVector[];
in vec4 vLightVector[];

out vec4 vView;
out vec4 vLight;
out vec4 vVertexNormal;

void main() {
  for(int i = 0; i < gl_in.length(); i++) {
    gl_Position = gl_in[i].gl_Position;
    vView = vViewVector[i];
    vLight = vLightVector[i];
    vVertexNormal = vNormalVs[i];
    EmitVertex();
  }

  EndPrimitive();
}

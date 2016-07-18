#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 mView, mProjection, mModel;

void main() {
  for(int i = 0; i < 3; i++) {
    gl_Position = mProjection * mView * mModel * gl_in[i].gl_Position;
    EmitVertex();
  }

  EndPrimitive();
}

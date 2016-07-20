#version 120

uniform mat4 mView, mProjection, mModel;
uniform vec4 cameraPos, lightPos;

varying vec4 vNormal, vView, vLight;

void main(void) {
  vec4 vPos = mModel * gl_Vertex;
  //vNormal = mModel * normalize(vec4(gl_Normal, 0.0));
  vNormal = vec4(gl_Normal, 0.0);
  vView   = normalize(cameraPos - vPos);
  vLight  = normalize(lightPos - vPos);
  gl_Position = mProjection * mView * vPos;
}


#version 120

uniform vec4 cameraPos, lightPos;

varying vec4 vNormal, vView, vLight;

void main(void) {
  vec4 vPos = gl_ModelViewMatrix * gl_Vertex;
  vNormal = vec4(gl_NormalMatrix * gl_Normal, 0.0);
  vView   = normalize(cameraPos - vPos);
  vLight  = normalize(lightPos - vPos);
  gl_Position = ftransform();
}


#version 400

precision lowp float;

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;

uniform mat4 mView, mProjection, mModel;
uniform vec4 cameraPos, lightPos;
uniform bool bInstanced;
uniform int xInstances, yInstances;
uniform float xInit, yInit, stride;

out vec4 vNormalVs;
out vec4 vViewVector;
out vec4 vLightVector;

void main() {
  vec4 vPos = mModel * vec4(vVertex.xyz, 1.0);
  if(bInstanced)
    vPos = vec4(vPos.x + ((gl_InstanceID % xInstances) * stride) + xInit, vPos.y + ((gl_InstanceID / xInstances) * stride) + yInit, vPos.z, vPos.w);
  vNormalVs = mModel * vec4(vNormal, 0.0);
  vViewVector = normalize(cameraPos - vPos);
  vLightVector = normalize(lightPos - vPos);
  gl_Position = mProjection * mView * vPos;
}

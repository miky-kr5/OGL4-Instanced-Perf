#version 400

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;

uniform mat4 mView, mProjection, mModel;
uniform bool bInstanced;

out vec4 vNormalVs;
out vec4 vViewVector;
out vec4 vLightVector;

const vec4 cameraPos = vec4(0.0, 0.0, -10.5, 1.0);
const vec4 lightPos  = vec4(1.0, 1.0, 1.5, 1.0);

void main() {
  vec4 vPos = mModel * vec4(vVertex.xyz, 1.0);
  if(bInstanced)
    vPos = vec4(vPos.x + ((gl_InstanceID % 7) * 3) - 9.0, vPos.y + ((gl_InstanceID % 6) * 3) - 7.5, vPos.z, vPos.w);
  vNormalVs = mModel * vec4(vNormal, 0.0);
  vViewVector = normalize(cameraPos - vPos);
  vLightVector = normalize(lightPos - vPos);
  gl_Position = mProjection * mView * vPos;
}

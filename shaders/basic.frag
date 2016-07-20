#version 400

layout(location = 0) out vec4 vFragColor;

in vec4 vView;
in vec4 vLight;
in vec4 vVertexNormal;

const vec4 baseColor = vec4(0.2, 0.2, 1.0, 1.0);
const vec4 ambient = vec4(0.0, 0.0, 0.025, 1.0);
const vec4 bLightColor = vec4(vec3(0.15), 1.0);
const vec4 specularColor = vec4(0.8, 0.8, 0.1, 1.0);

void main(void) {
  float NdotL, NdotL2, RdotV;
  vec4 r;
  vec4 diffuse = vec4(0.0);
  vec4 specular = vec4(0.0);
  vec4 n = normalize(vVertexNormal);
  vec4 l = normalize(vLight);
  vec4 v = normalize(vView);

  NdotL = max(dot(n, l), 0.0);
  if(NdotL > 0.0) {
    diffuse += NdotL * baseColor;
    r = normalize(reflect(l, n));
    RdotV = max(dot(r, normalize(v)), 0.0);
    specular += specularColor * pow(RdotV, 105.0);
  }

  NdotL2 = max(dot(n, -l), 0.0);
  if(NdotL2 > 0.0)
    diffuse += bLightColor * NdotL2;

  vFragColor = clamp(diffuse + specular + ambient, 0.0, 1.0);
}

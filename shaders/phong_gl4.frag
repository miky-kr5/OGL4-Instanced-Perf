#version 400

layout(location = 0) out vec4 vFragColor;

in vec4 vNormalVs;
in vec4 vViewVector;
in vec4 vLightVector;

const vec4 baseColor = vec4(1.0, 1.0, 1.0, 1.0);
const vec4 ambient = vec4(0.025, 0.025, 0.025, 1.0);
const vec4 bLightColor = vec4(vec3(0.15), 1.0);

void main(void) {
  float NdotL, RdotV;
  vec4 r;
  vec4 diffuse = vec4(0.0);
  vec4 specular = vec4(0.0);
  vec4 n = normalize(vNormalVs);
  vec4 l = normalize(vLightVector);
  vec4 v = normalize(vViewVector);

  NdotL = max(dot(n, l), 0.0);
  if(NdotL > 0.0) {
    diffuse += vec4(NdotL);
    r = normalize(reflect(l, n));
    RdotV = max(dot(r, normalize(v)), 0.0);
    specular += vec4(pow(RdotV, 105.0));
  }

  NdotL = max(dot(n, -l), 0.0);
  if(NdotL > 0.0)
    diffuse += bLightColor * NdotL;

  vFragColor = vec4(clamp(diffuse.rgb + specular.rgb + ambient.rgb, 0.0, 1.0), 1.0);
}

#version 120

varying vec4 vNormal, vView, vLight;

const vec4 baseColor = vec4(1.0, 1.0, 1.0, 1.0);
const vec4 ambient = vec4(0.025, 0.025, 0.025, 1.0);
const vec4 bLightColor = vec4(vec3(0.15), 1.0);
const float shiny = 105.0;

void main(void) {
  float NdotL, RdotV;
  vec4 r;
  vec4 diffuse = vec4(0.0);
  vec4 specular = vec4(0.0);
  vec4 n = normalize(vNormal);
  vec4 l = normalize(vLight);
  vec4 v = normalize(vView);

  NdotL = max(dot(n, l), 0.0);
  if(NdotL > 0.0) {
    diffuse += vec4(NdotL);
    r = normalize(reflect(l, n));
    RdotV = max(dot(r, normalize(v)), 0.0);
    specular += vec4(pow(RdotV, shiny));
  }

  NdotL = max(dot(n, -l), 0.0);
  if(NdotL > 0.0)
    diffuse += bLightColor * NdotL;

  //gl_FragColor = vec4(clamp(diffuse.rgb + specular.rgb + ambient.rgb, 0.0, 1.0), 1.0);
  gl_FragColor = vec4(clamp(abs(normalize(vNormal.xyz)), 0.0, 1.0), 1.0);
}

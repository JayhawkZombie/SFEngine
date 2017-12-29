uniform vec2 LightOrigin;

uniform vec3 LightColor;
uniform float Attenuation;
uniform vec2 ScreenResolution;

void main()
{
  vec2 baseDistance = gl_FragCoord.xy;
  baseDistance.y = ScreenResolution.y - baseDistance.y;

  vec2 distance = LightOrigin - baseDistance;
  float linear_distance = length(distance);

  float attenuation = 1.0 / (Attenuation * linear_distance + Attenuation * linear_distance);

  vec4 lightColor = vec4(LightColor, 1.0);
  vec4 color = vec4(attenuation, attenuation, attenuation, 1.0) * lightColor;
  
  gl_FragColor = color;
};

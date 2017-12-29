//uniform vec2 frag_LightOrigin;
//uniform vec3 frag_LightColor;
//uniform float frag_LightAttenuation;
//uniform vec2 frag_ScreenResolution;
//void main(){
//vec2 baseDistance =  gl_FragCoord.xy;
//baseDistance.y = frag_ScreenResolution.y-baseDistance.y;
//vec2 distance=frag_LightOrigin - baseDistance;
//float linear_distance = length(distance);
//float attenuation=1.0/( 2 * frag_LightAttenuation*linear_distance);
//vec4 lightColor = vec4(frag_LightColor, 1.0);
//vec4 color = vec4(attenuation, attenuation, attenuation, 1.0) * lightColor; gl_FragColor=color;};


uniform vec2 LightPosition;
uniform vec4 LightColor;
uniform float LightAttenuation;

void main()
{

  
}


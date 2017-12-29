#version 120

uniform sampler2D Scene;
uniform sampler2D NonShadowLightMap;

void main()
{

  vec4 color = texture2D(Scene, gl_TexCoord[0].st);
  vec4 lightcolor = texture2D(NonShadowLightMap, gl_TexCoord[0].st);

  color.rgb = color.rgb + lightcolor.rgb * length(lightcolor.rgb);

  gl_FragColor = color;

}
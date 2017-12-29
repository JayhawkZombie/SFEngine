#version 120

/*
  Shder to blend the light map with the scene's texture
  -- Render the scene to a renderTexture and give that to the light system
  -- This will blend the lightmap with that texture and you can then render your scene texture to the window
*/

uniform sampler2D MaskTexture;
uniform sampler2D NonShadowLightMap;
uniform sampler2D SceneTexture;
uniform vec2 l_pos;
uniform float l_atten;

//uniform float MinimumIntensity;
uniform vec4 AmbientColor;
uniform float AmbientIntensity;

void main()
{
  vec4 color = texture2D(SceneTexture, gl_TexCoord[0].st);
  vec4 maskColor = texture2D(MaskTexture, gl_TexCoord[0].st);
  
  float intensity = length(maskColor.rgb);
  //color += AmbientColor * AmbientIntensity;
  
  if (intensity > 0)
    color.rgb = color.rgb + color.rgb * maskColor.rgb * 15 * intensity;
  
  gl_FragColor = color;
}
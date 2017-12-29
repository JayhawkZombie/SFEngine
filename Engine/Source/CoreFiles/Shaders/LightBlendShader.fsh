#version 120

/*
  Shder to blend the light map with the scene's texture
  -- Render the scene to a renderTexture and give that to the light system
  -- This will blend the lightmap with that texture and you can then render your scene texture to the window
*/

//uniform sampler2D MaskTexture;
//uniform sampler2D SceneTexture;

//uniform float MinimumIntensity;

//uniform vec4 LightHue;
//uniform float HueIntensity;
//uniform float MaximumIntensity;

//void main()
//{
//  vec4 color = texture2D(SceneTexture, gl_TexCoord[0].st);
//  vec4 maskColor = texture2D(MaskTexture, gl_TexCoord[0].st);

//  vec3 rgbcolors = vec3(maskColor.rgb);
//  float intensity = length(rgbcolors) * 7;
//  intensity = min(MaximumIntensity, max(MinimumIntensity, intensity));

//  color += intensity > MinimumIntensity ? color * ( LightHue * HueIntensity * intensity / 2) : color * 0;
//  color *= intensity;

//  gl_FragColor = color * intensity;
//}

uniform sampler2D MaskTexture;
uniform sampler2D SceneTexture;
//uniform vec4 LightHue;

void main()
{
  vec4 color = texture2D(SceneTexture, gl_TexCoord[0].st);
  vec4 maskColor = texture2D(MaskTexture, gl_TexCoord[0].st);
  
  gl_FragColor = color * maskColor;
}

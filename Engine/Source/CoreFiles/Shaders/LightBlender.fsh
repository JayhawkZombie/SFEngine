uniform sampler2D LightTexture;
uniform sampler2D SceneTexture;

void main()
{
  vec4 lColor = texture2D(LightTexture, gl_TexCoord[0].st);
  vec4 sColor = texture2D(SceneTexture, gl_FragCoord.xy);

  vec4 fColor = sColor;

  fColor.rgb = sColor.rgb + lColor.rgb * lColor.a;
  gl_FragColor = fColor;
}

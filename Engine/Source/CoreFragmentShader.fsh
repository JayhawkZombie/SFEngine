#version 120

uniform float BRIGHTNESS;
uniform float CONTRAST;
uniform sampler2D SCENE;
uniform float GAMMA;
uniform int POST_PROCESS_EFFECT;
uniform float BLUR_AMOUNT;

uniform vec4 GLOBAL_LIGHT;
uniform float GLOBAL_LIGHT_INTENSITY;
uniform float GLOBAL_LIGHT_ATTENUATION;

uniform float offset = 1.0/300;

float BlurKernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16  
);

float SharpenKernel[9] = float[](
    -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1
);

vec4 brightnessContrast()
{
    vec4 pixel = texture2D(SCENE, gl_TexCoord[0].st);
    pixel *= gl_Color;
    pixel *= CONTRAST;
    pixel.rgb += vec3(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS);
    return pixel;
}

vec4 KernelMethod(vec4 color)
{
  vec2 offsets[9] = vec2[](
      vec2(-offset, offset),  // top-left
      vec2(0.0f,    offset),  // top-center
      vec2(offset,  offset),  // top-right
      vec2(-offset, 0.0f),    // center-left
      vec2(0.0f,    0.0f),    // center-center
      vec2(offset,  0.0f),    // center-right
      vec2(-offset, -offset), // bottom-left
      vec2(0.0f,    -offset), // bottom-center
      vec2(offset,  -offset)  // bottom-right    
  );

  float kernel[9];
  
  switch(POST_PROCESS_EFFECT)
  {
    case 1:
      kernel = BlurKernel;
      break;
    case 2:
      kernel = SharpenKernel;
      break;
    default:
      return vec4(1,1,1,1);
  }

  vec3 sampletex[9];
  for (int i = 0; i < 9; i++) {
    sampletex[i] = vec3(texture2D(SCENE, gl_TexCoord[0].st + offsets[i]));
  }
  vec3 col = vec3(0.0);
  for (int i = 0; i < 9; i++) {
    col += sampletex[i] * kernel[i];
  }

  vec4 c = vec4(1.0, 1.0, 1.0, 1.0);
  c.rgb = col;
  return c;
}

vec4 invert(vec4 color)
{
  return vec4(vec3(1.0 - texture2D(SCENE, gl_TexCoord[0].st)), 1.0);
}

void main()
{

  gl_FragColor = gl_Color;
}
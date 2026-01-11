#version 330

layout(location = 0) in vec2 pos;

uniform vec2 u_ScreenSize;

void main()
{
    vec2 ndc = (pos / u_ScreenSize) * 2.0 - 1.0;
    ndc.y = -ndc.y;

    gl_Position = vec4(ndc, 0.0, 1.0);
}
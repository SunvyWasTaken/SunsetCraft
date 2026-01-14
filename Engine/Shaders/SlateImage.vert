#version 330

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 uv;

uniform vec2 u_ScreenSize;

out vec2 u_Uv;

void main()
{
    vec2 ndc = (pos / u_ScreenSize) * 2.0 - 1.0;
    ndc.y = -ndc.y;

    gl_Position = vec4(ndc, 0.0, 1.0);
    u_Uv = uv;
}
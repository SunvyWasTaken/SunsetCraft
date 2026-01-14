#version 330

in vec2 u_Uv;

uniform sampler2D image;

out vec4 FragColor;

void main()
{
    FragColor = texture(image, u_Uv);
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
#version 330 core

layout(location = 0) in vec3 aPos;

uniform vec3 camPosition;
uniform mat4 projection;
uniform mat4 view;

out vec3 worldPos;

float planeHeight = 150.0;

void main()
{
    worldPos = aPos + vec3(camPosition.x, planeHeight, camPosition.z);
    gl_Position = projection * mat4(mat3(view)) * vec4(worldPos, 1.0);
}
#version 330

uniform vec3 BlockLocation;
uniform mat4 projection;
uniform mat4 view;

// 36 sommets d'un cube 1x1x1
const vec3 cubeVerts[36] = vec3[](
// front face
vec3(0,0,0), vec3(1,0,0), vec3(1,1,0),
vec3(0,0,0), vec3(1,1,0), vec3(0,1,0),
// back face
vec3(1,0,1), vec3(0,0,1), vec3(0,1,1),
vec3(1,0,1), vec3(0,1,1), vec3(1,1,1),
// left face
vec3(0,0,1), vec3(0,0,0), vec3(0,1,0),
vec3(0,0,1), vec3(0,1,0), vec3(0,1,1),
// right face
vec3(1,0,0), vec3(1,0,1), vec3(1,1,1),
vec3(1,0,0), vec3(1,1,1), vec3(1,1,0),
// top face
vec3(0,1,0), vec3(1,1,0), vec3(1,1,1),
vec3(0,1,0), vec3(1,1,1), vec3(0,1,1),
// bottom face
vec3(0,0,1), vec3(1,0,1), vec3(1,0,0),
vec3(0,0,1), vec3(1,0,0), vec3(0,0,0)
);

void main()
{
    vec3 loc = BlockLocation + cubeVerts[gl_VertexID % 36];
    gl_Position = projection * view * vec4(loc, 1.0);
}
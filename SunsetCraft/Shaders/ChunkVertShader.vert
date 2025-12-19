#version 330 core

layout(location = 0) in uint vData;

uniform vec3 chunkLocation;
uniform mat4 projection;
uniform mat4 view;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

// Décoder la position du bloc
vec3 DecodePos(uint v)
{
    return vec3(
        float(v & 31u),
        float((v >> 5) & 31u),
        float((v >> 10) & 31u)
    );
}

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

// Normales correspondantes pour chaque sommet (simple, face par face)
const vec3 cubeNormals[36] = vec3[](
    // front
    vec3(0,0,-1), vec3(0,0,-1), vec3(0,0,-1),
    vec3(0,0,-1), vec3(0,0,-1), vec3(0,0,-1),
    // back
    vec3(0,0,1), vec3(0,0,1), vec3(0,0,1),
    vec3(0,0,1), vec3(0,0,1), vec3(0,0,1),
    // left
    vec3(-1,0,0), vec3(-1,0,0), vec3(-1,0,0),
    vec3(-1,0,0), vec3(-1,0,0), vec3(-1,0,0),
    // right
    vec3(1,0,0), vec3(1,0,0), vec3(1,0,0),
    vec3(1,0,0), vec3(1,0,0), vec3(1,0,0),
    // top
    vec3(0,1,0), vec3(0,1,0), vec3(0,1,0),
    vec3(0,1,0), vec3(0,1,0), vec3(0,1,0),
    // bottom
    vec3(0,-1,0), vec3(0,-1,0), vec3(0,-1,0),
    vec3(0,-1,0), vec3(0,-1,0), vec3(0,-1,0)
);

void main()
{
    vec3 localPos = cubeVerts[gl_VertexID % 36];
    vec3 blockPos = DecodePos(vData);
    vec3 worldPos = blockPos + localPos + chunkLocation * 32;
    gl_Position = projection * view * vec4(worldPos,1.0);

    FragPos = worldPos;
    Normal = normalize(cubeNormals[gl_VertexID % 36]);
}

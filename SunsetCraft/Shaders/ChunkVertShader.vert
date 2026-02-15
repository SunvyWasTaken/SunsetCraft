#version 330 core

layout(location = 0) in uint vData;

uniform vec3 location;
uniform mat4 projection;
uniform mat4 view;

uniform float Distance;

out vec3 Normal;
out vec2 TexCoord;
flat out uint UvId;
out float dist;

// Decoder la position du bloc
vec3 DecodePos(uint v)
{
    return vec3(
        float(v & 31u),
        float((v >> 5) & 31u),
        float((v >> 10) & 31u)
    );
}

uint DecodeUV(uint v)
{
    return uint((v >> 23)& 511u);
}

uint DecodeSide(uint v)
{
    return (v >> 15u) & 7u; // 3 bits pour side (0–5)
}

int FaceOffset(uint side)
{
    if (side == 0u) return 18; // +X
    if (side == 1u) return 12; // -X
    if (side == 2u) return 24; // +Y
    if (side == 3u) return 30; // -Y
    if (side == 4u) return 6;  // +Z
    return 0;                  // -Z
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

const vec2 cubeUV[36] = vec2[](
// front
vec2(0,0), vec2(1,0), vec2(1,1),
vec2(0,0), vec2(1,1), vec2(0,1),

// back
vec2(0,0), vec2(1,0), vec2(1,1),
vec2(0,0), vec2(1,1), vec2(0,1),

// left
vec2(0,0), vec2(1,0), vec2(1,1),
vec2(0,0), vec2(1,1), vec2(0,1),

// right
vec2(0,0), vec2(1,0), vec2(1,1),
vec2(0,0), vec2(1,1), vec2(0,1),

// top
vec2(0,0), vec2(1,0), vec2(1,1),
vec2(0,0), vec2(1,1), vec2(0,1),

// bottom
vec2(0,0), vec2(1,0), vec2(1,1),
vec2(0,0), vec2(1,1), vec2(0,1)
);

void main()
{
    uint side = DecodeSide(vData);
    int faceOffset = FaceOffset(side);
    vec3 blockPos = DecodePos(vData);

    int vertId = faceOffset + (gl_VertexID % 6);

    vec3 localPos = cubeVerts[vertId];

    vec3 worldPos = blockPos + localPos + location * 16.0;

    gl_Position = projection * view * vec4(worldPos, 1.0);

    Normal = cubeNormals[vertId];
    TexCoord = cubeUV[vertId];
    UvId = DecodeUV(vData);
    dist = Distance;
}

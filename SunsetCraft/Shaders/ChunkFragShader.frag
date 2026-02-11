#version 330 core

in vec3 Normal;
in vec2 TexCoord;
flat in uint UvId;

uniform sampler2D atlasTexture;

out vec4 FragColor;

vec3 lightDir = normalize(vec3(-1.0, -1.0, 0.5));

vec3 GetTint()
{
    return vec3(0.55, 0.85, 0.35);
}

void main()
{
    float diff = max(dot(normalize(Normal), -lightDir), 0.0);

    // taille UV d'une tile
    float tileUVSize = 1.0 / 4.0;

    // offset UV correct (atlas vertical)
    float tileOffset = float(UvId) * tileUVSize;

    // UV final
    vec2 uv = vec2(TexCoord.x, tileOffset + TexCoord.y * tileUVSize);

    vec4 texColor = texture(atlasTexture, uv);

    vec3 color = texColor.rgb * (0.2 + 0.8 * diff);

    FragColor = vec4(color, 1.0);
}

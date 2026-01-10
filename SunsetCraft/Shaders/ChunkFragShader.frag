#version 330 core

in vec3 FragPos;  // position du fragment dans le monde
in vec3 Normal;   // normale du fragment
in vec2 TexCoord;
flat in uint UvId;

uniform sampler2D atlasTexture;

out vec4 FragColor;

// Parametres de la lumiere
vec3 lightDir = normalize(vec3(-1.0, -1.0, 0.5)); // direction de la lumiere

vec2 tileSize = vec2(32.0, 32.0);
vec2 uAtlasSize = vec2(32.0, 128.0);

vec3 GetTint()
{
    return vec3(0.55, 0.85, 0.35);
}

void main()
{
    float diff = max(dot(normalize(Normal), -lightDir), 0.0);

    vec2 tileUVSize = tileSize / uAtlasSize;

    vec2 tileOffset = vec2(0.0, float(UvId) * tileUVSize.y);

    vec2 uv = tileOffset + TexCoord * tileUVSize;

    vec4 texColor = texture(atlasTexture, uv);

    vec3 tint = (UvId == 2u) ? GetTint() : vec3(1.0);
    vec3 color = texColor.rgb * (0.2 + 0.8 * diff) * tint;

    FragColor = vec4(color, texColor.a);
}


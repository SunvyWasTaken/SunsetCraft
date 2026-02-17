#version 330 core

in vec3 worldPos;

uniform float uTimeOfDay; // 0-24
uniform vec3 dayColorTop;
uniform vec3 dayColorBottom;
uniform vec3 nightColorTop;
uniform vec3 nightColorBottom;

out vec4 FragColor;

vec3 uTopColor = vec3(0.05, 0.3, 0.8);     // bleu foncé (zénith)
vec3 uBottomColor = vec3(0.6, 0.8, 1.0);  // bleu clair (horizon)
float uRadius = 500.0;      // rayon de la sphère

void main()
{
    //float t = clamp(worldPos.y * 0.5 + 0.5, 0.0, 1.0);
//
    //vec3 topColor = mix(nightColorTop, dayColorTop, smoothstep(5.0, 18.0, uTimeOfDay));
    //vec3 bottomColor = mix(nightColorBottom, dayColorBottom, smoothstep(5.0, 18.0, uTimeOfDay));
//
    //vec3 color = mix(bottomColor, topColor, t);
    //FragColor = vec4(color, 1.0);

    // Normalisation hauteur -1 → 1
    float h = worldPos.y / uRadius;

    // On convertit en 0 → 1
    float t = clamp((h + 1.0) * 0.5, 0.0, 1.0);

    vec3 color = mix(uBottomColor, uTopColor, t);

    FragColor = vec4(color, 1.0);
}

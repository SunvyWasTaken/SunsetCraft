#version 330

in vec3 worldPos;
out vec4 FragColor;

uniform float uTime;
vec3 uSunDir = vec3(0.6, 0.8, 0.0);

float hash(vec2 p)
{
    p = fract(p * vec2(123.34, 345.45));
    p += dot(p, p + 34.345);
    return fract(p.x * p.y);
}

float noise(vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);

    float a = hash(i);
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
    (c - a)* u.y * (1.0 - u.x) +
    (d - b) * u.x * u.y;
}

void main()
{
    vec2 uv = worldPos.xz * 0.0005;

    // Scroll
    vec2 wind1 = uv + vec2(uTime * 0.01, 0.0);
    vec2 wind2 = uv * 2.0 + vec2(uTime * 0.02, 0.0);

    float base = noise(wind1);
    float detail = noise(wind2) * 0.5;

    float cloud = base + detail;

    // Densité
    cloud = smoothstep(0.6, 0.8, cloud);

    // Faux éclairage
    float light = clamp(dot(normalize(vec3(0.0,1.0,0.0)), -uSunDir), 0.0, 1.0);
    vec3 bright = vec3(1.0);
    vec3 shadow = vec3(0.75);

    vec3 color = mix(shadow, bright, light);

    FragColor = vec4(color, cloud);

    FragColor = vec4(1.0);
}
#version 330 core

in vec3 FragPos;  // position du fragment dans le monde
in vec3 Normal;   // normale du fragment

out vec4 FragColor;

// Paramètres de la lumière
vec3 lightDir = normalize(vec3(-1.0, -1.0, 0.5)); // direction de la lumière
vec3 lightColor = vec3(1.0, 1.0, 1.0);
vec3 objectColor = vec3(1.0, 0.5, 0.2);

void main()
{
    // éclairage diffuse basique
    float diff = max(dot(normalize(Normal), -lightDir), 0.0);

    vec3 color = objectColor * (0.2 + 0.8 * diff); // 0.2 = ambient
    FragColor = vec4(color, 1.0);
}


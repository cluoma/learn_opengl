#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D emission;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    // ambient component
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse component
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular component
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // emission
    vec3 emissionMask = step(vec3(1.0f), vec3(1.0f)-vec3(texture(material.specular, TexCoords)));
    vec3 emission = texture(emission, TexCoords).rgb * emissionMask;
    //vec3 emission = texture(emission, TexCoords * (1.0 + 0.15 * 2.0) - 0.15).rgb;

    // combine lighting components
    FragColor = vec4(ambient + diffuse + specular + emission, 1.0);
}
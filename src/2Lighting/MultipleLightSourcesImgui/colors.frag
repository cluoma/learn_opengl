#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // this stuff is for attenuation
    float constant;
    float linear;
    float quadratic;
};

uniform sampler2D emission;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform Material material;
uniform DirLight dirLight;
#define NBR_POINT_LIGHTS 4
uniform PointLight pointLights[NBR_POINT_LIGHTS];
uniform vec3 viewPos;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = calcDirLight(dirLight, norm, viewDir);
    for (int i = 0; i < NBR_POINT_LIGHTS; i++)
    {
        result += calcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    // combine lighting components
    FragColor = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    // light direction
    vec3 lightDir = normalize(-light.direction);  // this is for directional light

    // ambient component
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse component
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular component
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // combine lighting components
    return(ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // light direction
    vec3 lightDir = normalize(light.position - fragPos);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear*distance + light.quadratic*distance*distance);

    // ambient component
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse component
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular component
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // attenuation again
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // combine lighting components
    return(ambient + diffuse + specular);
}
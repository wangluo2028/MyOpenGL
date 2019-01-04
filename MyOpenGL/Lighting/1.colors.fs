#version 330 core
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 viewPos;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shiness;
};

uniform Material ObjectMaterial;

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

void main()
{
	vec3 ambientColor = vec3(texture(ObjectMaterial.diffuse, TexCoord)) * light.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diffuse = max(dot(norm, lightDir), 0.0);
	vec3 diffuseColor = diffuse * vec3(texture(ObjectMaterial.diffuse, TexCoord)) * light.diffuse;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 specColor = pow(max(dot(viewDir, reflectDir), 0.0), ObjectMaterial.shiness) * vec3(texture(ObjectMaterial.specular, TexCoord)) * light.specular;

	vec3 emissionColor = texture(ObjectMaterial.emission, TexCoord).rgb;
	vec3 result = ambientColor + diffuseColor + specColor + emissionColor;
    FragColor = vec4(result, 1.0);
}
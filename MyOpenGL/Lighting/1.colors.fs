#version 330 core
out vec4 FragColor;


struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	//sampler2D emission;
	float shininess;
};

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


struct SpotLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


//uniform vec3 objectColor;
uniform vec3 viewPos;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
uniform Material ObjectMaterial;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight[NR_POINT_LIGHTS] pointLights;
//uniform SpotLight spotLight;
//uniform Light light;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = CalcDirLight(dirLight, norm, viewDir);

	for (int i = 0; i < NR_POINT_LIGHTS; ++i)
	{
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}

	//CalcSpotLight(spotLight, norm, FragPos, viewDir);
	
	//vec3 emissionColor = texture(ObjectMaterial.emission, TexCoord).rgb;
	//vec3 result = ambientColor + diffuseColor + specColor + emissionColor;

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	vec3 ambientColor = light.ambient * vec3(texture(ObjectMaterial.diffuse, TexCoord));

	float diffuse = max(dot(normal, lightDir), 0.0); 
	vec3 diffuseColor = diffuse * light.diffuse* vec3(texture(ObjectMaterial.diffuse, TexCoord));

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), ObjectMaterial.shininess);
	vec3 specularColor = spec * light.specular * vec3(texture(ObjectMaterial.specular, TexCoord));

	return (ambientColor + diffuseColor + specularColor);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	vec3 ambientColor = texture(ObjectMaterial.diffuse, TexCoord).rgb * light.ambient;

	float diffuse = max(dot(normal, lightDir), 0.0); 
	vec3 diffuseColor = diffuse * texture(ObjectMaterial.diffuse, TexCoord).rgb * light.diffuse;

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), ObjectMaterial.shininess);
	vec3 specularColor = spec * texture(ObjectMaterial.specular, TexCoord).rgb * light.specular;

	float distance = length(light.position - fragPos);
	float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * distance * distance);

	ambientColor *= attenuation;
	diffuseColor *= attenuation;
	specularColor *= attenuation;

	return (ambientColor + diffuseColor + specularColor);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	vec3 ambientColor = texture(ObjectMaterial.diffuse, TexCoord).rgb * light.ambient;

	float diffuse = max(dot(normal, lightDir), 0.0); 
	vec3 diffuseColor = diffuse * texture(ObjectMaterial.diffuse, TexCoord).rgb * light.diffuse;

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), ObjectMaterial.shininess);
	vec3 specularColor = spec * texture(ObjectMaterial.specular, TexCoord).rgb * light.specular;

	float distance = length(light.position - fragPos);
	float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * distance * distance);

	ambientColor *= attenuation;
	diffuseColor *= attenuation;
	specularColor *= attenuation;

	return ambientColor + diffuseColor + specularColor;
}
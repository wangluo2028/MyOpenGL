#include "stdafx.h"
#include "MyShaderProgram.h"


UMaterial::UMaterial()
	:ObjectColor(1.0f, 1.0f, 1.0f)
{
	vertexShader = 0;
	fragmentShader = 0;
	shaderProgram = 0;
}

UMaterial::~UMaterial()
{
	if (glIsProgram(shaderProgram))
	{
		glDeleteProgram(shaderProgram);
	}	
}

unsigned int UMaterial::GetID()
{
	return shaderProgram;
}

bool UMaterial::SetupVertexShader(const char* vertexShaderFile)
{
	std::string vertexShaderSource = ReadStringFromFile(vertexShaderFile);
	const char *vertexShaderSrc = vertexShaderSource.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	int success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (GL_FALSE == success)
	{
		char infoLog[512];
		int logLength = 0;
		glGetShaderInfoLog(vertexShader, sizeof(infoLog)/sizeof(char), &logLength, infoLog);
		std::cout << "SHADER::VERTEX::COMPILE::ERROR" << infoLog << std::endl;

		return false;
	}

	return true;
}

bool UMaterial::SetupFragmentShader(const char* fragmentShaderFile)
{
	std::string fragmentShaderSource = ReadStringFromFile(fragmentShaderFile);
	const char *fragmentShaderSrc = fragmentShaderSource.c_str();

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	int success = 0;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (GL_FALSE == success)
	{
		char infoLog[512];
		int logLength = 0;
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog) / sizeof(char), &logLength, infoLog);
		std::cout << "SHADER::FRAGMENT::COMPILE::ERROR" << infoLog << std::endl;

		return false;
	}

	return true;
}

bool UMaterial::SetupShaderProgram()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	int success = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success != GL_TRUE)
	{
		char infoLog[512];
		int logLength = 0;
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog) / sizeof(char), &logLength, infoLog);
		std::cout << "SHADER::PROGRAM::LINK::ERROR" << infoLog << std::endl;

		return false;
	}

	return true;
}

void UMaterial::UseShaderProgram()
{
	glUseProgram(shaderProgram);

	size_t TextureCnt = Textures.size();
	for (size_t Index = 0; Index < TextureCnt; ++Index)
	{
		glActiveTexture(GL_TEXTURE0 + Index);
		Textures[Index]->UseTexture();

		std::string TextureName("MyTexture");
		TextureName += std::to_string(Index);
		glUniform1i(glGetUniformLocation(shaderProgram, TextureName.c_str()), Index);
	}
}

void UMaterial::SetTexture(size_t Index, UTexture2D *InTexture)
{
	if ((Index + 1) > Textures.size())
	{
		Textures.resize(Index + 1);
	}
	
	Textures[Index] = InTexture;
}

void UMaterial::SetObjectColor(glm::vec3 InObjectColor)
{
	ObjectColor = InObjectColor;
}

const glm::vec3& UMaterial::GetObjectColor()
{
	return ObjectColor;
}

std::string UMaterial::ReadStringFromFile(const char *FilePath)
{
	std::ifstream FileReader(FilePath);
	std::string FileContent((std::istreambuf_iterator<char>(FileReader)), std::istreambuf_iterator<char>());
	FileReader.close();

	return FileContent;
}

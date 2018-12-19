#include "stdafx.h"
#include "MyShaderProgram.h"


FMyShaderProgram::FMyShaderProgram()
{
	vertexShader = 0;
	fragmentShader = 0;
	shaderProgram = 0;
}

FMyShaderProgram::~FMyShaderProgram()
{
	if (glIsProgram(shaderProgram))
	{
		glDeleteProgram(shaderProgram);
	}	
}

bool FMyShaderProgram::SetupVertexShader(const char* vertexShaderFile)
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

bool FMyShaderProgram::SetupFragmentShader(const char* fragmentShaderFile)
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

bool FMyShaderProgram::SetupShaderProgram()
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

void FMyShaderProgram::UseShaderProgram()
{
	glUseProgram(shaderProgram);
}

std::string FMyShaderProgram::ReadStringFromFile(const char *FilePath)
{
	std::ifstream FileReader(FilePath);
	std::string FileContent((std::istreambuf_iterator<char>(FileReader)), std::istreambuf_iterator<char>());
	FileReader.close();

	return FileContent;
}

#include "stdafx.h"
#include "Texture2D.h"
#include "stb_image.h"

UTexture2D::UTexture2D()
{
	TextureData = NULL;

	TextureID = 0;

	ImgWidth = ImgHeight = 0;
	ImgChannels = 0;
}


UTexture2D::~UTexture2D()
{
}

unsigned char* UTexture2D::LoadFromFile(const std::string &FilePath)
{
	stbi_set_flip_vertically_on_load(true);
	TextureData = stbi_load(FilePath.c_str(), &ImgWidth, &ImgHeight, &ImgChannels, 0);
	
	return TextureData;
}

unsigned int UTexture2D::LoadTexture()
{
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (TextureData)
	{
		switch (ImgChannels)
		{
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImgWidth, ImgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);
			break;
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImgWidth, ImgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, TextureData);
			break;
		}
		
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(TextureData);
	}

	return TextureID;
}

void UTexture2D::UseTexture()
{
	glBindTexture(GL_TEXTURE_2D, TextureID);
}

unsigned int UTexture2D::GetObjectID() const
{
	return TextureID;
}

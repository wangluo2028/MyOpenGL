#pragma once
class UTexture2D
{
public:
	UTexture2D();
	~UTexture2D();

	unsigned char* LoadFromFile(const std::string &FilePath);

	unsigned int LoadTexture();

	void UseTexture();

	unsigned int GetObjectID() const;

protected:
	unsigned char *TextureData;
	int ImgWidth;
	int ImgHeight;
	int ImgChannels;

	unsigned int TextureID;
};


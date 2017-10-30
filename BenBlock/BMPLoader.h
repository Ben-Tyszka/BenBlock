#pragma once
class BMPLoader
{
public:
	BMPLoader();
	GLuint LoadTexture(const char* path);
	~BMPLoader();
private:
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
	GLuint textureID;
};


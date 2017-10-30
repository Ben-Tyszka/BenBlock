#include "stdafx.h"
#include "BMPLoader.h"


BMPLoader::BMPLoader()
{

}

GLuint BMPLoader::LoadTexture(const char * path)
{
	FILE * file;
	fopen_s(&file, path, "r");
	if (!file) {
		printf("Image %s could not be opened\n", path);
		return 0;
	}
	if (fread(header, 1, 54, file) != 54) {
		printf("%s is not a BMP File\n", path);
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("%s is a correct BMP file but passed first inspection\n", path);
		return 0;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0) {
		imageSize = width*height * 3;
	}
	if (dataPos == 0)
	{
		dataPos = 54;
	}

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;

}


BMPLoader::~BMPLoader()
{
	
}

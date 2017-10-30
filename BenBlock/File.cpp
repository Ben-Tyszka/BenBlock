#include "stdafx.h"
#include "File.h"


File::File(std::string path)
{
	std::ifstream textStream(path, std::ios::in);
	if (textStream.is_open()) {
		std::string Line = "";
		while (getline(textStream, Line))
			text += "\n" + Line;
		textStream.close();
	}
	else {
		printf("Can't open %s. Are you in the right directory?\n", path.c_str());
		getchar();
	}
}
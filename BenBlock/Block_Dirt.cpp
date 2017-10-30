#include "stdafx.h"
#include "Block_Dirt.h"


void Block_Dirt::Render()
{
	cube.Render();
}

void Block_Dirt::Generate(Camera cam)
{
	//cube = Cube::Cube(cam, "dirt.bmp");
}

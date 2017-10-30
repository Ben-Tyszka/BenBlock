#pragma once
#include "IBlock.h"
class Block_Dirt :
	public IBlock
{
public:
	Block_Dirt();
	void Generate(Camera cam);
	void Render();
private:
	Cube cube;
};


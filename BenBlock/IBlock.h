#pragma once
#include "Cube.h"
class IBlock
{
public:
	virtual void Generate(Camera cam) = 0;
	virtual void Render() = 0;
};


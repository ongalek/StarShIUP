#pragma once
#include "airs/math.h"
#include "CollisionObject.h"
#include "airs/SpritesRenderer.h"
#include "ResourceManager.h"
#include <vector>
class BloksTable
{
private:
	int MaxH;
	int MaxW;
	airs::vec2d SizeOfBlock;
	std::vector<int> Table;
	int ID[10];
	int GetElement(int x, int y);
	
public:
	BloksTable(airs::vec2d size, ResourceManager& resources);
	CollisionObject GetObjectAt(airs::vec2i A);
	airs::vec2d GetSize();
	int GetWidth();
	int GetHeight();


	void Render(airs::SpritesRenderer& renderer);
	

	
};


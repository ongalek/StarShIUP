#include "BloksTable.h"
#include <fstream>

int BloksTable::GetElement(int x, int y)
{
	return Table[x + y * MaxW];
}

BloksTable::BloksTable(airs::vec2d size, ResourceManager& resources)
{	
	std::ifstream fin("Table.txt");
	fin >> MaxW;
	fin >> MaxH;
	Table.resize(MaxW * MaxH);
	for (int j = MaxH - 1; j >= 0; j--)
		for (int i = 0; i < MaxW; i++)
			fin >> Table[i + j*MaxW];
	ID[0] = resources.GetSprite("back2");
	ID[1] = resources.GetSprite("earth");
	ID[2] = resources.GetSprite("grass");
	ID[3] = resources.GetSprite("planet1");
	ID[4] = resources.GetSprite("planet2");
	ID[5] = resources.GetSprite("planet3");
	ID[6] = resources.GetSprite("planet3");

	SizeOfBlock = size;
}

CollisionObject BloksTable::GetObjectAt(airs::vec2i A)
{
	if ((A.x >= MaxW) || (A.y >= MaxH) || (A.x < 0) || (A.y < 0))
		return CollisionObject(A * SizeOfBlock + SizeOfBlock / 2, SizeOfBlock);
	if (GetElement(A.x, A.y) == 0)
		return CollisionObject();
	else return CollisionObject(A * SizeOfBlock + SizeOfBlock / 2, SizeOfBlock);
}

airs::vec2d BloksTable::GetSize()
{
	return SizeOfBlock;
}

int BloksTable::GetWidth()
{
	return MaxW * SizeOfBlock.x;
}

int BloksTable::GetHeight()
{
	return MaxH * SizeOfBlock.y;
}

void BloksTable::Render(airs::SpritesRenderer& renderer)
{
  for (int i = 0; i < MaxH; i++)
	  for (int j = 0; j < MaxW; j++)
	  {
		  airs::vec2i Position(j, i);
		  if ((Position.x < 0) || (Position.y < 0))
		  { }
		  {
			  renderer.Push(ID[GetElement(j,i)], (Position * SizeOfBlock + SizeOfBlock / 2), SizeOfBlock);
		  }
	  }
}

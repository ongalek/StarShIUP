#include "ResourceManager.h"
#include <fstream>
#include <vector>
#include <iostream>
std::vector<std::string> parse(std::string a)
{
	std::vector<std::string> B;
	size_t found = a.find(':', 0);
	if (found == std::string::npos)
		return B;
	B.push_back(a.substr(0, found));
	size_t found2;
	for (found = a.find('"', found + 1); found != std::string::npos; found = a.find('"', found2 + 1))
	{
		found2 = a.find('"', found + 1);
		if (found2 == std::string::npos)
			return B;
		B.push_back(a.substr(found + 1, found2 - found - 1));
	}
	return B;
}



ResourceManager::ResourceManager(std::string path, airs::GUIWindow& window) : Window(window)
{

	std::ifstream fin(path);
	std::string str;
	while (getline(fin, str))
	{
		std::vector<std::string> A = parse(str);
		if (A.size() == 0)
		{
			continue;
		}
		if (A[0] == "sprite")
		{
			if (A.size() == 5)
			{
				SpriteMap.insert(std::make_pair(A[1], Spriteset.Size()));
				Spriteset.Load(A[2],stoi(A[3]),stoi(A[4]), 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			}
			else
			{
				SpriteMap.insert(std::make_pair(A[1], Spriteset.Size()));
				Spriteset.Load(A[2]);
			}
		}
		else throw std::runtime_error("error in string " + str);
	}
}



airs::Spriteset& ResourceManager::getSpriteset()
{
	return Spriteset;
}

int ResourceManager::GetSprite(std::string Name)
{
	return SpriteMap[Name];
}

airs::GUIWindow& ResourceManager::GetWindow()
{
	return Window;
}

bool ResourceManager::ControlUp()
{
	return (Window.Input[airs::key::W]) || (Window.Input[airs::key::Up]);
}

bool ResourceManager::ControlLeft()
{
	return (Window.Input[airs::key::A]) || (Window.Input[airs::key::Left]);
}

bool ResourceManager::ControlDown()
{
	return (Window.Input[airs::key::S]) || (Window.Input[airs::key::Down]);
}

bool ResourceManager::ControlRight()
{
	return (Window.Input[airs::key::D]) || (Window.Input[airs::key::Right]);
}

bool ResourceManager::ControlFire()
{
	return (Window.Input[airs::key::Space]) || (Window.Input[airs::key::F]);
}


double ResourceManager::Rand(double a,double  b)
{
	double j = rand();
	j = j / RAND_MAX;
	j = j * (b - a) + a;
	return j;

}




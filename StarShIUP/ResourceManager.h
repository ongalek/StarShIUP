#pragma once
#include <string>
#include"airs/Spriteset.h"
#include<map>
#include "airs/GUIWindow.h"

class ResourceManager
{
public:
	ResourceManager(std::string path, airs::GUIWindow&);
	airs::Spriteset& getSpriteset();
	int GetSprite(std::string);
	airs::GUIWindow& GetWindow();
	double Rand(double, double);
	bool ControlUp();
	bool ControlLeft();
	bool ControlDown();
	bool ControlRight();
	bool ControlFire();

private:
	airs::GUIWindow& Window;
	airs::Spriteset Spriteset;
	std::map<std::string,int> SpriteMap;
};




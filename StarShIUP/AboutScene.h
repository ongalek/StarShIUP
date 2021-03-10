#pragma once
#include "InfoScene.h"



class AboutScene : public InfoScene
{
private:
	static std::string GetSceneText();

public:
	AboutScene(ResourceManager& manager);

	virtual void Setup() override;
};


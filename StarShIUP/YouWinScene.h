#pragma once
#include "InfoScene.h"



class YouWinScene : public InfoScene
{
private:
	static std::string GetSceneText();

public:
    YouWinScene(ResourceManager& manager);

	virtual void Setup() override;
};


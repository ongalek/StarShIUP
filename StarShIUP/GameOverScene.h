#pragma once
#include "InfoScene.h"



class GameOverScene : public InfoScene
{
private:
	static std::string GetSceneText();

public:
    GameOverScene(ResourceManager& manager);

	virtual void Setup() override;
};


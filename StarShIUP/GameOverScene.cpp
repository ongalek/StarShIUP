#include "GameOverScene.h"
#include <chrono>
#include <array>



std::string GameOverScene::GetSceneText()
{
	int64_t millis = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()).count();

	const static std::array<std::string, 13> results = {
		"      Go and take a break!",
		"It was the worst game I have ever seen.",
		"Maybe you should lower the difficulty? :D"
		" Go and play something easier.",
		" Maybe you should try MLP game?",
		"Even my grandma was better then you!",
		"You are just a waste of sperm!",
		"         Suffer BITCH!",
		"        Was it to hard?",
		"      Try to play on ZERGS!",
		"  Even the dog plays better :D",
		"      So I guess you win.",
		"        Just go, sucker."
	};

	return R"SCENE_TEXT(

            You lose!
)SCENE_TEXT" + results[millis % results.size()];
}

GameOverScene::GameOverScene(ResourceManager& manager) : InfoScene(manager, "Menu", 0xff0000ffu)
{ 
}

void GameOverScene::Setup()
{
	SetInfoText(GetSceneText());
	InfoScene::Setup();
}

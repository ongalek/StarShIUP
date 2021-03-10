#include "YouWinScene.h"
#include <chrono>
#include <array>



std::string YouWinScene::GetSceneText()
{
	int64_t millis = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()).count();

	const static std::array<std::string, 7> results = {
		"  I saw much better than this...",
		"       Ok, take a cookie\n         from the floor.",
		"          Well, pleased?.",
		"   Now, I hear your ScreapOchka.",
		"  Switch to Terran and try again.",
		"         FUCKING CHEEZER!",
		"       Try without cheating.",
	};

	return R"SCENE_TEXT(

            You win!
)SCENE_TEXT" + results[millis % results.size()];
}

YouWinScene::YouWinScene(ResourceManager& manager) : InfoScene(manager, "Menu", 0x00ff00ffu)
{ 
}

void YouWinScene::Setup()
{
	SetInfoText(GetSceneText());
	InfoScene::Setup();
}

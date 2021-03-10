#include "AboutScene.h"
#include <chrono>
#include <array>



std::string AboutScene::GetSceneText()
{
	int64_t millis = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch()).count();

	const static std::array<std::string, 27> results = { 
		"Hi there!",
		"It was hard...",
		"Ugly motherfucker!",
		"Oh shit, I am sorry...",
		"That is the best scene in this\ngame :)",
		"Your bunny wrote!",
		"So, what is next?",
		"GLORY TO ARSTOTZKA!",
		"I love beer...",
		"Pray for the sorrow!",
		"Psss, I can help you to escape.",
		"You may think you're god. But I\nknow that             I. M. Sin.",
		"SUPERSHIT",
		"Do you want some magic powder?",
		"This is so fucking strange.",
		"ILAB and SWNLM D:",
		"Hello world!",
		"Fuck this world!",
		"What are you looking for?",
		"It is just another way to die.",
		"The cake is a Lie.",
		"You Ain`t Ready",
		"Maybe, I should stop here...",
		"It will only get worse :(",
		"You should see me in a crown!",
		"BATMETAL",
		"Internet is for porn."
	};

	return R"SCENE_TEXT(
Created by:         Controls:
Myachin N. M.       Up: W, Up
Smolenchuk I. K.  Left: A, Left
Bubnova P. K.     Down: S, Down
                 Right: D, Right
)SCENE_TEXT" + results[millis % results.size()];
}

AboutScene::AboutScene(ResourceManager& manager) : InfoScene(manager, "Menu", 0x0000ffffu)
{
}

void AboutScene::Setup()
{
	SetInfoText(GetSceneText());
	InfoScene::Setup();
}

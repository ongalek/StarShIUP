#pragma once
#include "airs/GraphicsWindow.h"
#include "airs/Text.h"
#include "airs/SpritesRenderer.h"
#include"ResourceManager.h"
#include "Scene.h"
#include "airs/GUIWindow.h"
#include "SceneMenu.h"
#include "SpaceShipScene.h"
#include "YouWinScene.h"
#include "GameOverScene.h"
#include "VanyaGame.h"
#include "AboutScene.h"



class GameManager
{
public:
	GameManager(std::string path);
	void Run();

private:
	Scene* CurScene;
	airs::DynamicCharset Charset;
	airs::GUIWindow Window;
	ResourceManager Resources;
	airs::SpritesRenderer Renderer;
	bool IsRunning;
	airs::StaticText FPSText;
	SceneMenu Menu;
	SpaceShipScene Ship;
	VanyaGame Ivan;
	YouWinScene YouWin;
	GameOverScene GameOver;
	AboutScene About;
	
	void SizeChanged(int, int);
	bool OnClose();
};


#pragma once
#include "Scene.h"
#include "airs/Button.h"
#include "airs/Layout.h"
class SceneMenu : public Scene 
{
private:
	airs::Layout Menu;
	airs::Button PlayButton;
	airs::Button SettingsButton;
	airs::Button ExitButton;
	std::string Request;

	void ShowAbout();
	void RequestQuit();

public:
	SceneMenu(ResourceManager& ReManager);
	virtual std::string Update(double dt) override;
	virtual void Render(airs::SpritesRenderer& Renderer, airs::StaticText& text) override;
	virtual void Setup() override;
	void NewScene();

};


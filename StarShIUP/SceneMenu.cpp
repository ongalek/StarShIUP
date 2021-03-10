#include "SceneMenu.h"


void SceneMenu::ShowAbout()
{
	Request = "About";
	Menu.Close();
}

void SceneMenu::RequestQuit()
{
	Request = "quit";
	Menu.Close();
}

SceneMenu::SceneMenu(ResourceManager& ReManager) : Scene(ReManager)
{
	Menu.SetPosition({ 0, 0 });
	PlayButton.SetText("Play");
	PlayButton.SetReleasedTextColor(0x00AA00ffu);
	PlayButton.SetPressedTextColor(0x0000ffddu);
	PlayButton.SetSelectedTextColor(0x0000ffbbu);
	PlayButton.SetPosition({0, 600});
	PlayButton.SetSize({ 400,110 });
	PlayButton.SetPressedUnit(airs::GfxUnit(airs::GfxUnit::Scaled,0, 0x808080ffu));
	PlayButton.SetReleasedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0xffffffffu));
	PlayButton.SetSelectedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0xA0A0A0ffu));
	Menu.Add(PlayButton);
	SettingsButton.SetText("About");
	SettingsButton.SetReleasedTextColor(0x00AA00ffu);
	SettingsButton.SetPressedTextColor(0x0000ffddu);
	SettingsButton.SetSelectedTextColor(0x0000ffbbu);
	SettingsButton.SetPosition({ 0,300 });
	SettingsButton.SetSize({ 400,110 });
	SettingsButton.SetPressedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0x808080ffu));
	SettingsButton.SetReleasedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0xffffffffu));
	SettingsButton.SetSelectedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0xA0A0A0ffu));
	Menu.Add(SettingsButton);
	ExitButton.SetText("Exit");
	ExitButton.SetReleasedTextColor(0x00AA00ffu);
	ExitButton.SetPressedTextColor(0x0000ffddu);
	ExitButton.SetSelectedTextColor(0x0000ffbbu);
	ExitButton.SetPosition({ 0,0 });
	ExitButton.SetSize({ 400,110 });
	ExitButton.SetPressedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0x808080ffu));
	ExitButton.SetReleasedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0xffffffffu));
	ExitButton.SetSelectedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0xA0A0A0ffu));
	Menu.Add(ExitButton);
	PlayButton.Click.bind<SceneMenu, &SceneMenu::NewScene>(this);
	SettingsButton.Click.bind<SceneMenu, &SceneMenu::ShowAbout>(this);
	ExitButton.Click.bind<SceneMenu, &SceneMenu::RequestQuit>(this);

}


std::string SceneMenu::Update(double dt)
{
	PlayButton.SetPosition({ResManager.GetWindow().Width()/2-200,ResManager.GetWindow().Height() / 2		+ 200 - 55 });
	SettingsButton.SetPosition({ ResManager.GetWindow().Width() / 2-200,ResManager.GetWindow().Height() / 2 - 0 - 55 });
	ExitButton.SetPosition({ ResManager.GetWindow().Width() / 2-200,ResManager.GetWindow().Height() / 2		- 200 - 55 });
	return Request;
	
}

void SceneMenu::NewScene()
{
	Request = "ShipScene";
	Menu.Close();
}
void SceneMenu::Render(airs::SpritesRenderer& Renderer, airs::StaticText& text)
{

}

void SceneMenu::Setup()
{
	 ResManager.GetWindow().Add(Menu);
	 Request = "";
}
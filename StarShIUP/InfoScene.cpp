#include "InfoScene.h"

void InfoScene::UnderstoodButton_Click()
{
	SceneLayout.Close();
	SceneRunning = false;
}

void InfoScene::SetInfoText(const std::string text)
{
	SceneText.SetText(text);
}

InfoScene::InfoScene(ResourceManager& manager, std::string exit_request, uint32_t text_color) : 
	Scene(manager), ExitRequest(std::move(exit_request))
{
	SceneLayout.SetPosition({ 0, 0 });
	UnderstoodButton.SetText("Understood");
	UnderstoodButton.SetReleasedTextColor(0x00aa00ffu);
	UnderstoodButton.SetPressedTextColor(0x0000ffddu);
	UnderstoodButton.SetSelectedTextColor(0x0000ffbbu);
	UnderstoodButton.SetPosition({ 500, 0 });
	UnderstoodButton.SetSize({ 500, 110 });
	UnderstoodButton.SetPressedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0x808080ffu));
	UnderstoodButton.SetReleasedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0xffffffffu));
	UnderstoodButton.SetSelectedUnit(airs::GfxUnit(airs::GfxUnit::Scaled, 0, 0xa0a0a0ffu));
	SceneLayout.Add(UnderstoodButton);

	SceneText.SetColor(text_color);
	SceneText.SetPosition({ 0, 750 });
	SceneLayout.Add(SceneText);

	UnderstoodButton.Click.bind<InfoScene, &InfoScene::UnderstoodButton_Click>(this);
}

void InfoScene::Setup()
{
	ResManager.GetWindow().Add(SceneLayout);
	SceneRunning = true;
}
std::string InfoScene::Update(double dt)
{
	SceneLayout.SetPosition({ ResManager.GetWindow().Width() / 2 - 750, ResManager.GetWindow().Height() / 2 - 350 });

	return SceneRunning ? "" : ExitRequest;
}
void InfoScene::Render(airs::SpritesRenderer& Renderer, airs::StaticText& text) { }

#pragma once
#include "Scene.h"
#include "airs/Layout.h"
#include "airs/Label.h"
#include "airs/Button.h"



class InfoScene : public Scene
{
private:
    airs::Layout SceneLayout;
    airs::Label SceneText;
    airs::Button UnderstoodButton;

    bool SceneRunning;

    const std::string ExitRequest;

    void UnderstoodButton_Click();

protected:
    void SetInfoText(const std::string text);

public:
    InfoScene(ResourceManager& manager, std::string exit_request, uint32_t text_color);

    virtual void Setup() override;
    virtual std::string Update(double dt) override;
    virtual void Render(airs::SpritesRenderer& Renderer, airs::StaticText& text) override;
};


#pragma once
#include "airs/Text.h"
#include <iostream>
#include "ResourceManager.h"
#include"airs/SpritesRenderer.h"
#include <string>



class Scene
{
protected:
   ResourceManager& ResManager;
   Scene(ResourceManager & ReManager);
public:
    virtual std::string Update(double dt) = 0;
    virtual void Render(airs::SpritesRenderer &Renderer, airs::StaticText& text)= 0;
    virtual void Setup() = 0;
    Scene() = delete;
};
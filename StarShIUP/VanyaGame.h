#pragma once
#include "Scene.h"
#include "airs/math.h"
#include "BloksTable.h"
#include "Heroes.h"
#include "VanyaProjectile.h"
class VanyaGame : public Scene
{
private:
	BloksTable Table;
	Hero Player;
	std::list<VanyaProjectile> PlayerProjectiles;
	std::list<VanyaProjectile> EnemyProjectiles;
	std::list<Hero> Enemies;
	double SpawnTimer;
	double ShootKD;
public:
	int Score;
	VanyaGame(ResourceManager& Resources);
	void Setup() override;
	void Render(airs::SpritesRenderer& Renderer, airs::StaticText& text) override;
	std::string Update(double dt) override;
	
	




};


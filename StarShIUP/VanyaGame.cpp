#include "VanyaGame.h"
#include "airs/math.h"
#include "BloksTable.h"
#include "VanyaProjectile.h"
#include <fstream>
#include "Heroes.h"
VanyaGame::VanyaGame(ResourceManager& Resources) : Scene(Resources), Table(100, Resources), 
Player(airs::vec2d(300,300 ),Resources.GetSprite("jump"), Resources.GetSprite("go"), Resources.GetSprite("stay"), Resources.GetSprite("fall"), Resources.GetSprite("health"),
Resources.GetSprite("health bar"),Table)
{

}

void VanyaGame::Setup()
{
	Player.SetPosition(airs::vec2d(300, 300));
	Player.SetHealth(15.0);
	Score = 0;
	double ShootKD = 0.09;
	PlayerProjectiles.clear();
	EnemyProjectiles.clear();
	Enemies.clear();
	int CountEnemies;
	std::ifstream fin("Enemies.txt");
	fin >> CountEnemies;
	
	for (int i = 0; i < CountEnemies; i++)
	{
		airs::vec2d Pos;
		fin >> Pos.x;
		fin >> Pos.y;
		Hero Enemy(Pos, ResManager.GetSprite("jump"), ResManager.GetSprite("go"), ResManager.GetSprite("stay"), ResManager.GetSprite("fall"), ResManager.GetSprite("health"), ResManager.GetSprite("health bar"), Table);
		Enemies.push_back(Enemy);
	}
	
}
std::string VanyaGame::Update(double dt)
{

	if (ResManager.ControlFire())
	{
		if (Player.ShootReady())
		{
			Player.ResetShoot();
			PlayerProjectiles.push_back(VanyaProjectile(Player.GetPosition(), 5, Player.GetDirection() * airs::vec2d(1000.0, 0), ResManager.GetSprite("fireball"), Table));
		}
	}


	Player.Update(ResManager.ControlUp(), ResManager.ControlLeft(), ResManager.ControlRight(), dt);
	for (auto Bullet = EnemyProjectiles.begin(); Bullet != EnemyProjectiles.end();)
	{
		Bullet->Update(dt);
		Player.GotIt(*Bullet);
		if (!Bullet->Alive()) Bullet = EnemyProjectiles.erase(Bullet);
		else Bullet++;
	}
	for (auto it = PlayerProjectiles.begin(); it != PlayerProjectiles.end();)
	{
		
		it->Update(dt);
		if (!it->Alive()) it = PlayerProjectiles.erase(it);
		else it++;
	}
	for (auto it = Enemies.begin(); it != Enemies.end();)
	{
		for (auto Kill = PlayerProjectiles.begin(); Kill != PlayerProjectiles.end(); Kill++)
		{
			it->GotIt(*Kill);
		}
		
		const int level = 5;
		it->Update(Player.GetPosition().y - it->GetPosition().y > level && 0.01 > ResManager.Rand(0, 1), it->GetPosition().x  > Player.GetPosition().x && 0.01 > ResManager.Rand(0, 1), it->GetPosition().x < Player.GetPosition().x && 0.01 > ResManager.Rand(0, 1),dt);
		if (it->ShootReady())
		{
			it->ResetShoot();
			EnemyProjectiles.push_back(VanyaProjectile(it->GetPosition(), 3,  it->GetDirection() * airs::vec2d(50.0, 0), ResManager.GetSprite("projectile red"),Table));
		}
		if (!it->Alive())
		{
			it = Enemies.erase(it);
			Score++;
		}
		else it++;
		
	}
	for (auto EnBullet = EnemyProjectiles.begin(); EnBullet != EnemyProjectiles.end();)
	{

		EnBullet->Update(dt);
		if (!EnBullet->Alive()) EnBullet = EnemyProjectiles.erase(EnBullet);
		else EnBullet++;
	}
	
	if (Enemies.size() == 0)
		return "YouWin";
	if (!Player.Alive())
		return "GameOver";
	return"";
}

void VanyaGame::Render(airs::SpritesRenderer& Renderer, airs::StaticText& text)
{
	airs::vec2d ScreenSize = ResManager.GetWindow().ClientSize();
	airs::vec2d CameraPosition = Player.GetPosition() - ScreenSize / 2.0;
	if (CameraPosition.x < 0) CameraPosition.x = 0;
	if (CameraPosition.y < 0) CameraPosition.y = 0;
	if (CameraPosition.x > Table.GetWidth() - ScreenSize.x) CameraPosition.x = Table.GetWidth() - ScreenSize.x;
	if (CameraPosition.y > Table.GetHeight() - ScreenSize.y) CameraPosition.y = Table.GetHeight() - ScreenSize.y;
	
	Renderer.Position(-CameraPosition);

	
	Table.Render(Renderer);
	for (VanyaProjectile p : PlayerProjectiles) p.Render(Renderer);
	for (VanyaProjectile p : EnemyProjectiles) p.Render(Renderer);
	for (Hero e : Enemies) e.Render(Renderer, 0xff0000ffu);

	Player.Render(Renderer, 0xffffffffu);
	text.Origin(0, 0);
	text.Color(0x00ffffffu);
	text << "Enemies alive: " << Enemies.size();

}




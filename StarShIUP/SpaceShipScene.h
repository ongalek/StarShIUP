#pragma once
#include "ResourceManager.h"
#include "Scene.h"
#include "Ship.h"
#include "Projectile.h"
#include <list>



class BackItem
{
private:
	airs::vec2d Position;
	int ID;

public:
	BackItem(airs::vec2d pos, int id)
	{
		Position = pos;
		ID = id;
	}
	void Render(airs::SpritesRenderer& renderer)
	{
		renderer.Push(ID, Position);
	}
};

class SpaceShipScene : public Scene
{
private:
	int PlayerID, EnemyID, HealthID, HealthBarID, StarIDs[7], PlanetIDs[4];
	double FieldW, FieldH;

	Ship Player;
	std::list<BackItem> Background;
	std::list<Projectile> PlayerProjectiles;
	std::list<Projectile> EnemyProjectiles;
	std::list<Ship> Enemies;
	double SpawnTimer;

	int Score;


public:
	SpaceShipScene(ResourceManager& manager) : Scene(manager),
		FieldW(6000), FieldH(3000),
		Player(FieldW, FieldH, airs::vec2d(0, 0), ResManager.GetSprite("shiup"),
		ResManager.GetSprite("health"), ResManager.GetSprite("health bar"))
	{
		PlayerID = ResManager.GetSprite("shiup");
		EnemyID = ResManager.GetSprite("enemy");
		HealthID = ResManager.GetSprite("health");
		HealthBarID = ResManager.GetSprite("health bar");
		StarIDs[0] = ResManager.GetSprite("star1");
		StarIDs[1] = ResManager.GetSprite("star2");
		StarIDs[2] = ResManager.GetSprite("star3");
		StarIDs[3] = ResManager.GetSprite("star4");
		StarIDs[4] = ResManager.GetSprite("star5");
		StarIDs[5] = ResManager.GetSprite("star6");
		StarIDs[6] = ResManager.GetSprite("star7");
		PlanetIDs[0] = ResManager.GetSprite("planet1");
		PlanetIDs[1] = ResManager.GetSprite("planet2");
		PlanetIDs[2] = ResManager.GetSprite("planet3");
		PlanetIDs[3] = ResManager.GetSprite("planet4");
	}

	void Setup() override
	{
		Score = 0;
		Player.SetPosition(airs::vec2d(FieldW / 2, FieldH / 2));
		Player.SetHealth(10);

		Background.clear();
		PlayerProjectiles.clear();
		EnemyProjectiles.clear();
		Enemies.clear();

		for (int i = 0; i < 5000; i++)
		{
			airs::vec2d pos(ResManager.Rand(0, FieldW), ResManager.Rand(0, FieldH));
			BackItem star(pos, StarIDs[(int)ResManager.Rand(0, 6.9)]);
			Background.push_back(star);
		}
		for (int i = 0; i < 30; i++)
		{
			airs::vec2d pos(ResManager.Rand(0, FieldW), ResManager.Rand(0, FieldH));
			BackItem planet(pos, PlanetIDs[(int)ResManager.Rand(0, 3.9)]);
			Background.push_back(planet);
		}
		
		SpawnTimer = 0.0;
	}
	std::string Update(double delta) override
	{
		double Friction = 0.1;
		airs::vec2d player_engines_force;
		if (ResManager.ControlUp()) player_engines_force.y += 10000.0;
		if (ResManager.ControlLeft()) player_engines_force.x -= 10000.0;
		if (ResManager.ControlDown()) player_engines_force.y -= 10000.0;
		if (ResManager.ControlRight()) player_engines_force.x += 10000.0;
		if (ResManager.ControlFire())
		{
			Projectile proj(Player.GetPosition(), Player.GetVelocity() + airs::vec2d(1000.0, 0), ResManager.GetSprite("projectile"));
			PlayerProjectiles.push_back(proj);
		}

		Player.Update(delta, Friction, player_engines_force);
		for (auto it = EnemyProjectiles.begin(); it != EnemyProjectiles.end();)
		{
			it->Update(delta);
			Player.Intersect(*it);
			if (!it->Alive()) it = EnemyProjectiles.erase(it);
			else it++;
		}

		for (auto it = PlayerProjectiles.begin(); it != PlayerProjectiles.end();)
		{
			it->Update(delta);
			if (!it->Alive()) it = PlayerProjectiles.erase(it);
			else it++;
		}
		for (auto it = Enemies.begin(); it != Enemies.end();)
		{
			for (auto itp = PlayerProjectiles.begin(); itp != PlayerProjectiles.end(); itp++)
			{
				it->Intersect(*itp);
			}

			it->Update(delta, Friction, airs::vec2d(-1000.0, 0.0));

			if (it->GetPosition().x <= 0) it->SetPosition(airs::vec2d(FieldW, it->GetPosition().y));

			if (it->ShootReady())
			{
				it->ResetShoot();
				Projectile proj(it->GetPosition(), it->GetVelocity() + airs::vec2d(-1000.0, 0), ResManager.GetSprite("projectile red"));
				EnemyProjectiles.push_back(proj);
			}

			if (!it->Alive())
			{
				it = Enemies.erase(it);
				Score++;
			}
			else it++;
		}

		SpawnTimer -= delta;
		if (SpawnTimer <= 0.0)
		{
			SpawnTimer = 0.5;
			if (Enemies.size() < 1000) Enemies.push_back(Ship(FieldW, FieldH, 
				airs::vec2d(FieldW, ResManager.Rand(0, FieldH)), EnemyID, HealthID, HealthBarID));
		}

		if (Score >= 10) return "VanyaGame";
		if (!Player.Alive()) return "GameOver";
		return "";
	}
	void Render(airs::SpritesRenderer& renderer, airs::StaticText& text) override
	{
		airs::vec2d ScreenSize = ResManager.GetWindow().ClientSize();
		airs::vec2d CameraPosition = Player.GetPosition() - ScreenSize / 2.0;
		if (CameraPosition.x < 0) CameraPosition.x = 0;
		if (CameraPosition.y < 0) CameraPosition.y = 0;
		if (CameraPosition.x > FieldW - ScreenSize.x) CameraPosition.x = FieldW - ScreenSize.x;
		if (CameraPosition.y > FieldH - ScreenSize.y) CameraPosition.y = FieldH - ScreenSize.y;

		renderer.Position(-CameraPosition);
		for (BackItem i : Background) i.Render(renderer);
		for (Projectile p : PlayerProjectiles) p.Render(renderer);
		for (Projectile p : EnemyProjectiles) p.Render(renderer);
		for (Ship e : Enemies) e.Render(renderer);
		Player.Render(renderer);

		text.Origin(0, 0);
		text.Color(0xffffffffu);
		text << "Score: " << Score << " / 10";
	}
};


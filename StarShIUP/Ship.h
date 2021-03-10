#pragma once
#include "airs/math.h"
#include "airs/SpritesRenderer.h"
#include "Projectile.h"



class Ship
{
private:
	double FieldW;
	double FieldH;

	airs::vec2d Position;
	airs::vec2d Velocity;
	airs::vec2d Size;
	int SpriteID;
	int HealthID;
	int BarID;
	double MaxHealth;
	double Health;
	double Mass;
	double ShootTimer;

public:
	Ship(double fw, double fh, airs::vec2d pos, int id, int hpid, int hbid)
	{
		FieldW = fw;
		FieldH = fh;

		Position = pos;
		Velocity = 0.0;
		SpriteID = id;
		HealthID = hpid;
		BarID = hbid;
		Size = airs::vec2d(64.0, 32.0);
		Mass = 1.0;
		Health = MaxHealth = 10.0;
		ShootTimer = 1.0;
	}

	bool Collision(Projectile& e)
	{
		airs::vec2d hsize = Size / 2.0;

		return e.GetPosition().x >= Position.x - hsize.x && e.GetPosition().x <= Position.x + hsize.x &&
			e.GetPosition().y >= Position.y - hsize.y && e.GetPosition().y <= Position.y + hsize.y;
	}

	void Update(double delta, double drag, airs::vec2d force)
	{
		Velocity += force / Mass * delta - (Velocity * Velocity.abs() + Velocity) / Mass * drag * delta;
		Position += Velocity * delta;
		ShootTimer -= delta;

		if (Position.x < 0) Position.x = 0;
		if (Position.y < 0) Position.y = 0;
		if (Position.x > FieldW) Position.x = FieldW;
		if (Position.y > FieldH) Position.y = FieldH;
	}
	void Intersect(Projectile& e)
	{
		if (Collision(e))
		{
			Health -= e.GetDamage();
			e.Kill();
		}
	}

	void Render(airs::SpritesRenderer& renderer)
	{
		renderer.Push(SpriteID, Position, Size);
		renderer.Push(BarID, Position - airs::vec2d(0.0, 10.0 + Size.y / 2.0));
		renderer.Push(HealthID, Position - airs::vec2d((MaxHealth - Health) / MaxHealth * 25.0, 10.0 + Size.y / 2.0),
			airs::vec2d(Health / MaxHealth * 50.0, 6.0));
	}
	bool Alive()
	{
		return Health > 0.0;
	}
	bool ShootReady()
	{
		return ShootTimer <= 0.0;
	}
	void ResetShoot()
	{
		ShootTimer = 1.0;
	}

	airs::vec2d GetPosition()
	{
		return Position;
	}
	airs::vec2d GetVelocity()
	{
		return Velocity;
	}

	void SetPosition(airs::vec2d pos)
	{
		Position = pos;
	}
	void SetHealth(double health)
	{
		Health = health;
	}
};


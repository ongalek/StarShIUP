#pragma once
#include "airs/SpritesRenderer.h"
#include "airs/math.h"



class Projectile
{
private:
	airs::vec2d Position;
	airs::vec2d Velocity;
	int SpriteID;
	double LifeTime;
	double Damage;

public:
	Projectile(airs::vec2d pos, airs::vec2d vel, int id)
	{
		Position = pos;
		Velocity = vel;
		SpriteID = id;
		Damage = 1;
		LifeTime = 2.0;
	}

	airs::vec2d GetPosition()
	{
		return Position;
	}
	airs::vec2d GetVelocity()
	{
		return Velocity;
	}
	double GetDamage()
	{
		return Damage;
	}
	void Kill()
	{
		LifeTime = -1.0f;
	}

	void Update(double delta)
	{
		Position += Velocity * delta;
		LifeTime -= delta;
	}
	void Render(airs::SpritesRenderer& renderer)
	{
		renderer.Push(SpriteID, Position);
	}
	bool Alive()
	{
		return LifeTime > 0.0;
	}
};


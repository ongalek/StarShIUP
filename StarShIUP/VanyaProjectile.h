#pragma once
#pragma once
#include "airs/SpritesRenderer.h"
#include "airs/math.h"
#include "CollisionObject.h"
#include "BloksTable.h"

class VanyaProjectile
{

private:
	airs::vec2d Position;
	airs::vec2d Velocity;
	int SpriteID;
	double LifeTime;
	double Damage;
	BloksTable& Table;

public:
	VanyaProjectile(airs::vec2d pos, double damage, airs::vec2d vel, int id, BloksTable& table) : Table(table)
	{
		Table = table;
		Position = pos;
		Velocity = vel;
		SpriteID = id;
		Damage = damage;
		LifeTime = 10.0;
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
		
	
		if (ProjectileCollision())
		{
			Kill();
		}
	}
	void Render(airs::SpritesRenderer& renderer)
	{
		renderer.Push(SpriteID, Position);
	}
	bool Alive()
	{
		return LifeTime > 0.0;
	}
	bool ProjectileCollision()
	{
		CollisionObject HitBox(Position, 0);
		for (int x = -5; x < 5; x++)
		{
			for (int y = -2; y < 2; y++)
			{
				airs::vec2d Near(x, y);
				if (HitBox.Collision(Table.GetObjectAt(Position / Table.GetSize() + Near)))
					return true;
			}
		}
		return false;

	}
};
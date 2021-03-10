#pragma once
#include "airs/math.h"
#include "airs/SpritesRenderer.h"
#include "Projectile.h"
#include "CollisionObject.h"
#include  "BloksTable.h"
#include "VanyaProjectile.h"
class Hero
{
private:
	airs::vec2d Position;
	airs::vec2d Velocity;
	airs::vec2d Size;
	int SpriteID;
	int	IDJump;
	int IDGo;
	int IDStay;
	int	IDFall;
	int HealthID;
	int BarID;
	double MaxHealth;
	double CurHealth;
	double Mass;
	double ShootKD;
	double ShootTimer;
	BloksTable& Table;
	airs::vec2d Direction;
	bool OnGround;

public:
	airs::vec2d GetDirection();
	airs::vec2d GetVelocity();
	Hero(airs::vec2d pos, int id1, int id2, int id3, int id4, int hpid, int hbid, BloksTable& table) : Table(table)
	{
		OnGround = true;
		Direction = airs::vec2d(1.0,1.0);
		Position = pos;
		Velocity = 0.0;
		IDJump = id1;
		IDGo = id2;
		IDStay = id3;
		IDFall = id4;
		HealthID = hpid;
		BarID = hbid;
		Size = airs::vec2d(50.0, 80.0);
		Mass = 1.0;
		CurHealth = MaxHealth = 15.0;
		ShootTimer = ShootKD = 1.0;
	}
	bool Collision(VanyaProjectile& ammo);
	void Update(bool, bool, bool, double);
	CollisionObject HitBoxCollision();
	bool Alive();
	void Render(airs::SpritesRenderer& renderer, uint32_t color);
	airs::vec2d GetPosition();
	void SetPosition(airs::vec2d pos);
	void SetHealth(double);
	bool ShootReady();
	void ResetShoot();
	void GotIt(VanyaProjectile& e);


	

	

};


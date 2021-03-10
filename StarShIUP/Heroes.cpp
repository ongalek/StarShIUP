#include "Heroes.h"
#include "CollisionObject.h"
#include "BloksTable.h"


airs::vec2d Hero::GetDirection()
{
	return Direction;
}

airs::vec2d Hero::GetVelocity()
{
	return Velocity;
}

bool Hero::Collision(VanyaProjectile& ammo)
{
	return  ammo.GetPosition().x >= (Position.x - Size.x / 2) && ammo.GetPosition().x <= (Position.x + Size.x / 2) && ammo.GetPosition().y >= (Position.y - Size.y / 2) && ammo.GetPosition().y <= (Position.y + Size.y / 2);
}

void Hero::Update(bool Up, bool Left, bool Right, double delta)
{

	double drag = 0.01f;
	ShootTimer -= delta;
	airs::vec2d force = 0;
	force.y = -500.0;
	if (Right)
		force.x = 2000;
	if (Left)
		force.x = -2000;
	if (Right && Left)
		force.x = 0;
	if (Up && OnGround)
	{
		Velocity.y = 3000;
		OnGround = false;
	}
	Velocity += force / Mass * delta - (Velocity * Velocity.abs() + Velocity) / Mass * drag * delta;
	CollisionObject buf;
	int i = 10;
	Position.x += Velocity.x * delta;
	while (!(buf = HitBoxCollision()).GetNonObj() && i--)
	{
		CollisionObject Player(Position, Size);
		Position = buf.PushX(Player);

		Velocity.x = 0;
	}

	i = 10;
	Position.y += Velocity.y * delta;
	while (!(buf = HitBoxCollision()).GetNonObj() && i--)
	{
		CollisionObject Player(Position, Size);
		Position = buf.PushY(Player);
		OnGround = true;

		Velocity.y = 0;
	}
	if (Velocity.x < 0)
		Direction.x = -1;
	if (Velocity.x > 0)
		Direction.x = 1;
}

CollisionObject Hero::HitBoxCollision()
{
	CollisionObject HitBox(Position, Size);
	for (int x = -5; x < 5; x++)
	{
		for (int y = -2; y < 2; y++)
		{
			airs::vec2d Near(x, y);
			if (HitBox.Collision(Table.GetObjectAt(Position / Table.GetSize() + Near)))
				return Table.GetObjectAt(Position / Table.GetSize() + Near);
		}
	}
	return CollisionObject();
}

bool Hero::Alive()
{
	return CurHealth > 0;
}

void Hero::Render(airs::SpritesRenderer& renderer, uint32_t colour)    
{


	if (Velocity.y > 10)
		renderer.Push(IDJump, Position, Size * Direction,0,colour);
	else if (Velocity.y < -10)
		renderer.Push(IDFall, Position, Size * Direction,0,colour);
	else if (Velocity.x > 10)
		renderer.Push(IDGo, Position, Size * Direction,0,colour);
	else if (Velocity.x < -10)
		renderer.Push(IDGo, Position, Size * Direction,0,colour);
	else
		renderer.Push(IDStay, Position, Size * Direction,0, colour);
	renderer.Push(BarID, Position + airs::vec2d(0.0, 10.0 + Size.y / 2.0));
	renderer.Push(HealthID, Position + airs::vec2d((MaxHealth - CurHealth) / MaxHealth * 25.0, 10.0 + Size.y / 2.0),
		airs::vec2d(CurHealth / MaxHealth * 50.0, 6.0));


}

airs::vec2d Hero::GetPosition()
{
	return Position;
}

void Hero::SetPosition(airs::vec2d pos)
{
	Position = pos;
}

void Hero::SetHealth(double h)
{
	CurHealth = h;
}

bool Hero::ShootReady()
{
	return ShootTimer <= 0.0;
}

void Hero::ResetShoot()
{
	ShootTimer = ShootKD;
}

void Hero::GotIt(VanyaProjectile& Bullet)
{

	if (Collision(Bullet))
	{
		CurHealth -= Bullet.GetDamage();
		Bullet.Kill();

	}
}

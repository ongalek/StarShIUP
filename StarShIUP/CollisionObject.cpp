#include "CollisionObject.h"

CollisionObject::CollisionObject()
{
	NonObj = true;
}

CollisionObject::CollisionObject(airs::vec2d pos, airs::vec2d size)
{
	Position = pos; 
	Size = size;
	NonObj = false;
}

bool CollisionObject::Collision(const CollisionObject& A)
{
	if((A.NonObj) || NonObj) 
		return false;
	double lineRight = Position.x + Size.x / 2;
	double lineLeft =  Position.x - Size.x / 2;
	double lineUp =  Position.y + Size.y / 2;
	double lineDown = Position.y - Size.y / 2;
	double AlineRight = A.Position.x + A.Size.x / 2;
	double AlineLeft = A.Position.x - A.Size.x / 2;
	double AlineUp = A.Position.y + A.Size.y / 2;
	double AlineDown = A.Position.y - A.Size.y / 2;
	return  (((lineRight > AlineLeft && lineRight < AlineRight) || (lineLeft < AlineRight && lineLeft > AlineLeft)) &&
		((lineUp > AlineDown && lineUp < AlineUp) || (lineDown < AlineUp && lineDown > AlineDown))) ||
		(((AlineRight > lineLeft && AlineRight < lineRight) || (AlineLeft < lineRight && AlineLeft > lineLeft)) &&
		((AlineUp > lineDown && AlineUp < lineUp) || (AlineDown < lineUp && AlineDown > lineDown)));
	

}

airs::vec2d CollisionObject::PushX(CollisionObject Obj)
{
	if (NonObj)
	{
		return Obj.Position;
	}
	if (Position.x > Obj.Position.x)
	{
		Obj.Position.x = Position.x - 0.1 - (Obj.Size.x + Size.x) / 2;
		return Obj.Position;
	}
	if (Position.x < Obj.Position.x)
	{
		Obj.Position.x = Position.x + 0.1 + (Obj.Size.x + Size.x) / 2;
		return Obj.Position;
	}
}


airs::vec2d CollisionObject::PushY(CollisionObject Obj)
{
	if (NonObj)
	{
		return Obj.Position;
	}
	if (Position.y > Obj.Position.y)
	{
		Obj.Position.y = Position.y - 0.1 - (Obj.Size.y + Size.y) / 2;
		return Obj.Position;
	}
	if (Position.y < Obj.Position.y)
	{
		Obj.Position.y = Position.y + 0.1 + (Obj.Size.y + Size.y) / 2;
		return Obj.Position;
	}
	
}

bool CollisionObject::GetNonObj()
{
	return NonObj;
}

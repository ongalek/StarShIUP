#pragma once
#include "airs/math.h"
class CollisionObject
{
protected:
	airs::vec2d Position;
	airs::vec2d Size;
	bool NonObj;
public:
	CollisionObject();
	CollisionObject(airs::vec2d pos,airs::vec2d size);
	bool Collision(const CollisionObject& A);
	airs::vec2d PushX(CollisionObject);
	airs::vec2d PushY(CollisionObject);
	bool GetNonObj();

};


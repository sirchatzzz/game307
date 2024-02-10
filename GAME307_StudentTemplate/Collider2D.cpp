#include "Collider2D.h"


Collider2D::Collider2D(): x(0.0), y(0.0), w(0.0), h(0.0), isActive(false) {}

Collider2D::Collider2D(float x_, float y_, float w_, float h_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
	isActive = true;
}

void Collider2D::SetColliderPosition(float x_, float y_)
{
	x = x_;
	y = y_;
}

void Collider2D::SetColliderBounds(float w_, float h_)
{
	w = w_;
	h = h_;
}

bool Collider2D::CollisionCheck(Collider2D objectOne, Collider2D objectTwo)
{
	if (objectTwo.isActive && objectOne.isActive)
	{
		//Player Collider Box
		Vec2 l1;
		Vec2 r1;

		//Object Collider Box
		Vec2 l2;
		Vec2 r2;

		//Set Player Box
		l1.x = objectOne.x;
		l1.y = objectOne.y;
		r1.x = objectOne.x + objectOne.w;
		r1.y = objectOne.y + objectOne.h;

		//Set Object Box
		l2.x = objectTwo.x;
		l2.y = objectTwo.y;
		r2.x = objectTwo.x + objectTwo.w;
		r2.y = objectTwo.y + objectTwo.h;



		if (l1.x > r2.x)
		{
			return false;
		}
		else
		{
			//check if within the object
			if (l1.x >= l2.x)
			{
				if (l1.y >= l2.y && l1.y <= r2.y)
					return true;
				if (r1.y <= l1.y && r1.y <= r2.y)
					return true;
			}
		}


		if (r1.x < l2.x)
		{
			return false;
		}
		else
		{
			//check if within the object
			if (r1.x <= r2.x)
			{
				if (l1.y >= l2.y && l1.y <= r2.y)
					return true;
				if (r1.y >= l2.y && r1.y <= r2.y)
					return true;

			}
		}
	}


	//if all else fails, not overlapping
	return false;
}

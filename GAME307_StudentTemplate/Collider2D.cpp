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

bool Collider2D::CollisionCheck(Collider2D otherObject)
{
	if (otherObject.isActive && isActive)
	{
		//Player Collider Box
		Vec2 l1;
		Vec2 r1;

		//Object Collider Box
		Vec2 l2;
		Vec2 r2;

		//Set Player Box
		l1.x = x;
		l1.y = y;
		r1.x = x + w;
		r1.y = y + h;

		//Set Object Box
		l2.x = otherObject.x;
		l2.y = otherObject.y;
		r2.x = otherObject.x + otherObject.w;
		r2.y = otherObject.y + otherObject.h;



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

bool Collider2D::CollisionCheckWithDebugMessages(Collider2D otherObject)
{
	if (otherObject.isActive && isActive)
	{
		//Player Collider Box
		Vec2 l1;
		Vec2 r1;

		//Object Collider Box
		Vec2 l2;
		Vec2 r2;

		//Set Player Box
		l1.x = x;
		l1.y = y;
		r1.x = x + w;
		r1.y = y + h;

		//Set Object Box
		l2.x = otherObject.x;
		l2.y = otherObject.y;
		r2.x = otherObject.x + otherObject.w;
		r2.y = otherObject.y + otherObject.h;

		std::cout << "\nObjectOne Dimensions: "
			<< "\nx: " << l1.x << " y: " << l1.y << " width: " << r1.x << " height: " << r1.y << std::endl;
		
		std::cout << "\nObjectTwo Dimensions: "
			<< "\nx: " << l2.x << " y: " << l2.y << " width: " << r2.x << " height: " << r2.y << std::endl;

		if (l1.x > r2.x)
		{
			std::cout << "\n COLLISION CHECK: FALSE!";
			return false;		
		}
		else
		{
			//check if within the object
			if (l1.x >= l2.x)
			{
				if (l1.y >= l2.y && l1.y <= r2.y)
				{
					std::cout << "\n COLLISION CHECK: TRUE!";
					return true;
				}	
				if (r1.y <= l1.y && r1.y <= r2.y)
				{
					std::cout << "\n COLLISION CHECK: TRUE!";
					return true;
				}
			}
		}


		if (r1.x < l2.x)
		{
			std::cout << "\n COLLISION CHECK: FALSE!";
			return false;
		}
		else
		{
			//check if within the object
			if (r1.x <= r2.x)
			{
				if (l1.y >= l2.y && l1.y <= r2.y)
				{
					std::cout << "\n COLLISION CHECK: TRUE!";
					return true;
				}
				if (r1.y >= l2.y && r1.y <= r2.y)
				{
					std::cout << "\n COLLISION CHECK: TRUE!";
					return true;
				}

			}
		}
	}


	//if all else fails, not overlapping
	std::cout << "\n COLLISION CHECK: FALSE!";
	return false;
}

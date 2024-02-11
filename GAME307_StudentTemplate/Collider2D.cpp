/*
* Programmer:		Ahmed Hammoud
* Project:			GAME 307 - AI Programming
* Date:				February 2024
* Description:		This class is to add a 2D collider box around the actor or objects in the scenes.
*/

#include "Collider2D.h"


Collider2D::Collider2D(): x(0.0), y(0.0), w(0.0), h(0.0), isActive(false), debugColliderFlag(false) {}

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

void Collider2D::SetColliderActive(bool changeState)
{
	isActive = changeState;
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
	debugColliderFlag = false;

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

		//Is left corner outside of right corner, then they don't intersect. 
		if (l1.x > r2.x)
		{
			if (debugColliderFlag)
			{
				debugColliderFlag = false;
				std::cout << "\n COLLISION CHECK: FALSE!";
			}
			return false;
		}
		else
		{
			//check if within the object
			if (l1.x >= l2.x)
			{
				if (l1.y >= l2.y && l1.y <= r2.y)
				{
					if (!debugColliderFlag)
					{
						debugColliderFlag = true;
						std::cout << "\n COLLISION CHECK: TRUE!";
					}
					return true;
				}	
				if (r1.y <= l1.y && r1.y <= r2.y)
				{
					if (!debugColliderFlag)
					{
						debugColliderFlag = true;
						std::cout << "\n COLLISION CHECK: TRUE!";
					}
					return true;
				}
			}
		}


		if (r1.x < l2.x)
		{
			if (debugColliderFlag)
			{
				debugColliderFlag = false;
				std::cout << "\n COLLISION CHECK: FALSE!";
			}
			return false;
		}
		else
		{
			//check if within the object
			if (r1.x <= r2.x)
			{
				if (l1.y >= l2.y && l1.y <= r2.y)
				{
					if (!debugColliderFlag)
					{
						debugColliderFlag = true;
						std::cout << "\n COLLISION CHECK: TRUE!";
					}
					return true;
				}
				if (r1.y >= l2.y && r1.y <= r2.y)
				{
					if (!debugColliderFlag)
					{
						debugColliderFlag = true;
						std::cout << "\n COLLISION CHECK: TRUE!";
					}
					return true;
				}

			}
		}
	}


	//if all else fails, not overlapping
	if (debugColliderFlag)
	{
		debugColliderFlag = false;
		std::cout << "\n COLLISION CHECK: FALSE!";
	}
	
	//Recursion call to test other side of collision.
	Collider2D tempColl = Collider2D(x, y, w, h);
	CollisionCheckWithDebugMessages(tempColl);

	return false;
}

void Collider2D::RenderCollider(SDL_Renderer* m_window_renderer)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(m_window_renderer, &rect);

	SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);

	SDL_RenderPresent(m_window_renderer);
}

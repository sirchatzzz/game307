/*
* Programmer:		Ahmed Hammoud
* Project:			GAME 307 - AI Programming
* Date:				February 2024
* Description:		This class is to add a 2D collider box around the actor or objects in the scenes.
*/

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

void Collider2D::SetColliderActive(bool changeState)
{
	isActive = changeState;
}

bool Collider2D::CollisionCheck(Collider2D otherObject)
{
	if (isActive && otherObject.isActive)
	{
		int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;
		leftA = x;
		rightA = x + w;
		topA = y;
		bottomA = y + h;

		leftB = otherObject.x;
		rightB = otherObject.x + otherObject.w;
		topB = otherObject.y;
		bottomB = otherObject.y + otherObject.h;

		if (bottomA <= topB)
		{
			return false;
		}

		if (topA >= bottomB)
		{
			return false;
		}

		if (rightA <= leftB)
		{
			return false;
		}

		if (leftA >= rightB)
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
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

	
}

bool Collider2D::CollisionMathTesting(Collider2D otherObject)
{

	int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;
	leftA = x;
	rightA = x + w;
	topA = y; 
	bottomA = y + h;

	leftB = otherObject.x;
	rightB = otherObject.x + otherObject.w;
	topB = otherObject.y;
	bottomB = otherObject.y + otherObject.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

SDL_Rect Collider2D::GetColliderRect()
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	return rect;
}

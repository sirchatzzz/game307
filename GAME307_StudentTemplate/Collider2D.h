#pragma once
/*
* Programmer:		Ahmed Hammoud
* Project:			GAME 307 - AI Programming
* Date:				February 2024
* Description:		This class is to add a 2D collider box around the actor or objects in the scenes.
*/
#include "Vector.h"
#include <SDL_rect.h>
#include <SDL_render.h>

using namespace MATH;

class Collider2D
{
private:
	//Variables

	/// <summary>
	/// Floats for X / Y and Width / Height
	/// Width and Height are the collidor bounds.
	/// X and Y are the collider position
	/// </summary>
	

	/// <summary>
	/// Is the collider active? True or False.
	/// </summary>
	bool isActive;
	bool collisionFlag = false;
	float x, y, w, h;
	bool printed;

public:
	

	//Constructors
	Collider2D();
	Collider2D(float x_, float y_, float w_, float h_);

	/// <summary>
	/// Set the position of the collider.
	/// </summary>
	/// <param name="x_"></param>
	/// <param name="y_"></param>
	void SetColliderPosition(float x_, float y_);

	/// <summary>
	/// Set the bounds of the collider
	/// </summary>
	/// <param name="w_"></param>
	/// <param name="h_"></param>
	void SetColliderBounds(float w_, float h_);

	/// <summary>
	/// Change state of if collider is active or not. 
	/// </summary>
	/// <param name="changeState"></param>
	void SetColliderActive(bool changeState);

	/// <summary>
	/// Check if two Collider2D objects have intersected. 
	/// </summary>
	/// <param name="otherObject"></param>
	/// <returns></returns>
	bool CollisionCheck(Collider2D otherObject);

	/// <summary>
	/// Renders a visual of the collider
	/// </summary>
	void RenderCollider(SDL_Renderer* m_window_renderer);

	bool CollisionMathTesting(Collider2D otherObject);

	void collFlagChange(bool newBool) { collisionFlag = newBool; }

	SDL_Rect GetColliderRect();

};


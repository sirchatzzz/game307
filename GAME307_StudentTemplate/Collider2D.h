#pragma once
/*
* Programmer:		Ahmed Hammoud
* Project:			GAME 307 - AI Programming
* Date:				February 2024
* Description:		This class is to add a 2D collider box around the actor or objects in the scenes.
*/
class Collider2D
{
private:
	//Variables

	/// <summary>
	/// Floats for X / Y and Width / Height
	/// Width and Height are the collidor bounds.
	/// X and Y are the collider position
	/// </summary>
	float x, y, w, h;

	/// <summary>
	/// Is the collider active? True or False.
	/// </summary>
	bool isActive;

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
	/// <param name="y_"></param>
	void SetColliderBounds(float w_, float y_);

	/// <summary>
	/// Check if two Collider2D objects have interected. 
	/// </summary>
	/// <param name="objectOne"></param>
	/// <param name="objectTwo"></param>
	/// <returns></returns>
	bool CollisionCheck(Collider2D objectOne, Collider2D objectTwo);

};


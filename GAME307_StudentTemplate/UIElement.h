#pragma once
#include <SDL_render.h>
#include <Matrix.h>
#include "Scene.h"

class UIElement
{
	class Scene* scene;
	
private:

	//Name for the UI Element
	std::string name;

	//UI Element Variables
	float scale;
	float orientation;
	SDL_Texture* texture;
	SDL_Surface* image;
	Vec3 position;

	//Spritesheet variables
	SDL_Rect sprite;
	int row, col;

	//Flags
	bool flagOnCreate;
	bool isSpriteSheet;

private: 
	bool LoadImage();
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="name_"></param>
	/// <param name="file"></param>
	/// <param name="position_"></param>
	/// <param name="scale_"></param>
	/// <param name="orientation_"></param>
	/// <param name="row_"></param>
	/// <param name="col_"></param>
	UIElement(std::string name_, const char* file, Vec3 position_, float scale_, float orientation_, int row_ = -1, int col_ = -1);
	~UIElement();

	bool OnCreate(Scene* scene_);

	void SelectSprite(int x, int y);

	void Render();
};


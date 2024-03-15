#pragma once
#include "Vector.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <GameManager.h>

using namespace MATH;

class Tiles
{
private:
	class GameManager* game;
	bool safeTile;
	float x, y, w, h;
	int id;

public:
	

	//Constructors
	Tiles();
	Tiles(float x_, float y_, float w_, float h_, bool safeTile_, GameManager* game_, int id_);


	void SetTilesPosition(float x_, float y_);


	void SetTilesBounds(float w_, float h_);

	bool TileStatus() { return safeTile; }


	void RenderTile(SDL_Renderer* m_window_renderer);

	SDL_Rect GetTileRect();
	
	Vec3 GetPos() { return Vec3(x, y, 0); }
	int GetID() { return id; }
};


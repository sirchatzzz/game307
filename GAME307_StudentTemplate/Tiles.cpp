
#include "Tiles.h"


Tiles::Tiles(): x(0.0), y(0.0), w(0.0), h(0.0), safeTile(true), game(nullptr), id(0) {}

Tiles::Tiles(float x_, float y_, float w_, float h_, bool safeTile_, GameManager* game_, int id_)
{
	x = x_;
	y = y_;
	w = w_;
	h = h_;
	safeTile = safeTile_;
	game = game_;
	id = id_;
}

void Tiles::SetTilesPosition(float x_, float y_)
{
	x = x_;
	y = y_;
}

void Tiles::SetTilesBounds(float w_, float h_)
{
	w = w_;
	h = h_;
}



void Tiles::RenderTile(SDL_Renderer* m_window_renderer)
{
	SDL_Renderer* renderer = game->getRenderer();
	Matrix4 projectionMatrix = game->getProjectionMatrix();

	// square represents the position and dimensions for where to draw the image

	SDL_Rect rect;
	Vec3 screenCoords;


	// convert the position from game coords to screen coords
	screenCoords = projectionMatrix * Vec3(x,y,0);

	// The square's x and y values represent the top left corner of
	// where SDL will draw the .png image
	// The 0.5f * w/h offset is to place the .png so that pos represents the center
	// (Note the y axis for screen coords points downward, hence subtractions!!!!)
	rect.x = static_cast<int>(screenCoords.x - 0.5f * w);
	rect.y = static_cast<int>(screenCoords.y - 0.5f * h);
	rect.w = static_cast<int>(w);
	rect.h = static_cast<int>(h);


	if (safeTile == true) SDL_SetRenderDrawColor(m_window_renderer, 0, 255, 0, 255);
	if (safeTile == false) SDL_SetRenderDrawColor(m_window_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(m_window_renderer, &rect);

	SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);

	SDL_RenderPresent(m_window_renderer);
}


SDL_Rect Tiles::GetTileRect()
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	return rect;
}

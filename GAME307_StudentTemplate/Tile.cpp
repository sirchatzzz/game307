#include "Tile.h"

Tile::Tile(Node* node_,Vec3 pos_, float width_, float height_, Scene* scene_) : 
	node{node_}, pos{pos_}, width{width_}, height{height_}
{	
	scene = scene_;
	
}

void Tile::Render()
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;

	Vec3 topLeft, bottomRight;
	Vec3 topLeftScreen, bottomRightScreen;

	topLeft = Vec3(pos.x - 0.5 * width, pos.y + 0.5 * height, 0.0f);
	bottomRight = Vec3(pos.x + 0.5 * width, pos.y - 0.5 * height, 0.0f);

	topLeftScreen = projectionMatrix * topLeft;
	bottomRightScreen = projectionMatrix * bottomRight;

	square.x = static_cast<int>(topLeftScreen.x);
	square.y = static_cast<int>(topLeftScreen.y);
	square.w = static_cast<int>(bottomRightScreen.x - topLeftScreen.x);
	square.h = static_cast<int>(bottomRightScreen.y - topLeftScreen.y);

	SDL_SetRenderDrawColor(renderer, tileColour[0], tileColour[1], tileColour[2], tileColour[3]);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &square);
	
	//Border around the square
	
	SDL_SetRenderDrawColor(renderer, tileBorderColour[0], tileBorderColour[1], tileBorderColour[2], tileBorderColour[3]);
	SDL_RenderDrawRect(renderer, &square);

}



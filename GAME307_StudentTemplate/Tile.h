#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_image.h>
#include <Scene.h>
#include "Node.h"

class Tile
{
private:
	float width, height;
	Scene* scene;
	Vec3 pos;
	Node* node;
	Uint8 tileColour[4] = {0, 0, 255, 0};
	Uint8 tileBorderColour[4] = { 255, 255, 255, 150 };
	

public:
	Tile(Node* node_, Vec3 pos_, float width_, float height_, Scene* scene_);
	virtual ~Tile() {}
	void Render();
	Node* getNode() { return node; }
	Vec3 GetPos() { return pos; }
	
	void setRGBA(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_)
	{

		tileColour[0] = r_;
		tileColour[1] = g_;
		tileColour[2] = b_;
		tileColour[3] = a_;

	}
	
};

#endif

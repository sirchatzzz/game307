#ifndef SCENE2_H
#define SCENE2_H

#include "MMath.h"
#include "VMath.h"
#include "Scene.h"
#include "AudioPlayer.h"
#include <vector>


using namespace MATH;

class Scene2 : public Scene {
private:

	SDL_Window *window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
    Matrix4 inverseProjection;

	SDL_Surface* background;
	SDL_Texture* texture;

public:
	Scene2(SDL_Window* sdlWindow, GameManager* game_);
	~Scene2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
    Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }

};

#endif

#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "VMath.h"
#include "Scene.h"
#include <vector>
#include "Character.h"
#include "Tile.h"
#include "Node.h"
#include "Graph.h"
#include "Path.h"
#include "FollowAPath.h"
#include "Spawner.h"
#include <memory>
#include "Island.h"
using namespace MATH;
class Scene1 : public Scene {
private:
	float animationCounter;
	SDL_Window *window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
    Matrix4 inverseProjection;

	SDL_Surface* playerImage[4];
	SDL_Texture* playerTexture[4];

	SDL_Surface* enemyImage[4];
	SDL_Texture* enemyTexture[4];

	SDL_Surface* waterBackground;
	SDL_Texture* waterTexture;

	// islands
	std::vector<SDL_Surface*> islandImage;
	std::vector<SDL_Texture*> islandTexture;
	std::vector<SDL_Rect> islandRect;

	std::vector<Collider2D> islandColls;

	Collider2D leftOutOfBoundsColl;
	Collider2D rightOutOfBoundsColl;
	Collider2D upOutOfBoundsColl;
	Collider2D downOutOfBoundsColl;

	Spawner* enemySpawner;
	Character* blinky;
	Character* enemy;
	Path patrolPath;

	//Scene nodes / Graph
	Graph* graph;
	std::vector<Node*> sceneNodes;

	//Tile rendering objects and arrays
	bool toggleTileRendering;
	float tileWidth, tileHeight;
	std::vector< std::vector<Tile*>> tiles;

	Island* island;
	std::vector<Island> islandsVector;

private:

	//Creates our tile map
	void createTiles();

	//calculate weight
	void CalculateConnectionWeights();
	void GetMousePOS();
	void ManageBullets();

public:
	Scene1(SDL_Window* sdlWindow, GameManager* game_);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
    void HandleEvents(const SDL_Event &event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
    Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
	void TestPathFinding();
	void SetBlinkyPath();

	void UpdateAIPositionNodes();
	
};

#endif

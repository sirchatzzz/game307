#ifndef SCENE1_H
#define SCENE1_H

#include "MMath.h"
#include "VMath.h"
#include "Scene.h"
#include "AudioPlayer.h"
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
#include "UIElement.h"

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
	Character* enemy;


	//Scene nodes / Graph
	Graph* graph;
	std::vector<Node*> sceneNodes;

	Node* playerNode;

	//Tile rendering objects and arrays
	bool toggleTileRendering;
	float tileWidth, tileHeight;
	std::vector< std::vector<Tile*>> tiles;

	Island* island1;
	Island* island2;
	Island* island3;
	Island* island4;
	Island* island5;
	Island* island6;
	std::vector<Island*> islandsVector;

	//UI Elements
	UIElement* backgroundUI = new UIElement("Background", "Assets/UI Assets/UI_Background.png", Vec3(2, 0.8, 0), 1, 0);
	UIElement* ammoUI = new UIElement("Ammo UI", "Assets/UI Assets/ammo_ui.png", Vec3(4, 0.8, 0), 1, 0);
	UIElement* ammoBackgroundUI = new UIElement("Ammo Background UI", "Assets/UI Assets/ammo_background.png", Vec3(4.35, 0.8, 0), 1, 0);

	//Player Health UI
	UIElement* heartOne = new UIElement("HeartOne", "Assets/UI Assets/Heart/heart.png", Vec3(0.5, 1.7, 0), 1.5, 0);
	UIElement* heartOneBorder = new UIElement("Heart One Border", "Assets/UI Assets/Heart/border.png", Vec3(0.5, 1.7, 0), 1.5, 0);
	UIElement* heartOneBG = new UIElement("Heart one Backround", "Assets/UI Assets/Heart/background.png", Vec3(0.5, 1.7, 0), 1.5, 0);

	UIElement* heartTwo = new UIElement("HeartTwo", "Assets/UI Assets/Heart/heart.png", Vec3(1, 1.7, 0), 1.5, 0);
	UIElement* heartTwoBorder = new UIElement("Heart Two Border", "Assets/UI Assets/Heart/border.png", Vec3(1, 1.7, 0), 1.5, 0);
	UIElement* heartTwoBG = new UIElement("Heart Two Backround", "Assets/UI Assets/Heart/background.png", Vec3(1, 1.7, 0), 1.5, 0);


	UIElement* heartThree = new UIElement("HeartThree", "Assets/UI Assets/Heart/heart.png", Vec3(1.5, 1.7, 0), 1.5, 0);
	UIElement* heartThreeBorder = new UIElement("Heart three Border", "Assets/UI Assets/Heart/border.png", Vec3(1.5, 1.7, 0), 1.5, 0);
	UIElement* heartThreeBG = new UIElement("Heart three Backround", "Assets/UI Assets/Heart/background.png", Vec3(1.5, 1.7, 0), 1.5, 0);

	UIElement* heartFour = new UIElement("HeartFour", "Assets/UI Assets/Heart/heart.png", Vec3(2, 1.7, 0), 1.5, 0);
	UIElement* heartFourBorder = new UIElement("Heart four Border", "Assets/UI Assets/Heart/border.png", Vec3(2, 1.7, 0), 1.5, 0);
	UIElement* heartFourBG = new UIElement("Heart four Backround", "Assets/UI Assets/Heart/background.png", Vec3(2, 1.7, 0), 1.5, 0);

	UIElement* heartFive = new UIElement("HeartFive", "Assets/UI Assets/Heart/heart.png", Vec3(2.5, 1.7, 0), 1.5, 0);
	UIElement* heartFiveBorder = new UIElement("Heart five Border", "Assets/UI Assets/Heart/border.png", Vec3(2.5, 1.7, 0), 1.5, 0);
	UIElement* heartFiveBG = new UIElement("Heart five Backround", "Assets/UI Assets/Heart/background.png", Vec3(2.5, 1.7, 0), 1.5, 0);


	//Gear Selection UI
	UIElement* reverseWhiteUI = new UIElement("Reverse White UI", "Assets/UI Assets/GearSelector/r.png", Vec3(0.75, 0.8, 0), 0.5 / 10, 0);
	UIElement* reverseRedUI = new UIElement("Reverse Red UI", "Assets/UI Assets/GearSelector/r-red.png", Vec3(0.75, 0.8, 0), 0.5 / 10, 0);
	UIElement* parkWhiteUI = new UIElement("Park White UI", "Assets/UI Assets/GearSelector/p.png", Vec3(1.25, 0.8, 0), 0.5 / 10, 0);
	UIElement* parkRedUI = new UIElement("Park Red UI", "Assets/UI Assets/GearSelector/p-red.png", Vec3(1.25, 0.8, 0), 0.5 / 10, 0);
	UIElement* neutralWhiteUI = new UIElement("Neutral White UI", "Assets/UI Assets/GearSelector/n.png", Vec3(1.75, 0.8, 0), 0.5 / 10, 0);
	UIElement* neutralRedUI = new UIElement("Neutral Red UI", "Assets/UI Assets/GearSelector/n-red.png", Vec3(1.75, 0.8, 0), 0.5 / 10, 0);
	UIElement* oneWhiteUI = new UIElement("First Gear White UI", "Assets/UI Assets/GearSelector/1.png", Vec3(2.25, 0.8, 0), 0.5 / 10, 0);
	UIElement* oneRedUI = new UIElement("First Gear Red UI", "Assets/UI Assets/GearSelector/1-red.png", Vec3(2.25, 0.8, 0), 0.5 / 10, 0);
	UIElement* twoWhiteUI = new UIElement("Second Gear White UI", "Assets/UI Assets/GearSelector/2.png", Vec3(2.75, 0.8, 0), 0.5 / 10, 0);
	UIElement* twoRedUI = new UIElement("Second Gear Red UI", "Assets/UI Assets/GearSelector/2-red.png", Vec3(2.75, 0.8, 0), 0.5 / 10, 0);
	UIElement* threeWhiteUI = new UIElement("Third Gear White UI", "Assets/UI Assets/GearSelector/3.png", Vec3(3.25, 0.8, 0), 0.5 / 10, 0);
	UIElement* threeRedUI = new UIElement("Third Gear Red UI", "Assets/UI Assets/GearSelector/3-red.png", Vec3(3.25, 0.8, 0), 0.5 / 10, 0);
	bool hitIsland = false;
	float hitIslandTimer = 0;

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

	void UpdateAIPositionNodes();
	
	void InitializeIslands();

	bool checkIslandsHealths();
};

#endif

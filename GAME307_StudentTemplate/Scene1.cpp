#include "Scene1.h"


Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_): playerImage(nullptr), playerTexture(nullptr), waterBackground(nullptr), waterTexture(nullptr){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// create a NPC
	blinky = nullptr;
}

Scene1::~Scene1(){
	if (blinky) 
	{
		blinky->OnDestroy();
		delete blinky;
	}
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	playerImage = IMG_Load("assets/playerBoat.png");
	waterBackground = IMG_Load("assets/water.png");

	for (int i = 0; i < 6; i++)
	{
		islandImage.push_back(nullptr);
		islandTexture.push_back(nullptr);
		islandRect.push_back(SDL_Rect());
	}

	islandImage[0] = IMG_Load("assets/island1.png");
	islandImage[1] = IMG_Load("assets/island2.png");
	islandImage[2] = IMG_Load("assets/island3.png");
	islandImage[3] = IMG_Load("assets/island4.png");
	islandImage[4] = IMG_Load("assets/island5.png");
	islandImage[5] = IMG_Load("assets/island6.png");

	playerTexture = SDL_CreateTextureFromSurface(renderer, playerImage);
	waterTexture = SDL_CreateTextureFromSurface(renderer, waterBackground);

	for (int i = 0; i < islandTexture.size(); i++)
	{
		islandTexture[i] = SDL_CreateTextureFromSurface(renderer, islandImage[i]);
	}

	islandRect[0] = { 550, 250, 250, 300 };
	islandRect[1] = { 400, 50, 150, 150 };
	islandRect[2] = { 700, 0, 200, 250 };
	islandRect[3] = { 100, 200, 200, 200 };
	islandRect[4] = { 350, 400, 150, 150 };
	islandRect[5] = { 100, 25, 150, 150 };

	game->getPlayer()->setImage(playerImage);
	game->getPlayer()->setTexture(playerTexture);


	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setTextureWith("Blinky.png") )
	{
		return false;
	}

	// end of character set ups

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {

	if (game->getPlayer()->getAccel().x > 0.0) game->getPlayer()->SetOrientation(-1.56f);
	if (game->getPlayer()->getAccel().x < 0.0) game->getPlayer()->SetOrientation(1.56f);
	if (game->getPlayer()->getAccel().y < 0.0) game->getPlayer()->SetOrientation(0.0f);
	if (game->getPlayer()->getAccel().y > 0.0) game->getPlayer()->SetOrientation(-3.15f);

	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	//blinky->render(0.15f);

	// render the background
	SDL_RenderCopy(renderer, waterTexture, nullptr, nullptr);

	// render the islands
	for (int i = 0; i < islandTexture.size(); i++)
	{
		SDL_RenderCopy(renderer, islandTexture[i], nullptr, &islandRect[i]);
	}

	// render the player
	game->RenderPlayer(0.05f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}

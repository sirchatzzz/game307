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
		islandColls.push_back(Collider2D());
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

	islandRect[0] = { 1350, 650, 250, 300 };
	islandColls[0] = Collider2D(islandRect[0].x, islandRect[0].y+50, islandImage[0]->w - 50, islandImage[0]->h / 1.5);
	islandColls[0].SetColliderActive(true);


	islandRect[1] = { 1300, 150, 150, 150 };
	islandRect[2] = { 900, 600, 200, 250 };
	islandRect[3] = { 300, 100, 200, 200 };
	islandRect[4] = { 800, 300, 150, 150 };
	islandRect[5] = { 400, 650, 150, 150 };

	game->getPlayer()->setImage(playerImage);
	game->getPlayer()->setTexture(playerTexture);
	game->getPlayer()->SetMaxSpeed(15);


	for (int i = 0; i < 25; i++)
	{

		tiles.push_back(Tiles());


	}

	tiles[0] = Tiles(1, 14, 250, 250, true, game,1);
	tiles[1] = Tiles(4.25, 14, 250, 250, false, game, 2);
	tiles[2] = Tiles(7.5, 14, 250, 250, true, game, 3);
	tiles[3] = Tiles(10.75, 14, 250, 250, true, game, 4);
	tiles[4] = Tiles(14, 14, 250, 250, true, game, 5);
	tiles[5] = Tiles(1, 11, 250, 250, true, game, 6);
	tiles[6] = Tiles(4.25, 11, 250, 250, false, game, 7);
	tiles[7] = Tiles(7.5, 11, 250, 250, true, game, 8);
	tiles[8] = Tiles(10.75, 11, 250, 250, false, game, 9);
	tiles[9] = Tiles(14, 11, 250, 250, true, game, 10);
	tiles[10] = Tiles(1, 8, 250, 250, true, game, 11);
	tiles[11] = Tiles(4.25, 8, 250, 250, true, game, 12);
	tiles[12] = Tiles(7.5, 8, 250, 250, true, game, 13);
	tiles[13] = Tiles(10.75, 8, 250, 250, true, game, 14);
	tiles[14] = Tiles(14, 8, 250, 250, true, game, 15);
	tiles[15] = Tiles(1, 5, 250, 250, true, game, 16);
	tiles[16] = Tiles(4.25, 5, 250, 250, false, game, 17);
	tiles[17] = Tiles(7.5, 5, 250, 250, false, game, 18);
	tiles[18] = Tiles(10.75, 5, 250, 250, true, game, 19);
	tiles[19] = Tiles(14, 5, 250, 250, false, game, 20);
	tiles[20] = Tiles(1, 2, 250, 250, true, game, 21);
	tiles[21] = Tiles(4.25, 2, 250, 250, true, game, 22);
	tiles[22] = Tiles(7.5, 2, 250, 250, true, game, 23);
	tiles[23] = Tiles(10.75, 2, 250, 250, true, game, 24);
	tiles[24] = Tiles(14, 2, 250, 250, true, game, 25);








	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setTextureWith("assets/enemyBoat3.png") )
	{
		return false;
	}
	blinky->getBody()->setPos(Vec3(4, 8, 0));
	// end of character set ups

	blinky->SetTiles(tiles);

	game->getPlayer()->GetCollider().collFlagChange(false);

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {

	//Enemy AI Targets Player
	blinky->setTarget(game->getPlayer()->getPos());

	game->getPlayer()->Update(deltaTime);
	
	
	

	//game->getPlayer()->GetCollider().CollisionCheckWithDebugMessages(blinky->GetCollider());
	//game->getPlayer()->GetCollider().CollisionMathTesting(blinky->GetCollider());

	if (game->getPlayer()->GetCollider().CollisionMathTesting(blinky->GetCollider()))
	{
		std::cout << "\nBlicky Collision Detected By Player";
		game->getPlayer()->GetPlayerStats()->TakeDamage(1);
	}

	blinky->setIslandColliders(islandColls);
	blinky->IslandAvoidance();
	blinky->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's


	// render the background
	SDL_RenderCopy(renderer, waterTexture, nullptr, nullptr);

	// render the islands
	for (int i = 0; i < islandTexture.size(); i++)
	{
		SDL_RenderCopy(renderer, islandTexture[i], nullptr, &islandRect[i]);
	}

	for (int i = 0; i < tiles.size(); i++)
	{

		tiles.at(i).RenderTile(renderer);


	}
	// render the player
	game->RenderPlayer(0.03f);
	blinky->render(0.03f);
	SDL_RenderPresent(renderer);

	islandColls[0].RenderCollider(renderer);

}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
	blinky->HandleEvents(event);
	
}

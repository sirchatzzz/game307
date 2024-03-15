#include "Scene1.h"



Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_): animationCounter(0), waterBackground(nullptr), waterTexture(nullptr){
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

void Scene1::createTiles()
{
	singleTile = new Tile(Vec3(1.25f, 0.25f,0.0f), 0.5f, 0.5f, this);
}


bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	playerImage[0] = IMG_Load("assets/playerBoat1.png");
	playerImage[1] = IMG_Load("assets/playerBoat2.png");
	playerImage[2] = IMG_Load("assets/playerBoat3.png");
	playerImage[3] = IMG_Load("assets/playerBoat4.png");

	enemyImage[0] = IMG_Load("assets/enemyBoat3_1.png");
	enemyImage[1] = IMG_Load("assets/enemyBoat3_2.png");
	enemyImage[2] = IMG_Load("assets/enemyBoat3_3.png");
	enemyImage[3] = IMG_Load("assets/enemyBoat3_4.png");

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

	playerTexture[0] = SDL_CreateTextureFromSurface(renderer, playerImage[0]);
	playerTexture[1] = SDL_CreateTextureFromSurface(renderer, playerImage[1]);
	playerTexture[2] = SDL_CreateTextureFromSurface(renderer, playerImage[2]);
	playerTexture[3] = SDL_CreateTextureFromSurface(renderer, playerImage[3]);

	waterTexture = SDL_CreateTextureFromSurface(renderer, waterBackground);

	for (int i = 0; i < islandTexture.size(); i++)
	{
		islandTexture[i] = SDL_CreateTextureFromSurface(renderer, islandImage[i]);
	}

	

	leftOutOfBoundsColl = Collider2D(-50, 0, 5, 1200);
	leftOutOfBoundsColl.SetColliderActive(true);

	rightOutOfBoundsColl = Collider2D(1920, 0, 5, 1200);
	rightOutOfBoundsColl.SetColliderActive(true);

	upOutOfBoundsColl = Collider2D(0, -50, 2000, 5);
	upOutOfBoundsColl.SetColliderActive(true);

	downOutOfBoundsColl = Collider2D(0, 1080, 2000, 5);
	downOutOfBoundsColl.SetColliderActive(true);

	//Island Colliders - Have to be manually sized per island.
	/** No longer needed with pathfinding implemented
	islandRect[0] = {1350, 650, 250, 300};
	islandColls[0] = Collider2D(islandRect[0].x, islandRect[0].y + 50, islandImage[0]->w - 50, islandImage[0]->h / 1.5);
	islandColls[0].SetColliderActive(true);

	islandRect[1] = { 1300, 150, 150, 150 };
	islandColls[1] = Collider2D(islandRect[1].x+15, islandRect[1].y+15, islandImage[1]->w/2.5, islandImage[1]->h/2.5);
	islandColls[1].SetColliderActive(true);

	islandRect[2] = { 900, 600, 200, 250 };
	islandColls[2] = Collider2D(islandRect[2].x+5, islandRect[2].y+25, islandImage[2]->w/1.6, islandImage[2]->h/1.6);
	islandColls[2].SetColliderActive(true);

	islandRect[3] = { 300, 100, 200, 200 };
	islandColls[3] = Collider2D(islandRect[3].x+10, islandRect[3].y+20, islandImage[3]->w / 1.6, islandImage[3]->h / 2);
	islandColls[3].SetColliderActive(true);

	islandRect[4] = { 800, 300, 150, 150 };
	islandColls[4] = Collider2D(islandRect[4].x+25, islandRect[4].y+25, islandImage[4]->w / 3, islandImage[4]->h / 3);
	islandColls[4].SetColliderActive(true);

	islandRect[5] = { 400, 650, 150, 150 };
	islandColls[5] = Collider2D(islandRect[5].x + 5, islandRect[5].y + 5, islandImage[5]->w / 2, islandImage[5]->h / 2);
	islandColls[5].SetColliderActive(true);
	*/

	//Player Initializers
	game->getPlayer()->setImage(playerImage[0]);
	game->getPlayer()->setTexture(playerTexture[0]);
	game->getPlayer()->SetMaxSpeed(15);




	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setImageWith(enemyImage[0]))
	{
		return false;
	}
	blinky->getBody()->setPos(Vec3(20, 15, 0));
	// end of character set ups

	blinky->SetTiles(tiles);

	game->getPlayer()->GetCollider().collFlagChange(false);

	createTiles();

	return true;
}

void Scene1::OnDestroy() {}

void Scene1::Update(const float deltaTime) {
	++animationCounter;
	if (animationCounter > 60) animationCounter = 0;
	int indexSelector = std::round(animationCounter / 20.0f);
	
	//Enemy AI Targets Player
	blinky->setTarget(game->getPlayer()->getPos());
	blinky->setImageWith(enemyImage[indexSelector]);

	game->getPlayer()->setImage(playerImage[indexSelector]);
	game->getPlayer()->setTexture(playerTexture[indexSelector]);

	game->getPlayer()->Update(deltaTime);


	//game->getPlayer()->GetCollider().CollisionCheckWithDebugMessages(blinky->GetCollider());
	//game->getPlayer()->GetCollider().CollisionMathTesting(blinky->GetCollider());

	if (game->getPlayer()->GetCollider().CollisionMathTesting(blinky->GetCollider()))
	{
		std::cout << "\nBlicky Collision Detected By Player";
		game->getPlayer()->GetPlayerStats()->TakeDamage(1);
	}


	//Check for player bullets hitting enemy
	for (int i = 0; i < game->getPlayer()->GetBullets()->size(); i++)
	{

		if (game->getPlayer()->GetBullets()->at(i).GetCollider().CollisionMathTesting(blinky->GetCollider()))
		{

			std::cout << "Blinky Hit!!" << std::endl;
			game->getPlayer()->GetBullets()->at(i).~Projectile();

			blinky->GetEnemyStats()->TakeDamage(game->getPlayer()->GetBullets()->at(i).GetProjectileDamage());

			auto it = game->getPlayer()->GetBullets()->begin() + i;
			game->getPlayer()->GetBullets()->erase(it);

		}
	}

	//Check for enemy bullets hitting player
	for (int i = 0; i < blinky->GetBullets()->size(); i++)
	{

		if (blinky->GetBullets()->at(i).GetCollider().CollisionMathTesting(game->getPlayer()->GetCollider()))
		{

			std::cout << "Player Hit!!" << std::endl;
			blinky->GetBullets()->at(i).~Projectile();

			game->getPlayer()->GetPlayerStats()->TakeDamage(blinky->GetBullets()->at(i).GetProjectileDamage());

			auto it = blinky->GetBullets()->begin() + i;
			blinky->GetBullets()->erase(it);

		}
	}

	//Check for player bullets going off screen
	for (int i = 0; i < game->getPlayer()->GetBullets()->size(); i++)
	{

		if (game->getPlayer()->GetBullets()->at(i).GetCollider().CollisionMathTesting(leftOutOfBoundsColl) || game->getPlayer()->GetBullets()->at(i).GetCollider().CollisionMathTesting(rightOutOfBoundsColl) || game->getPlayer()->GetBullets()->at(i).GetCollider().CollisionMathTesting(upOutOfBoundsColl) || game->getPlayer()->GetBullets()->at(i).GetCollider().CollisionMathTesting(downOutOfBoundsColl))
		{

			//game->getPlayer()->GetBullets()->at(i).~Projectile();

			auto it = game->getPlayer()->GetBullets()->begin() + i;
			game->getPlayer()->GetBullets()->erase(it);

		}
	}


	//Check for enemy bullets going off screen
	for (int i = 0; i < blinky->GetBullets()->size(); i++)
	{

		if (blinky->GetBullets()->at(i).GetCollider().CollisionMathTesting(leftOutOfBoundsColl) || blinky->GetBullets()->at(i).GetCollider().CollisionMathTesting(rightOutOfBoundsColl) || blinky->GetBullets()->at(i).GetCollider().CollisionMathTesting(upOutOfBoundsColl) || blinky->GetBullets()->at(i).GetCollider().CollisionMathTesting(downOutOfBoundsColl))
		{

			//game->getPlayer()->GetBullets()->at(i).~Projectile();

			auto it = blinky->GetBullets()->begin() + i;
			blinky->GetBullets()->erase(it);

		}
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

	
	// render the player
	game->RenderPlayer(0.5f);
	blinky->render(0.5f);

	
	singleTile->Render();
	SDL_RenderPresent(renderer);

	//islandColls[5].RenderCollider(renderer);

}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
	blinky->HandleEvents(event);
	
}

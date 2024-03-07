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

	islandRect[0] = { 1350, 650, 250, 300 };
	islandColls[0] = Collider2D(islandRect[0].x, islandRect[0].y+50, islandImage[0]->w - 50, islandImage[0]->h / 1.5);
	islandColls[0].SetColliderActive(true);

	leftOutOfBoundsColl = Collider2D(-50, 0, 5, 1200);
	leftOutOfBoundsColl.SetColliderActive(true);

	rightOutOfBoundsColl = Collider2D(1920, 0, 5, 1200);
	rightOutOfBoundsColl.SetColliderActive(true);

	upOutOfBoundsColl = Collider2D(0, -50, 2000, 5);
	upOutOfBoundsColl.SetColliderActive(true);

	downOutOfBoundsColl = Collider2D(0, 1080, 2000, 5);
	downOutOfBoundsColl.SetColliderActive(true);


	islandRect[1] = { 1300, 150, 150, 150 };
	islandRect[2] = { 900, 600, 200, 250 };
	islandRect[3] = { 300, 100, 200, 200 };
	islandRect[4] = { 800, 300, 150, 150 };
	islandRect[5] = { 400, 650, 150, 150 };

	game->getPlayer()->setImage(playerImage);
	game->getPlayer()->setTexture(playerTexture);
	game->getPlayer()->SetMaxSpeed(15);


	for (int i = 0; i < 29; i++)
	{

		tiles.push_back(Tiles());


	}

	tiles[0] = Tiles(5.25, 12.25, 175, 175, false, game,1);
	tiles[1] = Tiles(17.75, 12, 175, 175, false, game, 2);
	tiles[2] = Tiles(11.5, 10, 175, 175, false, game, 3);
	tiles[3] = Tiles(6.25, 5, 175, 175, false, game, 4);
	tiles[4] = Tiles(13, 5, 175, 175, false, game, 5);
	tiles[5] = Tiles(20, 4.5, 175, 175, false, game, 6);
	tiles[6] = Tiles(18.5, 4.5, 175, 175, false, game, 7);
	tiles[7] = Tiles(20, 3.5, 175, 175, false, game, 8);
	tiles[8] = Tiles(18.5, 3.5, 175, 175, false, game, 9);
	tiles[9] = Tiles(0, 14, 175, 175, false, game, 10);
	tiles[10] = Tiles(2, 11.5, 300, 175, true, game, 11);
	tiles[11] = Tiles(6, 14.5, 400, 125, true, game, 12);
	tiles[12] = Tiles(2.70, 13.75, 225, 225, true, game, 13);
	tiles[13] = Tiles(12.5, 1.75, 250, 275, true, game, 14);
	tiles[14] = Tiles(15.75, 1.75, 250, 275, true, game, 15);
	tiles[15] = Tiles(1, 5.25, 150, 250, false, game, 16);
	tiles[16] = Tiles(1.5, 1.5, 250, 300, false, game, 17);
	tiles[17] = Tiles(4, 1.5, 250, 300, false, game, 18);
	tiles[18] = Tiles(23, 14.1, 300, 200, true, game, 19);
	tiles[19] = Tiles(23, 11, 300, 250, true, game, 20);
	tiles[20] = Tiles(23, 7.5, 300, 250, true, game, 21);
	tiles[21] = Tiles(23, 4, 300, 250, true, game, 22);
	tiles[22] = Tiles(23.0, 1, 350, 175, true, game, 23);
	tiles[23] = Tiles(2, 1, 175, 175, true, game, 24);
	tiles[24] = Tiles(19, 1, 275, 175, true, game, 25);
	tiles[25] = Tiles(2, 8.5, 300, 225, true, game, 26);
	tiles[26] = Tiles(3.5, 5.25, 250, 250, true, game, 27);
	tiles[27] = Tiles(7, 1.75, 200, 275, true, game, 28);
	tiles[28] = Tiles(9.5, 1.75, 200, 275, true, game, 29);




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

	//for (int i = 0; i < tiles.size(); i++)
	//{

	//	tiles.at(i).RenderTile(renderer);


	//}
	// render the player
	game->RenderPlayer(0.5f);
	blinky->render(0.5f);
	SDL_RenderPresent(renderer);

	//islandColls[0].RenderCollider(renderer);
	//leftOutOfBoundsColl.RenderCollider(renderer);
	//rightOutOfBoundsColl.RenderCollider(renderer);
	//upOutOfBoundsColl.RenderCollider(renderer);
	//downOutOfBoundsColl.RenderCollider(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
	blinky->HandleEvents(event);
	
}

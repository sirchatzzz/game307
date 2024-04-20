#include "Scene1.h"

Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_): animationCounter(0), waterBackground(nullptr), waterTexture(nullptr), toggleTileRendering(false){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	tileWidth = 0.0;
	tileHeight = 0.0;
	graph = NULL;

	// create a NPC

	enemySpawner = nullptr;
}

Scene1::~Scene1(){

}

void Scene1::createTiles()
{
	tileWidth = 1;
	tileHeight = 1;
	
	int cols = ceil((xAxis - 0.5f * tileWidth) / tileWidth);
	int rows = ceil((yAxis - 0.5f * tileHeight) / tileHeight);

	tiles.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		tiles[i].resize(cols);
	}

	sceneNodes.resize(cols * rows);

	Node* n;
	int label = 0;
	Tile* t;
	int i, j;
	i = 0;
	j = 0;

	for (float y = 0.5f * tileHeight; y < yAxis; y += tileHeight)
	{
		//do stuff as y increases

		for (float x = 0.5f * tileWidth; x < xAxis; x+=tileWidth)
		{
			//do stuff as x increases
			n = new Node(label);
			sceneNodes[label] = n;
			//create tile
			Vec3 tilePos = Vec3(x, y, 0.0f);
			n->SetPos(tilePos);
			t = new Tile(n,tilePos, tileWidth, tileHeight, this);
			tiles[i][j] = t;
			j++;
			label++;
		}
		j = 0;
		i++;
	}

}

void Scene1::CalculateConnectionWeights()
{

	// I'm smart enough to only call this
	// after having properly created the tiles matrix
	int rows = tiles.size();
	int cols = tiles[0].size();

	//Island Nodes
	//islandRect[3]

	//Stores the nodes of which the islands occupy
	std::vector<Node*> islands;

	//Island[0]

	for (int i = 0; i < 4; i++)
	{
		for (int e = 0; e < 4; e++)
		{
			int number = 93;
			islands.push_back(graph->getNode(number + e + (25 * i)));


		}
	}


	//Island[1]
	for (int i = 0; i < 2; i++)
	{
		for (int e = 0; e < 2; e++)
		{
			int number = 292;
			islands.push_back(graph->getNode(number + e + (25 * i)));


		}
	}

	//Island[2]
	for (int i = 0; i < 3; i++)
	{
		for (int e = 0; e < 3; e++)
		{
			int number = 86;
			islands.push_back(graph->getNode(number + e + (25 * i)));


		}
	}

	//Island[3]
	for (int i = 0; i < 2; i++)
	{
		for (int e = 0; e < 2; e++)
		{
			int number = 279;
			islands.push_back(graph->getNode(number + e + (25 * i)));


		}
	}

	//Island[4]
	for (int i = 0; i < 2; i++)
	{
		for (int e = 0; e < 2; e++)
		{
			int number = 235;
			islands.push_back(graph->getNode(number + e + (25 * i)));


		}
	}

	//Island[5]
	for (int i = 0; i < 2; i++)
	{
		for (int e = 0; e < 2; e++)
		{
			int number = 105;
			islands.push_back(graph->getNode(number + e + (25 * i)));


		}
	}


	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles.at(i).size(); j++)
		{
			for (int e = 0; e < islands.size(); e++)
			{

				if (islands.at(e) == tiles.at(i).at(j)->getNode())
				{

					tiles.at(i).at(j)->setRGBA(255, 0, 0, 100);

				}


			}

			


		}


	}




	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//tiles[i][j]->getNode();
			//
			//          i+1, j
			//   i,j-1    i, j      i,j+1
			//          i-1, j
			Tile* fromTile = tiles[i][j];
			Node* from = fromTile->getNode();

			// left
			if (j > 0)
			{
				Node* to = tiles[i][j - 1]->getNode();

				bool islandFound = false;
				for (auto n : islands)
				{
					if (to == n || from == n)
					{
						graph->addWeightedConnection(from, to, 50.0f);
						islandFound = true;
					}
				}

				if (!islandFound)
					graph->addWeightedConnection(from, to, tileWidth);
				
			}

			// right
			if (j < cols - 1)
			{

				Node* to = tiles[i][j + 1]->getNode();
				
				bool islandFound = false;
				for (auto n : islands)
				{
					if (to == n || from == n)
					{
						graph->addWeightedConnection(from, to, 50.0f);
						islandFound = true;
					}
				}

				if(!islandFound)
					graph->addWeightedConnection(from, to, tileWidth);
			}

			// above
			if (i < rows - 1)
			{
				Node* to = tiles[i + 1][j]->getNode();
				bool islandFound = false;
				for (auto n : islands)
				{
					if (to == n || from == n)
					{
						graph->addWeightedConnection(from, to, 50.0f);
						islandFound = true;
					}
				}

				if (!islandFound)
					graph->addWeightedConnection(from, to, tileWidth);
			}

			// below
			if (i > 0)
			{
				Node* to = tiles[i - 1][j]->getNode();
				bool islandFound = false;
				for (auto n : islands)
				{
					if (to == n || from == n)
					{
						graph->addWeightedConnection(from, to, 50.0f);
						islandFound = true;
					}
				}

				if (!islandFound)
					graph->addWeightedConnection(from, to, tileWidth);
			}
		}
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

	

	leftOutOfBoundsColl = Collider2D(-50, 0, 5, 1200);
	leftOutOfBoundsColl.SetColliderActive(true);

	rightOutOfBoundsColl = Collider2D(1920, 0, 5, 1200);
	rightOutOfBoundsColl.SetColliderActive(true);

	upOutOfBoundsColl = Collider2D(0, -50, 2000, 5);
	upOutOfBoundsColl.SetColliderActive(true);

	downOutOfBoundsColl = Collider2D(0, 1080, 2000, 5);
	downOutOfBoundsColl.SetColliderActive(true);
	
	//Island Postions in screen coords
	islandRect[0] = {1350, 650, 250, 300};
	islandRect[1] = { 1300, 150, 150, 150 };
	islandRect[2] = { 900, 600, 200, 250 };
	islandRect[3] = { 285, 100, 200, 200 };
	islandRect[4] = { 765, 275, 150, 150 };
	//islandRect[5] = { 385, 650, 150, 150 };
	
	
	//Player Initializers
	game->getPlayer()->setImage(playerImage[0]);
	game->getPlayer()->setTexture(playerTexture[0]);
	game->getPlayer()->SetMaxSpeed(15);
	game->getPlayer()->setPos(Vec3(9,7,0));
	game->getPlayer()->SetAccel(Vec3(0, 0, 0));
	game->getPlayer()->SetVel(Vec3(0, 0, 0));
	game->getPlayer()->SetGearState(GearState::NEUTRAL);
	// Set up characters, choose good values for the constructor
	// or use the defaults, like this

	// end of character set ups

	game->getPlayer()->GetCollider().collFlagChange(false);

	createTiles();

	//create the graph
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		// TODO error message
		return false;
	}

	CalculateConnectionWeights();

	InitializeIslands();

	enemy = new Character();

	for (int i = 0; i < islandsVector.size(); i++)
	{
		enemy->SetIslands(*islandsVector.at(i));

	}

	enemy->OnCreate(this);
	enemy->setImageWith(enemyImage, 0);
	Stats* enemyStats = new Stats(50, 50, 10);
	enemy->SetEnemyStats(enemyStats);
	enemySpawner = new Spawner(enemy);
	enemySpawner->OnCreate(this);

	//UI Elements
	backgroundUI->OnCreate(this);
	ammoUI->OnCreate(this);
	ammoBackgroundUI->OnCreate(this);
	reverseWhiteUI->OnCreate(this);
	reverseRedUI->OnCreate(this);
	parkWhiteUI->OnCreate(this);
	parkRedUI->OnCreate(this);
	neutralWhiteUI->OnCreate(this);
	neutralRedUI->OnCreate(this);
	oneWhiteUI->OnCreate(this);
	oneRedUI->OnCreate(this);
	twoWhiteUI->OnCreate(this);
	twoRedUI->OnCreate(this);
	threeWhiteUI->OnCreate(this);
	threeRedUI->OnCreate(this);

	heartOne->OnCreate(this);
	heartOneBorder->OnCreate(this);
	heartOneBG->OnCreate(this);

	heartTwo->OnCreate(this);
	heartTwoBorder->OnCreate(this);
	heartTwoBG->OnCreate(this);

	heartThree->OnCreate(this);
	heartThreeBorder->OnCreate(this);
	heartThreeBG->OnCreate(this);

	heartFour->OnCreate(this);
	heartFourBorder->OnCreate(this);
	heartFourBG->OnCreate(this);

	heartFive->OnCreate(this);
	heartFiveBorder->OnCreate(this);
	heartFiveBG->OnCreate(this);

	game->getPlayer()->SetIsDead(false);
	game->getPlayer()->SetPlayerHealth(50);

	return true;
}

void Scene1::OnDestroy() {

	for (int i = 0; i < 4; i++)
	{
		SDL_FreeSurface(enemyImage[i]);
		SDL_FreeSurface(playerImage[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		SDL_DestroyTexture(playerTexture[i]);
		SDL_DestroyTexture(enemyTexture[i]);
	}
	
	for (int i = 0; i < islandImage.size(); i++)
	{
		SDL_FreeSurface(islandImage.at(i));
	}

	for (int i = 0; i < islandTexture.size(); i++)
	{
		SDL_DestroyTexture(islandTexture.at(i));
	}

	SDL_FreeSurface(waterBackground);
	SDL_DestroyTexture(waterTexture);

	delete graph;

	//UI Elements
	delete backgroundUI;
	delete ammoUI;
	delete ammoBackgroundUI;
	delete reverseWhiteUI;
	delete reverseRedUI;
	delete parkWhiteUI;
	delete parkRedUI;
	delete neutralWhiteUI;
	delete neutralRedUI;
	delete oneWhiteUI;
	delete oneRedUI;
	delete twoWhiteUI;
	delete twoRedUI;
	delete threeWhiteUI;
	delete threeRedUI;

	delete heartOne;
	delete heartOneBorder;
	delete heartOneBG;

	delete heartTwo;
	delete heartTwoBorder;
	delete heartTwoBG;

	delete heartThree;
	delete heartThreeBorder;
	delete heartThreeBG;

	delete heartFour;
	delete heartFourBorder;
	delete heartFourBG;

	delete heartFive;
	delete heartFiveBorder;
	delete heartFiveBG;


	enemySpawner->OnDestroy();

	for (int i = 0; i < islandsVector.size(); i++)
	{
		islandsVector.at(i)->OnDestroy();
	}
	islandsVector.clear();

	delete playerNode;
	tiles.clear();
	sceneNodes.clear();

	//game->getPlayer()->OnDestroy();

	delete this;

}

void Scene1::ManageBullets()
{
	//Check for player bullets hitting enemy

	for (int i = 0; i < enemySpawner->GetEnemyArr().size(); i++)
	{
		if (enemySpawner->GetEnemyArr().at(i) != nullptr)
		{
			for (int j = 0; j < game->getPlayer()->GetBullets()->size(); j++)
			{

				if (game->getPlayer()->GetBullets()->at(j).GetCollider().CollisionMathTesting(enemySpawner->GetEnemyArr().at(i)->GetCollider()))
				{

					std::cout << "Enemy Hit!!" << std::endl;

					enemySpawner->GetEnemyArr().at(i)->GetEnemyStats()->TakeDamage(game->getPlayer()->GetBullets()->at(j).GetProjectileDamage());

					auto it = game->getPlayer()->GetBullets()->begin() + j;
					game->getPlayer()->GetBullets()->erase(it);

				}
			}
		}
	}

	//Check for enemy bullets hitting island
	for (int i = 0; i < enemySpawner->GetEnemyArr().size(); i++)
	{
		if (enemySpawner->GetEnemyArr().at(i) != nullptr)
		{
			for (int j = 0; j < enemySpawner->GetEnemyArr().at(i)->GetBullets()->size(); j++)
			{
				bool breakout = false;
				for (int e = 0; e < islandsVector.size(); e++)
				{
					if (enemySpawner->GetEnemyArr().at(i)->GetBullets()->at(j).GetCollider().CollisionMathTesting(islandsVector.at(e)->GetCollider()))
					{

						std::cout << "Island Hit!!" << std::endl;

						islandsVector.at(e)->GetStats()->TakeDamage(enemySpawner->GetEnemyArr().at(i)->GetEnemyStats()->GetWeaponDamage());

						auto it = enemySpawner->GetEnemyArr().at(i)->GetBullets()->begin() + j;
						enemySpawner->GetEnemyArr().at(i)->GetBullets()->erase(it);
						breakout = true;
					}
					if (breakout)
						break;
				}
			}
		}
	}


	//Check for enemy bullets hitting player
	for (int i = 0; i < enemySpawner->GetEnemyArr().size(); i++)
	{
		if (enemySpawner->GetEnemyArr().at(i) != nullptr)
		{
			for (int j = 0; j < enemySpawner->GetEnemyArr().at(i)->GetBullets()->size(); j++)
			{

				if (enemySpawner->GetEnemyArr().at(i)->GetBullets()->at(j).GetCollider().CollisionMathTesting(game->getPlayer()->GetCollider()))
				{

					std::cout << "Player Hit!!" << std::endl;

					game->getPlayer()->GetPlayerStats()->TakeDamage(enemySpawner->GetEnemyArr().at(i)->GetEnemyStats()->GetWeaponDamage());

					auto it = enemySpawner->GetEnemyArr().at(i)->GetBullets()->begin() + j;
					enemySpawner->GetEnemyArr().at(i)->GetBullets()->erase(it);

				}
			}
		}
	}

	//Check for player bullets going off screen
	for (int i = 0; i < game->getPlayer()->GetBullets()->size(); i++)
	{

		if (game->getPlayer()->GetBullets()->at(i).GetCollider().CollisionMathTesting(leftOutOfBoundsColl) || game->getPlayer()->GetBullets()->at(i).GetCollider().CollisionMathTesting(rightOutOfBoundsColl) || game->getPlayer()->GetBullets()->at(i).GetCollider().CollisionMathTesting(upOutOfBoundsColl) || game->getPlayer()->GetBullets()->at(i).GetCollider().CollisionMathTesting(downOutOfBoundsColl))
		{


			auto it = game->getPlayer()->GetBullets()->begin() + i;
			game->getPlayer()->GetBullets()->erase(it);

		}
	}


	//Check for enemy bullets going off screen
	for (int e = 0; e < enemySpawner->GetEnemyArr().size(); e++)
	{
		for (int i = 0; i < enemySpawner->GetEnemyArr().at(e)->GetBullets()->size(); i++)
		{

			if (enemySpawner->GetEnemyArr().at(e)->GetBullets()->at(i).GetCollider().CollisionMathTesting(leftOutOfBoundsColl) || enemySpawner->GetEnemyArr().at(e)->GetBullets()->at(i).GetCollider().CollisionMathTesting(rightOutOfBoundsColl) || enemySpawner->GetEnemyArr().at(e)->GetBullets()->at(i).GetCollider().CollisionMathTesting(upOutOfBoundsColl) || enemySpawner->GetEnemyArr().at(e)->GetBullets()->at(i).GetCollider().CollisionMathTesting(downOutOfBoundsColl))
			{

				auto it = enemySpawner->GetEnemyArr().at(e)->GetBullets()->begin() + i;
				enemySpawner->GetEnemyArr().at(e)->GetBullets()->erase(it);

			}
		}
	}
}


void Scene1::Update(const float deltaTime) {

	bool isDead = game->getPlayer()->IsDead();
	if (isDead) game->LoadScene(2);

	if (!isDead)
	{
		bool islandsDead = checkIslandsHealths();
		if (islandsDead) game->LoadScene(2);

		if (!islandsDead)
		{
			++animationCounter;
			if (animationCounter > 60) animationCounter = 0;
			int indexSelector = std::round(animationCounter / 20.0f);

			//Set AI current node to each AI. So they know where they are in the tile graph ;)
			UpdateAIPositionNodes();

			static float updatePlayerNodeTime = 0;
			updatePlayerNodeTime++;

			//AI Find Path
			for (int i = 0; i < enemySpawner->GetEnemyArr().size(); i++)
			{
				if (enemySpawner->GetEnemyArr().at(i)->calculateIslandPath)
				{
					enemySpawner->GetEnemyArr().at(i)->SetIslandPath(graph->findPath(enemySpawner->GetEnemyArr().at(i)->GetCurrentNode(), enemySpawner->GetEnemyArr().at(i)->GetTargetNode()));
					enemySpawner->GetEnemyArr().at(i)->calculateIslandPath = false;
				}

				if (enemySpawner->GetEnemyArr().at(i)->calculatePlayerPath)
				{
					enemySpawner->GetEnemyArr().at(i)->SetPlayerPath(graph->findPath(enemySpawner->GetEnemyArr().at(i)->GetCurrentNode(), playerNode));
					enemySpawner->GetEnemyArr().at(i)->calculatePlayerPath = false;
				}
			}

			if (hitIsland != true)
			{
				for (int i = 0; i < islandsVector.size(); i++)
				{

					if (game->getPlayer()->GetCollider().CollisionMathTesting(islandsVector.at(i)->GetCollider()))
					{

						game->getPlayer()->GetPlayerStats()->TakeDamage(10);
						hitIsland = true;
						break;
					}
				}
			}

			if (hitIsland == true)
			{
				hitIslandTimer++;
			}

			if (hitIslandTimer > 200)
			{
				hitIsland = false;
				hitIslandTimer = 0;
			}


			game->getPlayer()->setImage(playerImage[indexSelector]);
			game->getPlayer()->setTexture(playerTexture[indexSelector]);

			game->getPlayer()->Update(deltaTime);

			ManageBullets();

			for (int i = 0; i < enemySpawner->GetEnemyArr().size(); i++)
			{

				enemySpawner->GetEnemyArr().at(i)->SetTargetPlayer(*game->getPlayer());

			}

			enemySpawner->Update(deltaTime);

			for (int i = 0; i < islandsVector.size(); i++)
			{

				islandsVector.at(i)->Update(deltaTime);

				for (int j = 0; j < enemySpawner->GetEnemyArr().size(); j++)
				{
					if (enemySpawner->GetEnemyArr().at(j)->GetTargetIsland() == *islandsVector.at(i))
					{
						if (islandsVector.at(i)->IsDestroyed()) enemySpawner->GetEnemyArr().at(j)->targetIslandDestroyed = true;
					}

				}

			}
		}
	}
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render the background
	SDL_RenderCopy(renderer, waterTexture, nullptr, nullptr);

	//Tile Rendering
	if (toggleTileRendering)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[i].size(); j++)
			{
				tiles[i][j]->Render();
			}
		}
	}

	//UI Rendering
	backgroundUI->Render();
	ammoBackgroundUI->Render();
	ammoUI->Render();

	//Hearts (health) Border/Background
	heartOneBorder->Render();
	heartOneBG->Render();
	heartTwoBorder->Render();
	heartTwoBG->Render();
	heartThreeBorder->Render();
	heartThreeBG->Render();
	heartFourBorder->Render();
	heartFourBG->Render();
	heartFiveBorder->Render();
	heartFiveBG->Render();

	//Player Health heart rendering
	int playerHealth = game->getPlayer()->GetPlayerStats()->GetHealth();
	switch (playerHealth)
	{
	case 50:
		heartOne->Render();
		heartTwo->Render();
		heartThree->Render();
		heartFour->Render();
		heartFive->Render();
		break;
	case 40:
		heartOne->Render();
		heartTwo->Render();
		heartThree->Render();
		heartFour->Render();
		break;
	case 30:
		heartOne->Render();
		heartTwo->Render();
		heartThree->Render();
		break;
	case 20:
		heartOne->Render();
		heartTwo->Render();
		break;
	case 10:
		heartOne->Render();
		break;
	}
	

	island1->render(0.75f);
	island2->render(0.5f);
	island3->render(0.75f);
	island4->render(0.5f);
	island5->render(0.5f);
	island6->render(0.45f);
	enemySpawner->render(0.5f);		

	// render the player
	game->RenderPlayer(0.5f);

	//Gear Selection UI
	switch(game->getPlayer()->GetGearState())
	{
	case GearState::REVERSE:
		parkWhiteUI->Render();
		neutralWhiteUI->Render();
		oneWhiteUI->Render();
		twoWhiteUI->Render();
		threeWhiteUI->Render();
		reverseRedUI->Render();
		break;
	case GearState::PARK:
		reverseWhiteUI->Render();
		neutralWhiteUI->Render();
		oneWhiteUI->Render();
		twoWhiteUI->Render();
		threeWhiteUI->Render();
		parkRedUI->Render();
		break;
	case GearState::NEUTRAL:
		reverseWhiteUI->Render();
		parkWhiteUI->Render();
		oneWhiteUI->Render();
		twoWhiteUI->Render();
		threeWhiteUI->Render();
		neutralRedUI->Render();
		break;
	case GearState::DRIVE1:
		reverseWhiteUI->Render();
		parkWhiteUI->Render();
		neutralWhiteUI->Render();
		oneRedUI->Render();
		twoWhiteUI->Render();
		threeWhiteUI->Render();
		break;
	case GearState::DRIVE2:
		reverseWhiteUI->Render();
		parkWhiteUI->Render();
		neutralWhiteUI->Render();
		oneWhiteUI->Render();
		twoRedUI->Render();
		threeWhiteUI->Render();
		break;
	case GearState::DRIVE3:
		reverseWhiteUI->Render();
		parkWhiteUI->Render();
		neutralWhiteUI->Render();
		oneWhiteUI->Render();
		twoWhiteUI->Render();
		threeRedUI->Render();
		break;
	default:
		reverseWhiteUI->Render();
		parkWhiteUI->Render();
		neutralWhiteUI->Render();
		oneWhiteUI->Render();
		twoWhiteUI->Render();
		threeWhiteUI->Render();
	}


	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles.at(i).size(); j++)
		{

			tiles.at(i).at(j)->Render();

		}


	}

	SDL_RenderPresent(renderer);



}

void Scene1::GetMousePOS() 
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	std::cout << "Mouse ScreenCoords\n x " << x << ", y " << y << "\n";
	Vec3 mousepos{ (float)x,(float)y,0 };
	mousepos =  projectionMatrix * mousepos;
	std::cout << "Mouse ProjectionCoords\n x " << mousepos.x << ", y " << mousepos.y << "\n";

}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
	
	  
	if (event.type == SDL_KEYDOWN)
	 {
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_F1:
			toggleTileRendering = !toggleTileRendering;
			break;
		case SDL_SCANCODE_F3:
			std::cout << std::endl;

			for (int i = 0; i < tiles.size(); i++)
			{
				for (int j = 0; j < tiles[i].size(); j++)
				{
					
					std::cout << "[" << i << "]" << "[" << j << "]" << tiles[i][j]->getNode()->getLabel() << " | ";

				}
				std::cout << std::endl;
			}		

			break;
		case SDL_SCANCODE_F4:

			TestPathFinding();
			break;
		case SDL_SCANCODE_4:


			break;
		case SDL_SCANCODE_3:
			break;
		 default:
			 break;
		 }
			}
}

void Scene1::TestPathFinding()
{

	Path newPath(graph->findPath(tiles[14][0]->getNode(), tiles[1][22]->getNode()));
	
	Uint8 r, g, b, a;
	r = 0;
	g = 0;
	b = 255;
	a = 100;

	while (newPath.GetCurrentNode() != nullptr)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[i].size(); j++)
			{
				if (tiles[i][j]->getNode() == newPath.GetCurrentNode())
				{
					tiles[i][j]->setRGBA(r, g, b, a);	
				}
			}
		}

		newPath.MoveToNextNode();
	}
}


void Scene1::UpdateAIPositionNodes()
{
	//Set AI Current Nodes

	for (int e = 0; e < enemySpawner->GetEnemyArr().size(); e++)
	{
		bool breakout = false;
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[i].size(); j++)
			{


				if (abs(enemySpawner->GetEnemyArr().at(e)->getBody()->getPos().x) - abs(tiles[i][j]->GetPos().x) < 1.8f
					&& abs(enemySpawner->GetEnemyArr().at(e)->getBody()->getPos().y) - abs(tiles[i][j]->GetPos().y) < 1.8f)
				{
				
					Node* blinkyNode = tiles[i][j]->getNode();
					enemySpawner->GetEnemyArr().at(e)->SetCurrentNode(blinkyNode);
					breakout = true;
				}

				if (breakout)
					break;
			}

			if (breakout)
				break;
		}

	}


	bool breakout = false;
	for (int i = 0; i < tiles.size(); i++)
	{

		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (abs(game->getPlayer()->getPos().x) - abs(tiles[i][j]->GetPos().x) < 1.8f
				&& abs(game->getPlayer()->getPos().y) - abs(tiles[i][j]->GetPos().y) < 1.8f)
			{

				Node* blinkyNode = tiles[i][j]->getNode();
				playerNode = blinkyNode;
				breakout = true;
			}

			if (breakout)
				break;
		}

		if (breakout)
			break;
	}

}

void Scene1::InitializeIslands()
{
	////Island 1
	island1 = new Island();
	island1->OnCreate(this);
	island1->setImageWith(IMG_Load("assets/island1.png"));

	std::vector<Node*> islands1;
	for (int i = 0; i < 4; i++)
	{
		for (int e = 0; e < 4; e++)
		{
			int number = 93;
			islands1.push_back(graph->getNode(number + e + (25 * i)));
		}
	}

	island1->getBody()->setPos(Vec3(20, 5, 0));
	for (int i = 0; i < islands1.size(); i++)
	{
		island1->AddIslandNode(islands1.at(i));
	}

	islandsVector.push_back(island1);


	////Island 2
	island2 = new Island();
	island2->OnCreate(this);
	island2->setImageWith(IMG_Load("assets/island2.png"));

	std::vector<Node*> islands2;
	for (int i = 0; i < 2; i++)
	{
		for (int e = 0; e < 2; e++)
		{
			int number = 292;
			islands2.push_back(graph->getNode(number + e + (25 * i)));
		}
	}

	island2->getBody()->setPos(Vec3(18, 12, 0));
	for (int i = 0; i < islands2.size(); i++)
	{
		island2->AddIslandNode(islands2.at(i));
	}

	islandsVector.push_back(island2);


	////Island 3
	island3 = new Island();
	island3->OnCreate(this);
	island3->setImageWith(IMG_Load("assets/island3.png"));

	std::vector<Node*> islands3;
	for (int i = 0; i < 3; i++)
	{
		for (int e = 0; e < 3; e++)
		{
			int number = 86;
			islands3.push_back(graph->getNode(number + e + (25 * i)));
		}
	}

	island3->getBody()->setPos(Vec3(12.5, 4.5, 0));
	for (int i = 0; i < islands3.size(); i++)
	{
		island3->AddIslandNode(islands3.at(i));
	}

	islandsVector.push_back(island3);


	////Island 4
	island4 = new Island();
	island4->OnCreate(this);
	island4->setImageWith(IMG_Load("assets/island4.png"));

	std::vector<Node*> islands4;
	for (int i = 0; i < 2; i++)
	{
		for (int e = 0; e < 2; e++)
		{
			int number = 279;
			islands4.push_back(graph->getNode(number + e + (25 * i)));
		}
	}


	island4->getBody()->setPos(Vec3(5, 12, 0));
	for (int i = 0; i < islands4.size(); i++)
	{
		island4->AddIslandNode(islands4.at(i));
	}

	islandsVector.push_back(island4);


	////Island 5
	island5 = new Island();
	island5->OnCreate(this);
	island5->setImageWith(IMG_Load("assets/island5.png"));

	std::vector<Node*> islands5;
	for (int i = 0; i < 2; i++)
	{
		for (int e = 0; e < 2; e++)
		{
			int number = 235;
			islands5.push_back(graph->getNode(number + e + (25 * i)));
		}
	}

	island5->getBody()->setPos(Vec3(11, 10, 0));
	for (int i = 0; i < islands5.size(); i++)
	{
		island5->AddIslandNode(islands5.at(i));
	}

	islandsVector.push_back(island5);


	////Island 6
	island6 = new Island();
	island6->OnCreate(this);
	island6->setImageWith(IMG_Load("assets/island6.png"));

	std::vector<Node*> islands6;
	//Island[5]
	for (int i = 0; i < 2; i++)
	{
		for (int e = 0; e < 2; e++)
		{
			int number = 105;
			islands6.push_back(graph->getNode(number + e + (25 * i)));
		}
	}

	island6->getBody()->setPos(Vec3(6, 5, 0));
	for (int i = 0; i < islands6.size(); i++)
	{
		island6->AddIslandNode(islands6.at(i));
	}

	islandsVector.push_back(island6);

	//Delete Nodes
	islands1.clear();
	islands2.clear();
	islands3.clear();
	islands4.clear();
	islands5.clear();
	islands6.clear();
	
}

bool Scene1::checkIslandsHealths()
{
	bool isDead;

	for (int i = 0; i < islandsVector.size(); i++)
	{
		if (islandsVector.at(i)->IsDestroyed()) isDead = true;
		else
		{

			isDead = false;
			break;

		}



	}

	return isDead;



}

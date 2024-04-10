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
	blinky = nullptr;
	enemySpawner = nullptr;
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
	islands.push_back(graph->getNode(69));
	islands.push_back(graph->getNode(93));
	islands.push_back(graph->getNode(94));
	islands.push_back(graph->getNode(118));
	islands.push_back(graph->getNode(119));
	islands.push_back(graph->getNode(120));


	//Island[1]
	islands.push_back(graph->getNode(292));
	islands.push_back(graph->getNode(293));
	islands.push_back(graph->getNode(317));
	islands.push_back(graph->getNode(318));

	//Island[2]
	islands.push_back(graph->getNode(112));
	islands.push_back(graph->getNode(113));
	islands.push_back(graph->getNode(137));
	islands.push_back(graph->getNode(138));

	//Island[3]
	islands.push_back(graph->getNode(279));
	islands.push_back(graph->getNode(280));
	islands.push_back(graph->getNode(304));
	islands.push_back(graph->getNode(305));

	//Island[4]
	islands.push_back(graph->getNode(235));
	islands.push_back(graph->getNode(236));
	islands.push_back(graph->getNode(260));
	islands.push_back(graph->getNode(261));

	//Island[5]
	islands.push_back(graph->getNode(105));
	islands.push_back(graph->getNode(106));
	islands.push_back(graph->getNode(130));
	islands.push_back(graph->getNode(131));

	




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
	audio.playAudio(3, 2);
	
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
	islandRect[5] = { 385, 650, 150, 150 };
	

	//Player Initializers
	game->getPlayer()->setImage(playerImage[0]);
	game->getPlayer()->setTexture(playerTexture[0]);
	game->getPlayer()->SetMaxSpeed(15);




	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setImageWith(enemyImage,0))
	{
		return false;
	}
	blinky->getBody()->setPos(Vec3(20, 0, 0));
	// end of character set ups

	island = new Island();
	if (!island->OnCreate(this) || !island->setImageWith(IMG_Load("assets/island6.png")))
	{
		return false;
	}


	island->getBody()->setPos(Vec3(10, 6, 0));
	std::vector<Island> islands;
	islands.push_back(*island);

	enemy = new Character();
	enemy->SetIslands(islands);
	enemy->OnCreate(this);
	enemy->setImageWith(enemyImage, 0);
	enemy->getBody()->setPos(Vec3(20, 0, 0));
	Stats* enemyStats = new Stats(50, 50, 10);
	enemy->SetEnemyStats(enemyStats);
	enemySpawner = new Spawner(enemy);
	enemySpawner->OnCreate(this);

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

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	enemySpawner->OnDestroy();

	for (int i = 0; i < islandsVector.size(); i++)
	{
		islandsVector.at(i)->OnDestroy();
	}
	islandsVector.clear();

	delete playerNode;
	tiles.clear();
	sceneNodes.clear();

	game->getPlayer()->OnDestroy();

	delete this;

}

void Scene1::ManageBullets()
{
	//Check for player bullets hitting enemy

	for (int i = 0; i < enemySpawner->GetEnemyArr().size(); i++)
	{
		for (int j = 0; j < game->getPlayer()->GetBullets()->size(); j++)
		{

			if (game->getPlayer()->GetBullets()->at(j).GetCollider().CollisionMathTesting(enemySpawner->GetEnemyArr().at(i)->GetCollider()))
			{

				std::cout << "Enemy Hit!!" << std::endl;
				audio.playAudio(1, 20);
	
				enemySpawner->GetEnemyArr().at(i)->GetEnemyStats()->TakeDamage(game->getPlayer()->GetBullets()->at(j).GetProjectileDamage());

				auto it = game->getPlayer()->GetBullets()->begin() + j;
				game->getPlayer()->GetBullets()->erase(it);

			}
		}
	}

	//Check for player bullets hitting island //Will be switched from player to enemy later
	for (int i = 0; i < game->getPlayer()->GetBullets()->size(); i++)
	{

		if (game->getPlayer()->GetBullets()->at(i).GetCollider().CollisionMathTesting(island->GetCollider()))
		{

			std::cout << "Island Hit!!" << std::endl;
			audio.playAudio(5, 20);
		
			island->GetStats()->TakeDamage(game->getPlayer()->GetBullets()->at(i).GetProjectileDamage());

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
			audio.playAudio(1, 20);
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
			audio.playAudio(6, 20);

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
			audio.playAudio(6, 20);

		}
	}
}


void Scene1::Update(const float deltaTime) {
	++animationCounter;
	if (animationCounter > 60) animationCounter = 0;
	int indexSelector = std::round(animationCounter / 20.0f);
	

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

	ManageBullets();

	for (int i = 0; i < enemySpawner->GetEnemyArr().size(); i++)
	{

		enemySpawner->GetEnemyArr().at(i)->SetTargetPlayer(*game->getPlayer());

	}

	enemySpawner->Update(deltaTime);

	island->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	

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
	
	// render the player
	game->RenderPlayer(0.5f);
	island1->render(0.75f);
	island2->render(0.5f);
	island3->render(0.75f);
	island4->render(0.5f);
	island5->render(0.5f);
	island6->render(0.45f);
	enemySpawner->render(0.5f);		

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

	//islandColls[5].RenderCollider(renderer);

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
	blinky->HandleEvents(event);
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
			SetBlinkyPath();

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

void Scene1::SetBlinkyPath()
{
	
	Uint8 r, g, b, a;
	r = 0;
	g = 0;
	b = 255;
	a = 100;
	
	

	patrolPath.SetPath(graph->findPath(tiles[14][0]->getNode(), tiles[1][22]->getNode()));
	blinky->SetCharacterPath(patrolPath);


	Path newPatrolPath = blinky->GetCharacterPath().GetPath();
	while (newPatrolPath.GetCurrentNode() != nullptr)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[i].size(); j++)
			{
				if (tiles[i][j]->getNode() == newPatrolPath.GetCurrentNode())
				{
					tiles[i][j]->setRGBA(r, g, b, a);
				}
			}
		}

		newPatrolPath.MoveToNextNode();
	}


	bool breakout = false;
	if (blinky->GetCurrentPath().GetCurrentNode() == NULL)
	{
		for (int i = 0; i < tiles.size(); i++)
		{
			for (int j = 0; j < tiles[i].size(); j++)
			{
				if (abs(blinky->getBody()->getPos().x) - abs(tiles[i][j]->GetPos().x) < 1.8f && abs(blinky->getBody()->getPos().y) - abs(tiles[i][j]->GetPos().y) < 1.8f)
				{
					Node* blinkyNode = tiles[i][j]->getNode();
					blinky->SetCurrentPath(graph->findPath(blinkyNode, patrolPath.GetCurrentNode()));
					breakout = true;
				}

				if (breakout)
					break;
			}
			
			if (breakout)
				break;
		}

		g = 255;
		b = 0;

		Path newPath = blinky->GetCurrentPath().GetPath();
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

}

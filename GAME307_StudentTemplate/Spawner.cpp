#include "Spawner.h"

Spawner::Spawner() : wrecksLifetime(600)
{
	scene = nullptr;
	enemyArr.clear();

}

Spawner::Spawner(Character* enemy_)
{
	enemy = enemy_;
}

bool Spawner::OnCreate(Scene* scene_)
{
	spawnLocation = Vec3(1, 9, 0);
	enemyCap = 6;
	scene = scene_;
	enemy->getBody()->setPos(spawnLocation);
	enemyArr.reserve(25);
	enemyArr.push_back(enemy);

	renderer = scene->game->getRenderer();
	destroyedShipImage = IMG_Load("assets/boatDebris.png");
	destroyedShipTexture = SDL_CreateTextureFromSurface(renderer, destroyedShipImage);
	return true;
}

void Spawner::Update(float time)
{

	for (int i = 0; i < enemyArr.size(); i++)
	{
		if (enemyArr.at(i)->IsDead())
		{
			SDL_Rect rect;
			Matrix4 projectionMatrix = scene->getProjectionMatrix();
			Vec3 screenCoords;
			screenCoords = projectionMatrix * enemyArr[i]->getBody()->getPos();
			rect.x = static_cast<int>(screenCoords.x - 0.5f * 75);
			rect.y = static_cast<int>(screenCoords.y - 0.5f * 75);
			rect.w = 75;
			rect.h = 75;
			destroyedShipsPos.push_back(rect);

			auto it = enemyArr.begin() + i;
			enemyArr.erase(it);
		}

	}


	static float spawnTime = 0;
	spawnTime++;
	for (int i = 0; i < enemyArr.size(); i++)
	{

		enemyArr.at(i)->Update(time);

	}

	if (spawnTime > 400)
	{
		if (enemyArr.size() < enemyCap) SpawnEnemy();
		spawnTime = 0;
	}

	
}

void Spawner::render(float scale)
{
	if (destroyedShipsPos.size() != 0) 
	{
		for (int i = 0; i < destroyedShipsPos.size(); ++i)
		{
			SDL_RenderCopy(renderer, destroyedShipTexture, nullptr, &destroyedShipsPos[i]);
		}
	}

	for (int i = 0; i < enemyArr.size(); i++)
	{

		enemyArr.at(i)->render(scale);

	}

	if (wrecksLifetime >= 600)
	{
		wrecksLifetime = 0;
		destroyedShipsPos.clear();
	}

	++wrecksLifetime;
}

void Spawner::RandomizeSpawnLocation()
{
	std::srand(std::time(nullptr));
	// Define the maximum value for random numbers
	int max_value = 8;

	// Generate a random number between 0 and max_value
	int r = std::rand() % (max_value + 1);

	if (r == 0) spawnLocation = Vec3(1, 9,0);
	if (r == 1) spawnLocation = Vec3(8, 1, 0);
	if (r == 2) spawnLocation = Vec3(16, 1, 0);
	if (r == 3) spawnLocation = Vec3(24, 1, 0);
	if (r == 4) spawnLocation = Vec3(24, 8, 0);
	if (r == 5) spawnLocation = Vec3(24, 14, 0);
	if (r == 6) spawnLocation = Vec3(12, 14, 0);
	if (r == 7) spawnLocation = Vec3(16, 8, 0);
	if (r == 8) spawnLocation = Vec3(6.5, 8.5, 0);


}

void Spawner::SpawnEnemy()
{
	RandomizeSpawnLocation();
	Character* newEnemy = new Character();
	newEnemy->SetIslands(enemy->GetIslands());
	newEnemy->OnCreate(scene);
	newEnemy->setImageWith(enemy->GetSpriteImages(), 0);
	newEnemy->getBody()->setPos(spawnLocation);
	Stats* enemyStats = new Stats(50, 50, 10);
	newEnemy->SetEnemyStats(enemyStats);
	enemyArr.push_back(newEnemy);

}

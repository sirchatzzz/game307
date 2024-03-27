#include "Spawner.h"

Spawner::Spawner()
{
	enemy = new Character();
	scene = nullptr;
	enemyArr.clear();
	std::srand(std::time(nullptr));
}

Spawner::Spawner(Character* enemy_)
{
	enemy = enemy_;
}

bool Spawner::OnCreate(Scene* scene_)
{
	spawnLocation = Vec3(0.11, 0.11, 0);
	enemyCap = 6;
	scene = scene_;
	enemyArr.push_back(enemy);
	return true;
}

void Spawner::Update(float time)
{

	static float spawnTime = 0;
	spawnTime++;
	for (int i = 0; i < enemyArr.size(); i++)
	{

		enemyArr.at(i)->Update(time);

	}

	if (spawnTime > 100)
	{
		if (enemyArr.size() < enemyCap) SpawnEnemy();
		spawnTime = 0;
	}

	
}

void Spawner::render(float scale)
{

	for (int i = 0; i < enemyArr.size(); i++)
	{

		enemyArr.at(i)->render(scale);

	}


}

void Spawner::RandomizeSpawnLocation()
{

	// Define the maximum value for random numbers
	int max_value = 10; // Change this to the desired maximum value

	// Generate a random number between 0 and max_value
	int r = std::rand() % (max_value + 1);

	std::cout << r << std::endl;

	if (r == 1) spawnLocation = Vec3(2, 2,0);
	if (r == 2) spawnLocation = Vec3(2, 6, 0);
	if (r == 3) spawnLocation = Vec3(2, 8, 0);
	if (r == 4) spawnLocation = Vec3(2, 12, 0);
	if (r == 5) spawnLocation = Vec3(8, 2, 0);
	if (r == 6) spawnLocation = Vec3(4, 12, 0);
	if (r == 7) spawnLocation = Vec3(20, 2, 0);
	if (r == 8) spawnLocation = Vec3(12, 12, 0);
	if (r == 9) spawnLocation = Vec3(4, 10, 0);
	if (r == 10) spawnLocation = Vec3(12, 10, 0);



}

void Spawner::SpawnEnemy()
{
	RandomizeSpawnLocation();
	Character* newEnemy = new Character();
	newEnemy->OnCreate(scene);
	newEnemy->setImageWith(enemy->GetSpriteImages(), 0);
	newEnemy->getBody()->setPos(spawnLocation);
	enemyArr.push_back(newEnemy);
}

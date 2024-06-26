#pragma once

#include "Character.h"
#include <memory>
class Spawner
{

private:

	std::vector<Character*> enemyArr;
	Character* enemy;
	class Scene* scene;
	Vec3 spawnLocation;
	
	std::vector<Vec3> spawnLocations;
	float enemyCap;
	float spawnTime = 0;
public:

	Spawner();
	Spawner(Character* enemy_);
	
	bool OnCreate(Scene* scene_);
	void OnDestroy();

	void Update(float time);
	void render(float scale = 1.0f);
	void SetEnemyType(Character* enemy_) { enemy = enemy_; }
	std::vector<Character*> GetEnemyArr() { return enemyArr; }
	
	void RandomizeSpawnLocation();
	void SpawnEnemy();

	void SetEnemyCap(float enemyCap_) { enemyCap = enemyCap_; }
};


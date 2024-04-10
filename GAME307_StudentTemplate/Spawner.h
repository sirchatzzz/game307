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
	SDL_Texture* destroyedShipTexture;
	SDL_Surface* destroyedShipImage;
	std::vector<SDL_Rect> destroyedShipsPos;
	SDL_Renderer* renderer;
	int wrecksLifetime;
	
	float enemyCap;

public:

	Spawner();
	Spawner(Character* enemy_);
	
	bool OnCreate(Scene* scene_);
	void OnDestroy() { delete scene; };

	void Update(float time);
	void render(float scale = 1.0f);
	void SetEnemyType(Character* enemy_) { enemy = enemy_; }
	std::vector<Character*> GetEnemyArr() { return enemyArr; }
	
	void RandomizeSpawnLocation();
	void SpawnEnemy();

	void SetEnemyCap(float enemyCap_) { enemyCap = enemyCap_; }
};


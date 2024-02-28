#pragma once

class ShipStats
{

private:
	//Ship stats variables
	float health;
	float maxHealth;
	float weaponDamage;

public:

	ShipStats();
	ShipStats(float health_, float maxHealth_, float weaponDamage_);

	//Setters for ship stats
	void SetHealth(float health_) { health = health_; }
	void SetMaxHealth(float maxHealth_) { maxHealth = maxHealth_; }
	void SetWeaponDamage(float weaponDamage_) { weaponDamage = weaponDamage_; }

	//Getters for ship stats
	float GetHealth() { return health; }
	float GetMaxHealth() { return maxHealth; }
	float GetWeaponDamage() { return weaponDamage; }

	//Functions to take damage and heal;
	void TakeDamage(float damage_);
	void Heal(float healthIncrease_);


};

class ShipAmmo
{

private:

	//Ship ammo stats
	float maxAmmo;
	float currentTotalAmmo;
	float currentMagAmmo;
	float magSize;
	bool isReloading;
	float reloadTimer;

public:
	
	ShipAmmo();
	ShipAmmo(float maxAmmo_, float currentTotalAmmo_, float magSize_);


	//Setters for ship ammo stats
	void SetMaxAmmo(float maxAmmo_) { maxAmmo = maxAmmo_; }
	void SetCurrentTotalAmmo(float currentTotalAmmo_);
	void SetMagSize(float magSize_) { magSize = magSize_; }

	//Check if ship is reloading
	bool IsReloading() { return isReloading; }

	//Getters for ship ammo stats
	float GetMaxAmmo() { return maxAmmo; }
	float GetCurrentTotalAmmo() { return currentTotalAmmo; }
	float GetMagSize() { return magSize; }
	float GetCurrentMagAmmo() { return currentMagAmmo; }

	//Increase total ammo
	void IncreaseCurrentTotalAmmo(float ammoIncrease_);

	//Decrease mag ammo
	void DecreaseCurrentMagAmmo(float ammoDecrease_);

	//Reload ship turret
	void Reload();

	//Initialize the ammo and calculate mag size 
	void InitializeAmmo();
	void Update(float deltaTime);

};

#pragma once

class ShipStats
{

private:

	float health;
	float maxHealth;
	float weaponDamage;
	float ammoAmount;
public:

	ShipStats();
	ShipStats(float health_, float maxHealth_, float weaponDamage_, float ammoAmount_);

	void SetHealth(float health_) { health = health_; }
	void SetMaxHealth(float maxHealth_) { maxHealth = maxHealth_; }
	void SetWeaponDamage(float weaponDamage_) { weaponDamage = weaponDamage_; }
	void SetAmmoAmount(float ammoAmount_) { ammoAmount = ammoAmount_; }

	float GetHealth() { return health; }
	float GetMaxHealth() { return maxHealth; }
	float GetWeaponDamage() { return weaponDamage; }
	float GetAmmoAmount() { return ammoAmount; }

	void TakeDamage(float damage_);
	void Heal(float healthIncrease_);


};

class ShipAmmo
{

private:

	float maxAmmo;
	float currentTotalAmmo;
	float currentMagAmmo;
	float magSize;
	bool isReloading;

public:
	
	ShipAmmo();
	ShipAmmo(float maxAmmo_, float currentTotalAmmo_, float magSize_);

	void SetMaxAmmo(float maxAmmo_) { maxAmmo = maxAmmo_; }
	void SetCurrentTotalAmmo(float currentTotalAmmo_);
	void SetMagSize(float magSize_) { magSize = magSize_; }
	bool IsReloading() { return isReloading; }

	float GetMaxAmmo() { return maxAmmo; }
	float GetCurrentTotalAmmo() { return currentTotalAmmo; }
	float GetMagSize() { return magSize; }
	float GetCurrentMagAmmo() { return currentMagAmmo; }

	void IncreaseCurrentTotalAmmo(float ammoIncrease_);
	void DecreaseCurrentMagAmmo(float ammoDecrease_);

	void Reload();
	void InitializeAmmo();


};

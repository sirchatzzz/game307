#include "Stats.h"
#include <iostream>
Stats::Stats()
{

	health = 0;
	maxHealth = 0;
	weaponDamage = 0;



}

Stats::Stats(float health_, float maxHealth_, float weaponDamage_)
{

	health = health_;
	maxHealth = maxHealth_;
	weaponDamage = weaponDamage_;

}

void Stats::TakeDamage(float damage_)
{

	health -= damage_;

	if (health < 0) health = 0;


}

void Stats::Heal(float healthIncrease_)
{

	health += healthIncrease_;

	if (health > maxHealth) health = maxHealth;



}

ShipAmmo::ShipAmmo()
{

	maxAmmo = 0;
	currentTotalAmmo = 0;
	currentMagAmmo = 0;
	isReloading = false;
	reloadTimer = 0;
	magSize = 0;
}

ShipAmmo::ShipAmmo(float maxAmmo_, float currentTotalAmmo_, float magSize_)
{
	maxAmmo = maxAmmo_;
	currentTotalAmmo = currentTotalAmmo_;
	isReloading = false;
	magSize = magSize_;
	currentMagAmmo = 0;
	reloadTimer = 0;
	InitializeAmmo();

}

void ShipAmmo::SetCurrentTotalAmmo(float currentTotalAmmo_)
{

	currentTotalAmmo = currentTotalAmmo_;
	if (currentTotalAmmo > maxAmmo) currentTotalAmmo = maxAmmo;
}



void ShipAmmo::IncreaseCurrentTotalAmmo(float ammoIncrease_)
{

	currentTotalAmmo += ammoIncrease_;

	if (currentTotalAmmo > maxAmmo) currentTotalAmmo = maxAmmo;

}

void ShipAmmo::DecreaseCurrentMagAmmo(float ammoDecrease_)
{

	currentMagAmmo -= ammoDecrease_;
	if (currentMagAmmo < 0) currentMagAmmo = 0;
	if (currentMagAmmo == 0) Reload();


}

void ShipAmmo::Reload()
{


	std::cout << "Reloading!" << std::endl;
	isReloading = true;
	
		
	

}

void ShipAmmo::InitializeAmmo()
{

	if (currentTotalAmmo > magSize)
	{
		if (currentMagAmmo == 0)
		{
			currentMagAmmo = magSize;
			currentTotalAmmo -= magSize;
		}
		else
		{

			float diff = magSize - currentMagAmmo;

			currentMagAmmo = magSize;

			currentTotalAmmo -= diff;
		}
	}
	else
	{
		if (currentMagAmmo == 0)
		{
			currentMagAmmo = currentTotalAmmo;
			currentTotalAmmo = 0;
		}
		else
		{

			float diff = magSize - currentMagAmmo;
			if (diff < currentTotalAmmo) currentMagAmmo += diff;
			else currentMagAmmo += currentTotalAmmo;
			currentTotalAmmo -= diff;
			if (currentTotalAmmo < 0) currentTotalAmmo = 0;
		}

	}

}

void ShipAmmo::Update(float deltaTime)
{

	if (isReloading == true) reloadTimer++;

	if (reloadTimer > 25)
	{
		InitializeAmmo();
		isReloading = false;
		reloadTimer = 0;
	}

}

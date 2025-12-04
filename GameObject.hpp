/*
File Name: GameObject.hpp
Created: 11/19/2025
Purpose: The main file that starts the program.
*/

#pragma once
#include "Header.hpp"
#include "Projectile.hpp"
#include "Weapon.hpp"

class GameObject : public sf::Sprite
{

public:

	GameObject(const sf::Texture& texture, int nCurrHealth, int nMaxHealth, int nDamage, int nProjectileCooldown,
		float nMoveSpeed, Weapon *nCurrWeapon, int nScore);
	~GameObject();
	int getCurrHealth();
	void setCurrHealth(int newCurrHealth);

	void setCurrWeapon(Weapon *newCurrWeapon);

	int getMaxHealth();
	void setMaxHealth(int newMaxHealth);

	int getDamage();
	void setDamage(int newDamage);

	float getMoveSpeed();
	void setMoveSpeed(float newMoveSpeed);

	int getScore();
	void setScore(int newScore);

	//std::string getCurrWeapon(){return currWeapon;}

	Weapon *getCurrWeapon(){return currWeapon;}

   void deincrementHealth(int damageTaken);

	sf::Sprite* getSprite();
	virtual void setSprite(std::string textureFilePath);

	Projectile* shootProjectile(sf::RenderWindow* window, const sf::Texture& texture, float projectileSpeed,
		int nDamage, double nLifeTime);

	virtual void characterMoveControls(std::vector<GameObject*> gameObjectArray);
	int projectileCooldown;

private:

	// whatever stats we need
	int currHealth;
	int maxHealth;
	int damage;
	float moveSpeed;
	Weapon *currWeapon;
	int score;
};

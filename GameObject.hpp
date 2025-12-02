/*
File Name: GameObject.hpp
Created: 11/19/2025
Purpose: The main file that starts the program.
*/

#pragma once
#include "Header.hpp"
#include "Projectile.hpp"

class GameObject : public sf::Sprite
{

public:

	GameObject(const sf::Texture& texture, int nCurrHealth, int nMaxHealth, int nDamage, int nProjectileCooldown, float nMoveSpeed);
	~GameObject();
	int getCurrHealth();
	void setCurrHealth(int newCurrHealth);

	int getMaxHealth();
	void setMaxHealth(int newMaxHealth);

	int getDamage();
	void setDamage(int newDamage);

	float getMoveSpeed();
	void setMoveSpeed(float newMoveSpeed);

	sf::Sprite* getSprite();
	virtual void setSprite(std::string textureFilePath);

	Projectile* shootProjectile(sf::RenderWindow* window, const sf::Texture& texture, float projectileSpeed, int nDamage, double nLifeTime);

	virtual void characterMoveControls();
	virtual void enemyMoveControls(float playerX,float playerY);
	int projectileCooldown;

private:

	// whatever stats we need
	int currHealth;
	int maxHealth;
	int damage;
	float moveSpeed;

};

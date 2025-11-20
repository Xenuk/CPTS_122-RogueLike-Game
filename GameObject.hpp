#pragma once
#include "header.hpp"
#include "Projectile.hpp"
class GameObject : public sf::Sprite{
public:
	GameObject(const sf::Texture& texture, int nCurrHealth, int nMaxHealth, int nDamage, double nMoveSpeed);
	~GameObject();
	int getCurrHealth();
	void setCurrHealth(int newCurrHealth);

	int getMaxHealth();
	void setMaxHealth(int newMaxHealth);

	int getDamage();
	void setDamage(int newDamage);

	double getMoveSpeed();
	void setMoveSpeed(double newMoveSpeed);

	sf::Sprite* getSprite();
	virtual void setSprite(std::string textureFilePath);

	Projectile* shootProjectile(const sf::Texture& texture, int nDamage, sf::Vector2f nDirectionAndSpeed, double nLifeTime, sf::Vector2f playerPosition);
private:
	// whatever stats we need
	int currHealth;
	int maxHealth;
	int damage;
	double moveSpeed;


};
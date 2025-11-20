#pragma once
#include "header.hpp"
class GameObject {
public:
	GameObject();

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
private:
	// whatever stats we need
	int currHealth;
	int maxHealth;
	int damage;
	double moveSpeed;
	sf::Sprite* sprite;
	sf::Texture* texture;

};
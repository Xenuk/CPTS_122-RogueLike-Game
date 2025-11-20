#include "GameObject.hpp"

GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}


int GameObject::getCurrHealth()
{
	return currHealth;
}
void GameObject::setCurrHealth(int newCurrHealth)
{
	currHealth = newCurrHealth;
}


int GameObject::getMaxHealth()
{
	return maxHealth;
}
void GameObject::setMaxHealth(int newMaxHealth)
{
	maxHealth = newMaxHealth;
}

int GameObject::getDamage()
{
	return damage;
}
void GameObject::setDamage(int newDamage)
{
	damage = newDamage;
}

double GameObject::getMoveSpeed()
{
	return moveSpeed;
}
void GameObject::setMoveSpeed(double newMoveSpeed)
{
	moveSpeed = newMoveSpeed;
}

sf::Sprite* GameObject::getSprite()
{
	return sprite;
}
void GameObject::setSprite(std::string textureFilePath)
{
	sf::Texture texture;
	if (!texture.loadFromFile(textureFilePath))
	{
		std::cout << "Error loading from file" << std::endl;

	}
	sprite = new sf::Sprite(texture);
}
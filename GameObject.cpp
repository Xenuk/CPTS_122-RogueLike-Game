#include "GameObject.hpp"

GameObject::GameObject(const sf::Texture& texture, int nCurrHealth,int nMaxHealth,int nDamage,double nMoveSpeed) :
Sprite(texture)
{
	currHealth = nCurrHealth;
	maxHealth = nMaxHealth;
	damage = nDamage;
	moveSpeed = nMoveSpeed;
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
	return nullptr;
}
void GameObject::setSprite(std::string textureFilePath)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(textureFilePath))
	{
		std::cout << "Error loading from file" << std::endl;
	}
	this->setTexture(*texture);
}
Projectile* GameObject::shootProjectile(const sf::Texture& texture, int nDamage, sf::Vector2f nDirectionAndSpeed, double nLifeTime, sf::Vector2f playerPosition)
{
	Projectile* lol = new Projectile(texture, nDamage, nDirectionAndSpeed, nLifeTime);
	lol->setOrigin({ 8,8 });
	lol->setPosition(playerPosition);


	return lol;
}
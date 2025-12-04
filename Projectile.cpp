/*
File Name: Projectile.cpp
Created: 11/20/2025
Purpose: Projectile content file, definitions.
*/

#include "Header.hpp"
#include "Projectile.hpp"


Projectile::Projectile(const sf::Texture& texture, int nDamage, sf::Vector2f nDirectionAndSpeed,
	double nLifeTime) : Sprite(texture), directionAndSpeed(nDirectionAndSpeed), damage(nDamage), lifeTime(nLifeTime), currLifeTime(0.0)
{
	std::cout << "Projectile Constructor Called." << std::endl;
	std::cout << "Projectile Damage: " << damage << std::endl;
}

Projectile::~Projectile()
{
	std::cout << "Projectile Destructor Called." << std::endl;
}

sf::Vector2f Projectile::getDirectionAndSpeed() const
{
	return directionAndSpeed;
}

int Projectile::getDamage() const
{
	return damage;
}

double Projectile::getLifeTime() const
{
	return lifeTime;
}

double Projectile::getCurrLifeTime() const
{
	return currLifeTime;
}

void Projectile::setDirectionAndSpeed(const sf::Vector2f& nDirectionAndSpeed)
{
	directionAndSpeed = nDirectionAndSpeed;
}

void Projectile::setDamage(int nDamage)
{
	damage = nDamage;
}

void Projectile::setLifeTime(double nLifeTime)
{
	lifeTime = nLifeTime;
}

void Projectile::setCurrLifeTime(double nCurrLifeTime)
{
	currLifeTime = nCurrLifeTime;
}

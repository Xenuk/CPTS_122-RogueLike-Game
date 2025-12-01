/*
File Name: Projectile.cpp
Created: 11/20/2025
Purpose: Fill In
*/

#include "Header.hpp"
#include "Projectile.hpp"


Projectile::~Projectile()
{
std::cout << "Projectile Destructor Called." << std::endl;
}

Projectile::Projectile(const sf::Texture& texture, int nDamage, sf::Vector2f nDirectionAndSpeed, double nLifeTime) : Sprite(texture)
{
	std::cout << "Projectile Constructor Called." << std::endl;
	damage = nDamage;
	directionAndSpeed = nDirectionAndSpeed;
	lifeTime = nLifeTime;
	currLifeTime = 0;

	std::cout << "Projectile Damage: " << damage << std::endl;
	// Add speed/lifetime/direction/life?	
}

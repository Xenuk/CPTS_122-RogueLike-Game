/*
File Name: Projectile.cpp
Created: 11/21/2025
Purpose: Declarations for Projectile.hpp Definitions
*/

#include "Header.hpp"
#include "Projectile.hpp"


Projectile::~Projectile()
{

}

Projectile::Projectile(const sf::Texture& texture, int nDamage, sf::Vector2f nDirectionAndSpeed, double nLifeTime) : Sprite(texture)
{
	damage = nDamage;
	directionAndSpeed = nDirectionAndSpeed;
	lifeTime = nLifeTime;
}

#include "header.hpp"
#include "Projectile.hpp"


Projectile::~Projectile()
{

}
Projectile::Projectile(const sf::Texture& texture, int nDamage, sf::Vector2f nDirectionAndSpeed, double nLifeTime) : Sprite(texture)
{
	damage = nDamage;
	directionAndSpeed = nDirectionAndSpeed;
	lifeTime = nLifeTime;
	currLifeTime = 0;
}

#pragma once
#include "header.hpp"


class Projectile : public sf::Sprite {

public:
	Projectile(const sf::Texture& texture, int nDamage, sf::Vector2f nDirectionAndSpeed, double nLifeTime); // nDirectionAndSpeed later will be used from mouse position calculated somehow or smth.
	~Projectile();
	sf::Vector2f directionAndSpeed;
	int damage;
	double lifeTime;
	double currLifeTime;
};
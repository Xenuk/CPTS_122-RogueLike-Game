/*
File Name: Projectile.hpp
Created: 11/20/2025
Purpose: Fill in
*/

#pragma once
#include "Header.hpp"

class Projectile : public sf::Sprite 
{
public:
    // Projectile();
    Projectile(const sf::Texture& texture, int nDamage, sf::Vector2f nDirectionAndSpeed,
        double nLifeTime);
    ~Projectile();

    // Getters
    sf::Vector2f getDirectionAndSpeed() const;
    int getDamage() const;
    double getLifeTime() const;
    double getCurrLifeTime() const;

    // Setters
    void setDirectionAndSpeed(const sf::Vector2f& nDirectionAndSpeed);
    void setDamage(int nDamage);
    void setLifeTime(double nLifeTime);
    void setCurrLifeTime(double nCurrLifeTime);

private:
    sf::Vector2f directionAndSpeed;
    int damage;
    double lifeTime;
    double currLifeTime;
};

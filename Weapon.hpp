/*
File Name: Weapon.hpp
Created: 11/28/2025
Purpose: Weapon class that inherits from Projectile
*/

#pragma once
#include "Header.hpp"
#include "Projectile.hpp"

class Weapon {
public:
  Weapon(/*const sf::Texture& texture, weapon textures???*/
         std::string nName = "default", int nDamage = 0, double nLifeTime = 0.0, int nCooldown = 0,
         int nAmmo = -1, bool nAutomatic = false);
  ~Weapon();

  std::string getName() const;
  int getCooldown() const;
  int getDamage() const;
  double getLifeTime() const;
  int getAmmo() const;
  int getCurrAmmo() const;
  bool isAutomatic() const;

  void setName(std::string nName);
  void setDamage(int nDamage);
  void setLifeTime(double nLifeTime);
  void setAmmo(int nAmmo);
  void setCurrAmmo(int nCurrAmmo);
  void setCooldown(int nCooldown);
  void setAutomatic(bool nAutomatic);

  void deincrementCurrAmmo();
  void reload();


private:
  std::string name;
  int damage;
  double lifeTime;
  int cooldown;
  int ammo; // -1 for infinite
  int currAmmo;
  bool automatic;
};

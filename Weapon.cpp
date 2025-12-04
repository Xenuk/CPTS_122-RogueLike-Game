/*
File Name: Weapon.cpp
Created: 11/28/2025
Purpose: Implementation for Weapon class
*/

#include "Weapon.hpp"
#include "Header.hpp"

Weapon::Weapon(std::string nName, int nDamage, double nLifeTime,
               int nCooldown, int nAmmo, int nReloadTime, bool nAutomatic)
    : name(nName), damage(nDamage), lifeTime(nLifeTime), cooldown(nCooldown),
      ammo(nAmmo), reloadTime(nReloadTime), automatic(nAutomatic) {
  this->currAmmo = nAmmo;
  std::cout << "Weapon Constructor Called. Cooldown: " << cooldown
            << " Ammo: " << ammo << "Current Ammo:" << currAmmo << std::endl;
}

Weapon::~Weapon() { std::cout << "Weapon Destructor Called." << std::endl; }

std::string Weapon::getName() const { return name; }

int Weapon::getDamage() const { return damage; }
double Weapon::getLifeTime() const { return lifeTime; }
int Weapon::getCooldown() const { return cooldown; }

int Weapon::getAmmo() const { return ammo; }
int Weapon::getCurrAmmo() const { return currAmmo; }

int Weapon::getReloadTime() const { return reloadTime; }
bool Weapon::isAutomatic() const { return automatic; }

void Weapon::setName(std::string nName) { name = nName; }
void Weapon::setDamage(int nDamage) { damage = nDamage; }

void Weapon::setLifeTime(double nLifeTime) { lifeTime = nLifeTime; }
void Weapon::setCooldown(int nCooldown) { cooldown = nCooldown; }

void Weapon::setAmmo(int nAmmo) { ammo = nAmmo; }
void Weapon::setCurrAmmo(int nCurrAmmo) { currAmmo = nCurrAmmo; }

void Weapon::setReloadTime(int nReloadTime) { reloadTime = nReloadTime; }
void Weapon::setAutomatic(bool nAutomatic) { automatic = nAutomatic; }
void Weapon::deincrementCurrAmmo() 
{
  if (this->currAmmo > 0){
    currAmmo--;
  }
}

void Weapon::reload() {
  currAmmo = ammo;
}

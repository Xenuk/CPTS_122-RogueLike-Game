/*
File Name: Save.hpp
Created: 12/3/2025
Purpose: Projectile content file, decs. Handles saving info and progress.
*/

#pragma once
#include "Header.hpp"

class Save
{

public:
    Save();

    void load();     // Load from Save.csv
    void save() const;  // Save to Save.csv

    // Getters
    int getScore() const { return score; }
    int getDmg()   const { return dmgLevel; }
    int getHlth()  const { return hlthLevel; }
    int getSpd()   const { return spdLevel; }
    int getProj()  const { return projLevel; }
    // Setters
    void setScore(int newScore) { score = newScore; }
    void setDmg(int newDmg) { dmgLevel = newDmg; }
    void setHlth(int newHealth) { hlthLevel = newHealth; }
    void setSpd(int newSpd) { spdLevel = newSpd; }
    void setProj(int newProj) { projLevel = newProj; }
    // Modifiers
    void addScore(int v) { score += v; }
    void addDmg(int v) { dmgLevel += v; }
    void addHlth(int v) { hlthLevel += v; }
    void addSpd(int v) { spdLevel += v; }
    void addProj(int v) { projLevel += v; }

    void subScore(int v) { score -= v; }
    void subDmg(int v) { dmgLevel -= v; }
    void subHlth(int v) { hlthLevel -= v; }
    void subSpd(int v) { spdLevel -= v; }
    void subProj(int v) { projLevel -= v; }

    
private:
    int score;
    int dmgLevel;
    int hlthLevel;
    int spdLevel;
    int projLevel;

}; 

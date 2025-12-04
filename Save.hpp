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

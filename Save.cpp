/*
File Name: Save.cpp
Created: 12/3/2025
Purpose: Save content file, definitions.
*/

#include "Save.hpp"
#include "Header.hpp"


Save::Save()
    : score(0), dmgLevel(0), hlthLevel(0),
    spdLevel(0), projLevel(0)

{
    load();  // Load automatically at start
}

void Save::load()
{
    std::ifstream file("Save.csv");

    if (!file.is_open())
    {
        std::cerr << "Save.csv not found.\n";
        return;
    }

    std::string line;
    if (std::getline(file, line))
    {

        std::stringstream ss(line);
        char comma;

        ss >> score >> comma
            >> dmgLevel >> comma
            >> hlthLevel >> comma
            >> spdLevel >> comma
            >> projLevel;
    }
}

void Save::save() const
{
    std::ofstream file("Save.csv");

    if (!file.is_open())
    {
        std::cerr << "Could not write to Save.csv.\n";
        return;
    }

    file << score << ","
        << dmgLevel << ","
        << hlthLevel << ","
        << spdLevel << ","
        << projLevel;

}

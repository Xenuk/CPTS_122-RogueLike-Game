/*
File Name: Game.hpp
Created: 11/21/2025
Purpose: This is the Game Header File, it contains the Game Class, and carries the main game interface.
*/

#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include "Header.hpp"
#include "GameObject.hpp"
#include "Projectile.hpp"

class Game
{

public:
	void introMenu();
	Game();
	~Game();
	void runGame();
	void createWindow(unsigned int nWidth, unsigned int nHeight);
	void drawToScreen();
	void projectileHandling();
	sf::Texture createTexture(std::string filepath);
	void mainMenu();
	void escapeMenu(bool& loopVariable);
	void guiInterface();
	sf::Font* createFont(std::string filepath);
	void weaponControls(Weapon* pistol, Weapon* rifle, Weapon* sniper);

private:

	unsigned int width;
	unsigned int height;
	std::vector<GameObject*> gameObjects;
	std::vector<Projectile*> projectiles;
	std::vector<sf::Text*> guiInterfaceArray;
	std::vector<sf::Font*> fontArray;
	sf::RenderWindow* window;
};


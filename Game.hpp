/*
File Name: Game.hpp
Created: 11/21/2025
Purpose: Fill This In
*/

#pragma once
#include "Header.hpp"
#include "GameObject.hpp"
#include "Projectile.hpp"


class Game
{

public:

	Game();
	~Game();
	void runGame();
	void createWindow(unsigned int nWidth, unsigned int nHeight);
	void drawToScreen();
	void projectileHandling();
	sf::Texture createTexture(std::string filepath);
	void mainMenu();
	void escapeMenu(bool& loopVariable);

private:

	unsigned int width;
	unsigned int height;
	std::vector<GameObject*> gameObjects;
	std::vector<Projectile*> projectiles;

	sf::RenderWindow* window;
};

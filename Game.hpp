#pragma once
#include "header.hpp"
#include "GameObject.hpp"
#include "Projectile.hpp"
class Game {

public:
	Game();
	~Game();
	void runGame();
	void createWindow(unsigned int nWidth, unsigned int nHeight);
	void drawToScreen();
	void projectileHandling();
	sf::Texture createTexture(std::string filepath);

private:
	unsigned int width;
	unsigned int height;
	std::vector<GameObject*> gameObjects;
	std::vector<Projectile*> projectiles;

	sf::RenderWindow* window;
};
/*
File Name: Game.cpp
Created: 11/21/2025
Purpose: Fill in
*/

#include "Game.hpp"


Game::Game()
{

}
Game::~Game()
{

}
void Game::runGame()
{
	createWindow(320, 240);

	int projectileTime = 0; // used for cooldown
	sf::Texture texture = createTexture("Sprites/ExampleSprite.png");
	sf::Texture texture2 = createTexture("Sprites/ExampleSpriteWall.png"); // static allocation so perhaps make it dynamic in the future if needed?
	sf::Texture texture3 = createTexture("Sprites/ExampleBullet.png");
	GameObject* newGameguy = new GameObject(texture, 10, 10, 10, 20,1);

	GameObject* newWallGuy = new GameObject(texture2, 10, 10, 10, 0,0);
	newGameguy->setOrigin({ 8,8 });
	newGameguy->setPosition({ 100,100 });
	gameObjects.push_back(newGameguy); // pushes it to the back of the vector.
	gameObjects.push_back(newWallGuy);
	Projectile* proj2 = nullptr;
	newWallGuy->setOrigin({ 8,8 });
	newWallGuy->setPosition({ 160,120 });
	while (window->isOpen())
	{
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
			}

		}

		newGameguy->characterMoveControls();


		if (window->hasFocus())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{	
				
				if (newGameguy->projectileCooldown <= projectileTime) // rework cooldown system.
				{
					// calculates based on world coords not pixels for accuracy.
					proj2 = newGameguy->shootProjectile(window,texture3,2,10,40);
					projectiles.push_back(proj2);
					projectileTime = 0;
				}
			}
		}
		projectileTime++; // for cooldown system, rework later.

		projectileHandling();
		drawToScreen();

	}
}
void Game::createWindow(unsigned int nWidth, unsigned int nHeight)
{
	height = nHeight;
	width = nWidth;
	sf::RenderWindow* newWindow = new sf::RenderWindow(sf::VideoMode({ width,height }), "Game");
	window = newWindow;
	window->setFramerateLimit(60); // everything scales off of frames so try to figure out a way to not get that.

}
void Game::drawToScreen()
{
	// creates a camera that follows the player(gameObject 1) based on window height and width.
	window->setView(sf::View({ gameObjects[0]->getPosition().x,gameObjects[0]->getPosition().y}, {static_cast<float>(width),static_cast<float>(height)}));
	// draw below this function
	window->clear(sf::Color::White);

	for (int i = 0; i < gameObjects.size(); i++) // same as below but with game objects
	{
		window->draw(*gameObjects[i]);
	}
	for (int i = 0; i < projectiles.size(); i++) // draws all the projectiles that were dynamically allocated
	{
		window->draw(*projectiles[i]);
	}
	window->display();
	// draw above this function
}
void Game::projectileHandling() // possibly rework and remove depending on what would be better
{
	// deletes based on life time which is range, which is set to a int based on framerate, 60 frame per sec.
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->currLifeTime++;
		if (projectiles[i]->currLifeTime >= projectiles[i]->lifeTime)
		{
			projectiles.erase(projectiles.begin() + i);
		}
	}
	// moves projectiles.
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->move(projectiles[i]->directionAndSpeed);
	}

}
sf::Texture Game::createTexture(std::string filepath) // possibly useless but cleans up the code.
{
	sf::Texture texture = sf::Texture(); // static not dynamic so possible problems in future.
	if (!texture.loadFromFile(filepath))
	{
		std::cout << "error loading sprite" << std::endl;
	}
	return texture;
}

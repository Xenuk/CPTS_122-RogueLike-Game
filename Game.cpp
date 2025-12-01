/*
File Name: Game.cpp
Created: 11/21/2025
Purpose: Fill in
*/

#include "Game.hpp"


Game::Game()
{
std::cout << "Game constructor called.\n" << std::endl;
}
Game::~Game()
{
std::cout << "Game Destructor called.\n" << std::endl;
}
void Game::runGame()
{
	createWindow(320, 240);

	int projectileTime = 0; // used for cooldown
	sf::Texture texture = createTexture("Sprites/ExampleSprite.png");
	sf::Texture texture2 = createTexture("Sprites/ExampleSpriteWall.png"); // static allocation so perhaps make it dynamic in the future if needed?
	sf::Texture texture3 = createTexture("Sprites/ExampleBullet.png");

	Weapon* pistol = new Weapon("pistol", 10, 30, 30, 20, true);
	Weapon* rifle = new Weapon("rifle", 20, 40, 10, 40, true);
	Weapon* sniper = new Weapon("sniper", 30, 60, 60, 5, true);
	GameObject* newGameguy = new GameObject(texture, 10, 10, 10, 20,1, pistol);

	GameObject* newWallGuy = new GameObject(texture2, 10, 10, 10, 0,0, pistol);

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
        if (newGameguy->getCurrWeapon()->getAmmo() == -1 || newGameguy->getCurrWeapon()->getCurrAmmo() > 0)
        {
          if (newGameguy->getCurrWeapon()->getCooldown() <= projectileTime) // rework cooldown system.
          // if (10 <= projectileTime) // rework cooldown system.
          {
            // calculates based on world coords not pixels for accuracy.
            proj2 = newGameguy->shootProjectile(window,texture3,2,10,40);
            newGameguy->getCurrWeapon()->deincrementCurrAmmo();
            std::cout << "Current Ammo: " << newGameguy->getCurrWeapon()->getCurrAmmo() << std::endl;
            projectiles.push_back(proj2);
            projectileTime = 0;
          }
        }
        else
        {
          std::cout << "Ammo depleted" << std::endl;
        }
			}
		}
		// Reloading
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
			{
		      // newGameguy->getCurrWeapon()->setCurrAmmo(newGameguy->getCurrWeapon()->getAmmo());
		      newGameguy->getCurrWeapon()->reload();
		      std::cout << "Reloaded. Current Ammo: " << newGameguy->getCurrWeapon()->getCurrAmmo() << std::endl;
			}

      // Weapon Switching
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
			{
		      newGameguy->setCurrWeapon(pistol);
          std::cout << "Switched to pistol" << std::endl;
			}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
      {
          newGameguy->setCurrWeapon(rifle);
          std::cout << "Switched to rifle" << std::endl;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
      {
          newGameguy->setCurrWeapon(sniper);
          std::cout << "Switched to sniper" << std::endl;
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
void Game::projectileHandling()
{
	for (int i = static_cast<int>(projectiles.size()) - 1; i >= 0; --i)
	{
		double curr = projectiles[i]->getCurrLifeTime();
		projectiles[i]->setCurrLifeTime(curr + 1.0);

		if (projectiles[i]->getCurrLifeTime() >= projectiles[i]->getLifeTime())
		{
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
		}
	}

	for (auto *p : projectiles)
	{
		p->move(p->getDirectionAndSpeed());
	}

}
sf::Texture Game::createTexture(std::string filepath) // possibly useless but cleans up the code.
{
	sf::Texture texture = sf::Texture(); // static not dynamic so possible problems in future.
	if (!texture.loadFromFile(filepath))
	{
		std::cout << "Error loading sprite" << std::endl;
	}
	return texture;
}

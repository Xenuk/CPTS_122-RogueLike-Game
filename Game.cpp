#include "Game.hpp"

sf::Clock globalClock; // global clock

void Game::escapeMenu(bool& loopVariable) // do relative camera menu.
{
	sf::Texture playButtonTexture = createTexture("Sprites/PlayButton.png");
	sf::Sprite playButton(playButtonTexture);
	playButton.setOrigin({ 47,10 });
	playButton.setPosition({ gameObjects[1]->getPosition().x,gameObjects[1]->getPosition().y - 50 });
	playButton.setScale({ 1,1 });

	sf::Texture settingsButtonTexture = createTexture("Sprites/SettingsButton.png");
	sf::Sprite settingsButton(settingsButtonTexture);
	settingsButton.setOrigin({ 47,10 });
	settingsButton.setPosition({ gameObjects[1]->getPosition().x, gameObjects[1]->getPosition().y }); // gets relative position.
	settingsButton.setScale({ 1,1 });

	sf::Texture exitButtonTexture = createTexture("Sprites/ExitButton.png");
	sf::Sprite exitButton(exitButtonTexture);
	exitButton.setOrigin({ 47,10 });
	exitButton.setPosition({ gameObjects[1]->getPosition().x,gameObjects[1]->getPosition().y + 50 });
	exitButton.setScale({ 1,1 });
	bool loop = true;
	int input = 0;
	while (window->isOpen() && loop)
	{
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
			}

		}

		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window)); // lotsa reused code.
		if (window->hasFocus())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (playButton.getGlobalBounds().contains(mousePos))
				{
					input = 1;
				}
				else if (settingsButton.getGlobalBounds().contains(mousePos))
				{
					input = 2;
				}
				else if (exitButton.getGlobalBounds().contains(mousePos))
				{
					input = 3;
				}
			}


		}
		switch (input)
		{
		case 1: // resume
			

			break;
		case 2: // settings

			break;
		case 3: // exit
			loop = false;
			loopVariable = false;// exit the gameloop somehow
			break;
		}
		window->draw(playButton);
		window->draw(settingsButton);
		window->draw(exitButton);
		window->display();
	}
}
void Game::mainMenu()
{
	createWindow(320, 180); // creates 1920x1080 window with a view that is 320 by 180.

	sf::Time elapsed1 = globalClock.getElapsedTime();
	std::cout << "Main Menu Opened At: " << elapsed1.asSeconds() << "s" << std::endl; // Functional Running Time Clock
	//sf::Clock globalClock.restart();

	sf::Texture backGroundTexture = createTexture("Sprites/SpriteMap.png");
	sf::Sprite backGround(backGroundTexture);
	backGround.setOrigin({ 500,450 });
	backGround.setPosition({ 960,540 });
	backGround.setScale({ 6,6 });

	sf::Texture playButtonTexture = createTexture("Sprites/PlayButton.png");
	sf::Sprite playButton(playButtonTexture);
	playButton.setOrigin({ 47,10 });
	playButton.setPosition({ 960,200 });
	playButton.setScale({ 5,5 });

	sf::Texture shopButtonTexture = createTexture("Sprites/ShopButton.png");
	sf::Sprite shopButton(shopButtonTexture);
	shopButton.setOrigin({ 47,10 });
	shopButton.setPosition({ 960,400 });
	shopButton.setScale({ 5,5 });

	sf::Texture settingsButtonTexture = createTexture("Sprites/SettingsButton.png");
	sf::Sprite settingsButton(settingsButtonTexture);
	settingsButton.setOrigin({ 47,10 });
	settingsButton.setPosition({ 960,600 });
	settingsButton.setScale({ 5,5 });

	sf::Texture exitButtonTexture = createTexture("Sprites/ExitButton.png");
	sf::Sprite exitButton(exitButtonTexture);
	exitButton.setOrigin({ 47,10 });
	exitButton.setPosition({ 960,800 });
	exitButton.setScale({ 5,5 });

	// variables
	int input = 0;
	bool exit = false;
	while (window->isOpen() && !exit)
	{
		window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
			}

		}
		if (window->hasFocus())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (playButton.getGlobalBounds().contains(mousePos))
				{
					input = 1;
				}
				else if (shopButton.getGlobalBounds().contains(mousePos))
				{
					input = 2;
				}
				else if (settingsButton.getGlobalBounds().contains(mousePos))
				{
					input = 3;
				}
				else if (exitButton.getGlobalBounds().contains(mousePos))
				{
					input = 4;
				}
			}


		}
		switch (input)
		{
		case 1: // stages
			runGame();

			break;
		case 2: // shop

			break;
		case 3: // settings

			break;
		case 4: // exit
			exit = true;
			break;
		}
		input = 0;
		window->clear(sf::Color::Black);
		window->draw(backGround);
		window->draw(playButton);
		window->draw(shopButton);
		window->draw(exitButton);
		window->draw(settingsButton);
		window->display();
	}
}
Game::Game()
{

}
Game::~Game()
{

}

void Game::runGame()
{
	// createWindow(320, 180);
	sf::Time elapsed1 = globalClock.getElapsedTime();
	std::cout << "Game Running Start Time: " << elapsed1.asSeconds() << "s" << std::endl;
	
	int projectileTime = 0; // used for cooldown
	sf::Texture map = createTexture("Sprites/SpriteMap.png");
	sf::Texture texture = createTexture("Sprites/cat.png");
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

	Projectile* proj2 = nullptr;
	newWallGuy->setOrigin({ 8,8 });
	newWallGuy->setPosition({ -160,-120 });

	bool gameState = true;

	while (window->isOpen() && gameState)
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			escapeMenu(gameState); // freezes everything because its a while loop in itself. this is glitchy so make game logic work on a timer rather than fps. 
			// Then we can pause time with this.
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

void Game::createWindow(unsigned int nWidth, unsigned int nHeight) // This is the actual game start
{
	sf::Time elapsed1 = globalClock.getElapsedTime();
	std::cout << "CreatWindow Called At: " << elapsed1.asSeconds() << "s" << endl;
	height = nHeight;
	width = nWidth;
	sf::RenderWindow* newWindow = new sf::RenderWindow(sf::VideoMode({ 1920,1080 }), "Game");
	std::cout << "Window Rendered: Height = " << height << ", Width = " << width << ". " << std::endl;

	window = newWindow;
	window->setFramerateLimit(60); // everything scales off of frames so try to figure out a way to not get that.
	std::cout << "Frame Rate Limit = 60. " << std::endl;

}

void Game::drawToScreen()
{
	// creates a camera that follows the player(gameObject 1) based on window height and width.
	window->setView(sf::View({ gameObjects[1]->getPosition().x,gameObjects[1]->getPosition().y }, { static_cast<float>(width),static_cast<float>(height) }));
	// draw below this function
	window->clear(sf::Color::White);

	for (int i = 0; i < gameObjects.size(); i++) // same as below but with game objects
	{
		std::cout << "drawing gameObject" << endl;
		window->draw(*gameObjects[i]);
	}
	for (int i = 0; i < projectiles.size(); i++) // draws all the projectiles that were dynamically allocated
	{
		std::cout << "drawing projectile" << endl;
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
		std::cout << "error loading sprite" << std::endl;
	}
	return texture;
}

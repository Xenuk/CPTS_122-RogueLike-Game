#include "Game.hpp"

sf::Clock globalClock; // global clock
sf::Clock timeClock;

void Game::escapeMenu(bool& loopVariable)
{
	timeClock.stop();
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
			loop = false;

			break;
		case 2: // settings

			break;
		case 3: // exit
			loop = false;
			loopVariable = false;
			for (int i = 0; i > gameObjects.size(); i++)
			{
				delete gameObjects[i];

			}
			break;
		}
		window->draw(playButton);
		window->draw(settingsButton);
		window->draw(exitButton);
		window->display();
		
	}
	timeClock.start();
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
void Game::guiInterface() // this code is so bad im so sorry.
{
	int secs = 60;
	std::string minutes, seconds;
	guiInterfaceArray.resize(4, nullptr); // cant access a array 0 if it wasnt initalized so create the size then reassign the index.
	fontArray.resize(4, nullptr);
	if (secs - static_cast<int>(timeClock.getElapsedTime().asSeconds()) <= 0)
	{
		secs += 60;
	}
	if (guiInterfaceArray[0] == nullptr)
	{
		if (fontArray[0] == nullptr)
		{
			fontArray[0] = createFont("Fonts/Pixeled.ttf");
		}

		sf::Text* time = new sf::Text(*fontArray[0], "N/A", 16);
		if (9 - static_cast<int>(timeClock.getElapsedTime().asSeconds() / 60) <= 0)
		{
			minutes = std::to_string(0) + ":";
		}
		else
		{
			minutes = std::to_string(9 - static_cast<int>(timeClock.getElapsedTime().asSeconds() / 60)) + ":";
		}
		if (secs - static_cast<int>(timeClock.getElapsedTime().asSeconds()) < 10)
		{
			seconds = "0" + std::to_string(secs - static_cast<int>(timeClock.getElapsedTime().asSeconds()));
		}
		else
		{
			seconds = std::to_string(secs - static_cast<int>(timeClock.getElapsedTime().asSeconds()));
		}
		time->setString(minutes + seconds);
		time->setPosition({ gameObjects[1]->getPosition().x - 10, gameObjects[1]->getPosition().y - 80 });
		time->setScale({ 0.4,0.4 });
		guiInterfaceArray[0] = time;
	}
	else if (guiInterfaceArray[0] != nullptr)
	{

		if (9 - static_cast<int>(timeClock.getElapsedTime().asSeconds() / 60) <= 0)
		{
			minutes = std::to_string(0) + ":";
		}
		else
		{
			minutes = std::to_string(9 - static_cast<int>(timeClock.getElapsedTime().asSeconds() / 60)) + ":";
		}
		if (secs - static_cast<int>(timeClock.getElapsedTime().asSeconds()) < 10)
		{
			seconds = "0" + std::to_string(secs - static_cast<int>(timeClock.getElapsedTime().asSeconds()));
		}
		else
		{
			seconds = std::to_string(secs - static_cast<int>(timeClock.getElapsedTime().asSeconds()));
		}
		guiInterfaceArray[0]->setString(minutes + seconds);
		guiInterfaceArray[0]->setPosition({ gameObjects[1]->getPosition().x - 10, gameObjects[1]->getPosition().y - 80 });
	}
	if (guiInterfaceArray[1] == nullptr)
	{
		sf::Text* weaponGui = new sf::Text(*fontArray[0], "N/A", 16);
		sf::Text* weaponAmmoGui = new sf::Text(*fontArray[0], "N/A", 16);
		std::string weaponMaxAmmo = std::to_string(gameObjects[1]->getCurrWeapon()->getAmmo());
		std::string weaponCurrAmmo = std::to_string(gameObjects[1]->getCurrWeapon()->getCurrAmmo());
		std::string weapon = gameObjects[1]->getCurrWeapon()->getName();
		weaponGui->setPosition({ gameObjects[1]->getPosition().x + 80, gameObjects[1]->getPosition().y + 70 });
		weaponAmmoGui->setPosition({ gameObjects[1]->getPosition().x + 110, gameObjects[1]->getPosition().y + 70 });
		weaponGui->setScale({ 0.3,0.3 });
		weaponAmmoGui->setScale({ 0.3,0.3 });
		weaponGui->setString(weapon);
		weaponAmmoGui->setString(weaponCurrAmmo + "/" + weaponMaxAmmo);
		guiInterfaceArray[1] = weaponGui;
		guiInterfaceArray[2] = weaponAmmoGui;
	}
	else if (guiInterfaceArray[1] != nullptr)
	{
		std::string weaponMaxAmmo = std::to_string(gameObjects[1]->getCurrWeapon()->getAmmo());
		std::string weaponCurrAmmo = std::to_string(gameObjects[1]->getCurrWeapon()->getCurrAmmo());
		std::string weapon = gameObjects[1]->getCurrWeapon()->getName();
		guiInterfaceArray[1]->setString(weapon);
		guiInterfaceArray[2]->setString(weaponCurrAmmo + "/" + weaponMaxAmmo);
		guiInterfaceArray[1]->setPosition({ gameObjects[1]->getPosition().x + 100, gameObjects[1]->getPosition().y + 70 });
		guiInterfaceArray[2]->setPosition({ gameObjects[1]->getPosition().x + 130, gameObjects[1]->getPosition().y + 70 });
	}
	if (guiInterfaceArray[3] == nullptr)
	{

	}
	else if (guiInterfaceArray[3] != nullptr)
	{

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
	timeClock.restart();
	float totalTimeAccumulated = 0.0f;
	const float dt = 1.0f / 60.0f;  // had to use ai for this due to it being jittery as heck.
	float accumulator = 0.0f;		// all the time calc except for the clock.getElapsedTime stuff, was used with chatgpt.
									// the time shit fixxed the bug with the vibration when paused????
	std::vector<GameObject*> newGameObjectArr;
	gameObjects = newGameObjectArr;
	sf::Time elapsed1 = globalClock.getElapsedTime();
	std::cout << "Game Running Start Time: " << globalClock.getElapsedTime().asSeconds() << "s" << std::endl;
	
	int projectileTime = 0; // used for cooldown
  int touchDamageTime = 0;
	int enemyProjectileTime = 0; // used for cooldown
	sf::Texture map = createTexture("Sprites/SpriteMap.png");
	sf::Texture texture = createTexture("Sprites/cat.png");
	sf::Texture texture2 = createTexture("Sprites/ExampleSpriteWall.png"); // static allocation so perhaps make it dynamic in the future if needed?
	sf::Texture texture3 = createTexture("Sprites/ExampleBullet.png");
  sf::Texture texture4 = createTexture("Sprites/ExampleEnemy.png");

	Weapon* pistol = new Weapon("pistol", 10, 30, 30, 20, true);
	Weapon* rifle = new Weapon("rifle", 20, 40, 10, 40, true);
	Weapon* sniper = new Weapon("sniper", 30, 60, 60, 5, true);

	GameObject* newGameguy = new GameObject(texture, 100, 100, 10, 20, 1, pistol);
	GameObject* newWallGuy = new GameObject(map, 10, 10, 10, 0,0, pistol); // TODO: make walls not have weapons
  GameObject* newEnemyGuy = new GameObject(texture4, 100, 100, 1, 0, 0.5, pistol);

	newGameguy->setOrigin({ 8,8 });
	newGameguy->setPosition({ 100,100 });
	gameObjects.push_back(newWallGuy);
	gameObjects.push_back(newGameguy); // the layer is based on who was DRAWN last, so look at draw function. // pushes it to the back of the vector.
	gameObjects.push_back(newEnemyGuy);
	Projectile* proj2 = nullptr;
	newWallGuy->setOrigin({ 8,8 });
	newWallGuy->setPosition({ -160,-120 });
	newEnemyGuy->setOrigin({ 0,0 });
	newEnemyGuy->setPosition({ 150,150 });

	bool gameState = true;
	newGameguy->characterMoveControls();
	while (window->isOpen() && gameState)
	{
		float frameTime = globalClock.restart().asSeconds();
		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
			}

		}
		accumulator += frameTime;
		if(accumulator >= dt)
		{ 
			newGameguy->characterMoveControls();
			
			// Enemy Handling Logic
			const float aggroDistance = 75.0f;
			GameObject* player = newGameguy;	
      int gameObjectsIndex = 0;
			for (auto *obj : gameObjects) {
				// check if obj is player or non-moving object
        // NOTE: this logic will break if non-moving objects are added to gameObjects[]
	 			if (obj != player && obj->getMoveSpeed() > 0) {
					sf::Vector2f direction = player->getPosition() - obj->getPosition();
					float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
          // nomarlize the direction
          sf::Vector2f normalizedDirection = direction / distance;
          // move enemy if within range
					if (distance < aggroDistance) {
						float enemySpeed = 0.2f;
						obj->move(normalizedDirection * enemySpeed);
					}
          // if enemy touches player do damage
          if (obj->getGlobalBounds().contains(player->getPosition())) {
            if (10 <= touchDamageTime) {
              player->deincrementHealth(obj->getDamage());
              std::cout << "ENEMY DAMAGE TAKEN!" << std::endl;
              std::cout << "Current Health: " << player->getCurrHealth();
              touchDamageTime = 0;
            }
          }
          // check if any projectiles hit enemy
          int projIndex = 0;
          for (auto *proj : projectiles) {
            if (obj->getGlobalBounds().contains(proj->getPosition())) {
              obj->deincrementHealth(proj->getDamage());
              projectiles.erase(projectiles.begin() + projIndex); // ??? maybe ??? but maybe no???!!
              delete proj;
            }
            projIndex++;
          }
          // enemy shoots if within range
          //  if (distance < aggroDistance * 1.25) {
          //    if (obj->getCurrWeapon()) {
          //      if (obj->getCurrWeapon()->getCooldown() <= enemyProjectileTime) {
          //        proj2 = obj->shootProjectile(window, texture3, 2, 10, obj->getCurrWeapon()->getLifeTime());
          // projectiles.push_back(proj2);
          //        enemyProjectileTime = 0;
          //      }
          //    }
          //  }
          // check if enemy is dead
          if (obj->getCurrHealth() <= 0) {
            gameObjects.erase(gameObjects.begin() + gameObjectsIndex);
            delete obj;
          }
	 			}
        gameObjectsIndex++;
			}

			if (window->hasFocus())
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
          Weapon *currWeapon = newGameguy->getCurrWeapon();
					if (currWeapon->getAmmo() == -1 || currWeapon->getCurrAmmo() > 0)
					{
						if (currWeapon->getCooldown() <= projectileTime) // rework cooldown system.
						{
							// calculates based on world coords not pixels for accuracy.
							proj2 = newGameguy->shootProjectile(window, texture3, 2, currWeapon->getDamage(), currWeapon->getLifeTime());
							currWeapon->deincrementCurrAmmo();
							std::cout << "Current Ammo: " << currWeapon->getCurrAmmo() << std::endl;
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
				escapeMenu(gameState); // freezes everything because its a while loop in itself. 
			}
			guiInterface();
			weaponControls(pistol,rifle,sniper);
			projectileTime++; // for cooldown system, rework later.
      enemyProjectileTime++;
      touchDamageTime++;
			accumulator -= dt;
			projectileHandling();
		}
		drawToScreen();
		}
}
void Game::weaponControls(Weapon* pistol, Weapon* rifle, Weapon* sniper)
{
	// Reloading
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
	{
		// newGameguy->getCurrWeapon()->setCurrAmmo(newGameguy->getCurrWeapon()->getAmmo());
		gameObjects[1]->getCurrWeapon()->reload();
		std::cout << "Reloaded. Current Ammo: " << gameObjects[1]->getCurrWeapon()->getCurrAmmo() << std::endl;
	}

	// Weapon Switching
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		gameObjects[1]->setCurrWeapon(pistol);
		std::cout << "Switched to pistol" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	{
		gameObjects[1]->setCurrWeapon(rifle);
		std::cout << "Switched to rifle" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
	{
		gameObjects[1]->setCurrWeapon(sniper);
		std::cout << "Switched to sniper" << std::endl;
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
	// window->setFramerateLimit(60);
	window = newWindow;

}

void Game::drawToScreen()
{
	// creates a camera that follows the player(gameObject 1) based on set window view height and width from createWindow func.
	window->setView(sf::View({ gameObjects[1]->getPosition().x,gameObjects[1]->getPosition().y}, {static_cast<float>(width),static_cast<float>(height)}));
	// draw below this function
	window->clear(sf::Color::White);

	for (int i = 0; i < gameObjects.size(); i++) // same as below but with game objects
	{
		// std::cout << "drawing gameObject" << endl;
		window->draw(*gameObjects[i]);
	}
	for (int i = 0; i < projectiles.size(); i++) // draws all the projectiles that were dynamically allocated
	{
		// std::cout << "drawing projectile" << endl;
		window->draw(*projectiles[i]);
	}
	for (int i = 0; i < guiInterfaceArray.size(); i++) // draws all the text for the gui.
	{
		if (guiInterfaceArray[i] != nullptr)
		{
			// std::cout << "drawing gui interface" << endl;
			window->draw(*guiInterfaceArray[i]);
		}
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
sf::Font* Game::createFont(std::string filepath)
{
	sf::Font* font = new sf::Font();
	if (!font->openFromFile(filepath))
	{
		cout << "Error loading font from file.\n";
	}
	return font;
}
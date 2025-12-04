/*
File Name: Game.cpp
Created: 11/21/2025
Purpose: This is the Game content File, it contains the Game Class, and carries the main game interface.
*/

#include "Game.hpp"
#include <random>
#include <ctime>
#include <cmath>
sf::Clock globalClock; // global clock
sf::Clock timeClock;
static bool secsFlag = true;
Save save; // Save load

bool flag = false;
// based off of view of character 320 by 180 or smth like that

// Save/Shop/Score Handling here

 // Internal Globals to hold info while ingame
int score;
int dmgLevel;
int hlthLevel;
int spdLevel;
int projLevel;
// based off of view of character 320 by 180 or smth like that

//

void Game::escapeMenu(bool& loopVariable)
{
	timeClock.stop();
	sf::Texture playButtonTexture = createTexture("Sprites/PlayButton.png");
	sf::Sprite playButton(playButtonTexture);
	playButton.setOrigin({ 47,10 });
	playButton.setPosition({ gameObjects[2]->getPosition().x,gameObjects[2]->getPosition().y - 50 });
	playButton.setScale({ 1,1 });

	sf::Texture settingsButtonTexture = createTexture("Sprites/SettingsButton.png");
	sf::Sprite settingsButton(settingsButtonTexture);
	settingsButton.setOrigin({ 47,10 });
	settingsButton.setPosition({ gameObjects[2]->getPosition().x, gameObjects[2]->getPosition().y }); // gets relative position.
	settingsButton.setScale({ 1,1 });

	sf::Texture exitButtonTexture = createTexture("Sprites/ExitButton.png");
	sf::Sprite exitButton(exitButtonTexture);
	exitButton.setOrigin({ 47,10 });
	exitButton.setPosition({ gameObjects[2]->getPosition().x,gameObjects[2]->getPosition().y + 50 });
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



//

// based on 1920 by 1080
// based on 1920 by 1080
void Game::mainMenu() // Main Menu Start (First Thing the Player Sees)
{
	createWindow(320, 180); // creates 1920x1080 window with a view that is 320 by 180.

	std::ofstream ofile("Save.csv"); // Save-to-file
	std::ifstream ifile("Save.csv"); // load from file

	score = save.getScore();
	dmgLevel = save.getDmg();
	hlthLevel = save.getHlth();
	spdLevel = save.getSpd();
	projLevel = save.getProj();

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
	float delay = 0;

	while (window->isOpen() && !exit) // Main menu loop
	{
		window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
		while (timeClock.getElapsedTime().asSeconds() < delay); // so that inputs dont overlap.
		// essentially if you click exit on pause menu it would exit the whole game due to the input being held down.
		{
		}
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
			}

		}

		if (window->hasFocus()) // Get bounds for selecting options
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

		switch (input) // Pick an option here
		{
		case 1: // stages
			runGame();
			delay = timeClock.getElapsedTime().asSeconds() + .5;
			// sets delay so it waits before checking stuff again.
			window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
			// this fixed the view taking too long to update.
			break;
		case 2: // shop
			shopMenu();
			delay = timeClock.getElapsedTime().asSeconds() + .5;
			// sets delay so it waits before checking stuff again.
			window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
			break;
		case 3: // settings

			break;
		case 4: // exit

			save.addScore(score - save.getScore());
			save.addDmg(dmgLevel - save.getDmg());
			save.addHlth(hlthLevel - save.getHlth());
			save.addSpd(spdLevel - save.getSpd());
			save.addProj(projLevel - save.getProj());

			save.save(); // I think this will save your stats before you leave(?) System is somewhat open

			exit = true;
			break;
		}

		input = 0;
		window->clear(sf::Color::Black);
		window->draw(backGround); // Render buttons
		window->draw(playButton);
		window->draw(shopButton);
		window->draw(exitButton);
		window->draw(settingsButton);
		window->display();

	}
}  // Main Menu End

void Game::guiInterface() // Escape Menu Start (After starting, click Esc to enter)
{
	static int secs;
	if (secsFlag)
	{
		secs = 60;
	}
	std::string minutes, seconds;
	guiInterfaceArray.resize(8, nullptr); // cant access a array 0 if it wasnt initalized so create the size then reassign the index.
	fontArray.resize(4, nullptr);

	if (secs - static_cast<int>(timeClock.getElapsedTime().asSeconds()) <= 0)
	{
		secsFlag = false;
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
		time->setPosition({ gameObjects[2]->getPosition().x - 10, gameObjects[2]->getPosition().y - 80 });
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
		guiInterfaceArray[0]->setPosition({ gameObjects[2]->getPosition().x - 10, gameObjects[2]->getPosition().y - 80 });
	}

	if (guiInterfaceArray[1] == nullptr)
	{
		sf::Text* weaponGui = new sf::Text(*fontArray[0], "N/A", 16);
		sf::Text* weaponAmmoGui = new sf::Text(*fontArray[0], "N/A", 16);
		std::string weaponMaxAmmo = std::to_string(gameObjects[2]->getCurrWeapon()->getAmmo());
		std::string weaponCurrAmmo = std::to_string(gameObjects[2]->getCurrWeapon()->getCurrAmmo());
		std::string weapon = gameObjects[2]->getCurrWeapon()->getName();
		weaponGui->setPosition({ gameObjects[2]->getPosition().x + 100, gameObjects[2]->getPosition().y + 80 });
		weaponAmmoGui->setPosition({ gameObjects[2]->getPosition().x + 130, gameObjects[2]->getPosition().y + 80 });
		weaponGui->setScale({ 0.3,0.3 });
		weaponAmmoGui->setScale({ 0.3,0.3 });
		weaponGui->setString(weapon);
		weaponAmmoGui->setString(weaponCurrAmmo + "/" + weaponMaxAmmo);
		guiInterfaceArray[1] = weaponGui;
		guiInterfaceArray[2] = weaponAmmoGui;
	}

	else if (guiInterfaceArray[1] != nullptr)
	{
		std::string weaponMaxAmmo = std::to_string(gameObjects[2]->getCurrWeapon()->getAmmo());
		std::string weaponCurrAmmo = std::to_string(gameObjects[2]->getCurrWeapon()->getCurrAmmo());
		std::string weapon = gameObjects[2]->getCurrWeapon()->getName();
		guiInterfaceArray[1]->setString(weapon);
		guiInterfaceArray[2]->setString(weaponCurrAmmo + "/" + weaponMaxAmmo);
		guiInterfaceArray[1]->setPosition({ gameObjects[2]->getPosition().x + 100, gameObjects[2]->getPosition().y + 80 });
		guiInterfaceArray[2]->setPosition({ gameObjects[2]->getPosition().x + 130, gameObjects[2]->getPosition().y + 80 });
	}

	if (guiInterfaceArray[3] == nullptr)
	{
		sf::Text* scoreGui = new sf::Text(*fontArray[0], "N/A", 16);
		sf::Text* scoreNumberGui = new sf::Text(*fontArray[0], "N/A", 16);
		std::string scoreString = std::to_string(gameObjects[2]->getScore());
		scoreGui->setString("SCORE: ");
		scoreGui->setScale({ 0.3,0.3 });
		scoreGui->setPosition({ gameObjects[2]->getPosition().x - 130, gameObjects[2]->getPosition().y - 80 });
		scoreNumberGui->setString(scoreString);
		scoreNumberGui->setScale({ 0.3,0.3 });
		scoreNumberGui->setPosition({ gameObjects[2]->getPosition().x - 100, gameObjects[2]->getPosition().y - 80 });
		guiInterfaceArray[3] = scoreGui;
		guiInterfaceArray[4] = scoreNumberGui;
	}

	else if (guiInterfaceArray[3] != nullptr)
	{
		std::string scoreString = std::to_string(gameObjects[2]->getScore());
		guiInterfaceArray[4]->setString(scoreString);
		guiInterfaceArray[3]->setPosition({gameObjects[2]->getPosition().x - 150, gameObjects[2]->getPosition().y - 80});
		guiInterfaceArray[4]->setPosition({ gameObjects[2]->getPosition().x - 120, gameObjects[2]->getPosition().y - 80 });
	}
} // GUI Interface End

Game::Game() {}
Game::~Game() {}

void Game::runGame() // Main Game Loop
{

	timeClock.restart();

	std::vector<GameObject*> newGameObjectArr;
	gameObjects = newGameObjectArr;
	std::cout << "Game Running Start Time: " << globalClock.getElapsedTime().asSeconds() << "s" << std::endl;

	int projectileTime = 0; // used for cooldown
	int reloadTime = 0;
	int touchDamageTime = 0;
	int enemyProjectileTime = 0; // used for cooldown
	sf::Texture map = createTexture("Sprites/SpriteMap.png");
	sf::Texture texture = createTexture("Sprites/cat.png");
	sf::Texture texture2 = createTexture("Sprites/ExampleSpriteWall.png"); // static allocation so perhaps make it
	// dynamic in the future if needed?
	sf::Texture texture3 = createTexture("Sprites/ExampleBullet.png");
	sf::Texture texture4 = createTexture("Sprites/ExampleEnemy.png");
	sf::Texture rightWallTexture = createTexture("Sprites/MapRightWall.png");
	sf::Texture leftWallTexture = createTexture("Sprites/MapLeftWall.png");
	sf::Texture topWallTexture = createTexture("Sprites/MapTopWall.png");
	sf::Texture bottomWallTexture = createTexture("Sprites/MapBottomWall.png");
	sf::Texture bottomRightWallTexture = createTexture("Sprites/MapRightBottom.png");
	sf::Texture bottomLeftWallTexture = createTexture("Sprites/MapLeftBottom.png");
	sf::Texture topRightWallTexture = createTexture("Sprites/MapRightTop.png");
	sf::Texture topLeftWallTexture = createTexture("Sprites/MapLeftTop.png");
	Weapon* pistol = new Weapon("pistol", 10, 30, 30, 20, 30, true);
	Weapon* rifle = new Weapon("rifle", 20, 40, 10, 40, 90, true);
	Weapon* sniper = new Weapon("sniper", 30, 60, 60, 5, 120,true);


	GameObject* newGameguy = new GameObject(texture, 100, 100, 10, 20, 1, pistol, 0);
	GameObject* newWallGuy = new GameObject(map, 10, 10, 10, 0, 0, pistol, 0); // TODO: make walls not have weapons
	GameObject* newEnemyGuy = new GameObject(texture4, 100, 100, 1, 0, 0.5, pistol, 10);
	GameObject* rightWall = new GameObject(rightWallTexture, 10, 10, 0, 0, 0, pistol, 0);
	GameObject* topWall = new GameObject(topWallTexture, 10, 10, 0, 0, 0, pistol, 0);
	GameObject* bottomWall = new GameObject(bottomWallTexture, 10, 10, 0, 0, 0, pistol, 0);
	GameObject* leftWall = new GameObject(leftWallTexture, 10, 10, 0, 0, 0, pistol, 0);
	GameObject* rightBottomWall = new GameObject(bottomRightWallTexture, 10, 10, 0, 0, 0, pistol, 0);
	GameObject* rightTopWall = new GameObject(topRightWallTexture, 10, 10, 0, 0, 0, pistol, 0);
	GameObject* leftTopWall = new GameObject(topLeftWallTexture, 10, 10, 0, 0, 0, pistol, 0);
	GameObject* leftBottomWall = new GameObject(bottomLeftWallTexture, 10, 10, 0, 0, 0, pistol, 0);

	newGameguy->setOrigin({ 8,8 });
	newGameguy->setPosition({ 400,400 });
	gameObjects.push_back(newWallGuy);
	gameObjects.push_back(topWall);
	gameObjects.push_back(newGameguy); // the layer is based on who was DRAWN last, so look at draw function. // pushes it to the back of the vector.
	gameObjects.push_back(rightWall);
	gameObjects.push_back(leftWall);
	gameObjects.push_back(bottomWall);
	gameObjects.push_back(rightTopWall);
	gameObjects.push_back(rightBottomWall);
	gameObjects.push_back(leftTopWall);
	gameObjects.push_back(leftBottomWall);
	Projectile* proj2 = nullptr;
	// wall positions
	newWallGuy->setOrigin({ 0,0 });
	newWallGuy->setPosition({ 0,0 });
	rightWall->setOrigin({ 0,0 });
	rightWall->setPosition({ 1024,0 });
	leftWall->setOrigin({ 0,0 });
	leftWall->setPosition({ -1024,0 });
	topWall->setOrigin({ 0,0 });
	topWall->setPosition({ 0,-944 });
	bottomWall->setOrigin({ 0,0 });
	bottomWall->setPosition({ 0,944 });
	newWallGuy->setOrigin({ 0,0 });
	newWallGuy->setPosition({ 0,0 });

	rightTopWall->setOrigin({ 0,0 });
	rightTopWall->setPosition({ 1024,-944 });
	leftTopWall->setOrigin({ 0,0 });
	leftTopWall->setPosition({ -1024,-944 });
	rightBottomWall->setOrigin({ 0,0 });
	rightBottomWall->setPosition({ 1024,944 });
	leftBottomWall->setOrigin({ 0,0 });
	leftBottomWall->setPosition({ -1024,944 });

	newEnemyGuy->setOrigin({ 0,0 });
	newEnemyGuy->setPosition({ 150,150 });

	if (!flag) // Flag for showing intro or not
	{
		introMenu();
		flag = true;
	}

	const float dt = 1.0f / 60.0f; // had to use ai for this due to it being jittery as heck.
	float accumulator = 0.0f; // all the time calc except for the clock.getElapsedTime stuff, was
	// used with chatgpt. the time shit fixxed the bug with the
	// vibration when paused????

	// Enemy spawn controls
// NOTE: used AI for the rng
	float difficulty = 0;
	int spawnTimer = 0;
	int spawnInterval = 150;     // spawn every x ticks
	const float spawnRadius = 250.0f;  // spawn distance from player
	const float aggroDistance = 200.0f;
	static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));

	bool gameState = true;
	newGameguy->characterMoveControls(gameObjects);
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

		if (accumulator >= dt)
		{
			newGameguy->characterMoveControls(gameObjects);

			GameObject* player = newGameguy;
			int gameObjectsIndex = 0;



			if (window->hasFocus()) 
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
				{
					Weapon* currWeapon = newGameguy->getCurrWeapon();
					if (currWeapon->getAmmo() == -1 || currWeapon->getCurrAmmo() > 0) 
					{
						if (currWeapon->getCooldown() <= projectileTime && currWeapon->getReloadTime() < reloadTime) // rework cooldown system.
						{
							// calculates based on world coords not pixels for accuracy.
							proj2 = newGameguy->shootProjectile(window, texture3, 2,
								currWeapon->getDamage(),
								currWeapon->getLifeTime());
							currWeapon->deincrementCurrAmmo();
							std::cout << "Current Ammo: " << currWeapon->getCurrAmmo()
								<< std::endl;
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))  // Opens Escape Menu
			{
				escapeMenu(gameState); // freezes everything because its a while loop in
				// itself.
			}

			for (auto* obj : gameObjects)
			{
				// Enemy Handling Logic
				// check if obj is player or non-moving object
				// NOTE: this logic will break if non-moving objects are added to
				// gameObjects[]
				// TODO: add collision handling to enemies
				if (obj != player && obj->getMoveSpeed() > 0) 
				{
					sf::Vector2f direction = player->getPosition() - obj->getPosition();
					float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
					sf::Vector2f normalizedDirection;
					// nomarlize the direction
					if (distance != 0)
					{
						normalizedDirection = direction / distance;
					}
					else
					{
						normalizedDirection = direction / (distance + 1);
					}
					// move enemy if within range
					if (distance <= aggroDistance + 2500) { // added 2500 to create a essentially infinite agroDistance because changing the value is dangerous.
						float enemySpeed = obj->getMoveSpeed();
            bool collisionFlag = false;
            for (auto* collisionObj : gameObjects) {
              if (collisionObj == obj) continue;
              if (obj->getGlobalBounds().contains(collisionObj->getPosition())){
                collisionFlag = true;
                break;
              }
            }
						if (!collisionFlag) {
							obj->move(normalizedDirection * enemySpeed);
						} else {
							std::uniform_real_distribution<float> altDir(0.0f,
								2.0f * 3.14159265358979323846f);
							float altDirAngle = altDir(rng);
							sf::Vector2f randDir = { std::cos(altDirAngle), std::sin(altDirAngle) };
							obj->move(randDir * enemySpeed);
						}
					}
					// if enemy touches player do damage
					if (obj->getGlobalBounds().contains(player->getPosition()) && player->getCurrHealth() > 0) {
						if (10 <= touchDamageTime) {
							player->deincrementHealth(obj->getDamage());
							std::cout << "ENEMY DAMAGE TAKEN!" << std::endl;
							std::cout << "Current Health: " << player->getCurrHealth();
							touchDamageTime = 0;
						}
					}
					// check if any projectiles hit enemy
					int projIndex = 0;
					for (auto* proj : projectiles) 
					{
						if (obj->getGlobalBounds().contains(proj->getPosition())) 
						{
							// TODO: implement collision movement controls
							obj->deincrementHealth(proj->getDamage());
							projectiles.erase(projectiles.begin() +
								projIndex); // ??? maybe ??? but maybe no???!!
							delete proj;
						}
						projIndex++;
					}
					// enemy shoots if within range
					//  if (distance < aggroDistance * 1.25) {
					//    if (obj->getCurrWeapon()) {
					//      if (obj->getCurrWeapon()->getCooldown() <=
					//      enemyProjectileTime) {
					//        proj2 = obj->shootProjectile(window, texture3, 2, 10,
					//        obj->getCurrWeapon()->getLifeTime());
					// projectiles.push_back(proj2);
					//        enemyProjectileTime = 0;
					//      }
					//    }
					//  }
					// check if enemy is dead
					if (obj->getCurrHealth() <= 0) 
					{
						gameObjects.erase(gameObjects.begin() + gameObjectsIndex);
						gameObjects[2]->setScore(gameObjects[2]->getScore() + obj->getScore());
						delete obj;
					}
				}
				// Player Health logic
				if (obj == player) {
					if (obj->getCurrHealth() <= 0) 
					{
						score += gameObjects[2]->getScore();
						gameObjects.erase(gameObjects.begin() + gameObjectsIndex);
						delete obj;
						gameState = false;
					}
				}
				gameObjectsIndex++;

			}

			/*		if (static_cast<int>(timeClock.getElapsedTime().asSeconds()) % 10) {
						spawnInterval = spawnInterval - 5.0f;
					}
			*/
			// Enemy spawn timer and logic
		  // NOTE: used AI for this logic
			static int previous = -1;
			int currentTime = static_cast<int>(timeClock.getElapsedTime().asSeconds());
			if (previous != currentTime && currentTime >= 10 && currentTime % 10 == 0)
			{
				previous = currentTime;
				if (spawnInterval >= 50)
				{


					difficulty += 5;
					spawnInterval -= 5;
				}
				else
				{
					difficulty += 5;
					spawnInterval = 50;
				}
			}
			spawnTimer++;
			if (spawnTimer >= spawnInterval) 
			{
				spawnTimer = 0;
				std::uniform_real_distribution<float> angleDist(0.0f,
					2.0f * 3.14159265358979323846f);
				std::uniform_real_distribution<float> radiusDist(
					aggroDistance + 50.0f, spawnRadius);
				float angle = angleDist(rng);
				float radius = radiusDist(rng);
				sf::Vector2f spawnPos = player->getPosition() +
					sf::Vector2f(std::cos(angle) * radius,
						std::sin(angle) * radius);
				GameObject* spawnedEnemy =
					new GameObject(texture4, 100 + difficulty, 100 + difficulty, 5 + (difficulty / 25), 0, .5f + (difficulty / 200.0f), pistol, 10 + (difficulty / 5.0f));
				spawnedEnemy->setOrigin({ 8, 8 });
				spawnedEnemy->setPosition(spawnPos);
				gameObjects.push_back(spawnedEnemy);
				std::cout << "Spawned enemy at (" << spawnPos.x << ", " << spawnPos.y
					<< ")\n";
			}


			guiInterface();
			weaponControls(pistol, rifle, sniper, reloadTime);
			projectileTime++; // for cooldown system, rework later.
      reloadTime++;
			enemyProjectileTime++;
			touchDamageTime++;
			accumulator -= dt;
			projectileHandling();
		}
		drawToScreen();

	}
	for (int i = static_cast<int>(projectiles.size()) - 1; i >= 0; --i) // deletes projectiles after game is done.
	{
		delete projectiles[i];
		projectiles.erase(projectiles.begin() + i);
	}
	if (gameObjects[2] != nullptr)
	{
		score += gameObjects[2]->getScore();
	}
}

	

void Game::weaponControls(Weapon* pistol, Weapon* rifle, Weapon* sniper, int &reloadTime)
{
	// Reloading
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
	{
		// newGameguy->getCurrWeapon()->setCurrAmmo(newGameguy->getCurrWeapon()->getAmmo());
    reloadTime = 0;
		gameObjects[2]->getCurrWeapon()->reload();
		std::cout << "Reloaded. Current Ammo: " << gameObjects[2]->getCurrWeapon()->getCurrAmmo() << std::endl;
	}

	// Weapon Switching
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		gameObjects[2]->setCurrWeapon(pistol);
		std::cout << "Switched to pistol" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	{
		gameObjects[2]->setCurrWeapon(rifle);
		std::cout << "Switched to rifle" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
	{
		gameObjects[2]->setCurrWeapon(sniper);
		std::cout << "Switched to sniper" << std::endl;
	}
}
void Game::createWindow(unsigned int nWidth, unsigned int nHeight) // This is the actual game start
{
	sf::Time elapsed1 = globalClock.getElapsedTime();
	std::cout << "CreatWindow Called At: " << elapsed1.asSeconds() << "s" << endl;
	height = nHeight;
	width = nWidth;
	sf::RenderWindow* newWindow = new sf::RenderWindow(sf::VideoMode({ 1920,1080 }), "Game", sf::Style::Default, sf::State::Fullscreen);
	
	std::cout << "Window Rendered: Height = " << height << ", Width = " << width << ". " << std::endl;
	// window->setFramerateLimit(60);
	window = newWindow;
      
}



void Game::drawToScreen() 
{
  // creates a camera that follows the player(gameObject 1) based on set window
  // view height and width from createWindow func.
  window->setView(sf::View(
      {gameObjects[2]->getPosition().x, gameObjects[2]->getPosition().y},
      {static_cast<float>(width), static_cast<float>(height)}));
  // draw below this function
  window->clear(sf::Color::White);

  for (int i = 0; i < gameObjects.size();
       i++) // same as below but with game objects
  {
    // std::cout << "drawing gameObject" << endl;
    window->draw(*gameObjects[i]);
  }
  for (int i = 0; i < projectiles.size();
       i++) // draws all the projectiles that were dynamically allocated
  {
    // std::cout << "drawing projectile" << endl;
    window->draw(*projectiles[i]);
  }
  for (int i = 0; i < guiInterfaceArray.size();
       i++) // draws all the text for the gui.
  {
    if (guiInterfaceArray[i] != nullptr) {
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
  sf::Texture texture =
      sf::Texture(); // static not dynamic so possible problems in future.
  if (!texture.loadFromFile(filepath))
  {
    std::cout << "error loading sprite" << std::endl;
  }
  return texture;
}
sf::Font *Game::createFont(std::string filepath) 
{
  sf::Font *font = new sf::Font();
  if (!font->openFromFile(filepath)) {
    cout << "Error loading font from file.\n";
  }
  return font;
}
void Game::shopMenu() // Shop Menu Start 
{
	guiInterfaceArray.resize(8, nullptr); // cant access a array 0 if it wasnt initalized so create the size then reassign the index.
	fontArray.resize(4, nullptr);
	//FILE* Save = fopen("Save.csv", "w");
	std::ofstream ofile("Save.csv"); // Save-to-file
	std::ifstream ifile("Save.csv"); // load from file


	sf::Time elapsed1 = globalClock.getElapsedTime();
	std::cout << "Shop Menu Opened At: " << elapsed1.asSeconds() << "s" << std::endl; // Functional Running Time Clock
	//sf::Clock globalClock.restart();

	sf::Texture backGroundTexture = createTexture("Sprites/SpriteMap.png");
	sf::Sprite backGround(backGroundTexture);
	backGround.setOrigin({ 500,450 });
	backGround.setPosition({ 960,540 });
	backGround.setScale({ 6,6 });

	sf::Texture shopButtonTexture = createTexture("Sprites/ShopButton.png");
	sf::Sprite shopButton(shopButtonTexture);
	shopButton.setOrigin({ 47,10 });
	shopButton.setPosition({ 960,150 });
	shopButton.setScale({ 5,5 });

	sf::Texture healthButtonTexture = createTexture("Sprites/Health.png");
	sf::Sprite healthButton(healthButtonTexture);
	healthButton.setOrigin({ 47,10 });
	healthButton.setPosition({ 350,400 });
	healthButton.setScale({ 3,3 });
	sf::Texture addButtonHTexture = createTexture("Sprites/Add.png");
	sf::Sprite addButtonH(addButtonHTexture);
	addButtonH.setOrigin({ 47,10 });
	addButtonH.setPosition({ 750,400 });
	addButtonH.setScale({ 3,3 });
	sf::Texture subButtonHTexture = createTexture("Sprites/Subtract.png");
	sf::Sprite subButtonH(subButtonHTexture);
	subButtonH.setOrigin({ 47,10 });
	subButtonH.setPosition({ 1150,400 });
	subButtonH.setScale({ 3,3 });

	sf::Texture damageButtonTexture = createTexture("Sprites/Damage.png");
	sf::Sprite damageButton(damageButtonTexture);
	damageButton.setOrigin({ 47,10 });
	damageButton.setPosition({ 350,500 });
	damageButton.setScale({ 3,3 });
	sf::Texture addButtonDTexture = createTexture("Sprites/Add.png");
	sf::Sprite addButtonD(addButtonDTexture);
	addButtonD.setOrigin({ 47,10 });
	addButtonD.setPosition({ 750,500 });
	addButtonD.setScale({ 3,3 });
	sf::Texture subButtonDTexture = createTexture("Sprites/Subtract.png");
	sf::Sprite subButtonD(subButtonDTexture);
	subButtonD.setOrigin({ 47,10 });
	subButtonD.setPosition({ 1150,500 });
	subButtonD.setScale({ 3,3 });

	sf::Texture movementButtonTexture = createTexture("Sprites/Movement.png");
	sf::Sprite movementButton(movementButtonTexture);
	movementButton.setOrigin({ 47,10 });
	movementButton.setPosition({ 350,600 });
	movementButton.setScale({ 3,3 });
	sf::Texture addButtonMTexture = createTexture("Sprites/Add.png");
	sf::Sprite addButtonM(addButtonMTexture);
	addButtonM.setOrigin({ 47,10 });
	addButtonM.setPosition({ 750,600 });
	addButtonM.setScale({ 3,3 });
	sf::Texture subButtonMTexture = createTexture("Sprites/Subtract.png");
	sf::Sprite subButtonM(subButtonMTexture);
	subButtonM.setOrigin({ 47,10 });
	subButtonM.setPosition({ 1150,600 });
	subButtonM.setScale({ 3,3 });


	sf::Texture projectileButtonTexture = createTexture("Sprites/Projectile.png");
	sf::Sprite projectileButton(projectileButtonTexture);
	projectileButton.setOrigin({ 47,10 });
	projectileButton.setPosition({ 350,700 });
	projectileButton.setScale({ 3,3 });
	sf::Texture addButtonPTexture = createTexture("Sprites/Add.png");
	sf::Sprite addButtonP(addButtonPTexture);
	addButtonP.setOrigin({ 47,10 });
	addButtonP.setPosition({ 750,700 });
	addButtonP.setScale({ 3,3 });
	sf::Texture subButtonPTexture = createTexture("Sprites/Subtract.png");
	sf::Sprite subButtonP(subButtonPTexture);
	subButtonP.setOrigin({ 47,10 });
	subButtonP.setPosition({ 1150,700 });
	subButtonP.setScale({ 3,3 });

	sf::Texture contButtonTexture = createTexture("Sprites/Continue.png");
	sf::Sprite contButton(contButtonTexture);
	contButton.setOrigin({ 47,10 });
	contButton.setPosition({ 960,900 });
	contButton.setScale({ 4,4 });

	// variables
	int input = 0;
	bool exit = false;
	float delay = 0;

	while (window->isOpen() && !exit) // Shop menu loop
	{
		if (fontArray[0] == nullptr)
		{
			fontArray[0] = createFont("Fonts/Pixeled.ttf");
		}
		if (guiInterfaceArray[5] == nullptr)
		{
			sf::Text* scoreGui = new sf::Text(*fontArray[0], "N/A", 16);
			sf::Text* scoreNumberGui = new sf::Text(*fontArray[0], "N/A", 16);
			std::string scoreString = std::to_string(score);
			scoreGui->setString("SCORE: ");
			scoreGui->setScale({ 3,3 });
			scoreGui->setPosition({ 100, 400 });
			scoreNumberGui->setString(scoreString);
			scoreNumberGui->setScale({ 3,3 });
			scoreNumberGui->setPosition({ 100, 500 });
			guiInterfaceArray[5] = scoreGui;
			guiInterfaceArray[6] = scoreNumberGui;
		}

		else if (guiInterfaceArray[5] != nullptr)
		{
			std::string scoreString = std::to_string(score);
			guiInterfaceArray[6]->setString(scoreString);
			guiInterfaceArray[5]->setPosition({ 100, 100 });
			guiInterfaceArray[6]->setPosition({ 200, 200 });
		}
		window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
		while (timeClock.getElapsedTime().asSeconds() < delay); // so that inputs dont overlap.
		// essentially if you click exit on pause menu it would exit the whole game due to the input being held down.
		{
		}
		sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
			}

		}

		if (window->hasFocus()) // Get bounds for selecting options
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (addButtonD.getGlobalBounds().contains(mousePos))
				{
					input = 1;
				}
				else if (subButtonD.getGlobalBounds().contains(mousePos))
				{
					input = 2;
				}
				else if (addButtonH.getGlobalBounds().contains(mousePos))
				{
					input = 3;
				}
				else if (subButtonH.getGlobalBounds().contains(mousePos))
				{
					input = 4;
				}
				else if (addButtonM.getGlobalBounds().contains(mousePos))
				{
					input = 5;
				}
				else if (subButtonM.getGlobalBounds().contains(mousePos))
				{
					input = 6;
				}
				else if (addButtonP.getGlobalBounds().contains(mousePos))
				{
					input = 7;
				}
				else if (subButtonP.getGlobalBounds().contains(mousePos))
				{
					input = 8;
				}
				else if (contButton.getGlobalBounds().contains(mousePos))
				{
					input = 9;
				}
			}


		}

		switch (input) // These are all multipliers that are additive and will be saved to file, each gun effected dif
		{
		case 1: // add dmg
			delay = timeClock.getElapsedTime().asSeconds() + .5;
			// sets delay so it waits before checking stuff again.
			window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
			std::cout << "Entered Add Damage" << endl;
			if (score >= 50 + (dmgLevel * 2))
			{
				std::cout << "Bought Damage Level: Current Score Global, Damage Level, Estimated Price: " << score << ", " << dmgLevel << ", " << 50 + (dmgLevel * 2) << std::endl; // info check
				save.addDmg(1);
				save.subScore(50 + (dmgLevel * 2));
			}
			break;

		case 2: // sub dmg
			delay = timeClock.getElapsedTime().asSeconds() + .5;
			// sets delay so it waits before checking stuff again.
			window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
			std::cout << "Entered Sub Damage" << endl;
			if (dmgLevel >= 1)
			{
				save.subDmg(1);
				save.addScore(50 + (dmgLevel * 2));
			}
			break;

		case 3: // add hlth
			delay = timeClock.getElapsedTime().asSeconds() + .5;
			// sets delay so it waits before checking stuff again.
			window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
			if (score >= 50 + (spdLevel * 2))
			{
				save.addHlth(1);
				save.subScore(50 + (hlthLevel * 2));
			}
			break;

		case 4: // sub hlth
			delay = timeClock.getElapsedTime().asSeconds() + .5;
			// sets delay so it waits before checking stuff again.
			window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
			if (hlthLevel >= 1)
			{
				save.subHlth(1);
				save.addScore(50 + (hlthLevel * 2));
			}
			break;

		case 5: // add sped
			delay = timeClock.getElapsedTime().asSeconds() + .5;
			// sets delay so it waits before checking stuff again.
			window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
			if (score >= 50 + (spdLevel * 2))
			{
				save.addSpd(1);
				save.subScore(50 + (spdLevel * 2));
			}
			break;

		case 6: // sub sped
			delay = timeClock.getElapsedTime().asSeconds() + .5;
			// sets delay so it waits before checking stuff again.
			window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
			if (spdLevel >= 1)
			{
				save.subSpd(1);
				save.addScore(50 + (spdLevel * 2));
			}
			break;

		case 7: // add proj sped
			delay = timeClock.getElapsedTime().asSeconds() + .5;
			// sets delay so it waits before checking stuff again.
			window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
			if (score >= 50 + (projLevel * 2)) // check to make sure they have enough score to buy it
			{
				save.addProj(1);
				save.subScore(50 + (projLevel * 2));
			}
			break;

		case 8: // sub proj sped
			delay = timeClock.getElapsedTime().asSeconds() + .5;
			// sets delay so it waits before checking stuff again.
			window->setView(sf::View({ 960,540 }, { static_cast<float>(1920),static_cast<float>(1080) }));
			if (projLevel >= 1) // As long as they have a level to take back
			{
				save.subProj(1);
				save.addScore(50 + (projLevel * 2));
			}
			break;

		case 9: // exit
			// finalize values

			score = save.getScore(); // Final values before continuing
			hlthLevel = save.getHlth();
			dmgLevel = save.getDmg();
			spdLevel = save.getSpd();
			projLevel = save.getProj();

			exit = true;
			break;
		}

		input = 0;
		window->clear(sf::Color::Black);
		window->draw(backGround); // Render buttons
		window->draw(shopButton);
		window->draw(damageButton);
		window->draw(addButtonD);
		window->draw(subButtonD);
		window->draw(healthButton);
		window->draw(addButtonH);
		window->draw(subButtonH);
		window->draw(movementButton);
		window->draw(addButtonM);
		window->draw(subButtonM);
		window->draw(projectileButton);
		window->draw(addButtonP);
		window->draw(subButtonP);
		window->draw(contButton);
		window->draw(*guiInterfaceArray[5]);
		window->draw(*guiInterfaceArray[6]);
		window->display();

	}
}  // Shop Menu End
void Game::introMenu()
{
	//timeClock.stop();
	sf::Texture instructionTexture = createTexture("Sprites/instructionsMenu.png");
	sf::Sprite instructions(instructionTexture);
	instructions.setOrigin({ 960,540 });
	instructions.setPosition({ 959,539 });
	instructions.setScale({ 1,1 });

	sf::Texture exitButtonTexture = createTexture("Sprites/PlayButton.png");
	sf::Sprite exitButton(exitButtonTexture);
	exitButton.setOrigin({ 47,10 });
	exitButton.setPosition({ 960,950 });
	exitButton.setScale({ 3,3 });
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
				if (exitButton.getGlobalBounds().contains(mousePos))
				{
					input = 1;
				}
			}


		}
		switch (input)
		{
		case 1: // start
			loop = false;

			break;
		}
		window->clear(sf::Color::Black);
		window->draw(instructions);
		window->draw(exitButton);
		window->display();

	}
	//timeClock.start();
}

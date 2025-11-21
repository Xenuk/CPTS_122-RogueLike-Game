#include "header.hpp"
#include "GameObject.hpp"
#include "Projectile.hpp" 
// directions for sprite
enum directions {down,left,right,up};
int main()
{
	unsigned int width = 320;
	unsigned int height = 240;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width,height }), "Test");
	window->setFramerateLimit(60);
	sf::Vector2f pos;
	sf::Texture texture;
	float angle;
	if (!texture.loadFromFile("Sprites/ExampleSprite.png"))
	{
		std::cout << "error loading sprite" << std::endl;
	}
	sf::Sprite sprite(texture);
	// creating uhh idk used for sprite
	sf::IntRect dir[4];
	// setting sprite up.
	sf::Texture texture2;

	if (!texture2.loadFromFile("Sprites/ExampleSpriteWall.png"))
	{
		std::cout << "error loading sprite" << std::endl;
	}
	sf::Texture texture3;

	if (!texture3.loadFromFile("Sprites/ExampleBullet.png"))
	{
		std::cout << "error loading sprite" << std::endl;
	}
	GameObject newGameguy = GameObject(texture2, 10, 10, 10, 0.4);
	newGameguy.setPosition({ 20, 20 });
	newGameguy.setSprite("Sprites/ExampleSpriteWall.png");
	Projectile proj = Projectile(texture3, 10, { 0.1,-0.1 }, 5);
	for (int i = 0; i < 4; ++i)
	{
		// says we read from sheet from starting at 0,0 then moving 16 to the right and the second bracket
		// is the size of the sprite total.
		dir[i] = sf::IntRect({ {16 * i, 0},{16,16} });

	}
	Projectile* proj2 = nullptr;
	proj.setPosition({160, 120});
	proj.setOrigin({ 32,32 });
	sprite.setTextureRect(dir[down]);
	sprite.setOrigin({ 8,8 });
	sprite.setPosition({ 160,120});
	bool cool = false;
	while (window->isOpen())
	{
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
			}

		}

		
		proj.move(proj.directionAndSpeed);	
		if (sprite.getGlobalBounds().findIntersection(proj.getGlobalBounds()))
		{
			cool = true;
		}


		//movement below
		float movementVerticle=0, movementHorizontal=0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
		{	
			movementVerticle = movementVerticle + 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
		{
			movementHorizontal = movementHorizontal - 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
		{
			movementHorizontal = movementHorizontal + 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
		{
			movementVerticle = movementVerticle - 1;
		}
		if (movementVerticle != 0 && movementHorizontal!=0) {
			//0.707106781187 ~ ((1+1)^(1/2))/2
			movementVerticle = movementVerticle* 0.707106781187;
			movementHorizontal = movementHorizontal* 0.707106781187;
		}

		if(movementVerticle != 0 || movementHorizontal != 0) {
			sprite.move({ movementHorizontal,movementVerticle });
		}
		if (movementVerticle>0) {sprite.setTextureRect(dir[down]);}
		else if (movementVerticle<0) {sprite.setTextureRect(dir[up]);}
		else if (movementHorizontal > 0) { sprite.setTextureRect(dir[right]); }
		else if (movementHorizontal < 0) { sprite.setTextureRect(dir[left]); }

		movementHorizontal = 0;
		movementVerticle = 0;



		pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window)); // converts pixels(int) to world coords(float).
		std::cout << pos.x << "," << pos.y << std::endl;
		std::cout << pos.x - sprite.getPosition().x << "," << pos.y - sprite.getPosition().y << std::endl;

		if (window->hasFocus())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{	// i got it to fucking work its this stupid map coords bs, im doing it based on pixels but sprite position is world coords.
				// THEN it was inaccurate and i went from working with pixels to world coords transforming mouse pos(pixels(int)) to world coords which is a float.
				// I AM GOD
				angle = atan2(pos.y - sprite.getPosition().y, pos.x - sprite.getPosition().x);
				proj2 = newGameguy.shootProjectile(texture3, 10, { 3 * cos(angle),3 * sin(angle) }, 10, sprite.getPosition());
			}
		}
		// THIS allows the camera to follow the sprite.
		window->setView(sf::View({ sprite.getPosition().x,sprite.getPosition().y }, {static_cast<float>(width),static_cast<float>(height) }));
		// draw below this
		window->clear(sf::Color::White);
		window->draw(sprite); 
		if (cool == false)
		{
			window->draw(proj);
		}
		if (proj2 != nullptr)
		{
			proj2->move(proj2->directionAndSpeed);
			window->draw(*proj2);
		}
		window->draw(newGameguy);
		window->display();
		// draw above this
	}

	return 0;
}
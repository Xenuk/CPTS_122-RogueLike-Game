#include "header.hpp"
// directions for sprite
enum directions {down,left,right,up};
int main()
{
	unsigned int width = 1920;
	unsigned int height = 1080;
	sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode({ width,height }), "Test");
	window->setFramerateLimit(60);

	sf::Texture texture;

	if (!texture.loadFromFile("Sprites/ExampleSprite.png"))
	{
		std::cout << "error loading sprite" << std::endl;
	}
	sf::Sprite sprite(texture);
	// creating uhh idk used for sprite
	sf::IntRect dir[4];
	// setting sprite up.
	for (int i = 0; i < 4; ++i)
	{
		// says we read from sheet from starting at 0,0 then moving 16 to the right and the second bracket
		// is the size of the sprite total.
		dir[i] = sf::IntRect({ {16 * i, 0},{16,16} });

	}
	sprite.setTextureRect(dir[down]);
	sprite.setOrigin({ 8,8 });
	sprite.setPosition({ 500,700});
	while (window->isOpen())
	{
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
			}

		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
		{
			sprite.move({ 0,0.1});
			sprite.setTextureRect(dir[down]);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
		{
			sprite.move({ -0.1,0 });
			sprite.setTextureRect(dir[left]);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
		{
			sprite.move({ 0.1,0 });
			sprite.setTextureRect(dir[right]);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
		{
			sprite.move({ 0,-0.1 });
			sprite.setTextureRect(dir[up]);
		}

		// draw below this
		window->clear(sf::Color::White);

		window->draw(sprite);

		window->display();
		// draw above this
	}

	return 0;
}
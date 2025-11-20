#include "header.hpp"


int main()
{
	sf::RenderWindow* window= new sf::RenderWindow(sf::VideoMode({ 400, 400 }), "Test");
	window->setFramerateLimit(60);

	while (window->isOpen())
	{
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
			}

		}
		// draw below this
		window->clear();

		

		window->display();
		// draw above this
	}

	return 0;
}
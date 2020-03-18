#include <SFML/Graphics.hpp>

#include "bacteria.h"
using namespace sf;

int main()
{
	const int size = 1000;
	sf::RenderWindow window(sf::VideoMode(size,size*3/4), "SFML works!");
	sf::CircleShape shape(50.f);
	RectangleShape square(Vector2f(20,20));
	shape.setFillColor(sf::Color::Green);
	square.setFillColor(Color::Red);
	

	Bacteria b(500,300);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		if (Keyboard::isKeyPressed(Keyboard::D))
			b.angle+=0.1;
		if (Keyboard::isKeyPressed(Keyboard::A))
			b.angle-=0.1;
		if (Keyboard::isKeyPressed(Keyboard::W))
			b.move();

		window.clear();

		//window.draw(shape);
		//window.draw(square);
		window.draw(b.draw());
		window.display();
	}

	return 0;
}
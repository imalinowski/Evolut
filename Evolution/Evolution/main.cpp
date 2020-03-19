#include <SFML/Graphics.hpp>
#include <iostream>;
#include "header.h";
#include "bacteria.h"
using namespace std;

int main()
{
	cout << "Hello world!" << endl;
	foo();
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	Bacteria b(0,0);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
			b.angle += 0.03;
		if (Keyboard::isKeyPressed(Keyboard::A))
			b.angle -= 0.03;
		if (Keyboard::isKeyPressed(Keyboard::W))
			b.move();

		window.clear();
		window.draw(b.draw());
		window.display();
	}

	return 0;
}
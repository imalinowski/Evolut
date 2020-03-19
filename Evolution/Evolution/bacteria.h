#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
using namespace sf;

#define PI 3.14159265

class Bacteria {
public:
	float angle = 0;

	Bacteria(float x, float y) {

		t.loadFromFile("bacteria.png");
		s.setTexture(t);

		s.setOrigin(s.getGlobalBounds().width / 2, s.getGlobalBounds().height / 2);
		s.setScale(size / s.getGlobalBounds().width, size / s.getGlobalBounds().height);
		s.setPosition(x, y);
		s.setRotation(angle);
		
		
		std::cout << "width " << s.getGlobalBounds().width << std::endl;
		std::cout << "height " << s.getGlobalBounds().height << std::endl;

		this->x = x;
		this->y = y;
	}
	Sprite& draw() {

		//s.setPosition(x, y);
		s.setRotation(angle);
		s.setPosition(x, y);

		return s;
	}
	void setPos(float x, float y) {
		this->x = x;
		this->y = y;
		//s.setPosition(x, y);
	}
	void move() {
		x += cos(PI/180*angle) *speed;
		y += sin(PI/180*angle) *speed;

		//std::cout << "x " << x << " " << s.getPosition().x << "   ";
		//std::cout << "y " << y << " " << s.getPosition().y << std::endl;
		//s.setPosition(x, y);
	}
private:

	float size = 100;
	float speed = 0.1;

	Texture t;
	Sprite s;
	float x,y;
};
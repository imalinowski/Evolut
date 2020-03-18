#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
using namespace sf;

#define PI 3.14159265

class Bacteria {
public:
	float angle = 45;

	Bacteria(float x, float y) {

		t.loadFromFile("bacteria.png");
		s.setTexture(t);

		s.setOrigin(size / 2, size / 2);
		s.setPosition(x, y);
		s.setScale(size/s.getTexture()->getSize().x, size/ s.getTexture()->getSize().y);
		s.setRotation(angle);
		

		this->x = x;
		this->y = y;
	}
	Sprite& draw() {
		s.setPosition(x-size/2, y-size/2);
		s.setRotation(angle);
		return s;
	}
	void setPos(float x, float y) {
		this->x = x;
		this->y = y;
		s.setPosition(x-size/2, y-size/2);
	}
	void move() {
		x += cos(PI/180*angle) *speed;
		y += sin(PI/180*angle) *speed;
		s.setPosition(x-size/2, y-size/2);
	}
private:

	float size = 100;
	float speed = 0.1;

	Texture t;
	Sprite s;
	float x,y;
};
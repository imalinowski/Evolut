#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <ctime>

using namespace sf;

#define PI 3.14159265

class Bacteria {
private:
	Texture t;
	Sprite s;
public:
	float angle = 0;
	float x, y;
	float size = 10;
	unsigned int foodCount = 0;

	static  int popR_count;
	static  int popG_count;
	static  int popY_count;

	time_t born;
	time_t feeded;
	float speed = 1;
	unsigned int hungry = 20;
	float rotateSpeed = 4;

	Bacteria(float x, float y) {

		t.loadFromFile("Res//bacteria.png");
		s.setTexture(t);

		s.setOrigin(s.getGlobalBounds().width / 2, s.getGlobalBounds().height / 2);
		s.setScale(size / s.getGlobalBounds().width, size / s.getGlobalBounds().height);
		s.setPosition(x, y);
		s.setRotation(angle);

		this->x = x;
		this->y = y;

		born = time(0);
		feeded = time(0);

		popG_count++;
	}
	
	//деление
	Bacteria(Bacteria& b) {
		x = b.x;
		y = b.y;
		angle = b.angle;

		float r = (rand()%2 == 0?1:-1)*rand() % 10 / 10.0;
		
		speed = b.speed + r;
		hungry = b.hungry - r*20;
		rotateSpeed = speed * 2;

		//std::cout << std::to_string(speed) << std::endl;

		b.foodCount = 0;

		if (speed > 1.3) {
			t.loadFromFile("Res//bacteria-r.png");
			popR_count++;
		}
		else if (speed < 0.7) {
			t.loadFromFile("Res//bacteria-y.png");
			popY_count++;
		}
		else {
			t.loadFromFile("Res//bacteria-g.png");
			popG_count++;
		}

		s.setTexture(t);
		s.setOrigin(s.getGlobalBounds().width / 2, s.getGlobalBounds().height / 2);
		s.setScale(size / s.getGlobalBounds().width, size / s.getGlobalBounds().height);
		s.setPosition(x, y);
		s.setRotation(angle);


		born = time(0);
		feeded = time(0);
	}

	~Bacteria() {
		if (speed > 1.3) {
			popR_count--;
		}
		else if (speed < 0.7) {
			popY_count--;
		}
		else {
			popG_count--;
		}
	}

	Sprite& draw() {

		s.setRotation(angle);
		s.setPosition(x, y);

		return s;
	}
	void setPos(float x, float y) {
		this->x = x;
		this->y = y;
	}
	std::string move(float _x, float _y) {
		
		float _angle = atan2((_y - y),(_x - x))*180/PI;
		if (abs(abs(_angle) - 180) < 10)
			angle = _angle;

		if (_angle != angle)
			angle += ((_angle > angle) ? rotateSpeed : -rotateSpeed);
		x += cos(PI / 180 * angle) * speed;
		y += sin(PI / 180 * angle) * speed;
		
		return std::to_string(_angle);
	}

	unsigned int dis(float _x, float _y) {
		return sqrt(pow(x - _x, 2) + pow(_y - y, 2));
	}
};

 int Bacteria::popR_count = 0;
 int Bacteria::popG_count = 0;
 int Bacteria::popY_count = 0;
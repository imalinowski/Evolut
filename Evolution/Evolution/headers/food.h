#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;

class Food {
public:
	float x;
	float y;
	clock_t born;

	static unsigned int count;

	Food(float x, float y) {
		born = clock();

		
		t.loadFromFile("Res//food.png");
		s.setTexture(t);
		
		s.setOrigin(s.getGlobalBounds().width / 2, s.getGlobalBounds().height / 2);
		s.setScale(size / s.getGlobalBounds().width, size / s.getGlobalBounds().height);
		s.setPosition(x, y);
		this->x=x;
		this->y=y;
		count++;
	}

	~Food() {
		count--;

	}

	void setXY(Vector2i v) {
		x = v.x;
		y = v.y;
		s.setPosition(v.x,v.y);
	}
	void setXY(float _x, float _y) {
		x = _x;
		y = _y;
		s.setPosition(x, y);
	}
	Sprite draw() {
		return s;
	}
	bool checkCollide(Bacteria *b) {
		bool ch = (abs(b->x - x) < b->size / 2)&& (abs(b->y - y) < b->size / 2);
		if (ch) {
			b->foodCount++;
			b->feeded = time(0);
		}
		return ch;
	}
private:
	Texture t;
	Sprite s;
	int size = 5;
};

unsigned int Food::count = 0;
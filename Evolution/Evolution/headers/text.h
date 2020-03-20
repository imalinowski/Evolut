#pragma once
#include <SFML/Graphics.hpp>
#include<string>

class MyText {
public:
	float x, y;
	std::string text;
	sf::Font f;
	sf::Text t;
	MyText(float x, float y) {
		f.loadFromFile("Res//font.ttf");
		t.setFont(f);
		t.setPosition(x, y);
		t.setFillColor(sf::Color::Green);
		t.setStyle(sf::Text::Bold);
	}
	sf::Text draw() {
		return t;
	}
	void setText(std::string text) {
		t.setString(text);
		this->text = text;
	}

};
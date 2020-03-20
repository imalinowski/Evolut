#include <SFML/Graphics.hpp>

#include <iostream>
#include "stdlib.h"
#include "time.h"
#include <chrono>
#include <fstream>

#include "bacteria.h"
#include "food.h"
#include "text.h"
using namespace std;
using namespace sf;

const int WINDOW_SIZE = 1800;


int main()
{	
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE*5/8), "Evolution");


	vector<Bacteria*> bs;
	bs.push_back(new Bacteria(WINDOW_SIZE / 2, WINDOW_SIZE / 2));
	
	MyText t(0,0);
	t.setText("0");

	vector<Food*> fs;
	fs.push_back(new Food(rand()%WINDOW_SIZE,rand()%(WINDOW_SIZE*5/8)));

	fstream rStat("Res//statR.txt", ios::out, ios::trunc);
	fstream gStat("Res//statG.txt", ios::out, ios::trunc);
	fstream yStat("Res//statY.txt", ios::out, ios::trunc);

	int fps = 0;
	int secFromStart = 0;
	auto tick = chrono::steady_clock::now();
	auto f = chrono::steady_clock::now();
	while (window.isOpen())
	{
		//временные штуки
		if (double(chrono::duration_cast<chrono::milliseconds>
			(chrono::steady_clock::now() - tick).count()) <= 1000.0/60)
			continue;

		tick = chrono::steady_clock::now();

		fps++;
		if (double(chrono::duration_cast<chrono::milliseconds>
			(chrono::steady_clock::now() - f).count()) >= 1000.0) {
			t.setText((stoi(t.text) != fps) ? to_string(fps) : t.text);
			fps = 0;
			f = chrono::steady_clock::now();
			secFromStart++;
			if (secFromStart % 5 == 0) {
				if (rStat)
					rStat << Bacteria::popR_count << "\n";
				if (gStat)
					gStat << Bacteria::popG_count << "\n";
				if (yStat)
					yStat << Bacteria::popY_count << "\n";
			}
		}
		//

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//генератор еды
		if (fs.size() == 0 || (Food::count < 1500 && rand()&100>10 
			&& clock()-fs[fs.size()-1]->born > 50)) {
			fs.push_back(new Food(rand() % WINDOW_SIZE, rand() % (WINDOW_SIZE * 5 / 8)));
		}
		
		for (int i = 0; i < bs.size(); i++) {
			if (time(0) - bs[i]->born < 3)
				continue;
			//поиск ближайшей еды
			unsigned int J = 0;
			unsigned int dis = INT_MAX;
			for (int j = 0; j < fs.size(); j++) {
				if (dis > bs[i]->dis(fs[j]->x,fs[j]->y)) {
					dis = bs[i]->dis(fs[j]->x,fs[j]->y);
					J = j;
				}
			}
			//
			bs[i]->move(fs[J]->x, fs[J]->y);

			if (fs[J]->checkCollide(bs[i])) {
				delete fs[J];
				fs.erase(fs.begin() + J);
				if (fs.size() == 0 ) {
					fs.push_back(new Food(rand() % WINDOW_SIZE, rand() % (WINDOW_SIZE * 5 / 8)));
				}
			}
			//деление
			if (bs[i]->foodCount > 2)
				bs.push_back(new Bacteria(*bs[i]));
			if (time(0) - bs[i]->feeded > bs[i]->hungry) {
				delete bs[i];
				bs.erase(bs.begin() + i);
			}
		}
			

		window.clear();
		for (int i = 0; i < bs.size(); i++) {
			window.draw(bs[i]->draw());
		}
		window.draw(t.draw());
		for (int i = 0; i < fs.size(); i++) {
			window.draw(fs[i]->draw());
		}
		window.display();

		
	}

	rStat.close();
	gStat.close();
	yStat.close();

	return 0;
}

string operator+ (string b, float a) {
	return to_string(a);
}
string operator+ (string b, int a) {
	return to_string(a);
}
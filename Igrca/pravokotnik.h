#pragma once
#pragma once
#ifndef PRAVOKOTNIK_H
#define PRAVOKOTNIK_H

#include <SFML/Graphics.hpp>
class Pravokotnik {
public:
	Pravokotnik(float width, float height);
	~Pravokotnik();
	
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	void setPosition(float x, float y);
	float x1 = 300.0;
	float y1 = 300.0;
	float x2 = 900.0;
	float y2 = 300.0;
private:
	
	sf::RectangleShape pravokotnik;
};

#endif
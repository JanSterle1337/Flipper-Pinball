#pragma once
#ifndef PADDLE_H
#define PADDLE_h
#include <SFML/Graphics.hpp>


class Paddle {
public:
	Paddle();
	~Paddle();

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	void setPosition(float,float);
	void draw(sf::RenderWindow& window);

private:

	sf::RectangleShape paddle;
};
#endif
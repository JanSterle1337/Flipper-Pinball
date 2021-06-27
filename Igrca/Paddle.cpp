#include "Paddle.h"


Paddle::Paddle() {                         //inicializacija paddla
	paddle.setPosition(700, 590);
	paddle.setSize(sf::Vector2f(100, 10));
	paddle.setFillColor(sf::Color::Black);
	paddle.setOutlineThickness(3);
	paddle.setOutlineColor(sf::Color::Blue);
	paddle.setOrigin(50 / 2, 10 / 2);
}


Paddle::~Paddle() {}



sf::Vector2f Paddle::getPosition() const {
	return paddle.getPosition();
}

sf::Vector2f Paddle::getSize() const {
	return paddle.getSize();
}

void Paddle::draw(sf::RenderWindow& window) {
	window.draw(paddle);
}

void Paddle::setPosition(float x, float y) {
	paddle.setPosition(x, y);
}
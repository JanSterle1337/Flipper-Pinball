#include "pravokotnik.h"

Pravokotnik::Pravokotnik(float height, float width) {

	pravokotnik.setSize(sf::Vector2f(width, height));
	pravokotnik.setPosition(rand()% (950-1+1)+1, 300);
	pravokotnik.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	pravokotnik.setOutlineThickness(5);
	pravokotnik.setOutlineColor(sf::Color::Black);
	pravokotnik.setOrigin(width / 2, height / 2);
}

Pravokotnik::~Pravokotnik() {

}

sf::Vector2f Pravokotnik::getPosition() const {
	return pravokotnik.getPosition();
}

sf::Vector2f Pravokotnik::getSize() const {
	return pravokotnik.getSize();
}

void Pravokotnik::setPosition(float x, float y) {
	pravokotnik.setPosition(x, y);
}

void Pravokotnik::draw(sf::RenderWindow& window) {
	window.draw(pravokotnik);
}


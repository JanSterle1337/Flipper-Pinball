#include "Collision.h"

Collision::Collision() {}

Collision::~Collision() {}

bool Collision::ballOverlap(Ball ball1, Ball ball2) { //pogleda ce se dve zogi overlappata(Prekiravata)
	float distance = distanceSquared(ball1.getPosition(), ball2.getPosition());
	float radiusSum = ball1.getRadius() + ball2.getRadius();

	return distance <= radiusSum * radiusSum;
}

//spodaj so zapisane funkcije ki gledajo ce se zoga overlappa glede na ostale objekte (zelo pomembno saj te funkcije klicemo iz drugih funkcij)


bool Collision::ballSquareOverlap(Ball ball, Pravokotnik pravokotnik) {          
	float ballDistanceX = abs(ball.getPosition().x - pravokotnik.getPosition().x);
	float ballDistanceY = abs(ball.getPosition().y - pravokotnik.getPosition().y);

	if (ballDistanceX > (pravokotnik.getSize().x / 2 + ball.getRadius())) {
		return false;
	}
	if (ballDistanceY > (pravokotnik.getSize().y / 2 + ball.getRadius())) { 
		return false; 
	
	}

	if (ballDistanceX <= ((pravokotnik.getSize().x)/2)) { 
		return true; 
	}
	if (ballDistanceY <= (pravokotnik.getSize().y / 2)) { 
		return true; 
	}

	float cornerDistance_sq = (ballDistanceX - pravokotnik.getSize().x / 2)*
		(ballDistanceX - pravokotnik.getSize().x / 2) +
		(ballDistanceX - pravokotnik.getSize().x / 2) *
		(ballDistanceX - pravokotnik.getSize().x / 2); 

	return (cornerDistance_sq <= (ball.getRadius() * ball.getRadius()));
}


bool Collision::ballPaddleOverlap(Ball ball, Paddle paddle) {
	float ballDistanceX = abs(ball.getPosition().x - paddle.getPosition().x);
	float ballDistanceY = abs(ball.getPosition().y - paddle.getPosition().y);

	if (ballDistanceX > (paddle.getSize().x / 2 + ball.getRadius())) {
		return false;
	}
	if (ballDistanceY > (paddle.getSize().y / 2 + ball.getRadius())) {
		return false;

	}

	if (ballDistanceX <= ((paddle.getSize().x) / 2)) {
		return true;
	}
	if (ballDistanceY <= (paddle.getSize().y / 2)) {
		return true;
	}

	float cornerDistance_sq = (ballDistanceX - paddle.getSize().x / 2) *
		(ballDistanceX - paddle.getSize().x / 2) +
		(ballDistanceX - paddle.getSize().x / 2) *
		(ballDistanceX - paddle.getSize().x / 2);

	return (cornerDistance_sq <= (ball.getRadius() * ball.getRadius()));
}



bool Collision::ballPointOverlap(sf::Vector2f point, Ball ball) {
	float distance = distanceSquared(ball.getPosition(), point);
	return distance < ball.getRadius()* ball.getRadius();
}

float Collision::distanceSquared(sf::Vector2f a, sf::Vector2f b) {
	float distX = a.x - b.x;
	float distY = a.y - b.y;
	return distX * distX + distY * distY;
}
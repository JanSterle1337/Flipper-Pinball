#pragma once
#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "pravokotnik.h"
#include "Paddle.h"


class Collision {
public:
	Collision();
	~Collision();

	bool ballOverlap(Ball ball, Ball ball2);
	bool ballSquareOverlap(Ball ball, Pravokotnik pravokotnik);
	bool ballPointOverlap(sf::Vector2f point, Ball ball);
	bool ballPaddleOverlap(Ball ball, Paddle paddle);
	float distanceSquared(sf::Vector2f a, sf::Vector2f b);

};

#endif
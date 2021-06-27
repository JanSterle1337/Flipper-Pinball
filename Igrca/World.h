#pragma once

#ifndef WORLD_H
#define WORLD_H
#include "Ball.h"
#include "Collision.h"
#include "pravokotnik.h"
#include "Paddle.h"


class World {
public:
	World();
	~World();

	void initBalls(size_t size);
	void initPravokotnik(size_t size);
	void initPaddle(size_t size);
	void update(float deltatime);
	
	void ballCollision();
	void ballSquareCollision();
	void ballPaddleCollision();
	void movePaddleLeft();
	void movePaddleRight();
	void ballGroundOverlap();
	bool dragBall(sf::Vector2f point);
	void setDraggedVelocity(float x, float y);
	

	

	Ball* getDraggedBall() const;
	std::vector<Ball> getBalls() const;
	float skupenScore = 0;
	std::vector<Pravokotnik> getPravokotnik() const;
	std::vector<Paddle> getPaddle() const;
	bool gameState = 0;
	
	


private:
	std::vector<Ball> balls;
	std::vector<Pravokotnik> pravokotniki;
	std::vector<Paddle> paddles;
	Ball* draggedBall;
	Collision collision;


};

#endif
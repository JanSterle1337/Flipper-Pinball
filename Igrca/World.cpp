#include "World.h"
#include <iostream>


World::World() {            //konstruktor, inicializacija raznih oblik
	draggedBall = nullptr;
	initBalls(3);
	initPravokotnik(2);
	initPaddle(1);
	
}

World::~World() {
	//delete draggedBall;

	
}

void World::initBalls(size_t size) {   //inicializacija zog, kordinate zgenerira random funkcija
	for (size_t i = 0; i < size; ++i) {
		
		float x = (float)(rand() % (850-400+1)+320);
		float y = (float)(rand() % (500-100+1)+100);
		float radius = (float)(15 + (rand() % (40 - 16)));

		Ball ball = Ball(radius);
		ball.setPosition(x, y);

		balls.push_back(ball);
	}
}

void World::initPravokotnik(size_t size) {              //inicalizacija sten(pravokotnika), pozicija je konstantna
	/*Pravokotnik pravokotnik = Pravokotnik(pravokotnik);
	pravokotniki.push_back(pravokotnik);*/

	for (size_t i = 0; i < size; ++i) {
		
		Pravokotnik pravokotnik = Pravokotnik(600,10);
		if (i == 0) {
			pravokotnik.setPosition(300.0, 300.0);
		}
		else {
			pravokotnik.setPosition(900.0, 300.0);
		}
		
		pravokotniki.push_back(pravokotnik);
	}
}

void World::initPaddle(size_t size) {          //inicializacija spodnjega pravokotnika
	float x = 700.0;
	float y = 580.0;
	for (size_t i = 0; i < size; ++i) {
		
		Paddle paddle;
		paddle.setPosition(x, y);
		paddles.push_back(paddle);
	}
}


void World::update(float deltatime) {    //updejt funkcija, klice funkcije ki chekirajo kolizije med dvema zogicama, zogico in pravokotnik, tlemi ter paddlam
	
	World::ballCollision();
	World::ballSquareCollision();
	World::ballPaddleCollision();
	World::ballGroundOverlap();
	for (Ball& ball : balls) {
		
		ball.update(deltatime);  //vsem zogice updejta
		
	}
	
	
}


void World::ballCollision() {
	for (Ball& ball : balls) {
		for (Ball& ball2 : balls) {

			if (&ball != &ball2) {
				if (collision.ballOverlap(ball, ball2)) {
					

					float distance = collision.distanceSquared(ball.getPosition(), ball2.getPosition());           //fizikalna enacba za smooth premikanje zogic
					float distanceSquared = sqrtf(distance);
					float overlap = (distanceSquared - ball.getRadius() - ball2.getRadius()) / 2.f;

					float moveX = (overlap * (ball.getPosition().x - ball2.getPosition().x) / distanceSquared);
					float moveY = (overlap * (ball.getPosition().y - ball2.getPosition().y) / distanceSquared);

					ball.setPosition(ball.getPosition().x - moveX, ball.getPosition().y - moveY);
					ball2.setPosition(ball2.getPosition().x + moveX, ball2.getPosition().y + moveY);

					sf::Vector2f normal((ball2.getPosition().x - ball.getPosition().x) / distanceSquared, (ball2.getPosition().y - ball.getPosition().y) / distanceSquared);
					sf::Vector2f tangent(-normal.y, normal.x);

					float dotProductTangent1 = ball.getVelocity().x * tangent.x + ball.getVelocity().y * tangent.y;
					float dotProductTangent2 = ball2.getVelocity().x * tangent.x + ball2.getVelocity().y * tangent.y;

					float dotProductNormal1 = ball.getVelocity().x * normal.x + ball.getVelocity().y * normal.y;
					float dotProductNormal2 = ball2.getVelocity().x * normal.x + ball2.getVelocity().y * normal.y;

					float m1 = (dotProductNormal1 * (ball.getMass() - ball2.getMass()) + 2.0f * ball.getMass() * dotProductNormal2) / (ball.getMass() + ball2.getMass());
					float m2 = (dotProductNormal2 * (ball2.getMass() - ball.getMass()) + 2.0f * ball.getMass() * dotProductNormal1) / (ball.getMass() + ball2.getMass());

					ball.setVelocity(tangent.x * dotProductTangent1 + normal.x * m1, (tangent.y * dotProductTangent1 + normal.y * m1));
					ball2.setVelocity(tangent.x * dotProductTangent2 + normal.x * m2, (tangent.y * dotProductTangent2 + normal.y * m2));


					ball.score += abs(ball.getVelocity().x) + abs(ball.getVelocity().y);
					ball2.score += abs(ball2.getVelocity().x) + abs(ball2.getVelocity().y);
					
					skupenScore += ball.score + ball2.score;
					std::cout << "Skupen score: " << skupenScore << std::endl;
					
 				}
			}
		}
	}

}

void World::ballSquareCollision() {         //preverjanje kolizije med pravokotniki in zogicami (ni najbolj optimalen nacin preverjanja saj mora pogledati vse kombinacije zogic, mozna implementacija bolsjega algoritma
	for (Pravokotnik& pravokotnik : pravokotniki) {
		for (Ball& ball : balls) {
			if (collision.ballSquareOverlap(ball, pravokotnik)) {
				//neka enacba
				if (ball.getPosition().x - ball.getRadius() < pravokotnik.getPosition().x) {

					ball.setPosition(ball.getPosition().x, ball.getPosition().y);
					ball.setVelocity(+ball.getVelocity().x, ball.getVelocity().y);
				}
				else if (ball.getPosition().x + ball.getRadius() > pravokotnik.getPosition().x) {
					ball.setPosition(ball.getPosition().x, ball.getPosition().y);
					ball.setVelocity(-ball.getVelocity().x, ball.getVelocity().y);
				}
				
			}
		}
		
	}
}

void World::ballGroundOverlap() {    //preveri kolizijo med zogico in tlemi
	for (Ball& ball : balls) {
	     if (ball.getPosition().y > 600 - ball.getRadius()) {
		ball.setPosition(ball.getPosition().x, 600 - ball.getRadius());
		ball.setVelocity(ball.getVelocity().x, 0);
		gameState = 1;
		 }
		 else {
			 gameState = 0;
			
		 }
	}
}

void World::ballPaddleCollision() {      //preveri kolizijo med zogico in paddlom
	
	for (Paddle& paddle : paddles) {
		for (Ball& ball : balls) {
			if (collision.ballPaddleOverlap(ball, paddle)) {
				//neka enacba
				if (ball.getPosition().y + ball.getRadius() > paddle.getPosition().y) {

					ball.setPosition(ball.getPosition().x, ball.getPosition().y);
					ball.setVelocity(+ball.getVelocity().x, -ball.getVelocity().y);
				}
			

			}
		}

	}
}

bool World::dragBall(sf::Vector2f point) {      //preveri ce kliknes na zogico
	for (Ball& ball : balls) {
		if (collision.ballPointOverlap(sf::Vector2f(point.x, point.y), ball)) {
			draggedBall = &ball;
			return true;
		}
	}
	return false;
}

void World::movePaddleLeft() {     //premakni paddle levo, konstantna hitrost
	Pravokotnik& pravokotnik = pravokotniki.at(0);
	for (Paddle& paddle : paddles) {
		if (paddle.getPosition().x - paddle.getSize().x / 2 > pravokotnik.getPosition().x) {
			paddle.setPosition(paddle.getPosition().x - 15, paddle.getPosition().y);
		}
		
	}
	
}

void World::movePaddleRight() {       //premakni paddle desno, konstantna hitrost
	Pravokotnik& pravokotnik = pravokotniki.at(1);
	for (Paddle& paddle : paddles) {
		if (paddle.getPosition().x + paddle.getSize().x / 2 < pravokotnik.getPosition().x-pravokotnik.getSize().x) {
			paddle.setPosition(paddle.getPosition().x + 15, paddle.getPosition().y);
		}
	}
}

void World::setDraggedVelocity(float x, float y) {  //nastavi hitrost ko potegnem za zogico, hitrost odvisna od razdalje med misko in srediscem zogice
	if (draggedBall) {
		draggedBall->setVelocity((draggedBall->getPosition().x - x) / 100,
			(draggedBall->getPosition().y - y) / 100);

		draggedBall = nullptr;
	}
}




Ball* World::getDraggedBall() const {
	return draggedBall;
}


std::vector<Ball> World::getBalls() const {
	return balls;
}

std::vector<Pravokotnik> World::getPravokotnik() const {
	return pravokotniki;
}

std::vector<Paddle> World::getPaddle() const {
	return paddles;
}


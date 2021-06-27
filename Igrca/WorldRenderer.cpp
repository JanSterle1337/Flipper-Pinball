#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(World& world) : world(world) {}

WorldRenderer::~WorldRenderer() {}

void WorldRenderer::render(sf::RenderWindow& window) const {  //klicanje vseh funkcij za rendranje objektov
	renderBalls(window);
	renderPravokotniki(window);
	renderPaddles(window);
	
}

//zoge,pravokotniki,paddle so shranjeni v vektorju...funkcije loopajo cez vektor ter jih narisejo na zaslon

void WorldRenderer::renderBalls(sf::RenderWindow& window) const {
	for (Ball ball : world.getBalls()) {
		ball.draw(window);
	}
}

void WorldRenderer::renderPravokotniki(sf::RenderWindow& window) const {
	for (Pravokotnik pravokotnik : world.getPravokotnik()) {
		pravokotnik.draw(window);
	}
}

void WorldRenderer::renderPaddles(sf::RenderWindow& window) const {
	for (Paddle paddle : world.getPaddle()) {
		paddle.draw(window);
	}
}


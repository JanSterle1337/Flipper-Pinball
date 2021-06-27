#pragma once
#ifndef WORLDRENDERER_H
#define WORLDRENDERER_H
#include <SFML/Graphics.hpp>
#include "World.h"

class WorldRenderer {

public:
	WorldRenderer(World& world);
	~WorldRenderer();

	void render(sf::RenderWindow& window) const;
	void renderBalls(sf::RenderWindow& window) const;
	void renderPravokotniki(sf::RenderWindow& window) const;
	void renderPaddles(sf::RenderWindow& window) const;
	
private:
	World& world;
};

#endif
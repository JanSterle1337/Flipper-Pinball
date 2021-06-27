#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "pravokotnik.h"
#include "WorldRenderer.h"
#include <vector>
#include <time.h>
#include "World.h"
#include "Paddle.h"
#include <iostream>
#include <string>
#include <fstream>

using std::cout; using std::cin;
using std::endl; using std::string;



int main() {

	std::ofstream ScoreDat("C:/Users/janst/source/repos/igrca/Igrca/score.txt", std::ios::out | std::ios::app);    //file za shranjevanje scora
	


	const int width = 1000;
	const int height = 600;
	sf::RenderWindow window(sf::VideoMode(width, height), "Flipper", sf::Style::Close);   //definicija windowa

	srand((unsigned)(time(NULL)));

	sf::Font font;                      //definicija startmenu texta
	sf::Text startMenuText;
	startMenuText.setFont(font);
	startMenuText.setFillColor(sf::Color::Red);
	startMenuText.setCharacterSize(40);
	startMenuText.setOutlineThickness(5);
	startMenuText.setOutlineColor(sf::Color::Black);
	startMenuText.setString("Press enter to start Bastetov Flipper...");
	startMenuText.setPosition(100, 270);
	//startMenuText.setOrigin(startMenuText.getPosition().x, startMenuText.getPosition().y);
	std::cout << startMenuText.getPosition().x << " " << startMenuText.getPosition().y << std::endl;



	World world;    //kreiranje našega glavnega objekta world, ki vsebuje še objekte collision, ball...
	 
	sf::Texture t;                                 //nastavitev background(klicem ga le ob igranju igre
	t.loadFromFile("background/whitey.jpg");
	sf::Sprite s(t);
	s.setScale(2, 2);

	//float neki = World::skupenScore;
	
	if (!font.loadFromFile("Fonts/nekineki.otf")) {     //preverimo ce se je font naloziw iz fila

		std::cout << "Failed to load font" << std::endl;
	}

	while (window.isOpen() && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) {    //odpre se nam zacetni window
		window.clear(sf::Color::White);
		window.draw(startMenuText);
		window.display();
	}
	


	int skupek = int(world.skupenScore);    
	sf::Text scoreText;                   //definicija scoreTexta
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::Blue);
	scoreText.setPosition(100, 100);
	scoreText.setString(std::to_string(skupek));

	 
	sf::Text text;            //definicija texta
	string score = "Score: ";
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Blue);
	text.setPosition(5, 100);
	text.setString(score);

	
	
	WorldRenderer worldRenderer(world);    //kreiranje objekta za rendranje nasih objektov

	sf::Vertex line[] = { sf::Vertex(sf::Vector2f(-1, -1)), sf::Vertex(sf::Vector2f(-1, -1)) };          //definica lina
	
	bool dragging = false;

	float deltatime = 0.f;     //definicija deltatime, pomaga nam da zoge letijo bolj smooth
	sf::Clock clock;





	while (window.isOpen()) {        //basiclly glavni program kind of
		sf::Event event;

		deltatime = clock.restart().asSeconds();

		while (window.pollEvent(event)) {         //ob razlicnih eventih se zgodijo razlicne stvari ==> check code
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {

					sf::Vector2i point = sf::Mouse::getPosition(window);

					if (world.dragBall(sf::Vector2f((float)point.x, (float)point.y))) {
						dragging = true;
					}
				}
				break;

			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {

					world.setDraggedVelocity(line[1].position.x, line[1].position.y);

					dragging = false;
				}
				break;

			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					world.movePaddleLeft();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					world.movePaddleRight();
				}

				break;

			
			}
		}
	
		if (dragging) {                                                //ce je dragging true seoravi ce kliknes na zogo un povleces potem je dragging true
			sf::Vector2i point = sf::Mouse::getPosition(window);

			line[0] = sf::Vertex(sf::Vector2f(world.getDraggedBall()->getPosition()), sf::Color::Blue);
			line[1] = sf::Vertex(sf::Vector2f((float)point.x, (float)point.y), sf::Color::Blue);
		}

		world.update(deltatime);
		
		while (world.gameState == 1 && window.isOpen()) {       //ce se zgodi da zoga zadane tla, potem zacne prikazat end tekst ter shrani score v datoteko
			
			


			string endText = "Konec igre, pojdi spat";                 
			sf::Text endMenuText;
			endMenuText.setFont(font);
			endMenuText.setCharacterSize(40);
			endMenuText.setFillColor(sf::Color::Red);
			endMenuText.setOutlineColor(sf::Color::Black);
			endMenuText.setOutlineThickness(3);
			endMenuText.setPosition(275, 270);
			endMenuText.setString(endText);

				window.clear(sf::Color::White);
				window.draw(endMenuText);
				window.display();
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))) {
					if (ScoreDat.is_open()) {
						ScoreDat <<"Tvoje trenutno dosezen score: "<< int(world.skupenScore) << "\n" ;
						ScoreDat.close();
					}
					else {
						std::cout << "Nemorem odpreti datoteke" << std::endl;
					}

					return 0;   //ce vse drzi potem se program zakljuci
				}
			
			
			
		  
		}

		window.clear(sf::Color::White);        //risanje scora
		window.draw(s);
		int skupek = int(world.skupenScore);
		scoreText.setString(std::to_string(skupek));
		window.draw(text);
		window.draw(scoreText);
		
		worldRenderer.render(window);  //risanje samih zogic, pravokotnikov...
		
		if (dragging) {
			window.draw(line, 2, sf::Lines);
		}
		window.display();

	}




	return 0;
}
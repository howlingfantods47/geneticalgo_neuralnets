/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/2015 03:01:58 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Neel Shah (), neelshah.sa@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <SFML/Graphics.hpp>
#include "creature.h"
#include "environment.h"
#include <cstdlib>
#include <ctime>



namespace Parameters{
	const float gridSize = 500;
	const size_t numPlants = 50;
	const size_t initCreatures = 20;
	const float maxHealth = 500;
	const float timeStamp = 1;
	const float collisionRad = 3;
	const float healthLossRate = 1;
	const float foodHealthGain = 20;
};

typedef sf::CircleShape Circle;
typedef sf::Vector2f V2;



int main(int argc, char* argv[]){
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(Parameters::gridSize, Parameters::gridSize), "Artificial Life Simulation");
	Environment env;
	env.initialize();
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		env.draw(window);
		env.update();
		window.display();
	}
	return 0;
}


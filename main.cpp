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
	const size_t numPlants = 100;
	const size_t initCreatures = 50;
	const float maxHealth = 200;
	const float timeStamp = 1;
	const float collisionRad = 1;
};

typedef sf::CircleShape Circle;
typedef sf::Vector2f V2;

void drawPlants(Environment& env, sf::RenderWindow& window){
	for(size_t i=0; i<env.numPlants(); ++i){
		V2 tempPos;
		env.getPlantPos(i, tempPos);
		Circle circ(3);
		circ.setPosition(tempPos);
		circ.setFillColor(sf::Color::Green);
		window.draw(circ);
	}
}

void drawCreatures(Environment& env, sf::RenderWindow& window){
	for(size_t i=0; i<env.numCreatures(); ++i){
		float angle;
		V2 tempPos, tempVel;
		env.getCreaturePos(i, tempPos);
		env.getCreatureVel(i, tempVel);
		Circle circ(6,3);
		circ.setPosition(tempPos);
		circ.setFillColor(sf::Color::Blue);
		angle = 180.0/M_PI*atan(tempVel.y/tempVel.x);
		angle = (angle>=0) ? angle : (angle+360);
		circ.setRotation(angle);
		window.draw(circ);
	}
}


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
		drawPlants(env, window);
		drawCreatures(env, window);
		env.updateCreatures();
		window.display();
	}
	return 0;
}


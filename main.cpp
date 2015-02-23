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


const float Parameters::gridSize = 1000;
const float Parameters::searchRad = 10;
const size_t Parameters::initNumPlants = 100;


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
		window.display();
	}
	return 0;
}


/*
 * =====================================================================================
 *
 *       Filename:  environment.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/2015 06:43:35 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Neel Shah (), neelshah.sa@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "environment.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <cmath>
#include <SFML/System.hpp>


void Environment::initialize(){
	plants.resize(Parameters::NumPlants);
	float tx, ty, norm;
	float size = Parameters::gridSize;
	for(size_t i=0; i<plants.size(); ++i){
		tx = size*rand()/(double)RAND_MAX;
		ty = size*rand()/(double)RAND_MAX;
		plants[i].setXY(tx, ty);
	}
	creatures.resize(Parameters::InitCreatures);
	for(size_t i=0; i<creatures.size(); ++i){
		tx = size*rand()/(double)RAND_MAX;
		ty = size*rand()/(double)RAND_MAX;
		creatures[i].setXY(tx, ty);
	}
	for(size_t i=0; i<creatures.size(); ++i){
		tx = 2*rand()/(double)RAND_MAX - 1;
		ty = 2*rand()/(double)RAND_MAX - 1;
		norm = sqrt(pow(tx,2) + pow(ty,2));
		tx /= norm;
		ty /= norm;
		creatures[i].setvXY(tx, ty);
	}

}


/*void Environment::getPlantPos(size_t i, sf::Vector2<float>& pos){
	//if(i >= plants.size())	throw std::invalid_argument("index out of bounds");
	plants[i].getXY(pos);
}


void Environment::getCreaturePos(size_t i, sf::Vector2<float>& pos){
	//if(i >= plants.size())	throw std::invalid_argument("index out of bounds");
	creatures[i].getXY(pos);
}

void Environment::getCreatureVel(size_t i, sf::Vector2<float>& vel){
	//if(i >= plants.size())	throw std::invalid_argument("index out of bounds");
	creatures[i].getvXY(vel);
}
*/

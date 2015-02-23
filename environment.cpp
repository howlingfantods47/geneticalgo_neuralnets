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
#include <SFML/System.hpp>


void Environment::initialize(){
	plants.resize(Parameters::initNumPlants);
	float tx, ty;
	float size = Parameters::gridSize;
	for(size_t i=0; i<plants.size(); ++i){
		tx = size*rand()/(double)RAND_MAX;
		ty = size*rand()/(double)RAND_MAX;
		plants[i].setXY(tx, ty);
	}
}


void Environment::getPlantPos(size_t i, sf::Vector2<float>& pos){
	//if(i >= plants.size())	throw std::invalid_argument("index out of bounds");
	plants[i].getXY(pos);
}


void Environment::getCreaturePos(size_t i, sf::Vector2<float>& pos){
	//if(i >= plants.size())	throw std::invalid_argument("index out of bounds");
	creatures[i].getXY(pos);
}


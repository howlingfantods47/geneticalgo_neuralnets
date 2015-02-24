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
//#include <stdexcept>
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

void Environment::updateCreatures(){
	sf::Vector2f newPos, vel;
	for(size_t i=0; i<creatures.size(); ++i){
		creatures[i].getXY(newPos);
		creatures[i].getvXY(vel);
		newPos += vel*Parameters::timeStamp;
		newPos.x = (newPos.x>=0) ? fmod(newPos.x, Parameters::gridSize) : (Parameters::gridSize + newPos.x) ;
		newPos.y = (newPos.y>=0) ? fmod(newPos.y, Parameters::gridSize) : (Parameters::gridSize + newPos.y) ;
		creatures[i].setXY(newPos);
	}
}

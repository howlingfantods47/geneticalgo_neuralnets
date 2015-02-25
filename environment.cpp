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

#include "creature.h"
#include "environment.h"
#include "helper.h"
#include <cstdlib>
#include <ctime>
//#include <iostream>
//#include <stdexcept>
#include <cmath>
#include <SFML/System.hpp>


void Environment::initialize(){
	plants.resize(Parameters::numPlants);
	float tx, ty, norm;
	float size = Parameters::gridSize;
	for(size_t i=0; i<plants.size(); ++i){
		tx = size*rand()/(double)RAND_MAX;
		ty = size*rand()/(double)RAND_MAX;
		plants[i].setXY(tx, ty);
	}
	creatures.resize(Parameters::initCreatures);
	for(size_t i=0; i<creatures.size(); ++i){
		tx = size*rand()/(double)RAND_MAX;
		ty = size*rand()/(double)RAND_MAX;
		creatures[i].setXY(tx, ty);
		creatures[i].setHealth(Parameters::maxHealth);
	}
	for(size_t i=0; i<creatures.size(); ++i){
		tx = 2.0*rand()/(double)RAND_MAX - 1;
		ty = 2.0*rand()/(double)RAND_MAX - 1;
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
	this->checkCollisions();
	this->updateSensors();
}

// This thing can be heavily optimized. Just writing terrible brute force for now to get the pieces working.
// Possible approach -  Divide space into bins/grids, make lookup tables for each bin, search only locally, so on.
// This can be further improved with better data structures, but requires more planning, so TODO.
void Environment::updateSensors(){
	std::vector<float> distPlants;
	std::vector<float> distCreatures;
	distPlants.resize(plants.size());
	distCreatures.resize(creatures.size());
	sf::Vector2f tempPos, curPos, foodSensor, mateSensor;
	for(size_t k=0; k<creatures.size(); ++k){
		creatures[k].getXY(curPos);
		for(size_t i=0; i<plants.size(); ++i){
			this->getPlantPos(i, tempPos);
			distPlants[i] = Helper::euclideanDist(curPos, tempPos);
		}
		for(size_t i=0; i<creatures.size(); ++i){
			this->getCreaturePos(i, tempPos);
			distCreatures[i] = Helper::euclideanDist(curPos, tempPos);
		}
		size_t idClosestPlant, idClosestCreature;
		idClosestPlant = std::min_element(distPlants.begin(), distPlants.end()) - distPlants.begin();
		idClosestCreature = std::min_element(distCreatures.begin(), distCreatures.end()) - distCreatures.begin();
		this->getPlantPos(idClosestPlant, foodSensor);
		this->getCreaturePos(idClosestCreature, mateSensor);
		creatures[k].setFoodSensor(foodSensor);
		creatures[k].setMateSensor(mateSensor);
	}
}


void Environment::checkCollisions(){

}

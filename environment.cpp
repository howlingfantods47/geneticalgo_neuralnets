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
		plants[i].setFlagEdible(true);
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
		creatures[i].setHealth(creatures[i].getHealth() - Parameters::healthLossRate);
	}
	this->updateSensors();
	this->checkCollisions();
}

// TODO - This thing can be heavily optimized. Just writing terrible brute force for now to get the pieces working.
// Most likely approach -  Divide space into bins/grids, make lookup tables for each bin, search only locally, so on.
// Check out ANN - Approximate Nearest Neighbors (http://www.cs.umd.edu/~mount/ANN/)
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
		creatures[k].setIDFoodSensor(idClosestPlant);
		creatures[k].setDistFood(distPlants[idClosestPlant]);
		creatures[k].setFoodSensor(foodSensor);
		creatures[k].setIDMateSensor(idClosestCreature);
		creatures[k].setDistMate(distCreatures[idClosestCreature]);
		creatures[k].setMateSensor(mateSensor);
	}
}


void Environment::checkCollisions(){
	std::vector<size_t> deadPlants;
	size_t tempID;
	for(size_t i=0; i<creatures.size(); ++i){
		if(creatures[i].getDistFood() <= Parameters::collisionRad){
			tempID = creatures[i].getIDFood();
			if(!(plants[tempID].getFlagEdible()))	continue;
			// eat the food, store plant id for removal at end, flip edible flag
			creatures[i].setHealth(creatures[i].getHealth() + Parameters::foodHealthGain);
			deadPlants.push_back(tempID);
			plants[tempID].setFlagEdible(false);
		}
	}
	// isntead of deleting and then growing, just replace dead plants with new random positions.
	float size = Parameters::gridSize;
	float tx, ty;
	for(size_t i=0; i<deadPlants.size(); ++i){
		tx = size*rand()/(double)RAND_MAX;
		ty = size*rand()/(double)RAND_MAX;
		plants[deadPlants[i]].setXY(tx, ty);
		plants[deadPlants[i]].setFlagEdible(true);
	}
}

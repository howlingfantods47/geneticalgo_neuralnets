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
#include <algorithm>
#include <ctime>
//#include <iostream>
//#include <stdexcept>
#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

typedef sf::CircleShape Circle;
typedef sf::Vector2f V2;


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
		tx = 2.0*rand()/(double)RAND_MAX - 1;
		ty = 2.0*rand()/(double)RAND_MAX - 1;
		norm = sqrt(pow(tx,2) + pow(ty,2));
		tx /= norm;
		ty /= norm;
		creatures[i].setvXY(tx, ty);
		creatures[i].initBrain();
	}
}

void Environment::draw(sf::RenderWindow& window){
	this->drawPlants(window);
	this->drawCreatures(window);
}

void Environment::drawPlants(sf::RenderWindow& window){
	for(size_t i=0; i<this->numPlants(); ++i){
		V2 tempPos;
		this->getPlantPos(i, tempPos);
		Circle circ(3);
		circ.setPosition(tempPos);
		circ.setFillColor(sf::Color::Green);
		window.draw(circ);
	}
}

void Environment::drawCreatures(sf::RenderWindow& window){
	for(size_t i=0; i<this->numCreatures(); ++i){
		float angle;
		V2 tempPos, tempVel;
		this->getCreaturePos(i, tempPos);
		this->getCreatureVel(i, tempVel);
		Circle circ(6,3);
		circ.setPosition(tempPos);
		circ.setFillColor(sf::Color::Blue);
		angle = 180.0/M_PI*atan(tempVel.y/tempVel.x);
		angle = (angle>=0) ? angle : (angle+360);
		circ.setRotation(angle);
		window.draw(circ);
	}
}


void Environment::update(){
	this->updateCreatures();
	this->updateSensors();
	this->processBrains();
	this->checkCollisions();
}


void Environment::updateCreatures(){
	sf::Vector2f newPos, vel;
	std::vector<size_t> deadCreatures;
	for(size_t i=0; i<creatures.size(); ++i){
		creatures[i].getXY(newPos);
		creatures[i].getvXY(vel);
		newPos += vel*Parameters::timeStamp;
		newPos.x = (newPos.x>=0) ? fmod(newPos.x, Parameters::gridSize) : (Parameters::gridSize + newPos.x) ;
		newPos.y = (newPos.y>=0) ? fmod(newPos.y, Parameters::gridSize) : (Parameters::gridSize + newPos.y) ;
		creatures[i].setXY(newPos);
		if(creatures[i].getHealth() <= Parameters::healthLossRate)	deadCreatures.push_back(i); 
		creatures[i].setHealth(creatures[i].getHealth() - Parameters::healthLossRate);
	}
	// have to delete in reverse order to avoid shifting indices at each step. Also, I know indices are added 
	// in ascending order, so no need of sorting.
	std::reverse(deadCreatures.begin(), deadCreatures.end());
	for(size_t i=0; i<deadCreatures.size(); ++i){
		creatures.erase(creatures.begin() + deadCreatures[i]);
	}
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


void Environment::processBrains(){
	std::vector<float> inputs, outputs;
	for(size_t i=0; i<creatures.size(); ++i){
		creatures[i].compute(inputs, outputs);
	}
}

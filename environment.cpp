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
	this->plants.resize(Parameters::numPlants);
	float tx, ty, norm;
	float size = Parameters::gridSize;
	for(size_t i=0; i<this->plants.size(); ++i){
		tx = size*rand()/(double)RAND_MAX;
		ty = size*rand()/(double)RAND_MAX;
		this->plants[i].setXY(tx, ty);
		this->plants[i].setFlagEdible(true);
	}
	this->creatures.resize(Parameters::initCreatures);
	for(size_t i=0; i<this->creatures.size(); ++i){
		tx = size*rand()/(double)RAND_MAX;
		ty = size*rand()/(double)RAND_MAX;
		this->creatures[i].setXY(tx, ty);
		this->creatures[i].setHealth(Parameters::maxHealth);
		tx = 2.0*rand()/(double)RAND_MAX - 1;
		ty = 2.0*rand()/(double)RAND_MAX - 1;
		norm = sqrt(pow(tx,2) + pow(ty,2));
		tx /= norm;
		ty /= norm;
		this->creatures[i].setvXY(tx, ty);
		this->creatures[i].initBrain();
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
	for(size_t i=0; i<this->creatures.size(); ++i){
		this->creatures[i].getXY(newPos);
		this->creatures[i].getvXY(vel);
		newPos += vel*Parameters::timeStamp;
		newPos.x = (newPos.x>=0) ? fmod(newPos.x, Parameters::gridSize) : (Parameters::gridSize + newPos.x) ;
		newPos.y = (newPos.y>=0) ? fmod(newPos.y, Parameters::gridSize) : (Parameters::gridSize + newPos.y) ;
		this->creatures[i].setXY(newPos);
		if(this->creatures[i].getHealth() <= Parameters::healthLossRate)	deadCreatures.push_back(i); 
		this->creatures[i].setHealth(creatures[i].getHealth() - Parameters::healthLossRate);
	}
	// have to delete in reverse order to avoid shifting indices at each step. Also, I know indices are added 
	// in ascending order, so no need of sorting.
	std::reverse(deadCreatures.begin(), deadCreatures.end());
	for(size_t i=0; i<deadCreatures.size(); ++i){
		this->creatures.erase(creatures.begin() + deadCreatures[i]);
	}
}

// TODO - This thing can be heavily optimized. Just writing terrible brute force for now to get the pieces working.
// Most likely approach -  Divide space into bins/grids, make lookup tables for each bin, search only locally, so on.
// Check out ANN - Approximate Nearest Neighbors (http://www.cs.umd.edu/~mount/ANN/)
void Environment::updateSensors(){
	sf::Vector2f tempPos, currentPos, foodSensor, mateSensor;
	float minDistPlants, minDistCreatures;
	float tempDist;
	size_t idClosestPlant, idClosestCreature;
	for(size_t k=0; k<this->creatures.size(); ++k){
		this->creatures[k].getXY(currentPos);
		minDistPlants = 1000000000000;
		idClosestPlant = 0;
		for(size_t i=0; i<this->plants.size(); ++i){
			this->getPlantPos(i, tempPos);
			tempDist = Helper::euclideanDist(currentPos, tempPos);
			if(tempDist < minDistPlants){
				minDistPlants = tempDist;
				idClosestPlant = i;
			}
		}
		minDistCreatures = 1000000000000;
		idClosestCreature = 0;
		for(size_t i=0; i<this->creatures.size(); ++i){
			this->getCreaturePos(i, tempPos);
			tempDist = Helper::euclideanDist(currentPos, tempPos);
			if(tempDist < minDistCreatures){
				minDistCreatures = tempDist;
				idClosestCreature = i;
			}
		}
		this->getPlantPos(idClosestPlant, foodSensor);
		this->getCreaturePos(idClosestCreature, mateSensor);
		this->creatures[k].setIDFoodSensor(idClosestPlant);
		this->creatures[k].setDistFood(minDistPlants);
		this->creatures[k].setFoodSensor(foodSensor);
		this->creatures[k].setIDMateSensor(idClosestCreature);
		this->creatures[k].setDistMate(minDistCreatures);
		this->creatures[k].setMateSensor(mateSensor);
	}
}


void Environment::checkCollisions(){
	// food collisions
	std::vector<size_t> deadPlants;
	size_t tempID;
	for(size_t i=0; i<this->creatures.size(); ++i){
		if(this->creatures[i].getDistFood() <= Parameters::collisionRad){
			tempID = this->creatures[i].getIDFood();
			if(!(this->plants[tempID].getFlagEdible()))	continue;
			// eat the food, store plant id for removal at end, flip edible flag
			this->creatures[i].setHealth(this->creatures[i].getHealth() + Parameters::foodHealthGain);
			deadPlants.push_back(tempID);
			this->plants[tempID].setFlagEdible(false);
		}
	}
	// isntead of deleting and then growing, just replace dead plants with new random positions.
	float size = Parameters::gridSize;
	float tx, ty;
	for(size_t i=0; i<deadPlants.size(); ++i){
		tx = size*rand()/(double)RAND_MAX;
		ty = size*rand()/(double)RAND_MAX;
		this->plants[deadPlants[i]].setXY(tx, ty);
		this->plants[deadPlants[i]].setFlagEdible(true);
	}


	// mate collisions
	// maybe make mate radius more than food radius, since it is less likelier to mate.

}


void Environment::processBrains(){
	std::vector<float> inputs, outputs;
	for(size_t i=0; i<this->creatures.size(); ++i){
			this->creatures[i].compute(inputs, outputs);
	}
}

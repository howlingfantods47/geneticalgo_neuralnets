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

#include <iostream>

typedef sf::CircleShape Circle;
typedef sf::Vector2f V2;

using namespace std;

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
		this->creatures[i].setFlagHorny(true);
		this->creatures[i].setGeneration(0);
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
		size_t alpha;
		V2 tempPos, tempVel;
		this->getCreaturePos(i, tempPos);
		this->getCreatureVel(i, tempVel);
		Circle circ(6,3);
		circ.setPosition(tempPos);
		alpha = this->creatures[i].getGeneration()*50+50;
		alpha = (alpha<256) ? alpha : 255;
		sf::Color col(0,0,255,alpha);
		circ.setFillColor(col);
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
			if(i == k)	continue;
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
	size_t foodID;
	for(size_t i=0; i<this->creatures.size(); ++i){
		if(this->creatures[i].getDistFood() <= Parameters::collisionRad){
			foodID = this->creatures[i].getIDFood();
			if(!(this->plants[foodID].getFlagEdible()))	continue;
			// eat the food, store plant id for removal at end, flip edible flag
			this->creatures[i].setHealth(this->creatures[i].getHealth() + Parameters::foodHealthGain);
			deadPlants.push_back(foodID);
			this->plants[foodID].setFlagEdible(false);
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
	// maybe make mate radius more than food radius later, since it is less likelier to mate.
	size_t mateID;
	std::vector<Creature<float> > offspring;
	for(size_t i=0; i<this->creatures.size(); ++i){
		if(this->creatures[i].getDistMate() <= Parameters::collisionRad){
			if(!(this->creatures[i].getFlagHorny()))	continue;
			mateID = this->creatures[i].getIDMate();
			if(!(this->creatures[mateID].getFlagHorny()))	continue;
			// mate, create child at random position with random velocity with genes combined from parents
			// TODO have cost of sex and health check before mating
			Creature<float> child;
			this->sexyTimes(this->creatures[i], this->creatures[mateID], child);
			this->creatures[i].setFlagHorny(false);
			this->creatures[mateID].setFlagHorny(false);
			offspring.push_back(child);
		}
	}
	this->creatures.insert(this->creatures.end(), offspring.begin(), offspring.end());
}



// make this more general later for better brain/NN topologies.
void Environment::processBrains(){
	std::vector<float> inputs, outputs;
	inputs.resize(4);
	outputs.resize(2);
	float norm;
	V2 pos;
	for(size_t i=0; i<this->creatures.size(); ++i){
		this->creatures[i].getXY(pos);
		inputs[0] = this->creatures[i].getFoodSensorX() - pos.x;
		inputs[1] = this->creatures[i].getFoodSensorY() - pos.y;
		inputs[2] = this->creatures[i].getMateSensorX() - pos.x;
		inputs[3] = this->creatures[i].getMateSensorY() - pos.y;
		this->creatures[i].compute(inputs, outputs);
		norm = sqrt(pow(outputs[0],2) + pow(outputs[1],2));
		outputs[0] /= norm;
		outputs[1] /= norm;
		this->creatures[i].setvXY(outputs[0], outputs[1]);
	}
}
// Current algorithm - not making explicit DNA strand. Just pick one of parents' weights randomly for each edge.
void Environment::sexyTimes(Creature<float> father, Creature<float>& mother, Creature<float>& child){
	float size = Parameters::gridSize;
	float tx, ty, norm;
	tx = size*rand()/(double)RAND_MAX;
	ty = size*rand()/(double)RAND_MAX;
	child.setXY(tx, ty);
	child.setHealth(Parameters::maxHealth);
	tx = 2.0*rand()/(double)RAND_MAX - 1;
	ty = 2.0*rand()/(double)RAND_MAX - 1;
	norm = sqrt(pow(tx,2) + pow(ty,2));
	tx /= norm;
	ty /= norm;
	child.setvXY(tx, ty);
	child.setFlagHorny(true);
	child.setGeneration(1+std::max(father.getGeneration(), mother.getGeneration()));

	// mating starts below
	std::vector<std::vector<float> > weights1, weights2, childWeights;
	std::vector<float> bias1, bias2, childBiases;
	father.getBrainWeights(weights1, bias1);
	mother.getBrainWeights(weights2, bias2);
	childWeights.resize(weights1.size());
	childBiases.resize(bias1.size());
	for(size_t i=0; i<childWeights.size(); ++i){
		childWeights.resize(weights1[0].size());
	}
	for(size_t i=0; i<childWeights.size(); ++i){
		for(size_t j=0; j<childWeights[i].size(); ++j){
			childWeights[i][j] = (rand()%2==0) ? weights1[i][j] : weights2[i][j];
		}
		childBiases[i] = (rand()%2==0) ? bias1[i] : bias2[i];
	}
	child.setBrainWeights(childWeights, childBiases);
}

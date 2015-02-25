/*
 * =====================================================================================
 *
 *       Filename:  environment.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/2015 06:30:34 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Neel Shah (), neelshah.sa@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  environment_INC
#define  environment_INC



#include "creature.h"
#include <vector>
#include <SFML/System.hpp>

namespace Parameters{
	extern const float gridSize;
	extern const float searchRad;
	extern const size_t numPlants;
	extern const size_t initCreatures;
	extern const float maxHealth;
	extern const float timeStamp;
	extern const float collisionRad;
	extern const float healthLossRate;
	extern const float foodHealthGain;
};


class Environment{
	private:
		std::vector<Plant<float> > plants;
		std::vector<Creature<float> > creatures;
	public:
		void getPlantPos(size_t i, sf::Vector2<float>& pos){
			plants[i].getXY(pos);
		}
		void getCreaturePos(size_t i, sf::Vector2<float>& pos){
			creatures[i].getXY(pos);
		}
		void getCreatureVel(size_t i, sf::Vector2<float>& vel){
			creatures[i].getvXY(vel);
		}
		size_t numPlants(){	return plants.size(); }
		size_t numCreatures(){	return creatures.size(); }
		void initialize();
		//void growPlants();	//incorporated into checkCollisions()
		void updateCreatures();
		void updateSensors();
		void checkCollisions();
};



#endif   /* ----- #ifndef environment_INC  ----- */


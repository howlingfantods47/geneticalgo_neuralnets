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
	extern const size_t NumPlants;
	extern const size_t InitCreatures;
	extern const float maxHealth;
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
		void growPlants();
		friend void Creature<float>::senseSurroundings();
};



#endif   /* ----- #ifndef environment_INC  ----- */


/*
 * =====================================================================================
 *
 *       Filename:  creature.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/2015 01:59:37 AM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Neel Shah (), neelshah.sa@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  creature_INC
#define  creature_INC



#include <vector>
#include <cstdlib>
#include <SFML/System.hpp>


template<class NumType> class Plant{
	private:
		sf::Vector2<NumType> position;
	public:
		/*  Plant(){ x = 0; y = 0; }
		Plant(NumType a, NumType b){
			x = a;
			y = b;
		}*/
		void setXY(NumType a, NumType b){
			position.x = a;
			position.y = b;
		}
		void getXY(sf::Vector2<NumType>& pos){
			pos.x = position.x;
			pos.y = position.y;
		}
};

template<class NumType> class Brain{
	private:
		size_t numInputs, numOutputs;
		std::vector<float> weights;
	public:
		void computeDecision(const std::vector<NumType>& inputs, std::vector<NumType>& outputs);
};

template<class NumType> class Creature{
	private:
		sf::Vector2<NumType> position;
		sf::Vector2<NumType> velocity;
		NumType searchRadius;
		NumType health;
		Brain<NumType> brain;
		size_t DNAlength;
		std::vector<bool> DNA;
		sf::Vector2<NumType> foodSensor;
		sf::Vector2<NumType> mateSensor;
	public:
		void senseSurroundings(); // will take input something from the environment
		void setXY(NumType a, NumType b){
			position.x = a;
			position.y = b;
		}
		void getXY(sf::Vector2<NumType>& pos){
			pos.x = position.x;
			pos.y = position.y;
		}

};



#endif   /* ----- #ifndef creature_INC  ----- */


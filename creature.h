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
#include <cmath>

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
		void setXY(const sf::Vector2<NumType>& pos){
			position.x = pos.x;
			position.y = pos.y;
		}
		void getXY(sf::Vector2<NumType>& pos){
			pos.x = position.x;
			pos.y = position.y;
		}
};

template<class NumType> class Brain{
	private:
		size_t numInputs, numOutputs;
		std::vector< std::vector<float> > weights;

		float activationFunction(float score){
			return 1.0/(1.0+exp(-score));
		}
	public:
		void computeDecision(const std::vector<NumType>& inputs, std::vector<NumType>& outputs);
};

template<class NumType> class Creature{
	private:
		sf::Vector2<NumType> position;
		sf::Vector2<NumType> velocity;
		NumType health;
		NumType searchRadius;
		Brain<NumType> brain;
		size_t DNAlength;
		std::vector<bool> DNA;
		sf::Vector2<NumType> foodSensor;
		sf::Vector2<NumType> mateSensor;
	public:
		void setXY(NumType a, NumType b){
			position.x = a;
			position.y = b;
		}
		void setXY(const sf::Vector2<NumType>& pos){
			position.x = pos.x;
			position.y = pos.y;
		}
		void getXY(sf::Vector2<NumType>& pos){
			pos.x = position.x;
			pos.y = position.y;
		}
		void setvXY(NumType a, NumType b){
			velocity.x = a;
			velocity.y = b;
		}
		void getvXY(sf::Vector2<NumType>& vel){
			vel.x = velocity.x;
			vel.y = velocity.y;
		}
		void setFoodSensor(NumType a, NumType b){
			foodSensor.x = a;
			foodSensor.y = b;
		}
		void setFoodSensor(const sf::Vector2<NumType>& food){
			foodSensor.x = food.x;
			foodSensor.y = food.y;
		}
		void setMateSensor(NumType a, NumType b){
			mateSensor.x = a;
			mateSensor.y = b;
		}
		void setMateSensor(const sf::Vector2<NumType>& mate){
			mateSensor.x = mate.x;
			mateSensor.y = mate.y;
		}

		void setHealth(NumType h){	health = h; }

};



#endif   /* ----- #ifndef creature_INC  ----- */


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
		bool flagEdible;
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
		void setFlagEdible(bool flag){	flagEdible = flag; }
		bool getFlagEdible(){	return flagEdible; }
};

class Brain{
	private:
		size_t numInputs, numOutputs;
		std::vector< std::vector<float> > weights;
		std::vector<float> biases;

		float activationFunction(float score);
	public:
		void computeDecision(std::vector<float>& inputs, std::vector<float>& outputs);
		void randInitWeights();
		void getWeights(std::vector<std::vector<float> >& w, std::vector<float>& b){
			w = this->weights;
			b = this->biases;
		}
		void createBrain(std::vector<std::vector<float> >& weights, std::vector<float>& biases);
};

template<class NumType> class Creature{
	private:
		sf::Vector2<NumType> position;
		sf::Vector2<NumType> velocity;
		NumType health;
		//NumType searchRadius;
		Brain brain;
		//size_t DNAlength;
		//std::vector<bool> DNA;
		sf::Vector2<NumType> foodSensor;
		sf::Vector2<NumType> mateSensor;
		size_t idFoodSensor;
		size_t idMateSensor;
		float distFood;
		float distMate;
		bool flagHorny;
		size_t generationID;
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
		void setvXY(const sf::Vector2<NumType>& vel){
			velocity.x = vel.x;
			velocity.y = vel.y;
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
		NumType getFoodSensorX(){	return foodSensor.x;	}
		NumType getFoodSensorY(){	return foodSensor.y;	}
		NumType getMateSensorX(){	return mateSensor.x;	}
		NumType getMateSensorY(){	return mateSensor.y;	}
		void setIDFoodSensor(size_t id){	idFoodSensor = id;	}
		void setIDMateSensor(size_t id){	idMateSensor = id;	}
		void setDistFood(float d){	distFood = d;	}
		void setDistMate(float d){	distMate = d;	}
		void setHealth(NumType h){	health = h; }
		float getDistFood(){	return distFood; }
		float getDistMate(){	return distMate; }
		size_t getIDFood(){		return idFoodSensor; }
		size_t getIDMate(){		return idMateSensor; }
		NumType getHealth(){	return health; }
		void setFlagHorny(bool flag){	flagHorny = flag; }
		bool getFlagHorny(){	return flagHorny; }
		void setGeneration(size_t gen){	generationID = gen;	}
		size_t getGeneration(){	return generationID;	}

		void setBrainWeights(std::vector<std::vector<float> >& weights, std::vector<float>& biases){
			brain.createBrain(weights, biases);
		}

		void getBrainWeights(std::vector<std::vector<float> >& weights, std::vector<float>& biases){
			brain.getWeights(weights, biases);
		}

		void compute(std::vector<float>& inputs, std::vector<float>& outputs){
			brain.computeDecision(inputs, outputs);
		}

		void initBrain(){	brain.randInitWeights();	}

};



#endif   /* ----- #ifndef creature_INC  ----- */


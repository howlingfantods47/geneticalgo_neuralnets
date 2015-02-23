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

#include <vector>
#include <cstdlib>

template<class NumType> class Plant{
	private:
		NumType x, y;
	public:
		Plant(NumType a, NumType b){
			x = a;
			y = b;
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
		NumType x, y;
		NumType vx, vy;
		NumType searchRadius;
		NumType health;
		Brain<NumType> brain;
		size_t DNAlength;
		std::vector<bool> DNA;
		NumType foodSensorx, foodSensory;
		NumType mateSensorx, mateSensory;
	public:
		void senseSurroundings(); // will take input something from the environment
};

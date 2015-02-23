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
 *       Compiler:  gcc
 *
 *         Author:  Neel Shah (), neelshah.sa@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>

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
		int numInputs, numOutputs;
	public:
		void computeDecision(const vector<NumType>& inputs, vector<NumType>& outputs);
};

template<class NumType> class Creature{
	private:
		NumType x, y;
		NumType vx, vy;
		NumType searchRadius;
		NumType health;
	public:
};

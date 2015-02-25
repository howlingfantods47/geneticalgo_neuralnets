/*
 * =====================================================================================
 *
 *       Filename:  creature.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/24/2015 06:16:10 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Neel Shah (), neelshah.sa@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "creature.h"
#include "helper.h"
#include "environment.h"
#include <vector>
#include <algorithm>

#include <SFML/System.hpp>


template<class NumType> void Brain<NumType>::computeDecision(const std::vector<NumType>& inputs, std::vector<NumType>& outputs){
	outputs.resize(numOutputs);
	for(size_t i=0 ; i<numOutputs; ++i){
		outputs[i] = activationFunction(Helper::dotProduct(inputs, weights[i]));
	}
}




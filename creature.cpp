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


void Brain::computeDecision(std::vector<float>& inputs, std::vector<float>& outputs){
	outputs.resize(numOutputs);
	for(size_t i=0 ; i<numOutputs; ++i){
		outputs[i] = activationFunction(Helper::dotProduct(inputs, weights[i]));
	}
}


float Brain::activationFunction(float score){
	return 1.0/(1.0+exp(-score));
}

void Brain::randInitWeights(){
	numInputs = 4;
	numOutputs = 2;
	weights.resize(numOutputs);
	biases.resize(numOutputs);
	for(size_t i=0; i<numOutputs; ++i){
		weights[i].resize(numInputs);
	}
	for(size_t i=0; i<numOutputs; ++i){
		for(size_t j=0; j<numInputs; ++j){
			weights[i][j] = 2.0*rand()/(double)RAND_MAX - 1;
		}
		biases[i] = 2.0*rand()/(double)RAND_MAX - 1;
	}
}

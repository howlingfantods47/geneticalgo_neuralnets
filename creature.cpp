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
	for(size_t i=0 ; i<this->numOutputs; ++i){
		outputs[i] = activationFunction(Helper::dotProduct(inputs, this->weights[i])+this->biases[i]);
	}
}

void Brain::createBrain(std::vector<std::vector<float> >& w, std::vector<float>& b){
	this->numInputs = w[0].size();
	this->numOutputs = w.size();
	this->weights = w;
	this->biases = b;
}

float Brain::activationFunction(float score){
	return 1.0/(1.0+exp(-score));
}

void Brain::randInitWeights(){
	this->numInputs = 4;
	this->numOutputs = 2;
	this->weights.resize(this->numOutputs);
	this->biases.resize(this->numOutputs);
	for(size_t i=0; i<this->numOutputs; ++i){
		this->weights[i].resize(this->numInputs);
	}
	for(size_t i=0; i<this->numOutputs; ++i){
		for(size_t j=0; j<this->numInputs; ++j){
			this->weights[i][j] = 2.0*rand()/(double)RAND_MAX - 1;
		}
		this->biases[i] = 2.0*rand()/(double)RAND_MAX - 1;
	}
}



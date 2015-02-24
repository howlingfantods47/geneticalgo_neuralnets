/*
 * =====================================================================================
 *
 *       Filename:  helper.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/24/2015 06:44:03 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Neel Shah (), neelshah.sa@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>

namespace Helper{
	template<class NumType1, class NumType2> float dotProduct(const std::vector<NumType1>& x, const std::vector<NumType2>& y){
		float sum = 0.0;
		for(size_t i=0; i<x.size(); ++i){
			sum += (float)x[i]*(float)y[i];
		}
		return sum;
	}
};

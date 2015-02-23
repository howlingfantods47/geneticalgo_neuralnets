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


namespace Parameters{
	extern const float gridSize;
	extern const float searchRad;
	extern const size_t initNumPlants;
};


class Environment{
	private:
		std::vector<Plant<float> > plants;
		std::vector<Creature<float> > creatures;
	public:
		void initialize();
		void growPlants();
		friend void Creature<float>::senseSurroundings();
};



#endif   /* ----- #ifndef environment_INC  ----- */



## Problem Statement

Make a simulation of small creatures (wolves/ants/etc) controlled by neural networks. 
Evolve them with a genetic algorithm, and train them to find food/not die (so they need to keep track of hunger and die accordingly).
Kudos if you can add predator/prey relationships.
C/C++, you can use any graphics lib you want. I suggest SFML since it's very lightweight.


### Basic Architecture 

* Universe - Cartesian 2D toroidal plane
* Plants - bottom of food chain, every time one is eaten, a new one spawns randomly to replace it.
* Animals - eat plants to regain health
	* Have a neural network 'brain' which controls motion
		* Inputs - nearest x and y food location, nearest x and y mate location, picks the nearest one for each.
		* Outputs - x and y velocities 
		* Fully connected to both outputs - logistic activation function for now
	* NN encoded into chromosome - direct encoding into bitstring for now
	* Two animals create offspring by mating if healthy enough
	* Lose health by moving
	* Die if below a health threshold
	* TODO (?) - predator/prey relationship encodings (has to evolve somehow)

* TODO - Optimize search later - brute force search over entire environment for now :/
	* Each creature/plant has a gridID tag which helps searching for food/mates. 
	* Each grid has plant/mate lookup tables maintained.
	* Check out ANN - Approximate Nearest Neighbors (http://www.cs.umd.edu/~mount/ANN/), binary space partitioning, etc. 


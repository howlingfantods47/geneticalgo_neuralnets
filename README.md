
## Problem Statement

Make a simulation of small creatures (wolves/ants/etc) controlled by neural networks. 
Evolve them with a genetic algorithm, and train them to find food/not die (so they need to keep track of hunger and die accordingly).
Kudos if you can add predator/prey relationships.
C/C++, you can use any graphics lib you want. I suggest SFML since it's very lightweight.


### Basic Architecture 

* Universe - Cartesian 2D toroidal plane
* Plants - bottom of food chain - random spawning in each generation
* Animals - eat plants to regain health
	* Have a neural network 'brain' which controls motion
	* NN encoded into chromosome - direct encoding into bitstring for now
	* Two animals create offspring by mating if healthy enough
	* Lose health by moving
	* Die if below a health threshold
	* TODO (?) - predator/prey relationship encodings (has to evolve somehow)


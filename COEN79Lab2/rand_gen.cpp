//rand_gen.cpp


#include <iostream>		//include libraries and header file
#include "random.h"

using namespace std;		//standard namespace

namespace coen79_lab2{
													//default constructor
	rand_gen::rand_gen(int _seed = 1, int _multiplier = 1, int _increment = 1, int _modulus = 1){
		seed = _seed;
		multiplier = _multiplier;
		increment = _increment;
		modulus = _modulus;
			
	}
							//set a new seed
	void rand_gen::set_seed(int newSeed){
		seed = newSeed;
	} 	
							//return next psuedorand int
	int rand_gen::next(){
		seed = (multiplier * seed + increment) % modulus;
		return seed;
	}
							//print seed
	void rand_gen::print_info(){
		cout << "Seed: " <<  seed << endl;
		cout << "Multiplier: " << multiplier <<endl;
		cout << "Increment: " << increment << endl;
		cout << "Modulus: " << modulus << endl;
	}


}



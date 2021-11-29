

#ifndef RAND_NUM_GEN_H
#define RAND_NUM_GEN_H

#include <iostream>
#include <cassert>
	

using namespace std;

namespace coen79_lab2{
	class rand_gen{
		public:
			rand_gen(int _seed, int _multiplier,int _increment, int _modulus);
			//pre:if passed something they better be ints
			//post: object initialized, variables set
		
			void print_info(); 
			//prints info	
			int next();
			//post:returns a pseudo rand and sets new seed
			
			void set_seed(int newSeed);
			//post: sets new seed
		private:
			int seed;
			int multiplier;
			int increment;
			int modulus;
			//store these variables
	};

}

#endif



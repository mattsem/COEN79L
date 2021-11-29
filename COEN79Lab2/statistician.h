// NON-MEMBER functions for the statistician class:
// 
// statistician operator +(const statistician& s1, const statistician& s2)
// Postcondition: The statistician that is returned contains all the// numbers of the sequences of s1 and s2.
// statistician operator *(double scale, const statistician& s)
// // Postcondition: The statistician that is returned contains the same// numbers that s does, but each number has been multiplied by the// scale number.
// // bool operator ==(const statistician& s1, const statistician& s2)
// // Postcondition: The return value is true if s1 and s2 have the zero// length. Also, if the length is greater than zero, then s1 and s2 must// have the same length, the samemean, the same minimum,// the same maximum, and the same sum.

#ifndef STATS_H
#define STATS_H
#include <iostream>

namespace coen79_lab2{
	class statistician{
		private:
			double total; //sum of the elmts
			int size; //num of elements
			double min; //min value
			double max; //max value
			
		public:
			statistician(); //post: initialized 
			
			//modification member functions
			void next(double item);	//pre:must be passed a double
						//post:sequence updated
			void reset();	//pre: object initialized
					//post: sequence reset
			
			//constant member functions
			int length() const;
			double sum() const;
			double mean() const;
			double minimum() const;
			double maximum() const;
			//all do the described math function
			
			//nonmember functions
			//friend functions
			friend statistician operator +(const statistician&, const statistician&);
			friend statistician operator *(double, const statistician&);
			
	};
		

		//not friend :(
		bool operator ==(const statistician&, const statistician&);	
}

#endif






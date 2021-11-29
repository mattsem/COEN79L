//invariants:
//
//the sequence is stored in "data" 
//the number of items is stored in "used"
//the index is in "index"

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <cmath>	

#include "sequence1.h"


using namespace std;

namespace coen79_lab3{
						//constructor	
	sequence::sequence(){
		used = 0;
		index = 0;
	}
						//set index to 0
	void sequence::start(){
		index = 0;
	}	
						//set index to end
	void sequence::end(){
		index = used - 1;
	}
						//set index to last of array
	void sequence::last(){
		index = CAPACITY -1;
	}
						//increase index if possible
	void sequence::advance(){
		if(is_item()){
			if(index == CAPACITY-1)
				cout << "error: currently at end of sequence" << endl;
			else
				index++;	
		}
		else
			cout << "error: no current element" << endl;
	}
						//reduce index if possible
	void sequence::retreat(){
		if(index = 0)
			cout << "error: at beginning of sequence" << endl;
		else
			index--;	
	}
						//insert at current index
	void sequence::insert(const value_type& entry){
		assert(size() < CAPACITY);
							//move all data over	
		for(size_type i = used; i>index;i--){		
			array[i]=array[i-1];
		}
		array[index] = entry;
		used++;	
	}
						//insert after current index
	void sequence::attach(const value_type& entry){
		assert(size() < CAPACITY);
		index = index + 1;
							//move all data after over
		for(size_type i = used; i>index;i--){	
			array[i] = array[i-1];
		}
		array[index] = entry;
		used++;	
	}
						//remove item at current index
	void sequence::remove_current(){
		assert(is_item());
							//move data back a spot
		for(size_type i = index; i < used; i++){
			array[i] = array[i+1];
		}
		used--; 
	}	
						//insert item at 0 index
	void sequence::insert_front(const value_type& entry){
		assert(size()<CAPACITY);
		index = 0;
		insert(entry);
	}
						//attach to last index
	void sequence::attach_back(const value_type& entry){
		assert(size()<CAPACITY);
		index = size();
		array[index] = entry;
		used++;
		end();
	}
						//remove index 0
	void sequence::remove_front(){
		index = 0;
		assert(is_item());
							//move data back 1
		for(size_type i =0; i<used; i++){
			array[i] = array[i+1];
		}
		used--;
	}	
							//add sequences to end
	void sequence::operator +=(const sequence& rhs){
		assert(used + rhs.used < CAPACITY);
		size_type temp = rhs.used;
		for(int i = 0; i < temp; i++){	
			array[used] = rhs.array[i];
			used++;
		}
		
	}


//constant member funtions		
							//return size
	sequence::size_type sequence::size() const{
		return used;
	}
							//return if item present
	bool sequence::is_item() const{
		return (index<size());
	}
							//return data at current index
	sequence::value_type sequence::current() const{
		assert(is_item());
		return array[index];
	}
							//return data at a certain index
	sequence::value_type sequence::operator[](int index) const{
		assert(index<used);
		return array[index];
	}
							//return mean
	double sequence::mean() const{
		double sum = 0;
		for(size_type i = 0; i<size();i++){
			sum += array[i];
		}
		return sum/size();
	}
							//return standard deviation
	double sequence::standardDeviation() const{
		value_type stdev = 0.0;
		value_type mean = sequence::mean();
		for(int i =0; i < used; i++){
			stdev += pow(array[i]-mean,2); 
		}
		return sqrt(stdev/used);

	}

//non member functions
							//add together two sequences
	sequence operator+(const sequence& lhs, const sequence& rhs){
		assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
		sequence temp;
		temp += lhs;
		temp += rhs;
		return temp;	
	}
							//sum the sequence	
	sequence::value_type summation(const sequence &s){
		sequence temp = s;
		sequence::value_type sum = 0;
		temp.start();
		for(sequence::size_type i = 0; i<temp.size(); i++){
			sum += temp.current();
			temp.advance();
		}
		return sum;
	}
	
} 








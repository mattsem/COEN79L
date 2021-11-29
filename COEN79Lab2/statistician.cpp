//statistician.cpp


#include <iostream>
#include <float.h>


#include <cassert>


#include "statistician.h"



using namespace std;



namespace coen79_lab2{
						//constructor setting everything to 0
	statistician::statistician() {
		reset();
	}
						//adds element and updates vars
	void statistician::next(double r){
		total  += r;
		size++;
		if(r > max){
			max = r;
		}
		if(r < min){
			min = r;
		}
	}
					//resets all members to 0;
	void statistician::reset(){
		total = 0;
		max = DBL_MIN;
		min = DBL_MAX;
		size = 0;
	}

						//return count
	int statistician::length() const{
		return size;
	} 
						//return total	
	double statistician::sum() const{
		return total;
	}
						//return the mean
	double statistician::mean() const{
		return (total/size);
	}
						//return min
	double statistician::minimum() const{
		return min;
	} 
						//return max
	double statistician::maximum() const{
		return max;
	}
	
	
												//override + operator to add the objects together
	statistician operator +(const statistician& s1, const statistician& s2){
		statistician temp;

		temp.total = s1.total + s2.total;
		temp.size = s1.size + s2.size;
										//find the bigger max	
		if(s1.max > s2.max)
			temp.max = s1.max;
		else{
			temp.max = s2.max;
		}
										//find the smaller min
		if(s1.min < s2.min)
			temp.min = s1.min;
		else{
			temp.min = s2.min;
		}

		return temp;
	}

												//override the * operator to multiply the object by a scalar
	statistician operator *(double scale, const statistician& s){
		statistician temp;
		
		temp.total = s.total * scale;
		temp.size = s.size;
		temp.max = s.max * scale;
		temp.min = s.min * scale;
		if(temp.min > temp.max){
			double x = temp.min;
			temp.min = temp.max;
			temp.max = x;
		}
		return temp;	
	}
												//not a friend
												//set equal to true, if something doesnt match then they are unequal
	bool operator ==(const statistician& s1, const statistician& s2){
		bool equal = true;

		if(s1.length() != s2.length())
			equal = false;
		else if(s1.sum() != s2.sum())
			equal = false;
		else if(s1.minimum() != s2.minimum())
			equal = false;
		else if(s2.maximum() != s2.maximum())
			equal = false;
		else if(s1.mean() != s2.mean())
			equal = false;

		return equal;
	}
	
	

}

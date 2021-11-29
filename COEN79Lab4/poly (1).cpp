#include "poly.h"
#include <iostream>
#include <assert.h>
#include <cmath>
#include <climits>
#include <algorithm>


namespace coen79_lab4 {
							//highest degree
	void polynomial::update_current_degree(){
		for(unsigned int i = polynomial::MAXDEGREE;i>0;i--){
			if(coef[i] != 0){
				order = i;
				//std::cout << order;
				return;
			}
		}
		order = 0;	
	}
		
	polynomial::polynomial(double c, unsigned int exponent){
		clear();
		assert(exponent <= polynomial::MAXDEGREE);
		order = exponent;
		coef[order] = c;
	}	
								//assign to coef
	void polynomial::assign_coef(double coefficient, unsigned int exponent){
		assert(exponent <= polynomial::MAXDEGREE);
		coef[exponent] = coefficient;
		//std::cout << exponent << std::endl;
		//std::cout << coefficient <<std::endl;
		update_current_degree();
	}
								//add to coef
	void polynomial::add_to_coef(double amount, unsigned int exponent){
		assert(exponent <= polynomial::MAXDEGREE);
		coef[exponent] += amount;
		update_current_degree();	
	}
								//clear array
	void polynomial::clear(){
		for(int i = 0; i<= polynomial::MAXDEGREE; i++){
			coef[i] = 0;
		}
		
		update_current_degree();
	} 
								//take integral
	polynomial polynomial::antiderivative() const{
		assert(degree() < polynomial::MAXDEGREE);
		polynomial temp;
		for(int i = 0; i<degree();i++){
			temp.assign_coef(coef[i]/i+1,i+1);
		}
		temp.update_current_degree();
		return temp;
	}
								//find coefficient
	double polynomial::coefficient(unsigned int exponent) const{
		if(exponent <= polynomial::MAXDEGREE)
			return coef[exponent];
		return 0;
	}
								//take integral
	double polynomial::definite_integral(double x0, double x1) const {
		polynomial temp = antiderivative();
		return temp.eval(x1) - temp.eval(x0);
	}
								//find highest degree
	unsigned int polynomial::degree() const {
		return order;
	}
								//take the derivative
	polynomial polynomial::derivative() const{
		polynomial temp;
		for(int e = 1;e <= degree(); e++){
			temp.assign_coef( e * coefficient(e),e-1);
		}
		temp.update_current_degree();
		return temp;
	}
									//eval at an x
	double polynomial::eval(double x) const{
		double sum = 0;
		for(int i = 0; i<= degree();i++){
			sum += coef[i] * pow(x,i);
		}
		return sum;
	}
									// is everything 0
	bool polynomial::is_zero() const{
		//should be able to just say if(degree = 0) but just to be thorough:
		for(int i = 0; i<=degree();i++){
			if(coef[i] != 0)
				return false;
		}
		return true; 
	}
									//next term
	unsigned int polynomial::next_term(unsigned int e) const{
		for(int i = e; i<degree()+1;i++){
			if(coef[i] != 0)
				return i;
		} 	
		return 0;
	}
									//previous term
	unsigned int polynomial::previous_term(unsigned int e) const{
		for(int i = e; i > 0; i--){
			if(coef[i] != 0)
				return i;
		}
		return UINT_MAX;
	}	
									//sums at a certain value
	double polynomial::operator() (double x) const{
		double sum = 0;
		for(int i = 0; i<=degree();i++){
			sum += coefficient(i) * pow(x,i);
		}
		return sum;
	}

											//adds polys
	polynomial operator +(const polynomial& p1, const polynomial& p2){
		polynomial temp;
		for(int i =0;i <= fmax(p1.degree(),p2.degree()); i++){
			temp.assign_coef(p1.coefficient(i) + p2.coefficient(i),i);
		}
		temp.update_current_degree();
		return temp;
	}
											//subtrats polys
	polynomial operator -(const polynomial& p1, const polynomial& p2){
		polynomial temp;
		for(int i =0;i <= fmax(p1.degree(),p2.degree()); i++){
			temp.assign_coef(p1.coefficient(i) - p2.coefficient(i),i);
		}
		temp.update_current_degree();
		return temp;
	}
											//multiplies out polynomials
	polynomial operator *(const polynomial& p1, const polynomial& p2){
		assert(p1.degree()+p2.degree() <= polynomial::MAXDEGREE);
		polynomial temp;
		for(int e1 = 0; e1 <= p1.degree();e1++){
			for(int e2 = 0; e2<=p2.degree();e2++){
				double oc = temp.coefficient(e1+e2);
				double tc = p1.coefficient(e1) * p2.coefficient(e2);
				temp.assign_coef(oc+tc,e1+e2);
			}
		}
		temp.update_current_degree();
		return temp;  
	}

											//prints out poly with proper spacing adn such
	std::ostream& operator << (std::ostream& out, const polynomial& p){
		char sign; 
		if(p.degree() == 0){
			std::cout << p.coefficient(0);
			return out;
		}
	
		std::cout << p.coefficient(p.degree()) << "x^" << p.degree(); 
		for(int i = p.degree()-1; i > 1; i--){
			if(p.coefficient(i) == 0)
				continue;
		
			if(p.coefficient(i) < 0)
				sign = '-';
			else
				sign = '+';
			
			std::cout << ' ' << sign << ' ' <<  std::abs(p.coefficient(i)) << "x^" << i; 
		}
		if(p.coefficient(1) != 0){
			if(p.coefficient(1) < 0)
				std::cout << ' ' << '-';
			else
				std::cout << ' ' << '+';
			std::cout << ' ' << p.coefficient(1) << "x";	
		}
		if(p.coefficient(0) != 0){
			if(p.coefficient(0) < 0)
				std::cout << ' ' <<'-';
			else
				std::cout << ' ' << '+';
			std::cout << ' ' << p.coefficient(0) << std::endl;
		}
		return out;  
	}
}


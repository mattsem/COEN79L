#include <iostream>
#include <cstring>
#include <assert.h>
#include <stdlib.h>
#include "mystring.h"

//invariants
//
//*characters points to an array of chars that ends in '\0'
//
//allocated gives the size of characters
//
//current_length gives the number of chars in characters


namespace coen79_lab5{

							//constructor reserves and creates a new string
	string::string(const char str[]){
		allocated = 0;
		characters = NULL;
		current_length = strlen(str);
		//std::cout << strlen(str) << std::endl;
		reserve(current_length+1);
		//std::cout << strlen(str) << std::endl;	
		strncpy(characters, str, strlen(str));
		characters[allocated] = '\0';
	}
							//create a new string with just the one character
	string::string(char c){
		allocated = 0;
		characters = NULL;
		current_length = 1;
		reserve(current_length +1);	
		characters[0] = c;
		characters[1] = '\0';
	}
							//create a new string from an existing string
	string::string(const string& source){
		allocated = 0;
		characters = NULL;
		current_length = source.length();
		//std::cout << source.length() << std::endl;
		reserve(source.length()+1);
		strncpy(characters, source.characters,allocated);
	}
							//delete string to free memory
	string::~string(){
		delete [] characters;
	}

	
							//add aonther string on to the end of the existing one
	void string::operator +=(const string& addend){
		reserve((current_length + addend.length() + 1));
		strncat(characters, addend.characters, addend.length());
		current_length += addend.length();	
	}
							//and a string to the end of an existing one
	void string::operator +=(const char addend[]){
		reserve(current_length+strlen(addend)+1);
		strncat(characters,addend,strlen(addend));
		current_length += strlen(addend);
	}
							//add a char to the end of the existing string
	void string::operator +=(char addend){
		reserve(current_length +1+1);
		characters[current_length] = addend;
		current_length++;
		characters[current_length] = '\0';
	}
							//reserve memory if a larger amount is needed
	void string::reserve(size_t n){
		char *arr;
		if(n <= allocated)			//if trying to allocate a smaller amount; 
			return;
		arr = new char[n];
		//std::cout << "new char" << std::endl;
		if(characters != NULL){
			strncpy(arr,characters,length()+1);
		//std::cout << "strncpy" << std::endl;
			delete [] characters;
		}
		characters = arr;
		allocated = n; 
	}
							//copy source string to characters
	string& string::operator =(const string& source){
		current_length = source.length();
		reserve(current_length+1);
		strncpy(characters, source.characters, current_length+1);
		//std::cout << strlen(str) << std::endl;
		return *this;
	}
							//insert source string before the character at position
	void string::insert(const string& source, unsigned int position){
		assert(position <= length());
		reserve(source.length() + current_length + 1);
		for(size_t i = 0; i<source.length();i++){				//cpoy the characters at position over to make room
			characters[position + i + source.length()] = characters[position + i];
		}			
		for(size_t i = 0; i < source.length();i++){					//move source in to the right spots
			characters[position +i] = source.characters[i];
		}
		characters[allocated] = '\0';
		current_length += source.length();
			
	}
							//delete the number of chars after teh position
	void string::dlt(unsigned int position, unsigned int num){
		assert((position+ num) <= length());
		for(size_t i = position; i< position + num; i++){				//if moves the char back to the deleted postiion and stops if it finds null char
			characters[i] = characters[i+num];
			if(characters[i] == '\0')
				break;
		}	
		current_length -=num;	
	}
							//replace one char with another
	void string::replace(char c, unsigned int position){
		assert(position < length());
		characters[position] = c;  	
	}
							//replace a part of character string with the source string
	void string::replace(const string& source, unsigned int position){
		assert(position + source.length() <= length());
		for(size_t i = 0; i< source.length(); i++){					//take characters at position and replace the first with first of source and so on
			characters[position +i] = source.characters[i];
		}
	}



							//return char at a specific position
	char string::operator[] (size_t position) const{
		assert(position < length());
		return characters[position];
	}
							//traverse to find a char and return position
	int string::search(char c) const{
		for(size_t i = 0; i < length();i++){						//traverse and if its the right char return index; if not found return -1
			if(characters[i] = c)
				return i;
		}
		return -1;
	}
							//search for a substring
	int string::search(const string& substring) const{
		for(size_t i = 0; i <= length() - substring.length();i++){
			bool flag = true;
			for(size_t j = 0;j<substring.length();i++){				//traverse the string and see if the first char matches the first char of the substring otherwise keep moving
				if(characters[i+j] != substring.characters[j]){
					flag = false;
					break;
				}
			}
			if(flag == true)
				return i;
		}
		return -1;
	}
							//count the appearences of a char
	unsigned int string::count(char c) const{
		int count = 0;
		for(size_t i =0; i< length(); i++){						//traverse and count if its the right char
			if(characters[i] = c)
				count++;
		}
		return count;
	}

	
							//add to the output stream 
	std::ostream& operator <<(std::ostream& outs, const string& source){
		outs << source.characters;
		return outs;
	}
							//compare the strings 
	bool operator ==(const string& s1, const string& s2){
		return (strncmp(s1.characters, s2.characters, s1.length() +1) == 0);
	}

	bool operator !=(const string& s1, const string& s2){
		return (strncmp(s1.characters,s2.characters, s1.length()+1) != 0);
	}

	bool operator >(const string& s1, const string& s2){
		return (strncmp(s1.characters, s2.characters, s1.length() +1) > 0);
	}

	bool operator <(const string& s1, const string& s2){
		return (strncmp(s1.characters, s2.characters, s1.length() +1) < 0);
	}

	bool operator >=(const string& s1, const string& s2){
		return (strncmp(s1.characters, s2.characters, s1.length() +1) >= 0);
	
	}
	
	bool operator <=(const string& s1, const string& s2){
		return (strncmp(s1.characters, s2.characters, s1.length() +1) <= 0);
	}


							//add two strings to a third and return
	string operator +(const string& s1, const string& s2){
		string temp;
		temp += s1;
		temp += s2;
		return temp;
	}
							//add two strings to a third and return
	string operator +(const string& s1, const char addend[]){
		string temp;
		temp += s1;
		temp += addend;
		return temp;
	}
							//read in input
	std::istream& operator >> (std::istream& ins, string& target){
		char temp;
		while(!ins.eof() && isspace(ins.peek())){						//if not end of file and theres a white space ignore the space
			ins.ignore();
		}
		target = "";
		while(!ins.eof() && !isspace(ins.peek())){						//if not end of file and theres not a white space read in the chars and add to string
			ins >> temp;
			target += temp;
		}
		return ins;
	}

}




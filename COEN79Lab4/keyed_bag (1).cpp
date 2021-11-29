#include "keyed_bag.h"
#include <assert.h>
#include <iostream>

	
namespace coen79_lab4{

	keyed_bag::keyed_bag(){
		used = 0;
	}
						//set used to 0	
	void keyed_bag::erase(){
		used = 0;	
	}
							//erase a key
	bool keyed_bag::erase(const key_type& key){
		if(has_key(key)){
			size_type index = find_key(key);
			keys[index] = keys[size()-1];
			data[index] = data[size()-1];
			used--;
			return true;		
		}
		return false;

	}
							//isert a key and entry
	void keyed_bag::insert(const value_type& entry, const key_type& key){
		assert(size() < keyed_bag::CAPACITY);
		keys[size()] = key;
		data[size()] = entry;
		used++;
	}
							//add another array to end
	void keyed_bag::operator +=(const keyed_bag& addend){
		assert(size() + addend.size() <= keyed_bag::CAPACITY);
		assert(!hasDuplicateKey(addend));
		for(size_type i = 0;i < addend.size();i++){
			insert(addend.data[i],addend.keys[i]);
		} 
	}
		
								//check for a key
	bool keyed_bag::has_key(const key_type& key) const{
		for(size_type i = 0;i<size();i++){
			if(keys[i] == key)
				return true;
		}
		return false;
	}
								//return a key
	keyed_bag::value_type keyed_bag::get(const key_type& key) const{
		assert(has_key(key));
		return data[find_key(key)];
	}
								//return size
	keyed_bag::size_type keyed_bag::size() const{
		return used;
	}
								//return count
	keyed_bag::size_type keyed_bag::count(const value_type& target) const{
		size_type count = 0;
		for(size_type i = 0;i < size();i++){
			if(data[i] == target)
				count++;
		}	
		return count;
	}
									//check for duplicate key
	bool keyed_bag::hasDuplicateKey(const keyed_bag& otherbag) const{
		for(size_type i =0; i < size();i++){
			if(otherbag.has_key(keys[i]))
				return true;
		}
		return false;
	}
								//find a key
	int keyed_bag::find_key(const key_type& key) const{
		assert(has_key(key));
		for(size_type i = 0; i<size();i++){
			if(keys[i] == key)
				return i;
		}
	}
								//add two arrays
	keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
		assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);
		assert(!b1.hasDuplicateKey(b2));
		keyed_bag temp;
		
		//std::cout<< temp.size();
		temp += b1;
		//std::cout << temp.size();
		temp += b2;
		//std::cout << temp.size();

		return temp;
	}
	
	
}

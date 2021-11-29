// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
						//copy constructor    
    database::database(const database &src) {
        Debug("Copy constructor...");

	this->used_slots = src.used_slots;
	this->aloc_slots = src.aloc_slots;
	company_array = new company[aloc_slots];
								//for each company copy it over
	for(int i = 0; i < used_slots; i++){
		this->company_array[i] = src.company_array[i];
	}

        // COMPLETE THE IMPLEMENTATION...
    }
    
    								//copy rhs to a current list
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);
	std::cout << "copying elements of database...";
	if(this == &rhs)
		return *this;
	
	this->used_slots = rhs.used_slots;
	this->aloc_slots = rhs.aloc_slots;
	company_array = new company[aloc_slots];
								//for each compnay copy it over	
	for(int i = 0; i < used_slots; i++){
		this->company_array[i] = rhs.company_array[i];
	}

	return *this;
        // COMPLETE THE IMPLEMENTATION...
    }
    
    								//delete the array
    database::~database() {
	delete [] company_array;
        // COMPLETE THE IMPLEMENTATION...
    }
    
    								//allocate new memory 
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.

	company* new_arr;
	
	try{ 
		new_arr = new company[new_capacity];
	}
	catch(std::bad_alloc &m){
		std::cout << "Bad Alloc:" << std::endl;
	}  

								//copy over the data	
	for(size_t i = 0; i < used_slots; i++){
		new_arr[i] = company_array[i];
	}
	
	aloc_slots = new_capacity;
	company_array = new_arr;

        // COMPLETE THE IMPLEMENTATION...
    }
    
    								//insert a new company at end
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
								//if no room reserve one more
	if((used_slots +1) >= aloc_slots)
		reserve(aloc_slots + 1);
								//add in the new company
	company_array[used_slots] = company(entry);
	used_slots++;

        // COMPLETE THE IMPLEMENTATION...
    }
    
    								//insert an item in a company
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

	size_type index = search_company(company);
	bool exists = true;
								//if no company make one and add it in
	if(index == COMPANY_NOT_FOUND){
		exists = false;
		insert_company(company);
		index = 0;
	}
	
	company_array[index].insert(product_name, price);

	return exists;

        // COMPLETE THE IMPLEMENTATION...
        
    }
    
    								//delete a company
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
								//if it doesn't exist return false	
	if(company_index == COMPANY_NOT_FOUND)
		return false;

	node* head = company_array[company_index].get_head();
	list_clear(head);
								//adjust array to delete the company
	for(size_type i = company_index; i<used_slots;i++){
		company_array[i] = company_array[i+1];
	}
        
	return true;
        // COMPLETE THE IMPLEMENTATION...
    }
    
    								//erase an item in the list
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

	size_type company_index = search_company(cName);
								//if it doesn't exist return false
	if(company_index == COMPANY_NOT_FOUND)
		return false;

	return company_array[company_index].erase(pName);

        // COMPLETE THE IMPLEMENTATION...
    }
    
    
    								//search for the company
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

	size_type traverse = 0;
								//traverse until end
	while(traverse < used_slots){
		if(company_array[traverse].get_name() == company)
			return traverse;
		traverse++;
	}
								//if not found return -1	
	return COMPANY_NOT_FOUND;
        // COMPLETE THE IMPLEMENTATION...
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif

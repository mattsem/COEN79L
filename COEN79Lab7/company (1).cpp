// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
							//clear pointers and then set name    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);
	this->company_name = "";
	this->head_ptr = NULL;
	this->tail_ptr = NULL;
		
	this->company_name = company_name;
	
        // COMPLETE THE IMPLEMENTATION...
    }
    							//clear pointers to be safe and then copy name and elements
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
	
	this->company_name = "";
	this->head_ptr = NULL;
	this->tail_ptr = NULL;
	
	this->company_name = src.get_name();
	
	list_copy(src.head_ptr, this->head_ptr, this->tail_ptr);
        // COMPLETE THE IMPLEMENTATION...
    }

    							//if this is src, return it, otherwise copy src to this and return it
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

	if(this == &src)
		return *this;
	
	this->company_name = src.get_name();
	list_copy(src.head_ptr, this->head_ptr, this->tail_ptr);

	return *this;
        // COMPLETE THE IMPLEMENTATION...
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    							//insert a new company
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        						//if head is null initialize a new list
        if (head_ptr == NULL) {
		list_init(this->head_ptr, this->tail_ptr, product_name, price); 
            // COMPLETE THE IMPLEMENTATION...
        }
							//insert a new node at the end
        else {
		list_tail_insert(this->tail_ptr, product_name, price);
		tail_ptr = tail_ptr->getLink(); 
            // COMPLETE THE IMPLEMENTATION...
        }
        
        return true;
    }

    							//erase an element
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

	node *location = list_search(head_ptr, product_name);
	if(location == NULL)
		return false;
							//if its the head remove the head
	if(location == head_ptr){
		list_head_remove(head_ptr);
		return true;
	}
	node *precursor = head_ptr;
							//otherwise traverse to the pos
	while(precursor->getLink() != location)
		precursor = precursor->getLink();
							//if its the tail set a new tail
	if(location->getLink() == NULL){
		tail_ptr = precursor;
		precursor->setLink(NULL);
	}
							//otherwise set a new link across 
	else
		precursor->setLink(location->getLink());

	delete location;
	return true;
        // COMPLETE THE IMPLEMENTATION...
    }
    
    
}

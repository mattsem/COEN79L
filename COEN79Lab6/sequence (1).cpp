#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "sequence.h"
#include "node.h"


namespace coen79_lab6{
						//constructor
		sequence::sequence(){
			init();
		}
						//copy constructor
		sequence::sequence(const sequence& source){
			init();
			many_nodes = source.size();
			cursor = NULL;
			precursor = NULL;
			list_copy(source.head_ptr, head_ptr, tail_ptr);	
		}
						//destructor
		sequence::~sequence(){
			list_clear(head_ptr);
			init();			//make sure all pointers are cleared to NULL
		}
						//sets everything to 0 or NULL
		void sequence::init(){
			head_ptr = NULL;
			tail_ptr = NULL;
			cursor = NULL;
			precursor = NULL;
			many_nodes = 0;
		}
						//set cursors to beginning
		void sequence::start(){
			cursor = head_ptr;
			precursor = NULL;	
		}
						//set cursors to end;
		void sequence::end(){
			precursor = list_locate(head_ptr, many_nodes - 1);
			cursor = precursor->link();
		}
						//move to the next item				
		void sequence::advance(){
			assert(is_item());
			precursor = cursor;
			cursor = cursor->link();
		}
						//insert item before cursor
		void sequence::insert(const value_type& entry){
			if(cursor == NULL){
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
				precursor = NULL;
				tail_ptr = head_ptr;
			}
			else if(precursor == NULL){
				list_head_insert(head_ptr,entry);
				cursor = head_ptr;
				precursor = NULL;
			}
			else{
				list_insert(precursor, entry);
				cursor = precursor->link();
			}
			many_nodes++;
		}
						//insert item after cursor
		void sequence::attach(const value_type& entry){
			if(head_ptr == NULL){
				list_head_insert(head_ptr, entry);
				cursor = head_ptr;
				precursor = NULL;
				tail_ptr = head_ptr;
			}
			else if(cursor == NULL){
				list_insert(tail_ptr, entry);
				cursor = tail_ptr->link();
				precursor = tail_ptr;
				tail_ptr = cursor;	
			}
			else{
				list_insert(cursor, entry);
				precursor = cursor;
				cursor = cursor->link();
				if(cursor->link() == NULL)
					tail_ptr = cursor;		
			}
			many_nodes++;
		}
								//sets equal to given list
		void sequence::operator =(const sequence& source){
			//clean up existing data
			list_clear(head_ptr);
			//copy over new object
			if(source.cursor == NULL){
				list_copy(source.head_ptr, head_ptr,tail_ptr);
				cursor = NULL;
				precursor = NULL;
			}
			else if(source.cursor == source.head_ptr){
				list_copy(source.head_ptr, head_ptr, tail_ptr);
				precursor = NULL;
				cursor = head_ptr;
			}	
			else{
				list_piece(source.head_ptr, source.precursor, head_ptr, precursor);
				list_piece(source.cursor, source.tail_ptr, cursor, tail_ptr);
				precursor->set_link(cursor);	
			}
			many_nodes = source.size();
		}
								//removes current node
		void sequence::remove_current(){
			assert(is_item());
			if(precursor == NULL){
				list_head_remove(cursor);
				cursor = head_ptr;
			}
			else{
				list_remove(precursor);
				cursor = precursor->link();
				if(precursor->link() == NULL)
					precursor = NULL;
			}
			many_nodes--;
		}

								//size of list
		sequence::size_type sequence::size() const{
			return many_nodes;
		}
								//determines if pointer points to node
		bool sequence::is_item() const{
			if(cursor == NULL)
				return false;
			return true;		
		}	
								//return cursor		
		sequence::value_type sequence::current() const{
			assert(is_item());	
			return cursor->data();
		}		
}

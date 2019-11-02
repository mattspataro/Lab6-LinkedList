#pragma once
#include <string>
#include "LinkedListInterface.h"
using namespace std;

template<typename T>
class LinkedList: public LinkedListInterface<T>{
private:
	struct Node { //can't have a class within a class in c++, a struct is lightweight class
        Node(T val){
            value = val;
            next = NULL;
        }
        T value;
        Node* next;
    };
    Node* head;
    int numNodes;
    bool isInList(T val){
    	Node *fakeIterator = head;
    	while(fakeIterator != NULL){
    		if(fakeIterator->value == val){
    			return true;
    		}
    		fakeIterator = fakeIterator->next;
    	}
    	return false;
    }
public:
	LinkedList() {
	    head = NULL;
	    numNodes = 0;
	};
	~LinkedList() {
		clear();
	};
	
	void insertHead(T value){
		if(isInList(value))	return; //if its a duplicate, end here
		
		Node *temp = head;
		Node *newNode = new Node(value);
		numNodes++;
		head = newNode;
		newNode->next = temp;
	    return;
	}
	
	void insertTail(T value){
		if(isInList(value)) return; //if its a duplicate, end here
		
	    //create a node
	    Node *newNode = new Node(value);
	    numNodes++;
	    //put that node at the end of the list
	    if(head == NULL){
	        head = newNode;
	    }else{
	        //find the last node
	        Node *fakeIterator = head;
	        while(fakeIterator->next != NULL){
	            fakeIterator = fakeIterator->next;
	        }
	        //set that node's next pointer to newNode
	        fakeIterator->next = newNode; //arrows are for pointers, dot is for values
	    }
	    return;
	}
	
	void insertAfter(T value, T insertionNode){
		if(isInList(value)) return; //if its a duplicate, end here
		
	    Node *fakeIterator = head;
	    while(fakeIterator != NULL){
	        if(fakeIterator->value == insertionNode){
	            Node *newNode = new Node(value);
	            numNodes++;
	            newNode->next = fakeIterator->next;
	            fakeIterator->next = newNode;
	        }
	        fakeIterator = fakeIterator->next;
	    }
	    return;
	}
	
	void remove(T value){
		Node *fakeIterator = head;
		if(head != NULL && head->value == value){
			//The first node is an exception
			//You don't have to worry about the node before it pointing to it
			//You can simply make it point to the next node to delete it
			Node *temp = head->next; //save the head pointer
			delete head; // delete the head node
			head = temp; //make the head node the next node
			numNodes--;
			return;
		}
		while(fakeIterator != NULL && fakeIterator->next != NULL){
			if(fakeIterator->next->value == value){ //if the next node's value is equal to the value
				Node *temp = fakeIterator->next->next; //save the next nodes pointer
				delete fakeIterator->next; // delete the next node
				fakeIterator->next = temp; //make the next node the pointer you saved
				numNodes--;
				break;
			}
			fakeIterator = fakeIterator->next;
	    }
	    return;
	}
	
	void clear(){
		while(head != NULL){
			Node *next = head->next;
			delete head;
			head = next;
			numNodes--;
	    }
	    return;
	}
	
	T at(int index){
		if(index > -1 && index < numNodes){
			Node *fakeIterator = head;
			for(int i = 0; i < index; i++){
				fakeIterator = fakeIterator->next;
			}
			return fakeIterator->value;
		} else{
			throw std::out_of_range ("FAILED");
		}
		T t;
	    return t;
	}
	
	int size(){
	    return numNodes;
	}
	
	string toString(){
	   ostringstream output;
	   Node *fakeIterator = head;
	   while(fakeIterator != NULL){
	    output << fakeIterator->value;
	    fakeIterator = fakeIterator->next;
	    if(fakeIterator !=NULL){
	    	output << " ";
	    }
	   }
	   return output.str();
	}
};

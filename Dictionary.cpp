/*
 * Dictionary.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 * 
 * Author: Kiarash Zamani & Anil Bronson
 * Date of last modification: March 11th. 2022
 */


#include "Dictionary.h"
#include <iostream>

/*Constructors and destructors*/

// Default constructor
template <class ElementType>
Dictionary<ElementType>::Dictionary(){
    keyValuePairs = new BST<ElementType>;
    elementCount = 0;
}

// Parameterized constructor 
template <class ElementType>
Dictionary<ElementType>::Dictionary(ElementType& element){
	keyValuePairs = new BST<ElementType>(element);
	elementCount = 1;
}

// Destructor 
template <class ElementType>
Dictionary<ElementType>::~Dictionary(){
    clear(keyValuePairs);
    keyValuePairs = NULL;
}


/* Dictionary Operations */

template <class ElementType>
unsigned int Dictionary<ElementType>::getElementCount() const{
    
    return this->elementCount;
}

template <class ElementType>
void Dictionary<ElementType>::put(const ElementType& newElement){
//call insert function
   keyValuePairs->insert(newElement);
}

template <class ElementType>
ElementType& Dictionary<ElementType> ::get(const ElementType& targetElement) const{
//call retrieve function
   ElementType& trans = keyValuePairs->retrieve(targetElement);
   return trans;
}


template <class ElementType>
void Dictionary<ElementType>::displayContent(void visit(const ElementType&)) const{

     keyValuePairs->traverseInOrder(visit);
}

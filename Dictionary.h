/*
 * Dictionary.h
 * 
 * Description: Dictonary data collection ADT class.
 *              BST-based implementation.
 *              Duplicated elements not allowed.
 *              
 * Author: Kiarash Zamani & Anil Bronson
 * Date of last modification: March 11th. 2022
 */

 #pragma once

#include "BST.h"

template <class ElementType>
class Dictionary {
	
private:

/* You cannot change the following data member of this class. */
    BST<ElementType> * keyValuePairs;   
    unsigned int elementCount;               

/* Feel free to add private methods to this class. */
	
public:

/* You cannot change the prototype of the public methods of this class.
   Remember, if you add public methods to this class, our test driver 
   - the one we will use to mark this assignment - will not know about them
   since we will use these public method prototypes to create our test driver. */

    // Constructors and destructor:
	Dictionary();                               // Default constructor
    Dictionary(ElementType& element);           // Parameterized constructor 
    ~Dictionary();                              // Destructor 
	
    // Dictionary operations:
	unsigned int getElementCount() const;
	
	// Description: Puts "newElement" into the dictionary.
	// ...
	void put(const ElementType& newElement);

	// Description: Gets "newElement" from the dictionary.
	// ...
	ElementType& get(const ElementType& targetElement) const;

    void displayContent(void visit(const ElementType&)) const;
	
}; // end Dictionary

#include "Dictionary.cpp" // Including "Dictionary.cpp" (instead of copying the content of Dictionary.cpp) 
                          // is another way of creating templates.
/*
 * BST.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Kiarash Zamani & Anil Bronson
 * Date of last modification: March 11th. 2022
 */

#include "BST.h"
	
// You can modify the implementation of these methods, but cannot modify their proptotype.
// However, if you modify the implementation of these methods, your code must still 
// satisfy the documentation contract above each of these methods.

/* Constructors and destructor */

	// Default constructor
    template<class ElementType>
	BST<ElementType>::BST() {
		root = NULL;
		elementCount = 0;
	}
	
	// Parameterized constructor
    template<class ElementType>      
    BST<ElementType>::BST(ElementType& element) {
		root = new BSTNode<ElementType>(element);
		elementCount = 1;	
	}               

    // Copy constructor
    template<class ElementType>  
	BST<ElementType>::BST(const BST<ElementType>& aBST)  
	{
		BST<ElementType>* BST2 = new BST<ElementType>();/////////making a new BST


		if(aBST.root != NULL){                         ///////////////copying the tree
			BST2.root = aBST.root;
			BST2.elementCount = aBST.elementCount;
			copyH(aBST.root, BST2.root);
		} else {
			throw EmptyDataCollectionException("Empty data collection.");////////// throwing an exception
		}
	}

	//copy constructor helper, a function being called by its wrapper
	template<class ElementType>
	void BST<ElementType>::CopyH(BSTNode<ElementType>* copyFrom, BSTNode<ElementType>* copyTo){
			
		if(copyFrom->hasLeft() == true){
			copyTo->left = copyFrom.left;
			copyH(copyFrom.left, copyTo.left);

		} else if (copyFrom->hasRight() == true){
			copyTo->right = copyFrom.right;
			copyH(copyFrom.right, copyTo.right);
		}

	}


	// Destructor 
    template<class ElementType> 
	BST<ElementType>::~BST() {
		clear();			//calling a helper function to clear 
    }               
	//clear function as the end
	
	
/* Getters and setters */

    // Description: Returns the number of elements currently stored in the binary search tree.	
	// Time efficiency: O(1)
    template<class ElementType>	
	unsigned int BST<ElementType>::getElementCount() const {		

		return this->elementCount;
	}
	

/* BST Operations */

    // Description: Inserts an element into the binary search tree.
	//              This is a wrapper method which calls the recursive insertR( ).
	// Precondition: "newElement" does not already exist in the binary search tree.
    // Exception: Throws the exception "ElementAlreadyExistsException" 
	//            if "newElement" already exists in the binary search tree.
	// Time efficiency: O(log2 n)	
    template<class ElementType>
	void BST<ElementType>::insert(const ElementType& newElement) {
		
	    // Binary search tree is empty, so add the new element as the root
		if (elementCount == 0) {
			root = new BSTNode<ElementType>(newElement);
			elementCount++;
		}
		else 
		  if ( !insertR(newElement, root) ) {
  	         throw ElementAlreadyExistsException("Element already exists in the data collection.");
  	      }
  	   return;
  	}

    // Description: Recursive insertion into a binary search tree.
	//              Returns true when "anElement" has been successfully inserted into the 
	//              binary search tree. Otherwise, returns false.
 	template<class ElementType>
	bool BST<ElementType>::insertR(const ElementType& anElement, BSTNode<ElementType>* current) { 
		
		if(current->hasLeft()==true && current->hasRight()==true && current->element > anElement){  //left, right, smaller
			insertR(anElement, current->left);
		
		} else if(current->hasLeft() == true && current->hasRight()==true && current->element < anElement){		// left, right, bigger			
			insertR(anElement, current->right);

		} else if(current->hasLeft() == true && current->hasRight() == false && current->element > anElement){	//left, no right, smaller				
			insertR(anElement, current->left);

		} else if(current->hasLeft()==true && current->hasRight()==false && current->element < anElement){	//left, no right, bigger
			current->right = new BSTNode<ElementType>(anElement);
			elementCount++;
			return true;

		} else if(current->hasLeft()==false && current->hasRight()==true && current->element > anElement){	//no left, right, smaller
			current->left = new BSTNode<ElementType>(anElement);
			elementCount++;
			return true;

		} else if(current->hasLeft()==false && current->hasRight()==true && current->element < anElement){	//no left, right bigger
			insertR(anElement, current->right);

		} else if(current->isLeaf() && current->element > anElement){	//no left, no right, smaller
			current->left = new BSTNode<ElementType>(anElement);
			elementCount++;
			return true;
		
		} else if(current->isLeaf() && current->element < anElement){	//no left, no right, bigger
			current->right = new BSTNode<ElementType>(anElement);
			elementCount++;
			return true;
		
		} else if(current->isLeaf() && current->element == anElement){	
			return false;
		}
	}

	
    // Description: Retrieves "targetElement" from the binary search tree.
	//              This is a wrapper method which calls the recursive retrieveR( ).
	// Precondition: Binary search tree is not empty.
    // Exception: Throws the exception "EmptyDataCollectionException" 
	//            if the binary search tree is empty.
	// Exception: Throws (propagates) the exception "ElementDoesNotExistException" 
	//            thrown from the retrieveR(...)
	//            if "targetElement" is not in the binary search tree.
	// Time efficiency: O(log2 n)
    template<class ElementType>
    ElementType& BST<ElementType>::retrieve(const ElementType& targetElement) const {
        
	    //checking precondition
		if (elementCount == 0){  
			throw EmptyDataCollectionException("Binary search tree is empty currently.");
		}

		ElementType& translated = retrieveR(targetElement, root);

		return translated;
	}

    // Description: Recursive retrieval from a binary search tree.
	// Exception: Throws the exception "ElementDoesNotExistException" 
	//            if "targetElement" is not found in the binary search tree.
    template<class ElementType>
    ElementType& BST<ElementType>::retrieveR(const ElementType& targetElement, BSTNode<ElementType>* current) const {

		if (current->element > targetElement && current->hasRight() == true && current->hasLeft() == true){  ///smaller, left, right
			current = current->left;
			return retrieveR(targetElement, current);

		} else if (current->element < targetElement && current->hasLeft() == true && current->hasRight() == true){	///bigger, left, right
			current  = current->right;
			return retrieveR(targetElement, current);

		} else if (current->element > targetElement && current->hasLeft() == true && current->hasRight() == false){	/// smaller, left, no right
			current = current->left;
			return retrieveR(targetElement, current);

		} else if ( current->element > targetElement && current->hasLeft()== false && current->hasRight() == true){	/// smaller, no left, right
			
			throw ElementDoesNotExistException("The element does not exist in this tree 1");

		} else if ( current->element < targetElement && current->hasLeft() == true && current->hasRight() == false){	/// bigger, left, no right
			
			throw ElementDoesNotExistException("The element does not exist in this tree 2");

		} else if ( current->element < targetElement && current->hasLeft() == false && current->hasRight() == true){	///bigger, no left, right
			current = current->right;
			return retrieveR(targetElement, current);

		} else if ( current->isLeaf() && current->element > targetElement){

			throw ElementDoesNotExistException("The element does not exist in this tree 3");

		} else if ( current->isLeaf() && current->element < targetElement){

			throw ElementDoesNotExistException("The element does not exist in this tree 4");
			
		} else if(current->element == targetElement){

			return current->element;
		
		}

	} // end of retrieveR
				
	
    // Description: Traverses the binary search tree in order.
	//              This is a wrapper method which calls the recursive traverseInOrderR( ).
	//              The action to be done on each element during the traverse is the function "visit".
	// Precondition: Binary search tree is not empty.
    // Exception: Throws the exception "EmptyDataCollectionException" 
	//            if the binary search tree is empty.
	// Time efficiency: O(n)		
    template<class ElementType>
	void BST<ElementType>::traverseInOrder(void visit(const ElementType&)) const {
		
		// Check precondition: If binary search tree is empty
		if (elementCount == 0){
			throw EmptyDataCollectionException("Binary search tree is empty.");
		}
		traverseInOrderR(visit, root);
		
		return;
	}

    // Description: Recursive in order traversal of a binary search tree.	
	template<class ElementType>
	void BST<ElementType>::traverseInOrderR(void visit(const ElementType&), BSTNode<ElementType>* current) const {

		cout << current->element;
		if(current->hasLeft() && current->hasRight())
		{
			traverseInOrderR(visit, current->left);

			traverseInOrderR(visit, current->right);
		}
		else if(current->hasLeft() && !current->hasRight())
		{
			traverseInOrderR(visit, current->left);
		}
		else if(!current->hasLeft() && current->hasRight())
		{
			traverseInOrderR(visit, current->right);
		}
		else if(current->isLeaf())
		{
			return;	
		}
		
		return;

	}

	//clearing the functions and then giving the root to a different function to clear node by node
	template<class ElementType>
	void BST<ElementType>::clear(){
		clearNode(root);
		root = NULL;
	}

	//clearing the tree node by node and calling itself recursively again and deleting the node as it goes
	template<class ElementType>
	void BST<ElementType>::clearNode(BSTNode<ElementType>* current) const{

		if(current != NULL){
			clearNode(current->left);
			clearNode(current->right);
			delete current;
		}

	}


	
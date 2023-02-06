/*
 * Translator.cpp
 * 
 * Description: Drives the testing of the BST, the BSTNode, 
 *              the WordPair and all the exceptions classes. 
 *
 * Author: Kiarash Zamani & Anil Bronson
 * Date of last modification: March 11th. 2022
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "Dictionary.h"
#include "WordPair.h"
#include "ElementAlreadyExistsException.h"
#include "ElementDoesNotExistException.h"
#include "EmptyDataCollectionException.h"


void display(const WordPair& anElement) {
  cout << anElement << endl;
} // end of display

// Translation Algorithm:
 
// While not EOF  (typing <CTRL+D> at the command line creates an <EOF> signal)
//   Your Translator Application allows the user to enter 1 English word at a time (on 1 line).
//   It reads the English word entered.
//   It gets its translation from the dictionary object and prints it on the computer monitor screen.
//   If the English word is not found, ***Not Found!*** is printed instead.


int main(int argc, char *argv[]) {

  Dictionary<WordPair>* keyValuePairsWordPair = new Dictionary<WordPair>();
    
  string aLine = "";
  string aWord = "";
  string englishW = "";
  string translationW = "";
  string filename = "myDataFile.txt";
  string delimiter = ":";
  size_t pos = 0;
  WordPair translated;

  
  ifstream myfile (filename);
  if (myfile.is_open()) {
  	cout << "Reading from a file:" << endl; 
    while ( getline (myfile,aLine) )
    {
       pos = aLine.find(delimiter);
       englishW = aLine.substr(0, pos);
       aLine.erase(0, pos + delimiter.length());
       translationW = aLine;
       WordPair aWordPair(englishW, translationW);
	   // insert aWordPair into "testing" using a try/catch block
       cout << "put: " << aWordPair<< " ";
       try {
         keyValuePairsWordPair->put(aWordPair); //added
       }
       catch (const ElementAlreadyExistsException &anException) {
         cout << anException.what();
       }

    }
    
    myfile.close();
   
    // If user entered "Display" at the command line ...
    if ( ( argc > 1 ) && ( strcmp(argv[1], "Display") == 0) ) {
        // ... then display the content of the BST.

        cout << endl << "displaying Tree: " << endl << endl;

        keyValuePairsWordPair->displayContent(display);
        
    }
    else if (argc == 1) {
      cout << "enter the word you want to find: " << endl;
       // while user has not entered CTRL+D
       while ( getline(cin, aWord) ) {   
          
          WordPair aWordPair(aWord);
          // retrieve aWordPair from "testing" using a try/catch block
		  // print aWordPair

          try {
            
            WordPair French = keyValuePairsWordPair->get(aWordPair);
            cout << endl << "getting" << endl;
            cout << French << endl;
            cout << "enter the word you want to find: " << endl;
          }
          catch(ElementDoesNotExistException &anException) {
            cout<<anException.what();
            cout<< "***Not Found!***";
          }

       }
    }
  }
  else 
    cout << "failed to open file"; 

  return 0;
}

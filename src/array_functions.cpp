/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include "constants.h"
#include "utilities.h"
using namespace std;
//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
struct tracker{
	string word[50];
	int numTimes;
};
//TODO add a global array of entry structs (global to this file)
tracker myEntryArray [1000];
//TODO add variable to keep track of next available slot in array
int nextOpen = 0;
//void findNextOpen(){
//	for (int i=0; i < sizeof(trackerArray); i++) {
//		if(trackerArray[i].empty()){
//			nextOpen = i;
//		}
//	}
//}
//TODO define all functions in header file

//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!

//zero out array that tracks words and their occurrences
void clearArray();

//how many unique words are in array
int getArraySize(){
	int size = 0;
	size = nextOpen -1 ;
	return size;
}

//get data at a particular location
std::string getArrayWordAt(int i);
int getArrayWord_NumbOccur_At(int i);

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream);

/*take 1 line and extract all the tokens from it
feed each token to processToken for recording*/
void processLine(std::string &myString);

/*Keep track of how many times each token seen*/
void processToken(std::string &token);

/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode = std::ios_base::in){

	myfile.open("myFileName", std::fstream::in);
	if (!myfile.is_open()){
		bool notOpen = false;
		return notOpen;
	}

	bool open = true;
	return open;
}


/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile){
	if(myfile.is_open()){
		myfile.close();
	}
}
/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename){
	ofstream myfile ("outputfilename.cproject");


	}


}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so);

#endif /* ARRAY_FUNCTIONS_H_ */

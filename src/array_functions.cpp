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
#include<cstring>
#include "constants.h"
#include "utilities.h"
using namespace std;
//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
struct tracker{
	string word;
	int numTimes;
};
//TODO add a global array of entry structs (global to this file)
tracker myEntryArray [constants::MAX_WORDS];
//TODO add variable to keep track of next available slot in array
int nextOpen = 0;
//TODO define all functions in header file
//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!

//zero out array that tracks words and their occurrences
void clearArray(){
	for (int i = 0; i < constants::MAX_WORDS; i++) {
		myEntryArray[i].word = "";
		myEntryArray[i].numTimes = 0;
	}
	nextOpen = 0;
}

//how many unique words are in array
int getArraySize(){
	return nextOpen;
}

//get data at a particular location
std::string getArrayWordAt(int i){
	string word = "";
	if (nextOpen > i && i >= 0) {
		word = myEntryArray[i].word;
		return word;
	}
	return constants::TEST_DATA_NON_EXISTANT;
}

int getArrayWord_NumbOccur_At(int i){
	int occur = 0;
		if (nextOpen > i && i >= 0) {
			occur = myEntryArray[i].numTimes;
			return occur;
		}
	return constants::FAIL_NO_ARRAY_DATA;
}

/*iff myfile is open then close it*/
void closeFile(std::fstream& myfile){

	if(myfile.is_open()){
		myfile.close();
	}
}

/*Keep track of how many times each token seen*/
void processToken(std::string &token){
	if (strip_unwanted_chars(token)){
		for (int i=0; i < constants::MAX_WORDS; i++){
			string temp = token;
			string word = myEntryArray[i].word;
			toUpper(temp);
			toUpper(word);
			if (temp == word) {
				myEntryArray[i].numTimes++;
				return;
			}
		}
		myEntryArray[nextOpen].word = token;
		myEntryArray[nextOpen].numTimes++;
		nextOpen++;
	}
}

/*take 1 line and extract all the tokens from it
feed each token to processToken for recording*/
void processLine(std::string &myString){

	stringstream ss(myString);
	string tempToken = "";

	while(getline(ss, tempToken, constants::CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream){

	bool fileStatus = true;
	if (!myfstream.is_open()){
		fileStatus= false;
		return fileStatus;
	}

	std::string line;
	while(!myfstream.eof()){
		getline(myfstream,line);
		processLine(line);
	}
	closeFile(myfstream);
	return fileStatus;
}

/*if you are debugging the file must be in the project parent directory
  in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode = std::ios_base::in){

	myfile.open(myFileName.c_str(), std::fstream::in);
	if (!myfile.is_open()){
		bool notOpen = false;
		return notOpen;
	}
	bool open = true;
	return open;
}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename){
	ofstream file;
	file.open(outputfilename.c_str());
	if (!file.is_open()){
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}
	if (nextOpen == 0){
		return constants::FAIL_NO_ARRAY_DATA;
	}
	for (int i = 0; i < getArraySize(); i++){
		file << myEntryArray[i].word << " " << myEntryArray[i].numTimes << endl;
	}
	file.close();
	return constants::SUCCESS;
}

/*
 * Sort myEntryArray based on so enum value.
 * You must provide a solution that handles alphabetic sorting (A-Z)
 * The presence of the enum implies a switch statement based on its value
 */
void sortArray(constants::sortOrder so){
	switch(so) {
	case constants::NONE:
		break;

	case constants::ASCENDING:
		for(int i=0; i< getArraySize(); i++) {
		        for(int j=i+1; j<getArraySize(); j++) {
		            //If there is a smaller element found on right of the array then swap it.
		        	if(myEntryArray[j].word < myEntryArray[i].word) {
		                tracker temp = myEntryArray[i];
		                myEntryArray[i] = myEntryArray[j];
		                myEntryArray[j] = temp;
		            }
		        }
		}
		break;
	case constants::DESCENDING:
		for(int i=0; i< getArraySize(); i++) {
			for(int j=i+1; j<getArraySize(); j++) {
				if(myEntryArray[i].word < myEntryArray[j].word) {
					{
						tracker temp  = myEntryArray[i];
						myEntryArray[i]= myEntryArray[j];
						myEntryArray[j]=temp;
					}
				}
			}
		}
		break;
	case constants::NUMBER_OCCURRENCES:
		for(int i=0; i< getArraySize(); i++) {
			for(int j=i+1; j<getArraySize(); j++) {
				if(myEntryArray[j].numTimes< myEntryArray[i].numTimes) {
					tracker temp = myEntryArray[i];
					myEntryArray[i] = myEntryArray[j];
					myEntryArray[j] = temp;
				}
			}
		}
		break;
	}
}



#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include "WordAnalysis.h" //import the header file

//CORRECT: create array of 50 most commond words
std::string common[] = {"the", "be", "to", "of","and","a","in","that",
		"have", "i", "it", "for", "not", "on", "with",
		"he", "as", "you", "do", "at", "this", "but",
		"his", "by", "from", "they", "we", "say", "her",
		"she", "or", "an", "will", "my", "one", "all",
		"would", "there", "their", "what", "so", "up",
		"out", "if", "about", "who", "get", "which",
		"go", "me"};

WordAnalysis::WordAnalysis(int sizeA){ //CORRECT: constructor: creates the new array in heap and initalizes variables
	words = new word[sizeA];
        wordCount = sizeA;
        timesDoubled = 0;  //initialize timesDoubled and index both as zero
        index = -1;
}

//CORRECT: checks if a word is in the common word list
bool WordAnalysis::checkIfCommonWord(std::string word){
	for(int i=0; i<50; i++){
		if(word == common[i]){ //if word is common word, return true
			return true;
		}
	}
	return false; //else return false
}

//CORRECT: returns index variable
int WordAnalysis::getUniqueWordCount(){
	return index;
}

//CORRECT: returns timeDoubled variable
int WordAnalysis::getArrayDoubling(){
	return timesDoubled;
}

//CORRECT: returns total word count
int WordAnalysis::getWordCount(){
	int totcount = 0;
	for(int i=0; i<=index; i++){ //why does <= work and not < ???!!!
		totcount = words[i].count + totcount;
	}
	return totcount;
}

//CORRECT: sorts the word array
void WordAnalysis::sortData(){ //uses insertion sort algorithm
	int i, j;
	for(i=1; i<index; i++){
		word swap = words[i];
		j = i;
		while(j>0 && words[j-1].count < swap.count){
			words[j] = words[j-1];
			j = j - 1;
		}
		words[j] = swap;
	}
}

//CORRECT: prints the most common words in the text. the argument is # of words to print.
void WordAnalysis::printCommonWords(int n){
	sortData(); //sort data
	for(int i=0; i<n; i++){
		std::cout << words[i].count; //print out top n words in specified format
		std::cout << " - ";
		std::cout << words[i].w;
		std::cout << std::endl;
	}
}

//CORRECT: prints the final output of my program
void WordAnalysis::printResult(int n){
	printCommonWords(n);
	std::cout << "#" << std::endl;
	std::cout << "Array doubled: " << getArrayDoubling() << std::endl;
	std::cout << "#" << std::endl;
	std::cout << "Unique non-common words: " << getUniqueWordCount() << std::endl;
	std::cout << "#" << std::endl;
	std::cout << "Total non-common words: " << getWordCount() << std::endl;	
}

//CORRECT: double the array and add the new word to the array
void WordAnalysis::doubleArrayAndAdd(std::string newword){

	//double array
	wordCount = wordCount * 2; //double word count
	word *newwords = new word[wordCount]; //create a new array double the size of old array
	for(int i = 0; i<(wordCount/2); i++){ 
		newwords[i] = words[i]; //copy contents from old array into new array
	}
	delete []words; //delete old array
	words = newwords; //reuse old pointer
	newwords = nullptr; //reset new pointer
	timesDoubled++;

	//add new word to array
	index++;
	words[index].count = 1;
	words[index].w = newword;
}

//CORRECT: opens a file and reads in the data
bool WordAnalysis::readDataFile(char *filename){
	int counter = 0; //used to verify validity of wordCount
	int counter2 = 0;
	int flag = 0; //used to track uniqueness of word
	char newchar; //stores individual letters read from the text file
	std::string newword; //stores words read from the text file
	std::ifstream myfile(filename); //initialize file
	if(myfile.is_open()){ //returns true if file can be successfully opened. Otherwise returns false.
		while(myfile.get(newchar)){ //grab a character
			std::cout<<newchar<<std::endl;
			if((isalpha(newchar)!=0)|(isdigit(newchar)!=0)|(newchar=='—')){ //if it is a letter or a number
				newword = newchar; //begin forming a new word
				while(myfile.get(newchar)){ //keep grabbing characters until no longer letters
					std::cout<<newchar<<std::endl;
					if((isalpha(newchar)==0)&(isdigit(newchar)==0)&(newchar!='—')){ //break out of loop once word is formed
						break;
					}
					else{
						newword = newword + newchar; //otherwise, construct the word
					}
				}
				counter2++;
				//std::cout << newword << std::endl;
				if(checkIfCommonWord(newword)==false){ //CORRECT
					counter++;
					for(int i=0; i<=index; i++){
						if(newword == words[i].w){ //if newword is not unique, increase corresponding word count
							words[i].count++;
							flag = 1;
							break;
						}
					}
                                	if(flag==0){ //if word is unique, find out if array is full
                                        	if((index+1) == wordCount){ //if full, double array and add new word
                                                	doubleArrayAndAdd(newword);
                                        	}
                                        	else{ //else add new word to end of array
                                                	index++; 
                                                	words[index].count = 1;
                                                	words[index].w = newword;
                                        	}
					}
					flag = 0;
				}
			}
		}
		std::cout<<counter<<std::endl;
		std::cout<<counter2<<std::endl;
		myfile.close();
		return true;
	}
	else{
		return false;
	}
}

//CORRECT: empty destructor
WordAnalysis::~WordAnalysis(){}

int main(){
	//char filename[] = "HungerGames_edit.txt";
	char filename[] = "test.txt";
	int number_of_most_frequent_words_to_output = 20;

	//std::cin >> filename;
	//std::cin >> number_of_most_frequent_words_to_output;

	WordAnalysis myWords(100); //create an instance of the class
	myWords.readDataFile(filename);
	myWords.printResult(number_of_most_frequent_words_to_output);
	std::cout << std::endl;
	std::cout << "SOLUTIONS" << std::endl;
	std::cout << "Unique non-common words (SOL): 7682" << std::endl;
	std::cout << "Total non-common words (SOL): 59158" << std::endl;
}

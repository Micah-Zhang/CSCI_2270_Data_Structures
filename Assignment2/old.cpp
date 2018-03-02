#include <iostream>
#include <string>

struct word {
	int count;
	std::string w;
};

class WordAnalysis{
	private:
		int timesDoubled;
		word *words;
		int wordCount;
		int index;
		void doubleArrayAndAdd(std::string);
		bool checkIfCommonWord(std::string word, std::string filename);
		void sortData();
	public:
		bool readDataFile(char*); //returns an error if file not opened
		int getWordCount();
		int getUniqueWordCount();
		int getArrayDoubling();
		void printCommonWords(int);
		void printResult(int);
		WordAnalysis(int);
		~WordAnalysis();
};

bool WordAnalysis::checkIfCommonWord(std::string word, std::string filename){
	std::string commmonword;
	std::ifstream myfile;
	myfile.open(filename);
	while(std::getline(myfile, commonword, ' ')){
		if(word == commonword){
			myfile.close();
			return true;
		}
	}
	myfile.close();
	return false;
}

int main(){
	//read in the name of the file and the number of most frequent words to output
	/*cout<<"What is the name of the file?: ";
	cin>>filename;
	cout<<"How many of the most frequent words to output?: ";
	cin>>number_of_most_frequent_words_to_output;*/

	WordAnalysis Word1;
	state = Word1.checkIfCommonWord("cow","commonwords.txt");
	std::cout<<state<<std::endl;
}

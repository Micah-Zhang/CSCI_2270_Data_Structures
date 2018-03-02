struct word {
	int count;
	std::string w;
};

class WordAnalysis{
	private:
		/*stores the number of times the array has been 
		doubled in the program*/
		int timesDoubled;
		/*stores the array of words. Memory will be
		dynamically allocated*/
		word *words;
		/*Current size of the array. when you double the
		array, wordCount = wordCount * 2 to double the size*/
		int wordCount;
		//how many unique words found
		int index;
		/*call this method when you want to double the array
		and add the new word to the array. The new word is 
		the input to the method*/
		void doubleArrayAndAdd(std::string);
		/*call this method to check if a word is in the
		common word list */
		bool checkIfCommonWord(std::string);
		//call this method to sort the words array
		void sortData();
	public:
		/*Call this method to open a file and read in the
		data. the filename is the argument. */
		bool readDataFile(char*); //returns an error if file not opened
		/*returns index*count for each word*/
		int getWordCount();
		//returns index variable
		int getUniqueWordCount();
		//returns timeDoubled variable
		int getArrayDoubling();
		/*call this method to print the common words. the 
		argument is the number of words to print*/
		void printCommonWords(int);
		/*call this method to print the final output of
		your program*/ 
		void printResult(int);
		/* constructor. the argument is the initial size
		of the array */
		WordAnalysis(int);
		~WordAnalysis();
};

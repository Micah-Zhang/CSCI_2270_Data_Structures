/* Micah Zhang
Assignment 4
Shirly */

#include <iostream>
#include <string>
#include <stdlib.h>
//#include "Queue.hpp"

//HEADER
class Queue
{
        private:
                int queueHead; //index to first item in queue
                int queueTail; //index to last item in queue
                std::string *arrayQueue; //contains contents of queue
                int queueCount; //the current size (sentinel)
                int queueSize; //maximum size of queue
                bool isEmpty(); //tells whether queue is empty
                bool isFull(); //tells whther queue is full
        public:
                Queue(int qs); //constructor
                ~Queue(); //destructor
                void enqueue(std::string newWord); //pushes to queue
                void dequeue(); //pops from queue
                void printQueue(); //prints queue
                void enqueueSentence(std::string newSentence); //pushe$
                void quit();
};

//IMPLEMENTATION
Queue::Queue(int qs){ //constructor
	queueSize = qs; //max size of array
	arrayQueue = new std::string[queueSize]; //creation of array of strings
	queueHead = 0; //beginning of queue
	queueTail = 0; //end of queue
	queueCount = 0; //current size of array (sentinel)
}

Queue::~Queue(){ //destructor
	quit();
}

bool Queue::isEmpty(){
	//std::cout<<"Queue is empty"<<std::endl;
	return queueCount == 0; //if the current size of array is 0, then the queue is empty
}

bool Queue::isFull(){
	//std::cout<<"Queue is full"<<std::endl;
	return queueCount == queueSize; //if the current size of the array is equal to the max size, the queue is full
}

void Queue::printQueue(){
	if(queueTail==0){
		for(int index=queueHead; index<queueSize; index++){ //edge case: queue previously full
			std::cout<<index<<": "<<arrayQueue[index]<<std::endl;
		}
	}
	else{
		for(int index=queueHead; index<queueCount; index++){ //edge case: print contents of queue
			std::cout<<index<<": "<<arrayQueue[index]<<std::endl;
		}
	}
}

void Queue::enqueue(std::string newWord){
	if(!isFull()){ //if the queue is not yet full
		arrayQueue[queueTail]=newWord; //insert the new word into the queue
		queueCount++; //increase the sentinel
		if(queueTail==queueSize-1){ //edge case: if the queue is now full
			queueTail=0; //reset the tail by making it wrap around the queue
			std::cout<<"E: "<<newWord<<std::endl;
			std::cout<<"H: "<<queueHead<<std::endl;
			std::cout<<"T: "<<queueTail<<std::endl;
		}
		else{
			queueTail++; //move the sentinel to the next space to be filled
			std::cout<<"E: "<<newWord<<std::endl;
			std::cout<<"H: "<<queueHead<<std::endl;
			std::cout<<"T: "<<queueTail<<std::endl;
		}
	}
	else{
		std::cout<<"Queue is full"<<std::endl;
	}
}

void Queue::quit(){
	delete []arrayQueue; //delete queue from heap
	std::cout<<"Goodbye!"<<std::endl;
}


void Queue::dequeue(){
	std::string newWord;
	if(!isEmpty()){ //if the queue is not empty
		newWord=arrayQueue[queueHead]; //retrieve the first item in the queue
		queueCount--; //decrease the sentinel
		if(queueHead==queueSize-1){ //edge case: queue now empty, make head wrap around queue
			queueHead=0;
			std::cout<<"H: "<<queueHead<<std::endl;
			std::cout<<"T: "<<queueTail<<std::endl;
			std::cout<<"word: "<<newWord<<std::endl;
		}
		else{ //normal case: increment head to effectively "shrink" the queue
			queueHead++;
			std::cout<<"H: "<<queueHead<<std::endl;
			std::cout<<"T: "<<queueTail<<std::endl;
			std::cout<<"word: "<<newWord<<std::endl;
		}
	}
	else{
		std::cout<<"Queue is empty"<<std::endl;
	}
}

void Queue::enqueueSentence(std::string newSentence){
	std::string newWord;
	std::size_t newIndex=0, oldIndex=0; //words will be squeezed between two indexes
	while(newIndex!=std::string::npos){ //keep parsing words until end of sentence
		if(oldIndex==0){ //edge case: first word in sentence
			newIndex=newSentence.find(" "); //find first instance of " "
			newWord=newSentence.substr(0,(newIndex-oldIndex)); //parse sentence for first word
			enqueue(newWord); //enqueue first word
			oldIndex=newIndex; //move on to next word in sentence
		}
		else{ //normal case
			newIndex=newSentence.find(" ",oldIndex+1); //find next instance of " " 
			newWord=newSentence.substr(oldIndex+1,(newIndex-oldIndex)); //use two indexes to retrieve a new word
			enqueue(newWord); //enqueue new word
			oldIndex=newIndex; //move on to next word in sentence
		}
	}
}

//DRIVER
int main(int argc, char *argv[]){ //allows queueSize to be passed from the command line as a command line argument
	int qs=std::atoi(argv[1]); //convert inputed character into integer
	std::string choice, newWord, newSentence;
	Queue myQueue(qs); //create instance of queue class of size = user input
	while(true){ //print menu
		std::cout << "======Main Menu=====" << std::endl;
		std::cout << "1. Enqueue word" << std::endl;
		std::cout << "2. Dequeue word" << std::endl;
		std::cout << "3. Print queue" << std::endl;
		std::cout << "4. Enqueue sentence" << std::endl;
		std::cout << "5. Quit" << std::endl;

		std::getline(std::cin,choice); //get user inputed choice

		if(choice=="1"){ //choice 1 = enqueue word
			//std::cout<<"Enter a word: "<<std::endl;
			std::getline(std::cin,newWord);
			myQueue.enqueue(newWord);
		}
		else if(choice=="2"){ //choice 2 = dequeue word
			myQueue.dequeue();
		}
		else if(choice=="3"){ //choice 3 = print queue
			myQueue.printQueue();
		}
		else if(choice=="4"){ //choice 4 = enqueue sentence
			//std::cout<<"Enter a sentence: "<<std::endl;
			std::getline(std::cin, newSentence);
			std::cout<<"sentence: "<<newSentence<<std::endl; //extra print statement for moodle
			myQueue.enqueueSentence(newSentence);
		}
		else if(choice=="5"){ //choice 4 = quit
			break; //destructor deallocates by default
		}
	}
	return 0;
}

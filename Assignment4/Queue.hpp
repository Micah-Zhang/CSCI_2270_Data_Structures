#ifndef QUEUE_HPP
#define QUEUE_HPP

//implementation of a Queue class as array
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
		void enqueueSentence(std::string newSentence); //pushes sentence to queue
		void quit();
};


#endif // QUEUE_HPP

/* Micah Zhang
Assignment3
Shirly */

#include <iostream>
#include <string>
#include <fstream>
#include "CommunicationNetwork.hpp"

//constructor
CommunicationNetwork::CommunicationNetwork(){
	head=NULL; //initialize head and tail as NULL
	tail=NULL;
}

void CommunicationNetwork::buildNetwork(){
	std::string names[]={"Miami","New York","Chicago",
				"Seattle","Denver","Dallas"};
	City *walker = head;
	City *temp;
	for(int i=0;i<6;i++){
		temp = new City(names[i]); //create new city
		if(head==NULL){ //if list is empty
			head = temp; //head = new item
			walker = head;
		}
		else{ //if the list has nodes
			while(walker->next!=NULL){ //traverse to last item in list
				walker=walker->next; 
			}
			walker->next=temp; //insert new item to end of list
			temp->previous = walker;
		}
	}
	tail = temp; //create new tail = last item to be added to list
	std::cout<<"===CURRENT PATH==="<<std::endl;
	std::cout<<"NULL <- ";
	for(walker=head;walker->next!=NULL;walker=walker->next){ //traverse through network and print name of each item in list
		std::cout<<walker->cityName<<" <-> ";
	}
	std::cout<<walker->cityName<<" -> NULL"<<std::endl;
	std::cout<<"=================="<<std::endl;
	walker=NULL;
	temp=NULL;
}

void CommunicationNetwork::printNetwork(){
	City *walker;
	std::cout<<"===CURRENT PATH==="<<std::endl;
	if(head==NULL){ //if list empty, print NULL
		std::cout<<"NULL"<<std::endl;
	}
	else if(head->next==NULL){ //if only 1 item, print item name with NULL on either side
		std::cout<<"NULL <- "<<head->cityName<<" -> NULL"<<std::endl;
		std::cout<<"=================="<<std::endl;
	}
	else{ //print the entire list by traversing from left to right. enclose list items with NULL
		std::cout<<"NULL <- ";
		for(walker=head;walker->next!=NULL;walker=walker->next){
			std::cout<<walker->cityName<<" <-> ";
		}
		std::cout<<walker->cityName<<" -> NULL"<<std::endl;
		std::cout<<"=================="<<std::endl;
	}
	walker=NULL;
}

void CommunicationNetwork::addCity(std::string newCityName, std::string previousCityName){
	City *walker;
	City *temp=new City(newCityName);
	if(previousCityName=="First"){ //edge case: add item to start of list
		temp->next=head;
		head->previous=temp;
		head=temp; //change head appropriately
	}
	else{
		walker=head;
		while(walker!=NULL){
			if((walker->cityName==previousCityName)&(walker->next==NULL)){//edge case: add item to end of list
				temp->next=walker->next;
				walker->next=temp; 
				temp->previous=walker;
				tail=temp; //change tail appropriately
				break;
			}
			else if(walker->cityName==previousCityName){ //normal case: add item to middle
				temp->next=walker->next;
				walker->next=temp;
				temp->previous=walker;
				break;
			}
			else{
				walker=walker->next; //traverse through list until desired insertion point is found
			}
		}
	}
	walker=NULL;
	temp=NULL;
}

void CommunicationNetwork::deleteCity(std::string cityNameDelete){
	int flag=0; //tracks match status
	City *walker=head; //create a walker to traverse through a list

	while(walker!=NULL){
		if((walker->cityName==cityNameDelete)&(walker->previous==NULL)&(walker->next==NULL)){ //edge case: delete last item left in list
			delete walker; 
			head=NULL; //ensures "printNetwork()" works properly
			tail=NULL;
			flag=1; //flag as match found
			break;
		}
		//edge case: item found, delete first item
		else if((walker->cityName==cityNameDelete)&(walker->previous==NULL)){
			head=walker->next; //move head appropriately
			(walker->next)->previous=NULL;
			walker->next=NULL;
			delete walker;
			flag=1;
			break;
		}
		else if((walker->cityName==cityNameDelete)&(walker->next==NULL)){ //edge case: item found, delete last item
			tail=walker->previous; //move tail appropriately
			(walker->previous)->next=NULL;
			walker->previous=NULL;
			delete walker;
			flag=1;
			break;
		}
		//NORMAL CASE: item found, delete item in middle of list
		else if(walker->cityName==cityNameDelete){ 
			(walker->previous)->next=walker->next; //isolate and delete
			(walker->next)->previous=walker->previous;
			walker->next=NULL;
			walker->previous=NULL;
			delete walker;
			flag=1;
			break;
		}
		//item NOT found, traverse through the list
		else{
			walker=walker->next;
		}
	} //if no match, return "not found"
	if(flag==0){
		std::cout<<cityNameDelete<<" not found"<<std::endl;
	}
	walker=NULL;
}

void CommunicationNetwork::deleteNetwork(){
	City *walker=head;
	City *temp;
	
	if(head==NULL){ //cannot delete nonexistent list
		return;
	}
	else{
		while(walker->next!=NULL){
			if(walker->previous==NULL){ //delete first item of list
				temp=walker;
				std::cout<<"deleting "<<temp->cityName<<std::endl;
				walker=walker->next;
				walker->previous=NULL;
				temp->next=NULL;
				delete temp;
			}
			else{ //delete middle of list
				temp=walker;
				std::cout<<"deleting "<<temp->cityName<<std::endl;
				walker=walker->next;
				(temp->previous)->next=walker;
				walker->previous=temp->previous;
				temp->next=NULL;
				temp->previous=NULL;
				delete temp;
			}
		}
		std::cout<<"deleting "<<walker->cityName<<std::endl;
		delete walker; //delete last item in list

		head=NULL;
		tail=NULL;
		walker=NULL;
		temp=NULL;
	}
}

//COMPLETE
void CommunicationNetwork::transmitMsg(std::string filename){
	std::ifstream myfile(filename); //open file
	std::string line; //used to store words
	std::string temp;
	int found;
	City *walker;
	if(head==NULL){ //cannot transmit through empty list
		std::cout<<"Empty list"<<std::endl;
	}
	else{
		while(std::getline(myfile,line,' ')){ //parse using whitespace. 
			found=line.find("\n"); //delete all extraneous newline characters.
			if(found!=-1){
				line.erase(found,found+1);
			}
			walker=head; //1st tower receives message from text
			walker->message=line;
			std::cout<<walker->cityName<<" received "<<walker->message<<std::endl;
			while((walker->next)->next!=NULL){ //1st tower shares message to other towers
				walker=walker->next;
				walker->message=(walker->previous)->message;
				(walker->previous)->message="";
				std::cout<<walker->cityName<<" received "<<walker->message<<std::endl;
			}
			temp=walker->message; //final tower needed a special variable "temp" to hold its message to prevent it from being deleted
			walker=walker->next;
			walker->message=temp;
			(walker->previous)->message="";
			std::cout<<walker->cityName<<" received "<<walker->message<<std::endl;
		}
		myfile.close(); //close file
	}

}

//destructor
CommunicationNetwork::~CommunicationNetwork(){
	deleteNetwork(); //automatically deletes/deallocates all objects in heap when program exits
}

int main(){
	std::string choice,cityNew,cityPrevious,cityNameDelete,filename;
	CommunicationNetwork myNetwork; //create object
	while(true){ //print menu
		std::cout<<"======Main Menu======"<<std::endl;
		std::cout<<"1. Build Network"<<std::endl;
		std::cout<<"2. Print Network Path"<<std::endl;
		std::cout<<"3. Transmit Message Coast-To-Coast-To-Coast"<<std::endl;
		std::cout<<"4. Add City"<<std::endl;
		std::cout<<"5. Delete City"<<std::endl;
		std::cout<<"6. Clear Network"<<std::endl;
		std::cout<<"7. Quit"<<std::endl;
		std::getline(std::cin,choice);

		if(choice=="1"){ //choice 1 = build network
			myNetwork.buildNetwork();
		}
		else if(choice=="2"){ //choice 2 = print network
			myNetwork.printNetwork();
		}
		else if(choice=="3"){ //choice 3 = transmit message
			std::cout<<"Enter name of file: "<<std::endl;
			std::getline(std::cin,filename);
			myNetwork.transmitMsg(filename);
		}
		else if(choice=="4"){ //choice 4 = add new city
			std::cout<<"Enter a city name: "<<std::endl;
			std::getline(std::cin,cityNew);
			std::cout<<"Enter a previous city name: "<<std::endl;
			std::getline(std::cin,cityPrevious);
			myNetwork.addCity(cityNew,cityPrevious);
		}
		else if(choice=="5"){ //choice 5 = delete city
			std::cout<<"Enter a city name: "<<std::endl;
			std::getline(std::cin,cityNameDelete);
			myNetwork.deleteCity(cityNameDelete);
		}
		else if(choice=="6"){ //choice 6 = delete all cities
			myNetwork.deleteNetwork();
		}
		else if(choice=="7"){ //choice 7 = exit program
			std::cout<<"Goodbye!"<<std::endl;
			break;
		}
	}
}

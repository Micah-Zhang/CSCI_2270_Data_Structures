#include <fstream>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;

struct item{ //create a struct with 3 attributes
	string type;
	string status;
	int price;
};

void leftover(item myArray[], int arraySize);

int main() {
	string filename = "messageBoard.txt";
	//cin >> filename;
	ifstream myfile; //prepare for reading
	myfile.open(filename); //open file
	item itemArray[100]; //create an array containing 100 structs
	string newtype, newstatus, newprice;
	int intnewprice, readcount = 0, searchcount = 0, shiftcount = 0;
	int i = 0, j = 0, flag = 0; //i is a sentinel and j is a loop iterator
	while(getline(myfile,newtype,',')){ //loop automatically exits at EOF
		readcount++;
		getline(myfile,newstatus,',');
		newstatus.erase(newstatus.begin()); //delete extraneous ' '
		getline(myfile,newprice,'\n');
		newprice.erase(newprice.begin());
		intnewprice = stoi(newprice); //convert string to integer for comparison
		cout << "item read " << newtype << " cost " << newprice << endl;
		if(i==0){ //automatically adds first item to array
			itemArray[i].type = newtype;
			itemArray[i].status = newstatus;
			itemArray[i].price = intnewprice;
			i++;
		}
		else{
			for(j=0;j<i;j++){
				searchcount++;
				if((itemArray[j].type == newtype) && (itemArray[j].status != newstatus)){ //if same type but different status, found match
					cout << itemArray[j].type  << endl;
					cout << newtype << endl;
					cout << itemArray[j].status << endl;
					cout << newstatus << endl;
					if(newstatus == "for sale"){ //print cost of item
						cout << itemArray[j].type << " " << intnewprice << endl;
					}
					else{
						cout << itemArray[j].type << " " << itemArray[j].price << endl;
					}
					for(j;j<i;j++){//delete the first match found by leftshifting array
						itemArray[j] = itemArray[j+1];
						shiftcount++;
					}
					flag = 1; //flag match found
					i-=2; //keep current index and account for deletion
					break;
				}
			}
			if(flag == 0){ //no matches found
				itemArray[i].type = newtype; //add new item to array
				itemArray[i].status = newstatus;
				itemArray[i].price = intnewprice;
				i++; //increment iterator
			}
			flag = 0; //reset flag for next item
		}
	}
	cout << "#" << endl;
	leftover(itemArray,i);
	cout << "#" << endl;
	//cout << "file read:" << readcount << endl;
	//cout << "search aray:" << searchcount << endl;
	//cout << "shift array:" << shiftcount <<endl;
	myfile.close(); //close file
	return 0;
}

void leftover(item myArray[], int arraySize){
	for(int x=0; x<arraySize; x++){ //print leftover items
		cout<<myArray[x].type<<endl;
	}
	cout<<arraySize<<endl; //print size of array
}

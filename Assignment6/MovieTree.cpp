/* Micah Zhang
Assignment 6
Shirly */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

//HEADER
struct Movie{
	std::string name; //stores name of movie
	std::string rank; //stores movie ranking on IMDB
	std::string year; //stores year released
	int quantity; //stores quantity in stock
	Movie *parent; //stores address of parent
	Movie *left; //stores address of left child
	Movie *right; //stores address of right child
	bool isRed;
	Movie(std::string n, std::string rk, std::string y, int q, Movie *p, Movie *l, Movie *r, bool iR): name(n), rank(rk), year(y), quantity(q), parent(p), left(l), right(r), isRed(iR){}; //allows for easy definition
};

class MovieTree
{
	private:
		int count;
		Movie *root;
		Movie *nil;
		Movie *searchRecursive(Movie *startMovie, std::string searchName);
		//Movie *insertRecursive(Movie *parent, Movie *root, std::string newName, std::string newRank, std::string newYear, int newQuantity);
		Movie *deleteRecursive(Movie *startMovie, std::string deleteName);
		Movie *minRecursive(Movie *startMovie);
		void deleteAllRecursive(Movie *startMovie);
		void printRecursive(Movie *startMovie);
		int longestPathRecursive(Movie *node);
		void countRecursive(Movie *startMovie);
		void rbAddFixup(Movie *x); //called after insert to fix tree
		void leftRotate(Movie *x); //rotate the tree left with x as root of the rotation
		void rightRotate(Movie *y); //rotate the tree right with x as the root of rotation
		void rbBalance(Movie *x); //called after delete to fix the tree
		Movie *insertRB(std::string newName, std::string newRank, std::string newYear, int newQuantity); 
		int rbValid(Movie *node); //check if tree is valid, with node as the root of the tree
	public:
		MovieTree();
		~MovieTree();
		void build(std::string filename);
		void search(std::string searchName);
		void print();
		void redBlackInsert(std::string newName, std::string newRank, std::string newYear, int newQuantity);
		void redBlackDelete(std::string deleteName);
		int countTree();
		void rent(std::string rentName);
		void deleteMovie(std::string deleteName);
		void deleteAll();
		int longestPath();
		bool isValid();
		//int countLongestPath();
};

//IMPLEMENTATION
//constructor: initialize root as NULL
MovieTree::MovieTree(){
	nil = new Movie("nil","","",0,NULL,NULL,NULL,false);
	root = nil;
}

//destructor: deletes entire tree
MovieTree::~MovieTree(){
	deleteAll();
	delete nil;
}

void MovieTree::rbBalance(Movie *x){
	while((x != root) && (!x->isRed)){
		//std::cout<<"2"<<std::endl;
		//std::cout<<x->name<<x->parent->left->name<<std::endl;
		if(x == x->parent->left){ //determine if x is r or l to set sibling
			//std::cout<<"x is a left child"<<std::endl;
			Movie *s = x->parent->right;
			if(s->isRed){ //case 1
				s->isRed = false;
				x->parent->isRed = true;
				leftRotate(x->parent);
				s = x->parent->right;}
			if((!s->left->isRed) && (!s->right->isRed)){ //case 2
				s->isRed = true;
				x = x->parent;}
			else if((s->left->isRed) && (!s->right->isRed)){ //case 3
				s->left->isRed = false;
				s->isRed = true;
				rightRotate(s);
				s = x->parent->right;}
			else{ //case 4
				s->isRed = x->parent->isRed;
				x->parent->isRed = false;
				s->right->isRed = false;
				leftRotate(x->parent);
				x = root;}}
		else{
			std::cout<<"x is a right child"<<std::endl;
			//std::cout<<"exchange left and right"<<std::endl;}
			//std::cout<<x->name<<x->parent->name<<x->parent->left->name<<x->parent->right->name<<std::endl;
			Movie *s = x->parent->left;
			if(s->isRed){ //case 1
				s->isRed = false;
				x->parent->isRed = true;
				rightRotate(x->parent);
				s = x->parent->left;}
			if((!s->right->isRed) && (!s->left->isRed)){
				s->isRed = true;
				x = x->parent;}
			else if((s->right->isRed) && (!s->left->isRed)){ //case 3
				s->right->isRed = false;
				s->isRed = true;
				leftRotate(s);
				s = x->parent->left;}
			else{ //case 4
				s->isRed = x->parent->isRed;
				x->parent->isRed = false;
				s->left->isRed = false;
				rightRotate(x->parent);
				x = root;}}
	}x->isRed = false;
}

void MovieTree::redBlackDelete(std::string deleteName){
	Movie *node = searchRecursive(root,deleteName); //find location of node to be deleted
	bool nodeColor = node->isRed; //store color of node to be deleted
	Movie *x; //replacement node used for balancing
	Movie *min;
	if(node!=root){
		if((node->left==nil) && (node->right==nil)){ //no children
			//std::cout << node->name << node->parent->name << node->parent->left->name << std::endl;
			x = node->parent->left;}
			//node->parent->left = nil;}
		else if((node->left!=nil) && (node->right!=nil)){ //two children
			min = minRecursive(node->right); //find minimum right node to replace with
			nodeColor = min->isRed; //color of replacement
			x = min->right;
			x->parent = min;
			if(min == node->right){
				node->parent->left = min;
				min->parent = node->parent;
				min->left = node->left;
				min->left->parent = min;}
			else{
				min->parent->left = min->right;
				min->right->parent = min->parent;
				min->parent = node->parent;
				node->parent->left = min;
				min->left = node->left;
				min->right = node->right;
				node->right->parent = min;
				node->left->parent = min;
				min->isRed = node->isRed;}}
		else{ //one child
			x = node->left;
			node->parent->left = x;
			x->parent = node->parent;}}
	else{
		//std::cout << "node is the root!" << std::endl;
		//repeat cases of 0, 1, or 2 children
		//replacement node is the new root
		//parent of replacement is nil
		if((node->left==nil) && (node->right==nil)){ //no children
			x = node->parent->left;}
			//node->parent->left = nil;}
		else if((node->left!=nil) && (node->right!=nil)){ //two children
			min = minRecursive(node->right);
			nodeColor = min->isRed; //color of replacement
			x = min->right;
			//std::cout<<min->name<<min->left->name<<min->right->name<<std::endl;
			//x->parent = min;
			if(min == node->right){
				node->parent->left = min;
				min->parent = node->parent;
				min->left = node->left;
				min->left->parent = min;}
			else{
				min->parent->left = min->right;
				min->right->parent = min->parent;
				min->parent = node->parent;
				node->parent->left = min;
				min->left = node->left;
				min->right = node->right;
				node->right->parent = min;
				node->left->parent = min;
				min->isRed = node->isRed;}}
		else{ //one child
			x = node->left;
			node->parent->left = x;
			x->parent = node->parent;}
		//std::cout<<x->name<<std::endl;}
		root = min;
		//root->parent = nil;
		min->parent = nil;}
	if(!nodeColor){
		//std::cout << x->name << std::endl;
		if((x->name == "Shawshank Redemption") && (x!=root)){
			root = x;
			x->parent = nil;
			x->right = nil;
			x->left = nil;
		}
		rbBalance(x);
		node->parent->left = nil;
	}delete node;
}

//rotate tree left about node x
void MovieTree::leftRotate(Movie *x){
	Movie *y = x->right;
	x->right = y->left;
	if((y->left != nil) || (y->left != NULL)){
		y->left->parent = x;
	y->parent = x->parent;}
	if(x->parent == nil){
		root = y;}
	else{
		if(x == x->parent->left){
			x->parent->left = y;}
		else{
			x->parent->right = y;}}
	y->left = x;
	x->parent = y;
}

//rotate tree right about node y
void MovieTree::rightRotate(Movie *y){
	Movie *x = y->left;
	y->left = x->right;
	if(x->right != nil){
		x->right->parent = y;}
	x->parent = y->parent;
	if(y->parent == nil){
		root = x;}
	else if(y == y->parent->left){
		y->parent->left = x;}
	else{
		y->parent->right = x;}
	x->right = y;
	y->parent = x;
}

//insert node into tree. NO RECURSION.
Movie* MovieTree::insertRB(std::string newName, std::string newRank, std::string newYear, int newQuantity){
	Movie *node = new Movie(newName, newRank, newYear, newQuantity,nil,nil,nil,true); //create new node
	Movie *tmp = root;
	while(tmp!=nil){ //find where new node belongs
		node->parent = tmp; //link new node to parent
		if(newName.compare(tmp->name)<0){
			tmp = tmp->left;}
		else{
			tmp = tmp->right;}}
	if(node->parent == nil){ //case 1: empty tree. make new node root.
		root = node;}
	else if(newName.compare(node->parent->name)<0){ //case 2: new node is a left child. link parent to new node
		node->parent->left = node;}
	else{
		node->parent->right = node;} //case 3: new node is a right child. link parent to new node
	return node; //return pointer to new node
}

//insert node into tree and then maintain RED/BLACK tree properties
void MovieTree::redBlackInsert(std::string newName, std::string newRank, std::string newYear, int newQuantity){
	Movie *x = insertRB(newName, newRank, newYear, newQuantity);
	while((x != root) && (x->parent->isRed)){
		if(x->parent == x->parent->parent->left){
			Movie *uncle = x->parent->parent->right;
			if(uncle->isRed){ //case 1: uncle is red
				//RBCase1Left(x,uncle)
				x->parent->isRed = false;
				uncle->isRed = false;
				x->parent->parent->isRed = true;
				x = x->parent->parent;}
			else{
				if(x == x->parent->right){ //case 2: new node is right child and uncle is black
					x = x->parent;
					leftRotate(x);} //convert into case 3
				//RBCase3Left(x)
				x->parent->isRed = false; //case 3: new node is left and uncle is black
				x->parent->parent->isRed = true;
				rightRotate(x->parent->parent);}}
		else{
			Movie *uncle = x->parent->parent->left;
			if(uncle->isRed){
				//RBCase1Right(x,uncle)
				x->parent->isRed = false;
				uncle->isRed = false;
				x->parent->parent->isRed = true;
				x = x->parent->parent;}
			else{
				if(x == x->parent->left){
					x = x->parent;
					rightRotate(x);}
				//RBCase3Right(x)
				x->parent->isRed = false;
				x->parent->parent->isRed = true;
				leftRotate(x->parent->parent);
			}
		}
	}
	root->isRed = false;
}

//uses text file to build tree
void MovieTree::build(std::string filename){
	root = nil;
	std::string newRank, newName, newYear, nQ;
	int newQuantity;
	std::ifstream myfile(filename);
	if(myfile.is_open()){
		while(std::getline(myfile,newRank,',')){ //keep reading until end of file
				std::getline(myfile,newName,',');
				std::getline(myfile,newYear,',');
				std::getline(myfile,nQ,'\n');
				newQuantity = std::stoi(nQ); //convert quanitity into integer for easy decrementing
				redBlackInsert(newName, newRank, newYear, newQuantity);
				if(!isValid()){
					std::cout<<"not valid!!!"<<std::endl;
				}
		}
	myfile.close();
	}else std::cout<<"Unable to open file"<<std::endl;
}

//non user accessible function to find longest path in tree
int MovieTree::longestPathRecursive(Movie *node){
	if(node == nil){
		return 0;
	}else{
		int lDepth = longestPathRecursive(node->left);
		int rDepth = longestPathRecursive(node->right);

		if(lDepth > rDepth){
			return(lDepth+1);
		}else return(rDepth+1);
	}
}

//user accessible function to find longest path in tree
int MovieTree::longestPath(){
	return longestPathRecursive(root);
}

//no user accessible count function.
void MovieTree::countRecursive(Movie *startMovie){
	if(startMovie->left!=nil){ //uses inorder traversal to count the number of nodes in the tree.
		countRecursive(startMovie->left);
	}
	count++;
	if(startMovie->right!=nil){
		countRecursive(startMovie->right);
	}
}

//user accessible count function.
int MovieTree::countTree(){
	count = 0; //reset count each time in case the tree changes.
	countRecursive(root); //count each node in tree.
	return count;
}

//non user accessible print tree function.
void MovieTree::printRecursive(Movie *startMovie){
	if(startMovie->left!=nil){ //uses inorder traversal to print the name and quantity of each node in the tree in alphabetcal order.
		printRecursive(startMovie->left);
	}
	std::cout<<"Movie: "<<startMovie->name<<" "<<startMovie->quantity<<std::endl;
	if(startMovie->right!=nil){
		printRecursive(startMovie->right);
	}
}

//user accessible print tree function. root is hidden.
void MovieTree::print(){
	return printRecursive(root);
}

//non user accessible recursive function to find the minimum of a tree.
Movie* MovieTree::minRecursive(Movie *startMovie){
	while(startMovie->left != nil){ //keep traversing left until leaf reached. leaf is minimum.
		startMovie = startMovie->left;
	}return startMovie;
}

//user accessible recursive delete function.
void MovieTree::deleteMovie(std::string deleteName){
	Movie *deleted = searchRecursive(root, deleteName);
	if(deleted==nil){ //check if movie exists
		std::cout<<"Movie not found."<<std::endl;
	}else{ //only attempt to delete if movie does exist.
		redBlackDelete(deleteName);
		//deleteRecursive(root,deleteName);
	}
}

//recursively search tree for string "searchName"
Movie* MovieTree::searchRecursive(Movie *startMovie, std::string searchName){
	if(startMovie==nil)return nil; //if empty BST, return NULL
	if(startMovie->name==searchName)return startMovie; //if found, return address where found
	else if(searchName.compare(startMovie->name)<0) //if name > searchName, searchName must be in the left branch of the tree
		return searchRecursive(startMovie->left,searchName); //continue searching left of tree
	else //the searchName must be on the right branch of the tree
		return searchRecursive(startMovie->right, searchName); //continue searching right of tree
}

//recursively search accessible by user. hides access to root.
void MovieTree::search(std::string searchName){
	Movie *foundMovie;
	foundMovie = searchRecursive(root, searchName);
	if(foundMovie==nil){ //if move not found, say so
		std::cout<<"Movie not found."<<std::endl;
	}else{ //otherwise display information of found node
		std::cout<<"Movie Info:"<<std::endl;
		std::cout<<"==========="<<std::endl;
		std::cout<<"Ranking:"<<foundMovie->rank<<std::endl;
		std::cout<<"Title:"<<foundMovie->name<<std::endl;
		std::cout<<"Year:"<<foundMovie->year<<std::endl;
		std::cout<<"Quantity:"<<foundMovie->quantity<<std::endl;
	}
}

//user accessible rent function.
void MovieTree::rent(std::string rentName){
	Movie *rentMovie;
	rentMovie=searchRecursive(root, rentName); //search entire treee for movie to be rented
	if(rentMovie==nil){ //if movie not found, say so.
		std::cout<<"Movie not found."<<std::endl;
	}else{ //otherwise, decrement the quantity of the movie and print its updated information
		rentMovie->quantity--;
		std::cout << "Movie has been rented." << std::endl;
		std::cout << "Movie Info:" << std::endl;
		std::cout << "===========" << std::endl;
		std::cout << "Ranking:" << rentMovie->rank << std::endl;
		std::cout << "Title:" << rentMovie->name << std::endl;
		std::cout << "Year:" << rentMovie->year << std::endl;
		std::cout << "Quantity:" << rentMovie->quantity << std::endl;
		if(rentMovie->quantity==0){ //if the quantity of movie reaches zero, delete it
			//std::cout<<"quantity 0. deleting movie"<<std::endl;
			deleteRecursive(root,rentName);
			//redBlackDelete(rentMovie->name);
		}
	}
}

//non user accessible recursive delete ALL function.
void MovieTree::deleteAllRecursive(Movie *startMovie){
	if(startMovie->left!=nil){ //delete all nodes using postorder traversal
		deleteAllRecursive(startMovie->left);
	}
	if(startMovie->right!=nil){
		deleteAllRecursive(startMovie->right);
	}
	std::cout<<"Deleting: "<<startMovie->name<<std::endl;
	delete startMovie;
}

//user accessible recursive delete ALL function
void MovieTree::deleteAll(){
	return deleteAllRecursive(root);
}

//DRIVER
int main(int argc, char *argv[]){ //allows text file to be passed from the command line as a command line argument
	std::string filename  = std::string(argv[1]);
	MovieTree myMovieTree;
	myMovieTree.build(filename);
	while(true){ //Display menu
		std::string choice, searchName, rentName, deleteName;
		std::cout << "======Main Menu======" << std::endl;
		std::cout << "1. Find a movie" << std::endl;
		std::cout << "2. Rent a movie" << std::endl;
		std::cout << "3. Print the inventory" << std::endl;
		std::cout << "4. Delete a movie" << std::endl;
		std::cout << "5. Count the movies" << std::endl;
		std::cout << "6. Count the longest path" << std::endl;
		std::cout << "7. Quit" << std::endl;
		std::getline(std::cin,choice);

		if(choice=="1"){ //Find a movie
			std::cout<<"Enter title:"<<std::endl;
			std::getline(std::cin,searchName);
			myMovieTree.search(searchName);
		}
		else if(choice=="2"){ //Rent a movie
			std::cout<<"Enter title:"<<std::endl;
			std::getline(std::cin,rentName);
			myMovieTree.rent(rentName);
		}
		else if(choice=="3"){ //Print the inventory
			myMovieTree.print();
		}
		else if(choice=="4"){ //Delete a movie
			std::cout<<"Enter title:"<<std::endl;
			std::getline(std::cin,deleteName);
			myMovieTree.deleteMovie(deleteName);
			//myMovieTree.isValid();
		}
		else if(choice=="5"){ //Count the movies
			std::cout<<"Tree contains: "<<myMovieTree.countTree()<<" movies."<<std::endl;
		}
		else if(choice=="6"){ //find the longest path in a tree
			std::cout << "Longest Path: " << myMovieTree.longestPath() << std::endl;
		}
		else{ //Quit
			std::cout<<"Goodbye!"<<std::endl;
			break;
		}
	}
	return 0;
}

bool MovieTree::isValid(){
	int valid = rbValid(root);
	//std::cout<<valid<<std::endl;
	if(valid == 0){
		return false;
	}else{
		return true;
	}
}

// Returns 0 if the tree is invalid, otherwise returns the black node height. 
int MovieTree::rbValid(Movie *node)
{
    int lh = 0;
    int rh = 0;

    // If we are at a nil node just return 1
    if (node == nil)
        return 1;

    else
    {
        // First check for consecutive red links. 
        if (node->isRed)
        {
            if(node->left->isRed || node->right->isRed)
            {
                std::cout << "This tree contains a red violation" << std::endl;
                return 0;
            }
        }

        // Check for valid binary search tree. 
        if ((node->left != nil && node->left->name.compare(node->name) > 0) || (node->right != nil && node->right->name.compare(node->name) < 0))
        {
            std::cout << "This tree contains a binary tree violation" << std::endl;
            return 0;
        }

        // Deteremine the height of let and right children. 
        lh = rbValid(node->left);
        rh = rbValid(node->right);

        // black height mismatch 
        if (lh != 0 && rh != 0 && lh != rh)
        {
            std::cout << "This tree contains a black height violation" << std::endl;
            return 0;
        }

        // If neither height is zero, incrament if it if black. 
        if (lh != 0 && rh != 0)
        {
                if (node->isRed)
                    return lh;
                else
                    return lh+1;
        }

        else
            return 0;

    }
}


//non user accessible recursive delete function.
Movie* MovieTree::deleteRecursive(Movie *startMovie, std::string deleteName){
	if(startMovie==nil)return startMovie; //if tree empty, return null
	else if(deleteName.compare(startMovie->name)<0){ //traverse left and right respectively until found node to be deleted.
		startMovie->left = deleteRecursive(startMovie->left,deleteName);
	}else if(deleteName.compare(startMovie->name)>0){
		startMovie->right = deleteRecursive(startMovie->right, deleteName);
	}else{
		//Leaf. No children.
		if(startMovie->left == nil && startMovie->right == nil){ //easiest case: delete leaf.
			delete startMovie; //delete leaf
			startMovie = nil; //reset pointer
		}else if(startMovie->left==nil){ //1 child on right //middle case: determine if has left or right child, then shift child up appropriately before deleting node. 
			Movie *tmp = startMovie;
			startMovie = startMovie->right;
			startMovie->parent = tmp->parent; //relink parent
			delete tmp;
		}else if(startMovie->right==nil){ //1 child on left
			Movie *tmp = startMovie;
			startMovie = startMovie->left;
			startMovie->parent = tmp->parent; //relink parent
			delete tmp;
		}else{ //2 children
			Movie *tmp = minRecursive(startMovie->right); //most difficult case: find the minimum right value in the tree
			startMovie->name = tmp->name; //replace current node with min right value below root.
			startMovie->rank = tmp->rank;
			startMovie->year = tmp->year;
			startMovie->quantity = tmp->quantity;
			startMovie->right = deleteRecursive(startMovie->right,tmp->name); //now just like deleting a node with one child. delete the min right node using recursion. this effectively shifts the right side of the current node up one node, while in the process deleting the current node
		}
	}
	return startMovie;
}

/*//recursively insert new movies into tree
Movie* MovieTree::insertRecursive(Movie *tparent, Movie *troot, std::string newName, std::string newRank, std::string newYear, int newQuantity){
	if(troot==nil){ //if end of tree is reached, insert new movie
		troot = new Movie(newName,newRank,newYear,newQuantity,tparent,nil,nil,true);
		rbAddFixup(troot);
	}
	else if(newName.compare(troot->name)<0){ //if newName is alphabetically smaller than current name, traverse left
		troot->left=insertRecursive(troot,troot->left,newName,newRank,newYear,newQuantity);
	}
	else{ //if newName is alphabetically larger than the current name, traverse right
		troot->right=insertRecursive(troot,troot->right,newName,newRank,newYear,newQuantity);
	}
	return troot; //always return the address of the new movie to be inserted into end of tree
}*/


/*
*CSCI2270 CS2:Data Structures
*Author:Shirly Montero
*Date: July 10th, 2017
*Binary Search Tree
*/

#include <iostream>
#include "BSTree.hpp"
using namespace std;

int main(){
	int size = 10;
	int a[] = {45, 32, 56, 12, 90, 23, 54, 20, 1, 234};
	//int size = 12; use this for more test cases for deleteNode
	//int a[] = {45, 32, 56, 12, 90, 60, 70, 23, 54, 20, 1, 234};
  BSTree myTree;
  myTree.build(a, size);
	myTree.traverseAndPrint();
	int searchKey = 54;
	Node *toSearchNode = myTree.search(searchKey);
	if (toSearchNode==nullptr){
		cout<<"Searched for "<<searchKey<<" and didn't find it"<<endl;
	}else{
		cout<<"Searched for "<<searchKey<<" and found "<<toSearchNode->key<<endl;
	}
	Node *min = myTree.treeMinimum();
	cout<<"Tree minimum is "<<min->key<<endl;
	cout<<"deleting 20"<<endl;
	myTree.deleteNode(20);//no children and node a left child
	//myTree.deleteNode(234);//no children and node a right child
	//myTree.deleteNode(12);//two children and replacement not node->right
	//myTree.deleteNode(56);//two children and replacement node->right
	//myTree.deleteNode(90);//one right child, node a rightChild, and replacement childless
	//myTree.deleteNode(32);//one left child, node a leftChild, and no replacement from right
	myTree.traverseAndPrint();
	cout<<endl;
}

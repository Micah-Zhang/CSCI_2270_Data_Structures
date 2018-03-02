/*
*CSCI2270 CS2:Data Structures
*Author:Shirly Montero
*Date: July 10th, 2017
*Binary Search Tree
*/

#include <iostream>
#include "BSTree.hpp"
using namespace std;

BSTree::BSTree(){
}

void BSTree::insert(int value){
	Node *newNode = new Node(value, nullptr, nullptr, nullptr);
	if (root == nullptr){//tree is empty
		root = newNode;
	}else{//tree has at least one Node
		Node *walker = root;
		Node *walker_parent = root;
		while(walker != nullptr){
			walker_parent = walker;//when nullptr reached, cannot access parent
			if(value < walker-> key){
				walker = walker->left;
			}else{
				walker = walker->right;
			}
		}//finished traversing/found location for newNode
		if(value < walker_parent->key){//newNode will be a left child
			walker_parent->left = newNode;
			newNode->parent = walker_parent;
			//cout<<"newNode: "<<newNode->key<<" with parent: "<<walker_parent->key<<endl;
		}else{//newNode will be a right child
			walker_parent->right = newNode;
			newNode->parent = walker_parent;
			//cout<<"newNode: "<<newNode->key<<" with parent: "<<walker_parent->key<<endl;
		}
	}
}

void BSTree::build(int *array, int arraySize){
	root = nullptr;
	for (int i=0; i<arraySize; i++){
		insert(array[i]);
	}
}

void printTreeInOrder(Node *n){//left-root-right
	if(n->left != nullptr){
		printTreeInOrder(n->left);
	}
	cout<<n->key<<" ";
	if(n->right != nullptr){
		printTreeInOrder(n->right);
	}
}

void printTreePreOrder(Node *n){//root-left-right
	cout<<n->key<<" ";
	if(n->left != nullptr){
		printTreePreOrder(n->left);
	}
	if(n->right != nullptr){
		printTreePreOrder(n->right);
	}
}

void printTreePostOrder(Node *n){//left-right-root
	if(n->left != nullptr){
		printTreePostOrder(n->left);
	}
	if(n->right != nullptr){
		printTreePostOrder(n->right);
	}
	cout<<n->key<<" ";
}
void BSTree::traverseAndPrint(){
	cout<<"Tree Pre-Order Traversal"<<endl;
	printTreePreOrder(root);
	cout<<endl;
	cout<<"Tree In-Order Traversal"<<endl;
	printTreeInOrder(root);
	cout<<endl;
	cout<<"Tree Post-Order Traversal"<<endl;
	printTreePostOrder(root);
	cout<<endl;
}

Node* BSTree::searchRecursive(Node *node, int searchKey){
	if(node==nullptr)return nullptr;//if tree is empty
	if (node->key==searchKey) return node;
	else if(node->key > searchKey)
		return searchRecursive(node->left,searchKey);
	else
		return searchRecursive(node->right, searchKey);
}

Node* BSTree::search(int searchKey){
	return searchRecursive(root, searchKey);
}

Node* BSTree::treeMinimum(Node *node){
	if (node==nullptr) return nullptr;
	else {
		while (node->left != nullptr){
			node = node->left;
		}
		return node;
	}
}
Node* BSTree::treeMinimum(){
	return treeMinimum(root);
}

void BSTree::deleteNode(int value){
	Node *node = search(value);
	if (node != root){
		if(node->left == nullptr && node->right == nullptr){//no children
			if (node->parent->left == node){//node is a left child
				node->parent->left = nullptr;
			}else{ //node is a right child
				node->parent->right = nullptr;}
		}else if (node->left != nullptr && node->right != nullptr){//two children
			 Node *min = treeMinimum(node->right);//replacement min right subtree
			 if (min == node->right){//replacement node rightChild
				 if (node->parent->left == node){//node is a leftChild
					 node->parent->left = min;
					 min->parent = node->parent;
					 min->left = node->left;
					 min->left->parent = min;
				 }else{//node is a rightChild
					 node->parent->right = min;//connecting 45 to 90
					 min->parent = node->parent;//connecting 90 to 45
					 min->left = node->left; //shifting 54
					 min->left->parent = min;//shilfting 54
				 }
			 }else {//replacement is not the rightChild of node e.g. 12
				 if (node->parent->left == node){//node is leftChild
 	 				min->parent->left = min->right;//detaching min
 					//linking min rightChild, next should have a conditional
 	 				if (min->right!=nullptr) min->right->parent = min->parent;
 	 				min->parent = node->parent;//linking min to parent
 	 				node->parent->left = min;//linking parent to min
 	 				min->left = node->left;//linking min to left child
 					node->left->parent = min;////linking left child to min
 	 				min->right = node->right;//linking min to right child
 	 				node->right->parent = min;//linking right child to min
 				}else{//node is rightChild e.g. 56 with 60 (not in the example)
 					min->parent->left = min->right;//detaching min from parent
 					//linking min rightChild, next should have a conditional
 					if (min->right != nullptr) min->right->parent = min->parent;
 					min->parent = node->parent;//linking min to parent
 					node->parent->right = min;//linking parent to min
 					min->left = node->left;//linking min to left child 54
 					node->left->parent = min;////linking left child 54 to min
 					min->right = node->right;//linking min to right child
 					node->right->parent = min;//linking right child to min
 				}
 			}
  		}else {//one child
 			if (node->parent->left == node){//node is leftChild
  				if (node->left != nullptr){//node has a leftChild
  					node->left->parent = node->parent;
 					node->parent->left = node->left;
 				}else{//node has a rightChild
 					node->right->parent = node->parent;
 					node->parent->left = node->left;
 				}
 			}else{//node is rightChild
 				if (node->left!=nullptr){//node has a left child
 					node->left->parent = node->parent;//linking leftChild
 					node->parent->right = node->left;//detaching node
 				}else{//node has a rightChild
 					node->right->parent = node->parent;//linking rightChild
 					node->parent->right = node->right;//detaching node
 				}
 			}
 		}
 	}else{
  	//repeat cases of 0, 1, or 2 children
 	//replacement node is the new root
  	//parent of replacement is nullptr

 	}
 delete node;
 }

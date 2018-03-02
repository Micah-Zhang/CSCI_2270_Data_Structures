/*
*CSCI2270 CS2:Data Structures
*Author:Shirly Montero
*Date: July 10th, 2017
*Binary Search Tree
*/
#ifndef BSTree_HPP
#define BSTree_HPP

struct Node{
	int key;
	Node *parent;
	Node *left;
	Node *right;
	Node(int k, Node *p, Node *l, Node *r):
								key(k), parent(p), left(l), right(r){};
};
class BSTree{
	private:
		Node *root;
		Node* searchRecursive(Node *node, int value);
		Node* treeMinimum(Node *node);
		//void printTreePreOrder(Node *node);
		//void printTreeInOrder(Node *node);
		//void printTreePostOrder(Node *node);
	public:
		BSTree();
		Node* treeMinimum();//for testing
		void build(int *array, int arraySize);//not in the textbook
		void insert(int value);
		Node *search(int value);
		void traverseAndPrint();
		void deleteNode(int value);
		void deleteTree();
};
#endif//BSTree_HPP

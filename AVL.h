#pragma once

#include "LinkedList.h"

#include <iostream>
#include <fstream>

using namespace std;

template <typename ItemType>

class AVLTreeSet {

private:

	struct Node {
		ItemType item;
		int height;
		Node* left;
		Node* right;
		Node(const ItemType& data, Node* leftVal = NULL, Node* rightVal = NULL) : item(data), height(1), left(leftVal), right(rightVal) {}

		~Node() {};
	};


	Node* root;

	void clearTree(Node* root) {
		if (root == NULL) {
			return;
		}
		else {
			clearTree(root->left);
			clearTree(root->right);
			delete(root);
			root = NULL;
		}
	}

public:
	AVLTreeSet() {
		root = NULL;
	}

	~AVLTreeSet() { clear(); };

//GET HEIGHT FUNCTION --------------------------------

	int getHeight(Node* n) {
		if (n == NULL) {
			return 0;
		}
		else {
			return n->height;
		}
	}

//SET HEIGHT FUNCTION ---------------------------------

	void setHeight(Node* n) {
		if (getHeight(n->right) > getHeight(n->left)) {
			n->height = getHeight(n->right) + 1;
		}
		else {
			n->height = getHeight(n->left) + 1;
		}
	}

//INSERT FUNCTION ------------------------------------

	void insert(const ItemType& item) {
		insert(root, item);
	}

	bool insert(Node*& n, const ItemType& item) {				//edit function to account for names alreqady included in the tree
		if (n == NULL) {
			n = new Node(item);
			return true;
		}
		else if (item < n->item) {
			if (insert(n->left, item)) {
				setHeight(n);					
				return true;
			}
		}
		else if (item > n->item) {
			if (insert(n->right, item)) {
				setHeight(n);					
				return true;
			}
		}
		else {
			return false;
		}

	}

//FIND MIN FUNCTION ---------------------------------

	ItemType findMin(Node* n) const {
		if (n->left == NULL) {
			return n->item;
		}
		else {
			return findMin(n->left);
		}
	}

//REMOVE FUNCTION -----------------------------------

	void  remove(const ItemType& item) {
		remove(root, item);
	}

	bool remove(Node*& n, const ItemType& item) {
		if (n == NULL) {
			return false;
		}
		else if (item < n->item) {
			remove(n->left, item);
			setHeight(n);
			return true;
		}
		else if (item > n->item) {
			remove(n->right, item);
			setHeight(n);
			return true;
		}
		else {
			Node* removeNode;

			if (n->left == NULL) {
				removeNode = n;
				n = n->right;
				delete removeNode;
			}
			else if (n->right == NULL) {
				removeNode = n;
				n = n->left;
				delete removeNode;
			}
			else {
				n->item = findMin(n->right);
				remove(n->right, n->item);
			}
			//delete removeNode;
			return true;
		}

	}

//FIND FUNCTION --------------------------------
	bool find(const ItemType& item) {

		return false;

	}

//CLEAR WRAPPER FUNCTION --------------------------

	void clear() {
		clearTree(root);
	}

//PRINT FUNCTION ---------------------------------

	void print() {
		int queueSize;
		int level = 0;
		int max = 8;
		LinkedList<Node*> printQueue;

		cout << "print" << endl;

		if (root != NULL) {
			printQueue.push_back(root);
			while (printQueue.getSize() != 0) {				
				queueSize = printQueue.getSize();
				cout << "level " << level << ": ";
				for (int i = 0; i < queueSize; i++) {
					if (queueSize > max) {
						cout << endl;
					}
					auto item = printQueue.pop_front();				//where do I add children as it will effect the size
						if (item->left != NULL) {
							printQueue.push_back(item->left);
						}
						if (item->right != NULL) {
							printQueue.push_back(item->right);
						}
						cout << item->item << "(" << getHeight(item) << ") ";
					//cout << printQueue.pop_front() << " " << getHeight(i->item);

				}
				level++;
				cout << endl;
			}
		}
	}
		


};


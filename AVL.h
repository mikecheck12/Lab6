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

	int getHeight(Node*& n) {
		if (n == NULL) {
			return 0;
		}
		else {
			return n->height;
		}
	}

//SET HEIGHT FUNCTION ---------------------------------

	void setHeight(Node*& n) {
		if (getHeight(n->right) > getHeight(n->left)) {
			n->height = getHeight(n->right) + 1;
		}
		else {
			n->height = getHeight(n->left) + 1;
		}
	}

//ROTATE FUNCTION -----------------------------------

	void rRight(Node*& n) {
		Node* k = n->left;
		n->left = k->right;
		k->right = n;
		setHeight(n);
		setHeight(k);
		n = k;

	}

	void rLeft(Node*& n) {
		Node* k = n->right;
		n->right = k->left;
		k->left = n; 
		setHeight(n);
		setHeight(k);
		n = k;
		
	}

//BALANCE RIGHT/LEFT FUNCTIONS ---------------------------------

	void balRight(Node*& n) {
		if (getHeight(n->left->right) > getHeight(n->left->left)) {
			rLeft(n->left);
		}
			rRight(n);
	}

	void balLeft(Node*& n) {
		if (getHeight(n->right->left) > getHeight(n->right->right)) {
			rRight(n->right);
		}
		rLeft(n);
	}

//BALANCE TREE FUNCTION -----------------------------------

	void balanceAVL(Node*& n) {
		if (getHeight(n->left) - getHeight(n->right) > 1) {
			balRight(n);
		}
		else if (getHeight(n->right) - getHeight(n->left) > 1) {
			balLeft(n);
		}
	}

//INSERT FUNCTION ------------------------------------

	void insert(const ItemType& item) {
		insert(root, item);
	}

	bool insert(Node*& n, const ItemType& item) {				//edit function to account for names alreqady included in the tree
	  if(!find(item))
		if (n == NULL) {
			n = new Node(item);
			balanceAVL(n);
			return true;
		}
		else if (item < n->item) {
			if (insert(n->left, item)) {
				setHeight(n);	
				balanceAVL(n);
				return true;
			}
		}
		else if (item > n->item) {
			if (insert(n->right, item)) {
				setHeight(n);	
				balanceAVL(n);
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
			if (!find(item) || n == NULL) {
				return false;
			}
			else if (item < n->item) {
				remove(n->left, item);
				setHeight(n);
				balanceAVL(n);
				return true;
			}
			else if (item > n->item) {
				remove(n->right, item);
				setHeight(n);
				balanceAVL(n);
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
                                        setHeight(n);                   //added for last test...
                                        balanceAVL(n);
				}
				//delete removeNode;
				return true;
			}
		}

//FIND FUNCTION --------------------------------
	
	bool find(const ItemType& item) {
		return find(root, item);
	}

	bool find(Node*& n, const ItemType& item) {
		if (n == NULL) {
			return false;
		}
		else if (item < n->item) {
			return find(n->left, item);
		}
		else if (item > n->item) {
			return find(n->right, item);
		}
		return true;
	}
	
//CLEAR WRAPPER FUNCTION --------------------------

	void clear() {
		clearTree(root);
	}

//PRINT FUNCTION ---------------------------------

	void print(ofstream& out) {
		int queueSize;
		int level = 0;
		int max = 8;
		LinkedList<Node*> printQueue;

		out << "print" << endl;

		if (root != NULL) {
			printQueue.push_back(root);
			while (printQueue.getSize() != 0) {				
				queueSize = printQueue.getSize();
				out << "level " << level << ":";
				for (int i = 0, j = 0; i < queueSize; i++, j++) {
						auto item = printQueue.pop_front();				
						if (item->left != NULL) {
							printQueue.push_back(item->left);
						}
						if (item->right != NULL) {
							printQueue.push_back(item->right);
						}
						if (j == max) {
                                                    j = 0;
                                                    out << endl;
                                                    out << "level " << level << ":";
                                                }
						out << " " << item->item << "(" << getHeight(item) << ")";

				}
				level++;
				out << endl;
			}
		}
	}
		


};


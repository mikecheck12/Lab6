#pragma once
#include <iostream>
#include <fstream>

using namespace std;

template <typename ItemType>

class LinkedList {

private:

	//Node* temp;
	//int count;
	//Linked List Constructor
	//LinkedList(Node* head = NULL, Node* tail = NULL, int size = 0) : head(head), tail(tail), size(size) {}

	struct Node {
		ItemType item;
		Node* next;
		Node* prev;
		//Constructor Node(data, next, prev)
		Node(const ItemType& data, Node* nextVal = NULL, Node* prevVal = NULL) : item(data), next(nextVal), prev(prevVal) {}
		//Destructor
		~Node() {};
	};

	Node* head;
	Node* tail;
	int size;


public:
	
	// List constructor
	LinkedList() {
		head = NULL;
		tail = NULL;
		size = 0;
	}

	//List Destructor
	~LinkedList() { clear(); };


//Clear function
	void clear(){
			while (head != NULL) {
				Node* current = head;
				head = head->next;
				delete current;
			}
			tail = NULL;
			size = 0;
			//cout << "clear" << endl;
	}

//Initial Item
	void startList(const ItemType& item) {
		head = new Node(item, NULL, NULL);
		tail = head;
		size++;
	}

//insert items to front of list
	void push_front(const ItemType& item) {
		if (size == 0) {
			startList(item);
		}
		else {
			//head = new Node(item, NULL, head);
			head = new Node(item, head, NULL);

			if (head->next != NULL) {
				head->next->prev = head;
			}
			size++;
			//if (tail == NULL) {
				//tail = head;
				//size++;
			//}
		}
	}
//insert items on back of list
	void push_back(const ItemType& item) {
		if (tail != NULL) {
			tail->next = new Node(item, NULL, tail);
			tail = tail->next;
			size++;
		}
		else {
			push_front(item);
		}
	}

//insert items inside the list
	//does temp need to be deleted at the end of the function?
	void insert(int index, const ItemType& item) {
		
		int count = 0;
		Node* temp = head;

		//cout << "insert " << index << " " << item << endl;

		if (index < 0 || index > size) {
			//not valid
			return;
		}
		else {
			while (count != index) {
				temp = temp->next;
				count++;
			}
			if (index == 0) {
				push_front(item);
			}
			else if (index == size) {
				push_back(item);
			}
			else {
				Node* new_node = new Node(item, temp, temp->prev);
				temp->prev->next = new_node;
				temp->prev = new_node;
				size++;
			}
		}
	}

	void addToQueue(Node* n) {
		if (n != NULL) {

		}
	}

//remove from the front of the 
	ItemType pop_front() {
		//if (head == NULL) {
		//	return;
		//}
		//else {
			Node* removeNode = head;
			ItemType item = head->item;
			head = head->next;
			delete removeNode;
			if (head != NULL) {
				head->prev = NULL;
			}
			else {
				tail = NULL;
			}
			size--;
			return item;
		//}
	}

// remove from the end of the list
	ItemType pop_back() {
		Node* removeNode = tail;
		ItemType item = tail->item;
		tail = tail->prev;
		delete removeNode;
		tail->next = NULL;
		size--;
		return item;
	}

//Remove function
	ItemType remove(int index) {
		
		int count = 0;
		Node* temp = head;


		if (index < 0 || index > size - 1) {
			//cout << "remove " << index << endl;
			return ItemType();
		}
		else {
			while (count != index) {
				temp = temp->next;
				count++;
			}

			if (index == 0) {
				//cout << "remove " << index << " " << head->item << endl;
				return pop_front();
			}
			else if (index == size - 1) {
				//cout << "remove " << index << " " << tail->item << endl;
				return pop_back();
			}
			else {
				//cout << "remove " << index << " " << temp->item << endl;
				Node* removeNode = temp;
				ItemType item = temp->item;
				removeNode->prev->next = removeNode->next;
				removeNode->next->prev = removeNode->prev;
				delete removeNode;
				size--;
				return item;

			}
		}
	}

//Find Function

	int find(const ItemType& item) {
		int counter = 0;
		Node* temp = head;
		while (counter < size) {
			if (temp->item == item) {
				return counter;
			}
			else {
				temp = temp->next;
				counter++;
			}

		}
		return -1;
	}

//Output function
	void print(ofstream& out) {
		int count = 0;
		Node* temp = head;

		//while (temp != NULL) {
		out << "print" << endl;
		while(count < size){
			out << "node" << " " << count << ": " << temp->item << endl;
			temp = temp->next;
			count++;
		}
	}

	int getSize() {
		return size;
	}


};

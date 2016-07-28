#include "AVL.h"
#include "LinkedList.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

	AVLTreeSet<string> tree;
	string cmd;
	string item;

	ifstream in;
	in.open("in60.txt");

	//ofstream out;
	//out.open("actual.txt");

	while (in >> cmd) {
		if (cmd == "clear") {
			cout << "clear" << endl;
			tree.clear();
		}
		if (cmd == "add") {
			in >> item;
			cout << "add " << item << endl;
			tree.insert(item);
		}
		if (cmd == "remove") {
			in >> item;
			cout << "remove " << item << endl;
			tree.remove(item);
		}
		if (cmd == "find") {
			in >> item;
			cout << "find " << item << " " << boolalpha << tree.find(item) << endl;
		}
		if (cmd == "print") {
			tree.print();			//pass out when writing to file
		}
	}

	//out.close();
	

	system ("pause");
	return 0;
}
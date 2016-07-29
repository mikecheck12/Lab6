#include "AVL.h"
#include "LinkedList.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char*argv[]) {

	AVLTreeSet<string> tree;
	string cmd;
	string item;

	ifstream in;
        in.open(argv[1]);

        ofstream out;
        out.open(argv[2]);

	while (in >> cmd) {
		if (cmd == "clear") {
                        out << "clear" << endl;
			tree.clear();
		}
		if (cmd == "add") {
			in >> item;
                        out << "add " << item << endl;
			tree.insert(item);
		}
		if (cmd == "remove") {
			in >> item;
                        out << "remove " << item << endl;
			tree.remove(item);
		}
		if (cmd == "find") {
			in >> item;
                        out << "find " << item << " " << boolalpha << tree.find(item) << endl;
		}
		if (cmd == "print") {
                        tree.print(out);	//pass out when writing to file
		}
	}

        out.close();
	

	return 0;
}

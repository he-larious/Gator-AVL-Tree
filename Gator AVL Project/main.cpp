#include "avl.h"

void RemoveQuote(string& str);

int main() {
	int num;
	string command;
	string name;
	string id;
	AVLTree avl;

	cin >> num;

	for (int i = 0; i < num; i++) {
		cin >> command;
		if (command == "insert") {
			string space;
			getline(cin, space, '\"');  // Use quotes as delimiter
			getline(cin, name, '\"' );
			getline(cin, space, ' ');
			getline(cin, id);
			avl.Insert(name, id);
		}
		else if (command == "remove") {
			cin >> id;
			avl.Remove(id);
		}
		else if (command == "removeInorder") {
			int n;
			cin >> n;
			avl.RemoveInorder(n);
		}
		else if (command == "search") {
			string space, nameOrId;
			getline(cin, space, ' ');
			getline(cin, nameOrId);
			RemoveQuote(nameOrId);
			if (isdigit(nameOrId.at(0))) {
				avl.SearchID(nameOrId);
			}
			else if (isalpha(nameOrId.at(0))) {
				avl.SearchName(nameOrId);
			}
		}
		else if (command == "printInorder") {
			avl.PrintInorder();
		}
		else if (command == "printPreorder") {
			avl.PrintPreorder();
		}
		else if (command == "printPostorder") {
			avl.PrintPostorder();
		}
		else if (command == "printLevelCount") {
			avl.PrintLevelCount();
		}
	}
	return 0;
}

void RemoveQuote(string& str) {
	// Only remove quote from beginning and end of string.
	if (str.at(0) == '\"') {
		str.erase(0, 1);
	}
	if (str.at(str.size() - 1) == '\"') {
		str.erase(str.size() - 1, 1);
	}
}
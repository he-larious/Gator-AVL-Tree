#pragma once
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::max;
using std::cin;
using std::getline;

class AVLTree {
private:
	struct AVLNode {
		string name;
		string id;
		int height = 0;
		AVLNode* left = nullptr;
		AVLNode* right = nullptr;
		AVLNode(string _name, string _id) : name(_name), id(_id) {};
	};
	AVLNode* root = nullptr;
	vector<AVLNode*> inorder;
	vector<AVLNode*> preorder;

	// Helper Functions
	AVLNode* HelperInsert(AVLNode* node, string name, string id);
	AVLNode* HelperRemove(AVLNode* node, string id);
	void HelperRemoveInorder(AVLNode* node);
	AVLNode* HelperSearchID(AVLNode* node, string id);
	void HelperSearchName(AVLNode* node);
	void HelperPrint(AVLNode* root, string traversal);

	// Rotation Functions
	AVLNode* RotateLeft(AVLNode* node);
	AVLNode* RotateRight(AVLNode* node);
	AVLNode* RotateLeftRight(AVLNode* node);
	AVLNode* RotateRightLeft(AVLNode* node);

	// Tree Functions
	AVLNode* MinNode(AVLNode* node);
	AVLNode* MaxNode(AVLNode* node);

	// Node Functions
	int Height(AVLNode* node);
	int BalanceFactor(AVLNode* node);
	bool ValidName(string name);
	bool ValidID(string id);

public:

	// Insert, Remove, Search Functions
	void Insert(string name, string id);
	void Remove(string id);
	void RemoveInorder(int n);
	void SearchID(string id);
	void SearchName(string name);

	// Print Functions
	void PrintInorder();
	void PrintPreorder();
	void PrintPostorder();
	void PrintLevelCount();
};

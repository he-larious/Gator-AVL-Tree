#include "avl.h"

// Insert, Remove, Search Functions (+Helper)
void AVLTree::Insert(string name, string id) {
	// Helper search function will return nullptr if the id doesn't exist.
	if (ValidName(name) && ValidID(id) && !HelperSearchID(root, id)) {
		root = HelperInsert(root, name, id);
		cout << "successful" << endl;
	}
	else {
		cout << "unsuccessful" << endl;
	}
}

AVLTree::AVLNode* AVLTree::HelperInsert(AVLNode* node, string name, string id) {
	// Normal BST insertion from Aman
	if (!node) {
		return new AVLNode(name, id);
	}
	else if (id < node->id) {
		node->left = HelperInsert(node->left, name, id);
	}
	else if (id > node->id) {
		node->right = HelperInsert(node->right, name, id);
	}

	// Update height of ancestor nodes while inserting a new node.
	node->height = Height(node);

	// Calculate balance factor for local node to see if node became unbalanced.
	int balance = BalanceFactor(node);

	// Left left case
	if (balance > 1 && id < node->left->id) {
		return RotateRight(node);
	}
	// Right right case
	else if (balance < -1 && id > node->right->id) {
		return RotateLeft(node);
	}
	// Left right case
	else if (balance > 1 && id > node->left->id) {
		return RotateLeftRight(node);
	}
	// Right left case
	else if (balance < -1 && id < node->right->id) {
		return RotateRightLeft(node);
	}

	return node;
}

void AVLTree::Remove(string id) {
	// Helper search function returns nullptr if the id doesn't exist.
	if (HelperSearchID(root, id)) {
		HelperRemove(root, id);
		cout << "successful" << endl;
	}
	else {
		cout << "unsuccessful" << endl;
	}
}

AVLTree::AVLNode* AVLTree::HelperRemove(AVLNode* node, string id) {
	if (!root) {
		return root;
	}
	if (id < node->id) {
		node->left = HelperRemove(node->left, id);
	}
	else if (id > node->id) {
		node->right = HelperRemove(node->right, id);
	}
	else {
		// Leaf node - set parent to nullptr.
		if (!node->left && !node->right) {
			// If root is a leaf node then removing it will leave an empty tree.
			if (node == root) {
				delete node;
				root = nullptr;
			}
			return nullptr;
		}
		// Node has 1 child - set parent to reference that child.
		else if (!node->left) {
			AVLNode* child = node->right;
			delete node;
			return child;
		}
		else if (!node->right) {
			AVLNode* child = node->left;
			delete node;
			return child;
		}
		// Node has 2 children - find inorder successor.
		else {
			// Inorder successor = next smallest id in tree.
			AVLNode* inorderSuccessor = MinNode(node->right);

			// Copy inorder successor's name and id into node.
			node->name = inorderSuccessor->name;
			node->id = inorderSuccessor->id;

			// Delete inorder successor correctly by checking for its number of children.
			node->right = HelperRemove(node->right, inorderSuccessor->id);
		}
	}
	return node;
}

void AVLTree::RemoveInorder(int n) {
	// Helper function loads nodes into a vector with an inorder traversal.
	HelperRemoveInorder(root);

	// Check if index exists.
	if (n < 0 || n >= inorder.size()) {
		cout << "unsuccessful" << endl;
	}
	else {
		HelperRemove(root, inorder.at(n)->id);
		cout << "successful" << endl;
	}

	inorder.clear();
}

void AVLTree::HelperRemoveInorder(AVLNode* node) {
	if (!node) {
		return;
	}
	HelperRemoveInorder(node->left);
	inorder.push_back(node);
	HelperRemoveInorder(node->right);
}

void AVLTree::SearchID(string id) {
	// Helper search function returns node w/ matching id, or nullptr if the id doesn't exist.
	if (HelperSearchID(root, id)) {
		cout << HelperSearchID(root, id)->name << endl;
	}
	else {
		cout << "unsuccessful" << endl;
	}
}

AVLTree::AVLNode* AVLTree::HelperSearchID(AVLNode* node, string id) {
	if (!node) {
		return nullptr;
	}
	else if (id == node->id) {
		return node;
	}
	else if (id < node->id) {
		return HelperSearchID(node->left, id);
	}
	else {
		return HelperSearchID(node->right, id);
	}
}

void AVLTree::SearchName(string name) {
	// Helper function loads nodes into a vector with a preorder traversal.
	HelperSearchName(root);
	bool exist = false;

	for (unsigned int i = 0; i < preorder.size(); i++) {
		if (preorder.at(i)->name == name) {
			exist = true;
			cout << preorder.at(i)->id << endl;
		}
	}

	if (!exist) {
		cout << "unsuccessful" << endl;
	}

	preorder.clear();
}

void AVLTree::HelperSearchName(AVLNode* node) {
	if (!node) {
		return;
	}
	preorder.push_back(node);
	HelperSearchName(node->left);
	HelperSearchName(node->right);
}

// Rotation Functions

/***************************************************************************************
*    Title: Left Rotation: Right Right Case
*    Author: Amanpreet Kapoor
*    Availability: Balanced Trees Lecture Slides
***************************************************************************************/
AVLTree::AVLNode* AVLTree::RotateLeft(AVLNode* node) {
	AVLNode* grandchild = node->right->left;
	AVLNode* parent = node->right;
	parent->left = node;
	node->right = grandchild;
	return parent;
}

AVLTree::AVLNode* AVLTree::RotateRight(AVLNode* node) {
	AVLNode* grandchild = node->left->right;
	AVLNode* parent = node->left;
	parent->right = node;
	node->left = grandchild;
	return parent;
}

AVLTree::AVLNode* AVLTree::RotateLeftRight(AVLNode* node) {
	node->left = RotateLeft(node->left);
	return RotateRight(node);
}

AVLTree::AVLNode* AVLTree::RotateRightLeft(AVLNode* node) {
	node->right = RotateRight(node->right);
	return RotateLeft(node);
}

// Tree Functions
AVLTree::AVLNode* AVLTree::MinNode(AVLNode* node) {
	// Find the node with the smallest id.
	while (node && node->left) {
		node = node->left;
	}
	return node;
}

AVLTree::AVLNode* AVLTree::MaxNode(AVLNode* node) {
	// Find the node with the largest id.
	while (node && node->right) {
		node = node->right;
	}
	return node;
}

// Node Functions
int AVLTree::Height(AVLNode* node) {
	// Return the longest distance from the local node to a leaf node.
	if (!node) {
		return 0;
	}
	else if (!node->left && !node->right) {
		return 1;
	}
	else if (!node->left) {
		return 1 + Height(node->right);
	}
	else if (!node->right) {
		return 1 + Height(node->left);
	}
	return max(Height(node->left), Height(node->right)) + 1;  // 1-based height.
}

int AVLTree::BalanceFactor(AVLNode* node) {
	if (!node) {
		return 0;
	}
	return Height(node->left) - Height(node->right);
}

bool AVLTree::ValidName(string name) {
	// Check if name has only letters and spaces.
	for (unsigned int i = 0; i < name.size(); i++) {
		if (!isalpha(name.at(i)) && !isblank(name.at(i))) {
			return false;
		}
	}
	return true;
}

bool AVLTree::ValidID(string id) {
	// Check if id is 8 digits long.
	if (id.size() != 8) {
		return false;
	}
	for (unsigned int i = 0; i < id.size(); i++) {
		if (!isdigit(id.at(i))) {
			return false;
		}
	}
	return true;
}

// Print Functions (+Helper)
void AVLTree::PrintInorder() {
	HelperPrint(root, "inorder");
}

void AVLTree::PrintPreorder() {
	HelperPrint(root, "preorder");
}

void AVLTree::PrintPostorder() {
	HelperPrint(root, "postorder");
}

void AVLTree::HelperPrint(AVLNode* root, string traversal) {
	if (!root) {
		return;
	}

	/* Last node in preorder traversal is either:
	 *	1. Largest node if it doesn't have left children.
	 *  2. Smallest left node of the largest node if it has left children.
	 */
	if (traversal == "preorder") {
		AVLNode* largest = MaxNode(this->root);
		AVLNode* smallestLeft = MinNode(largest->left);

		if (root != largest && root != smallestLeft) {
			cout << root->name << ", ";
		}
		else if (root == largest) {
			if (!largest->left) {
				cout << root->name << endl;
			}
			else {
				cout << root->name << ", ";
			}
		}
		else {
			cout << root->name << endl;
		}
	}

	HelperPrint(root->left, traversal);

	// Last node in inorder traversal is the largest node.
	if (traversal == "inorder") {
		if (root != MaxNode(this->root)) {
			cout << root->name << ", ";
		}
		else {
			cout << root->name << endl;
		}
	}

	HelperPrint(root->right, traversal);

	// Last node in postorder traversal is the root.
	if (traversal == "postorder") {
		if (root != this->root) {
			cout << root->name << ", ";
		}
		else {
			cout << root->name << endl;
		}
	}
}

void AVLTree::PrintLevelCount() {
	/* Passing root into height function will return 1-based height of tree, which
	 * is equivalent to the number of levels in the tree.
	 */
	cout << Height(root) << endl;
}
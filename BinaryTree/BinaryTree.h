#pragma once

struct Node
{
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	int data = 0;
};

class BinaryTree
{
private:
	Node* root = nullptr;
	bool isEmpty = true;
	int count = 0;

	/*recursively removes all leaf nodes connected to the provided node,
	  and removes the provided node.*/
	void deleteLeafAndBranches(Node* root);
public:
	/*initializes*/
	BinaryTree(bool startWithRoot = false, int rootValue = 0);
	~BinaryTree();
};
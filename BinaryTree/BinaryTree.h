#pragma once

struct Node
{
	Node* parent = nullptr;
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
	void deleteLeafAndBranchesRecursive(Node* root);

	/*adds the provided node to the binary tree at the suitable branch.
	  recursive. Starting at the provided leaf pointer.*/
	void insertNodeRecursive(Node* parentLeaf, Node* newNode);

	/*recursively searches for a node which contains the provided value.
	  Returns true if found, else false.*/
	bool searchForValueRecursive(Node* root, int value) const;

	/*recursively searches for a node which contains the provided value.
	  if found, removes that node safely and returns true. else returns false.*/
	bool searchAndDeleteLeafRecursive(Node* parentLeaf, int value);

	void deleteLeaf(Node* )
public:
	/*initializes*/
	BinaryTree(bool startWithRoot = false, int rootValue = 0);
	~BinaryTree();

	/*adds a node with the provided value to the binary tree*/
	void addNode(int value);

	/*Returns true if the binary tree contains a node with the provided value.
	  Uses binary searching.*/
	bool contains(int value) const;

	/*returns true if node with value was found and removed, 
	  else returns false.*/
	bool remove(int value);
};
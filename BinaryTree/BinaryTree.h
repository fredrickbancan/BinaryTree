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
public:
	BinaryTree();
	~BinaryTree();
};
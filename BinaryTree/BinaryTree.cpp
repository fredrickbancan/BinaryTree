#include "BinaryTree.h"

bool BinaryTree::searchForValueRecursive(Node* root, int value) const
{
	if (root->data == value)
	{
		return true;
	}

	if (value > root->data && root->rightChild != nullptr)
	{
		
		return searchForValueRecursive(root->rightChild, value);
		
	}
	else if (root->leftChild != nullptr)
	{
		return searchForValueRecursive(root->leftChild, value);
	}
	return false;
}

bool BinaryTree::searchAndDeleteLeafRecursive(Node* root, int value)
{
	if (root->data == value)
	{
		deleteLeaf(root);
		return true;
	}

	if (value > root->data && root->rightChild != nullptr)
	{

		return searchForValueRecursive(root->rightChild, value);

	}
	else if (root->leftChild != nullptr)
	{
		return searchForValueRecursive(root->leftChild, value);
	}
	return false;
}

void BinaryTree::deleteLeaf(Node* leaf)
{
	//TODO: impliment

}

Node* BinaryTree::getDeepestSmallestNodeRecursive(Node* root)
{
	if (root->leftChild == nullptr)
	{
		return root;
	}
	return getDeepestSmallestNodeRecursive(root->leftChild);
}

BinaryTree::BinaryTree(bool startWithRoot /*= false*/, int rootValue/*= 0*/)
{
	if (startWithRoot)
	{
		root = new Node{nullptr, nullptr, nullptr, rootValue};
		count++;
		isEmpty = false;
	}
}

void BinaryTree::deleteLeafAndBranchesRecursive(Node* leaf)
{
	if (leaf == nullptr)
	{
		return;
	}

	deleteLeafAndBranchesRecursive(leaf->leftChild);
	deleteLeafAndBranchesRecursive(leaf->rightChild);

	//changing parents pointer to this node to nullptr will prevent pointing to invalid memory
	if (leaf->parent != nullptr)
	{
		if (leaf->parent->leftChild == leaf)
		{
			leaf->parent->leftChild = nullptr;
		}
		else if (leaf->parent->rightChild == leaf)
		{
			leaf->parent->rightChild = nullptr;
		}
	}

	count--;
	delete leaf;
}

void BinaryTree::insertNodeRecursive(Node* parentLeaf, Node* newNode)
{
	if (newNode->data > parentLeaf->data)
	{
		if (parentLeaf->rightChild == nullptr)
		{
			newNode->parent = parentLeaf;
			parentLeaf->rightChild = newNode;
			isEmpty = false;
			count++;
			return;
		}
		insertNodeRecursive(parentLeaf->rightChild, newNode);
	}
	else
	{
		if (parentLeaf->leftChild == nullptr)
		{
			newNode->parent = parentLeaf;
			parentLeaf->leftChild = newNode;
			isEmpty = false;
			count++;
			return;
		}
		insertNodeRecursive(parentLeaf->leftChild, newNode);
	}
}

BinaryTree::~BinaryTree()
{
	deleteLeafAndBranchesRecursive(root);
}

void BinaryTree::addNode(int value)
{
	if (isEmpty)
	{
		root = new Node{ nullptr, nullptr, nullptr, value };
		count++;
		isEmpty = false;
		return;
	}
	insertNodeRecursive(root, new Node{nullptr, nullptr, nullptr, value});
}

bool BinaryTree::contains(int value) const
{
	if(isEmpty)
	return false;

	return searchForValueRecursive(root, value);
}

bool BinaryTree::remove(int value)
{
	if (isEmpty)
		return false;

	return searchAndDeleteLeafRecursive(root, value);
}

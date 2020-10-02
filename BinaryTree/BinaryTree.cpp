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
	//if this is a leaf at the end of the tree
	if (leaf->leftChild == nullptr && leaf->rightChild == nullptr)
	{
		//if the leaf has a parent, ie, if the leaf is NOT the root
		if (leaf->parent != nullptr)
		{
			//correct parent pointers
			if (leaf->parent->leftChild == leaf)
			{
				leaf->parent->leftChild = nullptr;
			}
			else
			{
				leaf->parent->rightChild = nullptr;
			}
		}

		//delete leaf at end of tree
		delete leaf;
		count--;
		if (count < 1)
		{
			isEmpty = true;
		}
		return;
	}

	//correcting pointers

	
	Node* nodeToSwap = nullptr;//the node that will be put in the position of the deleted node

	//finding replacement node and attaching leaf children to replacement node
	if(leaf->leftChild == nullptr)//if the leaf only has a right child
	{
		nodeToSwap = getDeepestSmallestNodeRecursive(leaf->rightChild);
		nodeToSwap->rightChild = leaf->rightChild;
	}
	else if(leaf->rightChild == nullptr)//if the leaf only has a left child
	{
		nodeToSwap = getDeepestLargestNodeRecursive(leaf->leftChild);
		nodeToSwap->leftChild = leaf->leftChild;
	}
	else//if the leaf has both children
	{
		nodeToSwap = getDeepestSmallestNodeRecursive(leaf->rightChild);
		nodeToSwap->rightChild = leaf->rightChild;
		nodeToSwap->leftChild = leaf->leftChild;
	}

	//disconnect replacement node from its parent
	if (nodeToSwap->parent != nullptr)
	{
		//correct parent pointers
		if (nodeToSwap->parent->leftChild == nodeToSwap)
		{
			nodeToSwap->parent->leftChild = nullptr;
		}
		else
		{
			nodeToSwap->parent->rightChild = nullptr;
		}
	}
	
	//attach replacement node to leaf parent
	if (leaf->parent != nullptr)
	{
		if (leaf->parent->leftChild == leaf)
		{
			leaf->parent->leftChild = nodeToSwap;
		}
		else
		{
			leaf->parent->rightChild = nodeToSwap;
		}
		nodeToSwap->parent = leaf->parent;
	}
	
	//finally delete leaf
	delete leaf;
	count--;
	if (count < 1)
	{
		isEmpty = true;
	}
}

Node* BinaryTree::getDeepestSmallestNodeRecursive(Node* root)
{
	if (root->leftChild == nullptr)
	{
		return root;
	}
	return getDeepestSmallestNodeRecursive(root->leftChild);
}

Node* BinaryTree::getDeepestLargestNodeRecursive(Node* root)
{
	if (root->rightChild == nullptr)
	{
		return root;
	}
	return getDeepestSmallestNodeRecursive(root->rightChild);
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
	if (count < 1)
	{
		isEmpty = true;
	}
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

int BinaryTree::getCount()
{
	count;
}

bool BinaryTree::getIsEmpty()
{
	return isEmpty;
}

Node* BinaryTree::getRoot()
{
	return root;
}

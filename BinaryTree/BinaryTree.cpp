#include "BinaryTree.h"

BinaryTree::BinaryTree(bool startWithRoot /*= false*/, int rootValue/*= 0*/)
{
	if (startWithRoot)
	{
		root = new Node{nullptr, nullptr, rootValue};
		count++;
	}
}

void BinaryTree::deleteLeafAndBranches(Node* root)
{
	//TODO: impliment
}

BinaryTree::~BinaryTree()
{

}

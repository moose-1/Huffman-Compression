#include "TreeNode.h"

TreeNode::TreeNode(void)
{
	nFrequency = 0;
	byAscii = 0;
	dwCode = 0;
	nCodeLength = 0;

	pParent = 0;
	pLeft = 0;
	pRight = 0;

    dwGeneratedCode = 0;
    isGenerated = 0;
}

TreeNode::~TreeNode(void)
{
}

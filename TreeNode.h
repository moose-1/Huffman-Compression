#pragma once

class TreeNode
{
public:
	TreeNode(void);
	~TreeNode(void);

	int nFrequency;	// must be first for byte align
	unsigned int byAscii;
	long dwCode;
	int nCodeLength;

    long dwGeneratedCode;
    int isGenerated;

	TreeNode *pParent, *pLeft, *pRight;
};

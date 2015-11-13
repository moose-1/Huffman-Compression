#pragma once
\
using namespace std;
#include "TreeNode.h"

/** A 'function class' for use as the Compare class in a
 *  priority_queue<TreeNode*>. 
 */
class HuffmanNodeComparator {
public:
    bool operator()(TreeNode*& lhs, TreeNode*& rhs) const {
        return lhs->nFrequency  > rhs->nFrequency; 
    }
};

class HuffmanTree
{	
	TreeNode* root;
    TreeNode* leafNode[256];
			
	void DeleteNode(TreeNode* node);

    void CalculateLength(TreeNode* node, int code, int length);

    TreeNode* cursor;
public:
	HuffmanTree(int frequencies[]);
	~HuffmanTree(void);

	TreeNode* GetNode(unsigned char c){ return leafNode[c]; };	

    void Start();
    int Traverse(int direction, int& finished);

};

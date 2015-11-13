#include <queue>
using namespace std;
#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(int frequencies[])
{
    // build Huffman tree here
    HuffmanNodeComparator comparator;
    priority_queue<TreeNode*, vector<TreeNode*>, HuffmanNodeComparator> pq(comparator);

    // build pairs (Frequency - Node)
    for(int i=0;i<256; i++)
	{
        leafNode[i] = 0;
        // ignore entries with 0 value
		if (frequencies[i]>0)
		{
			TreeNode *node = new TreeNode();
            node->byAscii = i;
            node->nFrequency = frequencies[i];
            pq.push(node);
            leafNode[i] = node;
		}
    }

    // also these pairs are sorted ascending
    do{
        // Get least frequent entry

        TreeNode* c0 = pq.top();
        pq.pop();

        // Move to other least frequent entry, excepting current now

        TreeNode* c1 = pq.top();
        pq.pop();

        // calculate total frequency of both these least freqnent nodes
        int totalFrequency  = c1->nFrequency + c0->nFrequency;

        // Merge it into one node
        TreeNode* current = new TreeNode;
        current->nFrequency = totalFrequency;
        current->byAscii = 0;
        current->pLeft = c0;
        current->pRight = c1;
        // add those (least freqnect entries) to this merging node
        c0->pParent = current;
        c1->pParent = current;
        c0->dwCode = 0;
        c1->dwCode = 1;

        // add merged node to priority queue
        pq.push(current);

        // after finishing, it will contains root node
		root = current;
        // run, until one node is left in priority queue
    }while(pq.size()>1);

    CalculateLength(root, 0, 0);
}

HuffmanTree::~HuffmanTree(void)
{
	if (root)
		DeleteNode(root);
}

void HuffmanTree::DeleteNode(TreeNode* node)
{
	if (node->pLeft)
		DeleteNode(node->pLeft);
	if (node->pRight)
		DeleteNode(node->pRight);
}

void HuffmanTree::CalculateLength(TreeNode* node, int code, int length)
{
	if (node != root)
	{
		node->dwCode |= code;
		node->nCodeLength = length;
	}

	if (node->pLeft)
		CalculateLength(node->pLeft, (node->dwCode)<<1, length+1);

	if (node->pRight)
		CalculateLength(node->pRight, (node->dwCode)<<1, length+1);
}

void HuffmanTree::Start()
{
    cursor = root;
}

int HuffmanTree::Traverse(int direction, int& finished)
{
    if (direction==1)		
		cursor=cursor->pRight;
	else
		cursor=cursor->pLeft;

    if (!cursor->pRight && !cursor->pLeft)
    {		
        finished = 1;
        return cursor->byAscii;
    } else {
		finished = 0;
        return 0;
    }
}
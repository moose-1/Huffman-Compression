#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#include "HuffmanTree.h"
#include "BitStream.h"

void Encode(TreeNode *pNode, BitStream& out)
{
    if (!pNode->isGenerated)
    {
	    long code = pNode->dwCode;

        pNode->dwGeneratedCode = 0;
	    for(int k=0;k<pNode->nCodeLength;k++)
	    {
		    pNode->dwGeneratedCode <<= 1;

		    if ( code&1 )
			    pNode->dwGeneratedCode |= 1;

		    code >>= 1;
        }

        pNode->isGenerated = 1;
    }

	out.Write(pNode->dwGeneratedCode, pNode->nCodeLength);
}

void compress(const char* sourceFile, const char* compressedFile)
{
    ifstream infile(sourceFile, ios::in | ios::binary);

	if (infile)
	{
		int FrequencyTable[256];

		for(int i=0; i<256; i++)
			FrequencyTable[i] = 0;

		int summary = 0;
		//int count = 0;
		int notZeroFrequencies = 0;

		do
		{
			unsigned char c = 0;
			infile.read((char*)&c, 1);
			if (!infile.eof())
			{
				if (!FrequencyTable[c])
					notZeroFrequencies++;

				FrequencyTable[c]++;
				summary++;
			}
		}while(!infile.eof());

		HuffmanTree tree(FrequencyTable);

		infile.clear();
		infile.seekg(0, ios_base::beg);
		BitStream out(compressedFile, true);

		if (out.IsOpened())
		{
			out.Write(summary, 32);
			out.Write(notZeroFrequencies-1, 8);

			for(int i=0;i<256;i++)
				if (FrequencyTable[i])
				{
					out.Write(i, 8);
					out.Write(FrequencyTable[i], 32);
				}

			do
			{
				unsigned char c = 0;
				infile.read((char*)&c, 1);
				if (!infile.eof())
                    Encode(tree.GetNode(c), out);
			}while(!infile.eof());

		} else {
			cout << "ERROR: Cannot open output file: " << compressedFile << endl;
		}

		infile.close();
	} else {
		cout << "ERROR: Cannot open input file: " << sourceFile << endl;
	}
}

void decompress(const char* compressedFile, const char* decompressedFile)
{
    int FrequencyTable[256];

	for(int i=0; i<256; i++)
		FrequencyTable[i] = 0;

	BitStream in(compressedFile, false);

    if (in.IsOpened())
	{		
		int ReasultFileLength = in.Read(32);

		int treeSize = in.Read(8);
		treeSize++;

		for(int i=0; i<treeSize; i++)
		{
			unsigned char c = (unsigned char)in.Read(8);
			FrequencyTable[c] = in.Read(32);
		}

		HuffmanTree tree(FrequencyTable);

		ofstream outfile(decompressedFile, ios::out | ios::binary);


		
		if (outfile)
		{
			while(ReasultFileLength)
			{                
				tree.Start();

                int finished = 0;
                unsigned char c;
                do
                {
                    c = (unsigned char)tree.Traverse(in.Read(1), finished);
                }while(!finished);

				outfile.write((char*)&c, 1);
				ReasultFileLength--;
			}
			outfile.close();	
		} else {			
            cout << "ERROR: Cannot open output file: " << decompressedFile << endl;
		}			
	}
	else {
        cout << "ERROR: Cannot open input file: " << compressedFile << endl;		
	}
}

int main(int argc, char* argv[])
{
	if (argc<3)
	{
		cout << "Using: " << endl;
		cout << "huffmanCompression [-c] <source file> <compreseed file>" << endl;
        cout << " or " << endl;
        cout << "huffmanCompression [-d] <compreseed file> <decompressed file>" << endl;
	} else {
        if (!strcmp(argv[1], "-c"))
            compress(argv[2], argv[3]);
        else if (!strcmp(argv[1], "-d"))
            decompress(argv[2], argv[3]);
        else
        {
            cout << "Error: " << endl;
            cout << "Invalid option is specified. " << endl;
        }
	}
	return 0;
}


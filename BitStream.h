#pragma once
#include <fstream>
using namespace std;


class BitStream
{
	ofstream outfile;
    ifstream infile;

    bool writing;
	int bitCounter;
	unsigned char accumulatedByte;
public:
	BitStream(const char *fileName, bool write);
	~BitStream(void);

	void Write(int value, int bits);
    int Read(int bits);
	int IsOpened() { return (!!outfile); };
};

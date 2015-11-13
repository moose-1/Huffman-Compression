#include "BitStream.h"

BitStream::BitStream(const char *fileName, bool write)
{
    writing = write;

    if (write)
    {
	    outfile.open(fileName, ios::out | ios::binary);
    } else {
        infile.open(fileName, ios::in | ios::binary);
    }

    bitCounter =  0;
    accumulatedByte = 0;
}

BitStream::~BitStream(void)
{
    if (writing)
    {
	    if (bitCounter)
		    outfile.write((char*)&accumulatedByte, 1);

	    outfile.close();
    } else {
        infile.close();
    }
}

void BitStream::Write(int value, int bits)
{
	while(bits)
	{
		if (value&1)
			accumulatedByte |= (1 << bitCounter);

		value >>= 1;

		bits--;
		bitCounter++;
		bitCounter &= 7;

		if (!bitCounter)
		{
			outfile.write((char*)&accumulatedByte, 1);
			outfile.flush();
			accumulatedByte = 0;
		}
	}
}

int BitStream::Read(int bits)
{
	int value = 0;

	int bits2 = 0;

	while(bits)
	{
		if (!bitCounter)
		{
			infile.read((char*)&accumulatedByte, 1);
		}

		if (accumulatedByte & (1 << bitCounter))
			value |= (1 << bits2);

		bitCounter++;
		bitCounter &= 7;
		bits--;

		bits2++;
	}

	return value;
}

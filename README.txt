This program was written in C++ on Xubuntu 14.04 using CodeBlocks. To run the terminal from the command line, cd into the directory and run the following command:

g++ BitStream.cpp huffmanCompression.cpp HuffmanTree.cpp TreeNode.cpp -o huffmanCompression

This will generate an executeable file inside the root of the folder. Drag any media test files here to this portion of the folder and then run the following command to compress the file.

./huffmanCompression -c originalfile.extension newcompressedfile.extension

A new file will be created in the folder, and you can compare the two files. However, as I've stated in my writeup, many of the compressed files will not open. Doc files are the only ones I have seen consistently open. Txt files seem to be unreadable and won't open unless you add a characters to the contents of the file that are in another language besides English. I tossed a few Japanese characters in the file and I was able to open it, albeit there was no compression and the output file ended up being bigger than the original.

To decompress the compressed file (and return to a copy of the original file that will indeed open), run the following command:

./huffmanCompression -d compressedfile.extension newfilename.extension

Note: You do not have to name the files according to a particular name, just make sure your extensions match up in the decompression state so that you can open the file. For example, the following sequence is acceptable:

./huffmanCompression -c red.jpg apple.jpg.compresssed
./huffmanCompression -d apple.jpg.compresssed finished.jpg

or

./huffmanCompression -c red.jpg red2.jpg
./huffmanCompression -d red2.jpg red_.jpg

I'm sure you get the point by now.

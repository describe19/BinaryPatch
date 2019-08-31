#include <string>
#include <fstream>
#include <functional>
#include <iterator>
#include <algorithm>
#include <vector>
#include <Windows.h>
//extern void replaceSubArray(char* longArray, int longLength, char* find, char* replace, int shortLength);

void patch(std::string filename, char* what, char* repl, int size) {
	
	std::string backupname = filename + ".bak";
	
	if (MoveFile(filename.c_str(), backupname.c_str())) { 												//if renaming file to backup succeeds:

		std::ifstream infile(backupname.c_str(), std::ios::binary | std::ios::in | std::ios::ate);	//open input and output files
		std::ofstream outfile(filename.c_str(), std::ios::binary | std::ios::out);

		if (infile.bad() || outfile.bad()) { 													//check if files opened successfully
			return;
		}

		std::vector<char> buffer(infile.tellg());												//create buffer to store file (reads size with tellg)
		infile.seekg(0, std::ios::beg);														//go to beginning of file

		infile.read(&buffer[0], buffer.size());													//read infile into buffer
		infile.close();

		auto searcher = std::boyer_moore_searcher(what, what+size-1);
		auto it = buffer.begin();
		for (;;) {																//can remove infinite loop if you only want to replace first occurrence
			it = std::search(it, buffer.end(), searcher);
			if ((it == buffer.end())) {
				break;
			}
			it = std::copy(repl, repl + size - 1, it);
			
		}

		outfile.write(&buffer[0], buffer.size()); 												//write modified buffer to file and close files
		outfile.close();
	}
	return;
}
#ifndef _PARSEDFILE_H_
#define _PARSEDFILE_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#define BUFFERSIZE 1024

class ParsedFile {

private:

	std::vector<std::string> parsedFileContainer;

public:
	ParsedFile(const char*);

	bool loadFile(const char*);

	std::vector<std::string> getFileContainer();
};



#endif
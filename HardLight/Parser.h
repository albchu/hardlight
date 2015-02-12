#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#define BUFFERSIZE 1024

class Parser {

private:

	std::vector<std::string> parsedFileContainer;

public:
	Parser(const char*);

	bool loadFile(const char*);

	std::vector<std::string> getFileContainer();
};



#endif
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
};

Parser::Parser(const char* filename) {
	loadFile(filename);
}

bool Parser::loadFile(const char* filename) {

	std::fstream fileIn;
	char lineBuffer[BUFFERSIZE];

	fileIn.open(filename, std::fstream::in | std::fstream::binary);
	if(!fileIn.is_open()) {
		std::cerr << "Couldn't open file." << std::endl;
		return false;
	}

	while(!fileIn.getline(lineBuffer, BUFFERSIZE)) {
		parsedFileContainer.push_back(std::string(lineBuffer) + "\n");
	}

	std::cout << parsedFileContainer.size() << std::endl;
	return true;
}

#endif
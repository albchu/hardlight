
#include "Parser.h"

std::vector<std::string> Parser::getFileContainer() {
	return parsedFileContainer;
}

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

	while(fileIn.getline(lineBuffer, BUFFERSIZE)) {
		parsedFileContainer.push_back(std::string(lineBuffer) + "\n");
	}

	fileIn.close();

	std::cout << parsedFileContainer.size() << std::endl;

	std::string testString;

	std::getline(std::cin, testString);
	return true;
}
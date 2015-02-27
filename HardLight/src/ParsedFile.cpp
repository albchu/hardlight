
#include "ParsedFile.h"

std::vector<std::string> ParsedFile::getFileContainer() {
	return parsedFileContainer;
}

ParsedFile::ParsedFile(const char* filename) {
	loadFile(filename);
}

bool ParsedFile::loadFile(const char* filename) {

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
	return true;
}
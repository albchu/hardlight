#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <stdlib.h>
#include <glm/glm.hpp>
#include "MeshData.h"
#include "ParsedFile.h"

class objParser {

private:

public:

	objParser();

	MeshData loadObj(ParsedFile);

};

#endif
#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <stdlib.h>
#include <glm/glm.hpp>
#include "MeshData.h"
#include "Parser.h"

class objLoader {

private:

public:

	objLoader();

	MeshData loadObj(Parser);

};

#endif
#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

/* OBJ file parser
 *
 * use loadObj to parse an OBJ file that has been read
 */

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
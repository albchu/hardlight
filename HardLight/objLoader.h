#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <stdlib.h>
#include <glm/glm.hpp>
#include "Parser.h"

class objLoader {

private:

	std::vector<glm::vec3> m_vertices; 	// essentially an array of type Vector3f
	std::vector<glm::tvec3<int> > m_faces;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::tvec3<int> > m_fnormals; 	// use in face normal calculation
	std::vector<glm::vec3> m_vnormals;
	std::vector<glm::vec2> m_textures; 	// used to store texture coordinates
	std::vector<glm::tvec3<int> > m_textfaces;	// used to associate a texture coordinate with a face

	char* mtl_filename;

public:

	objLoader();

	bool loadObj(Parser);

};

#endif
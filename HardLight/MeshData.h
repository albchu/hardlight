#ifndef _MESHDATA_H_
#define _MESHDATA_H_

#include <vector>
#include <glm/glm.hpp>

class MeshData {

private:

	std::vector<glm::vec3> m_vertices; 	// essentially an array of type Vector3f
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_textures; 	// used to store texture coordinates

	std::vector<glm::tvec3<int> > m_faces;
	std::vector<glm::tvec3<int> > m_fnormals; 	// use in face normal calculation
	std::vector<glm::tvec3<int> > m_textfaces;	// used to associate a texture coordinate with a face

	char* mtl_filename;

public:

	MeshData();
	MeshData(std::vector<glm::vec3>, std::vector<glm::vec3>, std::vector<glm::vec2>, std::vector<glm::tvec3<int> >, std::vector<glm::tvec3<int> >, std::vector<glm::tvec3<int> >);


};


#endif
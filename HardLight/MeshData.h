#ifndef _MESHDATA_H_
#define _MESHDATA_H_

/*
 * MeshData class
 *
 * Holds data read from OBJ file.
 *
 */

#include <vector>
#include <glm/glm.hpp>

class MeshData {

private:

	std::vector<glm::tvec3<int> > m_faces;
	std::vector<glm::tvec3<int> > m_fnormals; 	// use in face normal calculation
	std::vector<glm::tvec3<int> > m_textfaces;	// used to associate a texture coordinate with a face

	std::vector<glm::vec3> m_vertices; 	// essentially an array of type Vector3f
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_textures; 	// used to store texture coordinates

	char* mtl_filename;

public:


	MeshData();
	MeshData(std::vector<glm::vec3>, std::vector<glm::vec3>, std::vector<glm::vec2>, 
			 std::vector<glm::tvec3<int> >, std::vector<glm::tvec3<int> >, std::vector<glm::tvec3<int> >, char* filename);

	void order_arrays();

	void addVertex(glm::vec3);
	glm::vec3 getVertex(int);

	void addNormal(glm::vec3);
	glm::vec3 getNormal(int);

	void addTexture(glm::vec2);
	glm::vec2 getTexture(int);

	void addFace(glm::tvec3<int>);
	glm::tvec3<int> getFace(int);

	void addFaceNormal(glm::tvec3<int>);
	glm::tvec3<int> getFaceNormal(int);

	void addFaceTexture(glm::tvec3<int>);
	glm::tvec3<int> getFaceTexture(int);

	std::vector<glm::vec3>* getVertices();
	std::vector<glm::vec3>* getNormals();
	std::vector<glm::vec2>* getTextureCoordinates();
};


#endif
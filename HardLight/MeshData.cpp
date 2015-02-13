/* Implementation of MeshData.h
 *
 */

#include "MeshData.h"
#include <iostream>

MeshData::MeshData() {
	m_vertices = std::vector<glm::vec3>();
	m_normals = std::vector<glm::vec3>();
	m_textures = std::vector<glm::vec2>();

	m_faces = std::vector<glm::tvec3<int> >();
	m_fnormals = std::vector<glm::tvec3<int> >();
	m_textfaces = std::vector<glm::tvec3<int> >();

	mtl_filename = NULL;
}

MeshData::MeshData(std::vector<glm::vec3> verts, std::vector<glm::vec3> norms, std::vector<glm::vec2> texts, 
				   std::vector<glm::tvec3<int> > faces, std::vector<glm::tvec3<int> > fnorms, std::vector<glm::tvec3<int> > ftexts, char* filename) {

	m_vertices = verts;
	m_normals = norms;
	m_textures = texts;

	m_faces = faces;
	m_fnormals = fnorms;
	m_textfaces = ftexts;

	mtl_filename = filename;
}

void MeshData::addVertex(glm::vec3 vertex) {
	m_vertices.push_back(vertex);
}

glm::vec3 MeshData::getVertex(int pos) {
	if(pos > m_vertices.size() || pos < 0) {
		std::cout << "vertex position is out of bounds" << std::endl;
	}

	return m_vertices[pos];
}

void MeshData::addNormal(glm::vec3 normal) {
	m_normals.push_back(normal);
}

glm::vec3 MeshData::getNormal(int pos) {
	if(pos > m_normals.size() || pos < 0) {
		std::cout << "normal position is out of bounds" << std::endl;
	}

	return m_normals[pos];
}

void MeshData::addTexture(glm::vec2 texture) {
	m_textures.push_back(texture);
}

glm::vec2 MeshData::getTexture(int pos) {
	if(pos > m_textures.size() || pos < 0) {
		std::cout << "texture position is out of bounds" << std::endl;
	}

	return m_textures[pos];
}

void MeshData::addFace(glm::tvec3<int> face) {
	m_faces.push_back(face);
}

glm::tvec3<int> MeshData::getFace(int pos) {
	if(pos > m_faces.size() || pos < 0) {
		std::cout << "face position is out of bounds" << std::endl;
	}

	return m_faces[pos];
}

void MeshData::addFaceNormal(glm::tvec3<int> faceNorm) {
	m_fnormals.push_back(faceNorm);
}

glm::tvec3<int> MeshData::getFaceNormal(int pos) {
	if(pos > m_fnormals.size() || pos < 0) {
		std::cout << "face normal position is out of bounds" << std::endl;
	}

	return m_fnormals[pos];
}

void MeshData::addFaceTexture(glm::tvec3<int> faceTexture) {
	m_textfaces.push_back(faceTexture);
}

glm::tvec3<int> MeshData::getFaceTexture(int pos) {
	if(pos > m_textfaces.size() || pos < 0) {
		std::cout << "face texture position is out of bounds" << std::endl;
	}

	return m_textfaces[pos];
}
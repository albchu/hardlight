/* Implementation of MeshData.h
 *
 */

#include "MeshData.h"

MeshData::MeshData()
{
	m_vertices = std::vector<glm::vec3>();
	m_normals = std::vector<glm::vec3>();
	m_textures = std::vector<glm::vec2>();

	m_faces = std::vector<glm::tvec3<int> >();
	m_fnormals = std::vector<glm::tvec3<int> >();
	m_textfaces = std::vector<glm::tvec3<int> >();

	mtl_filename = NULL;
}

MeshData::MeshData(std::vector<glm::vec3> verts, std::vector<glm::vec3> norms, std::vector<glm::vec2> texts, 
				   std::vector<glm::tvec3<int> > faces, std::vector<glm::tvec3<int> > fnorms, std::vector<glm::tvec3<int> > ftexts, char* filename)
{

	m_vertices = verts;
	m_normals = norms;
	m_textures = texts;

	m_faces = faces;
	m_fnormals = fnorms;
	m_textfaces = ftexts;

	mtl_filename = filename;
}

void MeshData::order_arrays()
{

	std::vector<glm::vec3> temp_vertices, temp_normals;
	std::vector<glm::vec2> temp_textfaces;

	for(glm::tvec3<int> face : m_faces) {

		glm::vec3 vertex1 = m_vertices[face.x];
		glm::vec3 vertex2 = m_vertices[face.y];
		glm::vec3 vertex3 = m_vertices[face.z];

		temp_vertices.push_back(vertex1);
		temp_vertices.push_back(vertex2);
		temp_vertices.push_back(vertex3);

	}

	for(glm::tvec3<int> faceNormal : m_fnormals) {

		glm::vec3 normal1 = m_normals[faceNormal.x];
		glm::vec3 normal2 = m_normals[faceNormal.y];
		glm::vec3 normal3 = m_normals[faceNormal.z];

		temp_normals.push_back(normal1);
		temp_normals.push_back(normal2);
		temp_normals.push_back(normal3);

	}

	for(glm::tvec3<int> facetexture : m_textfaces) {

		glm::vec2 text1 = m_textures[facetexture.x];
		glm::vec2 text2 = m_textures[facetexture.y];
		glm::vec2 text3 = m_textures[facetexture.z];

		temp_textfaces.push_back(text1);
		temp_textfaces.push_back(text2);
		temp_textfaces.push_back(text3);

	}

	m_vertices = temp_vertices;
	m_normals = temp_normals;
	m_textures = temp_textfaces;

}

void MeshData::addVertex(glm::vec3 vertex)
{
	m_vertices.push_back(vertex);
}

glm::vec3 MeshData::getVertex(int pos)
{
	if(pos > (int)m_vertices.size() || pos < 0) {
		fprintf(stderr, "vertex position is out of bounds\n");
	}

	return m_vertices[pos];
}

void MeshData::addNormal(glm::vec3 normal)
{
	m_normals.push_back(normal);
}

glm::vec3 MeshData::getNormal(int pos)
{
	if(pos > (int)m_normals.size() || pos < 0) {
		fprintf(stderr, "normal position is out of bounds\n");
	}

	return m_normals[pos];
}

void MeshData::addTexture(glm::vec2 texture)
{
	m_textures.push_back(texture);
}

glm::vec2 MeshData::getTexture(int pos)
{
	if(pos > (int)m_textures.size() || pos < 0) {
		fprintf(stderr, "texture position is out of bounds\n");
	}

	return m_textures[pos];
}

void MeshData::addFace(glm::tvec3<int> face)
{
	m_faces.push_back(face);
}

glm::tvec3<int> MeshData::getFace(int pos)
{
	if(pos > (int)m_faces.size() || pos < 0) {
		fprintf(stderr, "face position is out of bounds\n");
	}

	return m_faces[pos];
}

void MeshData::addFaceNormal(glm::tvec3<int> faceNorm)
{
	m_fnormals.push_back(faceNorm);
}

glm::tvec3<int> MeshData::getFaceNormal(int pos)
{
	if(pos > (int)m_fnormals.size() || pos < 0) {
		fprintf(stderr, "face normal position is out of bounds\n");
	}

	return m_fnormals[pos];
}

void MeshData::addFaceTexture(glm::tvec3<int> faceTexture)
{
	m_textfaces.push_back(faceTexture);
}

glm::tvec3<int> MeshData::getFaceTexture(int pos)
{
	if(pos > (int)m_textfaces.size() || pos < 0) {
		fprintf(stderr, "face texture position is out of bounds\n");
	}

	return m_textfaces[pos];
}

std::vector<glm::vec3>* MeshData::getVertices() { return &m_vertices; }
std::vector<glm::vec3>* MeshData::getNormals() { return &m_normals; }
std::vector<glm::vec2>* MeshData::getTextureCoordinates() { return &m_textures; }
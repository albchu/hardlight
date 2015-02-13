
#include "MeshData.h"

MeshData::MeshData() {
	m_vertices = std::vector<glm::vec3>();
	m_normals = std::vector<glm::vec3>();
	m_textures = std::vector<glm::vec2>();

	m_faces = std::vector<glm::tvec3<int> >();
	m_fnormals = std::vector<glm::tvec3<int> >();
	m_textfaces = std::vector<glm::tvec3<int> >();
}

MeshData::MeshData(std::vector<glm::vec3> verts, std::vector<glm::vec3> norms, std::vector<glm::vec2> texts, std::vector<glm::tvec3<int> > faces, std::vector<glm::tvec3<int> > fnorms, std::vector<glm::tvec3<int> > ftexts) {

	m_vertices = verts;
	m_normals = norms;
	m_textures = texts;

	m_faces = faces;
	m_fnormals = fnorms;
	m_textfaces = ftexts;
}
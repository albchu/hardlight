#include <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <utility>

struct Vector3f{
	float x;
	float y;
	float z;
};

struct Vector3i{
	int x;
	int y;
	int z;
};

struct Vector2f{
	float u;
	float v;
};

std::vector<Vector3f> m_vertices; 	// essentially an array of type Vector3f
std::vector<Vector3i> m_faces;
std::vector<Vector3f> m_normals;
std::vector<Vector3f> m_fnormals; 	// use in face normal calculation
std::vector<Vector3f> m_vnormals;
std::vector<Vector2f> m_textures; 	// used to store texture coordinates
std::vector<Vector3i> m_textfaces;	// used to associate a texture coordinate with a face

std::pair<Vector3f, Vector3f> m_bbox;

void VertNormals()
{
	// for every face in m_faces, find the normal of each face using 
	// (p2-p1) x (p3-p1) = facenormal
	for( int i = 0; i < m_faces.size(); i++ )
	{
		Vector3f fnorm;		// fnorm = c
		Vector3f avec;
		Vector3f bvec;
		float magn = 0.0f;

		fnorm.x = 0.0f;	
		fnorm.y = 0.0f;
		fnorm.z = 0.0f;	

		avec.x = 0.0f;	
		avec.y = 0.0f;	
		avec.z = 0.0f;		

		bvec.x = 0.0f;	
		bvec.y = 0.0f;	
		bvec.z = 0.0f;		

		// create vectors a and b of the face
		avec.x = m_vertices[m_faces[i].y].x - m_vertices[m_faces[i].x].x;
		avec.y = m_vertices[m_faces[i].y].y - m_vertices[m_faces[i].x].y;
		avec.z = m_vertices[m_faces[i].y].z - m_vertices[m_faces[i].x].z;

		bvec.x = m_vertices[m_faces[i].z].x - m_vertices[m_faces[i].x].x;
		bvec.y = m_vertices[m_faces[i].z].y - m_vertices[m_faces[i].x].y;
		bvec.z = m_vertices[m_faces[i].z].z - m_vertices[m_faces[i].x].z;
	
		// calculate each coordinate of c (the face normal)
		fnorm.x = avec.y*bvec.z - avec.z*bvec.y;
		fnorm.y = avec.z*bvec.x - avec.x*bvec.z;
		fnorm.z = avec.x*bvec.y - avec.y*bvec.x;

		// normalize vnorm
		magn = sqrt((fnorm.x*fnorm.x) + (fnorm.y*fnorm.y) + (fnorm.z*fnorm.z));
		fnorm.x = fnorm.x/magn;
		fnorm.y = fnorm.y/magn;
		fnorm.z = fnorm.z/magn;

		// Add face normal to vector list
		m_fnormals.push_back(fnorm);	
//std::cout << "(" << avec.x << ", " << avec.y << ", " << avec.z << ")" << std::endl;
//std::cout << "(" << bvec.x << ", " << bvec.y << ", " << bvec.z << ")" << std::endl;
		//std::cout << "(" << fnorm.x << ", " << fnorm.y << ", " << fnorm.z << ")" << std::endl;
	}

	// for every vertice in m_vertices, find each face it is involved with
	// and add that face normal to the vector normal
	for( int i = 0; i < m_vertices.size(); i++ )
	{
		Vector3f vnorm;		
		float magn = 1.0f;

		vnorm.x = 0.0f;	
		vnorm.y = 0.0f;
		vnorm.z = 0.0f;	

		// find each face m_vertices[i] is in
		for( int j = 0; j < m_faces.size(); j++ )
		{
			// if m_vertices[i] is in m_faces[j], add m_fnormals[j] to vnorm
			if(i == m_faces[j].x || i == m_faces[j].y || i == m_faces[j].z)
			{
				vnorm.x += m_fnormals[j].x;
				vnorm.y += m_fnormals[j].y;
				vnorm.z += m_fnormals[j].z;
				//std::cout << j;
				//std::cout << "(" << vnorm.x << ", " << vnorm.y << ", " << vnorm.z << ")" << std::endl;
			}
		}
		// normalize vnorm
		magn = sqrt((vnorm.x*vnorm.x) + (vnorm.y*vnorm.y) + (vnorm.z*vnorm.z));
		vnorm.x = vnorm.x/magn;
		vnorm.y = vnorm.y/magn;
		vnorm.z = vnorm.z/magn;

		// Add vertice normal to vector list
		m_normals.push_back(vnorm);
		//std::cout << "(" << vnorm.x << ", " << vnorm.y << ", " << vnorm.z << ")" << std::endl;
		//std::cout << std::endl;
	}
}

bool LoadObj(const char* filename)
{
	using std::fstream;
	using std::ios;
	
	fstream file;
	file.open(filename, ios::in | ios::binary);
	if (!file.is_open()) {
		std::cout << "error open file" << filename << std::endl;
	}

	m_bbox.first.x = 
	m_bbox.first.y = 
	m_bbox.first.z = (float)10e10;

	m_bbox.second.x = 
	m_bbox.second.y = 
	m_bbox.second.z = (float)-10e10;


	while (!file.eof()) {
		char lineBuffer[1024];
		char seps[] = " /";
		char *token;
		int i;
		Vector3f vertex;
		Vector3i face;
		Vector2f texture;
		Vector3i facetext;

		file.getline(lineBuffer, sizeof(lineBuffer));
		switch (lineBuffer[0]) {
			case 'v':
				if(lineBuffer[1] == 't')
				{
					lineBuffer[0] = ' ';
					lineBuffer[1] = ' ';
					token = strtok(lineBuffer, seps);
					texture.u = (float) atof(token);
					token = strtok(NULL, seps);
					texture.v = (float) atof(token);

					m_textures.push_back(texture);

					//std::cout << "vt = (" << texture.u << ", " << texture.v <<  ")" << std::endl;

				}
				else
				{
					lineBuffer[0] = ' ';
					token = strtok(lineBuffer, seps);
					vertex.x = (float) atof(token);
					token = strtok(NULL, seps);
					vertex.y = (float) atof(token);
					token = strtok(NULL, seps);
					vertex.z = (float) atof(token);

					m_vertices.push_back(vertex);

					m_bbox.first.x = vertex.x < m_bbox.first.x ? vertex.x : m_bbox.first.x;
					m_bbox.first.y = vertex.y < m_bbox.first.y ? vertex.y : m_bbox.first.y;
					m_bbox.first.z = vertex.z < m_bbox.first.z ? vertex.z : m_bbox.first.z;

					m_bbox.second.x = vertex.x > m_bbox.second.x ? vertex.x : m_bbox.second.x;
					m_bbox.second.y = vertex.y > m_bbox.second.y ? vertex.y : m_bbox.second.y;
					m_bbox.second.z = vertex.z > m_bbox.second.z ? vertex.z : m_bbox.second.z;

					//std::cout << "v = (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;
				}
				break;

			case 'f':
				lineBuffer[0] = ' ';

				token = strtok(lineBuffer, seps);
				face.x = atoi(token) - 1;

				token = strtok(NULL, seps);
				facetext.x = atoi(token) - 1;

				token = strtok(NULL, seps);
				face.y = atoi(token) - 1;

				token = strtok(NULL, seps);
				facetext.y = atoi(token) - 1;

				token = strtok(NULL, seps);
				face.z = atoi(token) - 1;

				token = strtok(NULL, seps);
				facetext.z = atoi(token) - 1;

				m_faces.push_back(face);
				m_textfaces.push_back(facetext);

				//std::cout << "f = (" << face.x << ", " << face.y << ", " << face.z << ")" << std::endl;
				//std::cout << "tf = (" << facetext.x << ", " << facetext.y << ", " << facetext.z << ")" << std::endl;

				break;
		}
	}

	file.close();

	std::cout << "Obj file loaded with " << m_vertices.size() << " vertices, " << m_textures.size() << " texture coords, and " << m_faces.size() << " faces." << std::endl;
	std::cout << "bounding-box: min(" << m_bbox.first.x << ", " << m_bbox.first.y << ", " << m_bbox.first.z << ") ";
	std::cout << "max(" << m_bbox.second.x << ", " << m_bbox.second.y << ", " << m_bbox.second.z << ")" << std::endl;
	return true;
}
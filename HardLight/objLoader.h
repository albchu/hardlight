#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <utility>
#include <glm/glm.hpp>

class objLoader {

private:

std::vector<glm::vec3> m_vertices; 	// essentially an array of type Vector3f
std::vector<glm::vec3> m_faces;
std::vector<glm::vec3> m_normals;
std::vector<glm::vec3> m_fnormals; 	// use in face normal calculation
std::vector<glm::vec3> m_vnormals;
std::vector<glm::vec2> m_textures; 	// used to store texture coordinates
std::vector<glm::vec3> m_textfaces;	// used to associate a texture coordinate with a face

char* mtl_filename;

public:

objLoader();

bool LoadObj(const char*);

};


objLoader::objLoader() {

	m_vertices = std::vector<glm::vec3>();
	m_faces = std::vector<glm::vec3>();
	m_normals = std::vector<glm::vec3>();
	m_fnormals = std::vector<glm::vec3>();
	m_vnormals = std::vector<glm::vec3>();
	m_textures = std::vector<glm::vec2>();
	m_textfaces = std::vector<glm::vec3>();

}


bool objLoader::LoadObj(const char* filename)
{
	using std::fstream;
	using std::ios;
	
	fstream file;
	file.open(filename, ios::in | ios::binary);
	if (!file.is_open()) {
		std::cout << "error open file" << filename << std::endl;
	}


	while (!file.eof()) {
		char lineBuffer[1024];
		char seps[] = " /";
		char *token;
		int i;
		glm::vec3 face;
		glm::vec2 texture;
		glm::vec3 faceText;
		glm::vec3 faceNorm;

		glm::vec3 temp_vec3;
		glm::vec2 temp_vec2;

		file.getline(lineBuffer, sizeof(lineBuffer));
		switch (lineBuffer[0]) {
			case 'v':
				if(lineBuffer[1] == 't')
				{
					lineBuffer[0] = ' ';
					lineBuffer[1] = ' ';
					token = strtok(lineBuffer, seps);
					texture.x = (float) atof(token);
					token = strtok(NULL, seps);
					texture.y = (float) atof(token);

					m_textures.push_back(texture);

				}
				else if(lineBuffer[1] == 'n') 
				{
					lineBuffer[0] = ' ';
					lineBuffer[1] = ' ';
					token = strtok(lineBuffer, seps);
					temp_vec3.x = (float) atof(token);
					token = strtok(NULL, seps);
					temp_vec3.y = (float) atof(token);
					token = strtok(NULL, seps);
					temp_vec3.z = (float) atof(token);

					m_normals.push_back(temp_vec3);
				}
				else
				{
					lineBuffer[0] = ' ';
					token = strtok(lineBuffer, seps);
					temp_vec3.x = (float) atof(token);
					token = strtok(NULL, seps);
					temp_vec3.y = (float) atof(token);
					token = strtok(NULL, seps);
					temp_vec3.z = (float) atof(token);

					m_vertices.push_back(temp_vec3);

				}
				break;

			case 'f':
				lineBuffer[0] = ' ';

				token = strtok(lineBuffer, seps);
				face.x = atoi(token) - 1;

				token = strtok(NULL, seps);
				faceText.x = atoi(token) - 1;

				token = strtok(NULL, seps);
				faceNorm.x = atoi(token) - 1;

				token = strtok(NULL, seps);
				face.y = atoi(token) - 1;

				token = strtok(NULL, seps);
				faceText.y = atoi(token) - 1;

				token = strtok(NULL, seps);
				faceNorm.y = atoi(token) - 1;

				token = strtok(NULL, seps);
				face.z = atoi(token) - 1;

				token = strtok(NULL, seps);
				faceText.z = atoi(token) - 1;

				token = strtok(NULL, seps);
				faceNorm.z = atoi(token) - 1;

				m_faces.push_back(face);
				m_textfaces.push_back(faceText);
				m_fnormals.push_back(faceNorm);


				break;
			case 'm':
				for(int i = 0; i < 6; i++) {
					lineBuffer[i] = ' ';
				}

				mtl_filename = strtok(lineBuffer, seps);
				break;

			case 'u':


		}
	}

	file.close();

	std::cout << "Obj file loaded with " << m_vertices.size() << " vertices, " << m_textures.size() << " texture coords, and " << m_faces.size() << " faces." << std::endl;
	return true;
}

#endif
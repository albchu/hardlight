#include "objLoader.h"

objLoader::objLoader() {

	m_vertices = std::vector<glm::vec3>();
	m_faces = std::vector<glm::vec3>();
	m_normals = std::vector<glm::vec3>();
	m_fnormals = std::vector<glm::vec3>();
	m_vnormals = std::vector<glm::vec3>();
	m_textures = std::vector<glm::vec2>();
	m_textfaces = std::vector<glm::vec3>();

}


bool objLoader::loadObj(Parser parser)
{

	for(std::string line : parser.getFileContainer()) {
		char seps[] = " /";
		char *token;
		char *context = NULL;
		int i;
		glm::vec3 face;
		glm::vec2 texture;
		glm::vec3 faceText;
		glm::vec3 faceNorm;

		glm::vec3 temp_vec3;
		glm::vec2 temp_vec2;

		switch (line[0]) {
		case 'v':
			if(line[1] == 't')
			{
				line[0] = ' ';
				line[1] = ' ';
				token = strtok_s((char*)line.c_str(), seps, &context);
				texture.x = (float) atof(token);
				token = strtok_s(NULL, seps, &context);
				texture.y = (float) atof(token);

				m_textures.push_back(texture);

			}
			else if(line[1] == 'n') 
			{
				line[0] = ' ';
				line[1] = ' ';
				token = strtok_s((char*)line.c_str(), seps, &context);
				temp_vec3.x = (float) atof(token);
				token = strtok_s(NULL, seps, &context);
				temp_vec3.y = (float) atof(token);
				token = strtok_s(NULL, seps, &context);
				temp_vec3.z = (float) atof(token);

				m_normals.push_back(temp_vec3);
			}
			else
			{
				line[0] = ' ';
				token = strtok_s((char*)line.c_str(), seps, &context);
				temp_vec3.x = (float) atof(token);
				token = strtok_s(NULL, seps, &context);
				temp_vec3.y = (float) atof(token);
				token = strtok_s(NULL, seps, &context);
				temp_vec3.z = (float) atof(token);

				m_vertices.push_back(temp_vec3);

			}
			break;

		case 'f':
			line[0] = ' ';

			token = strtok_s((char*)line.c_str(), seps, &context);
			face.x = atoi(token) - 1;

			token = strtok_s(NULL, seps, &context);
			faceText.x = atoi(token) - 1;

			token = strtok_s(NULL, seps, &context);
			faceNorm.x = atoi(token) - 1;

			token = strtok_s(NULL, seps, &context);
			face.y = atoi(token) - 1;

			token = strtok_s(NULL, seps, &context);
			faceText.y = atoi(token) - 1;

			token = strtok_s(NULL, seps, &context);
			faceNorm.y = atoi(token) - 1;

			token = strtok_s(NULL, seps, &context);
			face.z = atoi(token) - 1;

			token = strtok_s(NULL, seps, &context);
			faceText.z = atoi(token) - 1;

			token = strtok_s(NULL, seps, &context);
			faceNorm.z = atoi(token) - 1;

			m_faces.push_back(face);
			m_textfaces.push_back(faceText);
			m_fnormals.push_back(faceNorm);


			break;
		case 'm':
			for(i = 0; i < 6; i++) {
				line[i] = ' ';
			}

			mtl_filename = strtok_s((char*)line.c_str(), seps, &context);
			break;

		}
	}

	std::cout << "Obj file loaded with " << m_vertices.size() << " vertices, " << m_textures.size() << " texture coords, and " << m_faces.size() << " faces." << std::endl;
	std::cout << "Also has " << m_normals.size() << "normals " << std::endl;

	std::string testString;

	std::getline(std::cin, testString);
	return true;
}
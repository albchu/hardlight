#include "objLoader.h"

objLoader::objLoader() {

}

MeshData objLoader::loadObj(Parser parser)
{
	std::vector<glm::vec3> m_vertices; 	// essentially an array of type Vector3f
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec2> m_textures; 	// used to store texture coordinates

	std::vector<glm::tvec3<int> > m_faces;
	std::vector<glm::tvec3<int> > m_fnormals; 	// use in face normal calculation
	std::vector<glm::tvec3<int> > m_textfaces;	// used to associate a texture coordinate with a face

	char* mtl_filename;

	for(std::string line : parser.getFileContainer()) {
		char seps[] = " /";
		char *token;
		char *context = NULL;
		int i;
		glm::tvec3<int> face;
		glm::vec2 texture;
		glm::tvec3<int> faceText;
		glm::tvec3<int> faceNorm;

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

	/*std::cout << "Obj file loaded with " << m_vertices.size() << " vertices, " << m_textures.size() << " texture coords, and " << m_faces.size() << " faces." << std::endl;
	std::cout << "Also has " << m_normals.size() << "normals " << std::endl;

	std::string testString;

	std::getline(std::cin, testString);*/
	return MeshData(m_vertices, m_normals, m_textures, m_faces, m_fnormals, m_textfaces, mtl_filename);
}
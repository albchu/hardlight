#ifndef _TEXTURE_MAP_H_
#define _TEXTURE_MAP_H_

//#include "Entity.h"

#include <vector>
#include <map>
#include <string>
#include <GL\glew.h>
#include "ShaderTools.h"
#include <iostream>

using namespace std;
//using namespace glm;

class TextureMap
{
private:
	TextureMap();  // Private so that it can  not be called
	static TextureMap* m_pInstance;
	map<const char * , GLuint> textures;
	void setTexture(const char * ); // To preserve singleton behavior, setTexture should never be explicitly called 
public:
	static TextureMap* Instance();		// Singleton pattern	
	GLuint getTexture(const char * );
};

#endif
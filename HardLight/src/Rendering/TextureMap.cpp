#include "Rendering/TextureMap.h"

// Global static pointer used to ensure a single instance of the class.
TextureMap* TextureMap::m_pInstance = NULL; 

 
/** This function is called to create an instance of the class.
    Calling the constructor publicly is not allowed. The constructor
    is private and is only called by this Instance function.
*/
TextureMap* TextureMap::Instance()
{
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new TextureMap();
 
   return m_pInstance;
}

GLuint TextureMap::getTexture(const char * texturePath)
{
	if(!textures[texturePath])
		setTexture(texturePath);
	return textures[texturePath]; 
}

TextureMap::TextureMap(){}


void TextureMap::setTexture(const char * texturePath)
{
	textures[texturePath] = load_tga_texture(texturePath);
}
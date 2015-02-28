//taken from http://www.opengl-tutorial.org/
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <GL/glew.h>

#include "ShaderTools.h"

using namespace std;

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	string VertexShaderCode;
	ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		fprintf(stderr, "Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	//printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stderr, "%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	//printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		fprintf(stderr, "%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	//printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stderr, "%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

// prints error from specified function if applicable
void errorReport(const char* function) {
	int error = glGetError();

	if(error != GL_NO_ERROR) {
		switch(error) {
		case GL_INVALID_ENUM:
			fprintf(stderr, "%s has thrown an error. (GL_INVALID_ENUM)\n", function);
			break;
		case GL_INVALID_VALUE:
			fprintf(stderr, "%s has thrown an error. (GL_INVALID_VALUE)\n", function);
			break;
		case GL_INVALID_OPERATION:
			fprintf(stderr, "%s has thrown an error. (GL_INVALID_OPERATION)\n", function);
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			fprintf(stderr, "%s has thrown an error. (GL_INVALID_FRAMEBUFFER_OPERATION)\n", function);
			break;
		case GL_OUT_OF_MEMORY:
			fprintf(stderr, "%s has thrown an error. (GL_OUT_OF_MEMORY)\n", function);
			break;
		}
	}
}

GLuint load_tga_texture(const char * imagepath) {

	GLuint textureID;
	unsigned char * imageBuffer;
	unsigned char cGarbage, file_type, pixelDepth;
	short int iGarbage, width, height;
	int mode, total;
	FILE* file;

	file = fopen(imagepath, "rb");
	if(file == NULL) {
		fprintf(stderr, "Couldn't open %s.\n", imagepath);
		return -1;
	}

	// Read 12 byte Header
	fread(&cGarbage, sizeof(unsigned char), 1, file);
	fread(&cGarbage, sizeof(unsigned char), 1, file);
	
	fread(&file_type, sizeof(unsigned char), 1, file);

	fread(&iGarbage, sizeof(short int), 1, file);
	fread(&iGarbage, sizeof(short int), 1, file);
	fread(&cGarbage, sizeof(unsigned char), 1, file);
	fread(&iGarbage, sizeof(short int), 1, file);
	fread(&iGarbage, sizeof(short int), 1, file);

	fread(&width, sizeof(short int), 1, file);
	fread(&height, sizeof(short int), 1, file);
	fread(&pixelDepth, sizeof(unsigned char), 1, file);

	fread(&cGarbage, sizeof(unsigned char), 1, file);

	if((file_type != 2) && (file_type != 3)) {
		fprintf(stderr, "Cannot read %s. It is likely compressed.\n", imagepath);
		fclose(file);
		return -1;
	}

	mode = pixelDepth / 8;
	total = width * height * mode;

	// read image data
	imageBuffer = (unsigned char *)malloc(total * sizeof(unsigned char));

	if(imageBuffer == NULL) {
		fprintf(stderr, "Out of space reading file!\n");
		fclose(file);
		free(imageBuffer);
		return -1;
	}

	fread(imageBuffer, sizeof(unsigned char), total, file);

	if(ferror(file)) {
		fprintf(stderr, "Couldn't read %s.", imagepath);
		fclose(file);
		free(imageBuffer);
		return -1;
	}

	if (mode >= 3) {
		fprintf(stderr, "mode = %d\n", mode);
		int aux;

		for (int i=0; i < total; i+= mode) {
			aux = imageBuffer[i];
			imageBuffer[i] = imageBuffer[i+2];
			imageBuffer[i+2] = aux;
		}
	}


	// Bind and add texture
	glGenTextures(1, &textureID);

	errorReport("glGenTextures");

	glBindTexture(GL_TEXTURE_2D, textureID);
	errorReport("glBindTexture");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	errorReport("glTexParameteri");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	errorReport("glTexParameteri");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	errorReport("glTexParameteri");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	errorReport("glTexParameteri");

	if(mode == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);
	else if(mode == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBuffer);

	errorReport("glTexImage2D");

	free(imageBuffer);
	fclose(file);

	return textureID;

}
//
//#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
//#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
//#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
//
//GLuint load_dds_texture(const char * imagepath)
//{
//	unsigned char header[124];
//
//	FILE *fp; 
//
//	/* try to open the file */ 
//	fp = fopen(imagepath, "rb"); 
//	if (fp == NULL) {
//		fprintf(stderr, "%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
//		getchar(); 
//		return 0;
//	}
//
//	/* verify the type of file */ 
//	char filecode[4]; 
//	fread(filecode, 1, 4, fp); 
//	if (strncmp(filecode, "DDS ", 4) != 0) { 
//		fclose(fp); 
//		return 0; 
//	}
//
//	/* get the surface desc */ 
//	fread(&header, 124, 1, fp); 
//
//	unsigned int height      = *(unsigned int*)&(header[8 ]);
//	unsigned int width	     = *(unsigned int*)&(header[12]);
//	unsigned int linearSize	 = *(unsigned int*)&(header[16]);
//	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
//	unsigned int fourCC      = *(unsigned int*)&(header[80]);
//
//	unsigned char * buffer;
//	unsigned int bufsize;
//	/* how big is it going to be including all mipmaps? */ 
//	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
//	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char)); 
//	fread(buffer, 1, bufsize, fp); 
//	/* close the file pointer */ 
//	fclose(fp);
//
//	unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4; 
//	unsigned int format;
//	switch(fourCC) 
//	{ 
//	case FOURCC_DXT1: 
//		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; 
//		break; 
//	case FOURCC_DXT3: 
//		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; 
//		break; 
//	case FOURCC_DXT5: 
//		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; 
//		break; 
//	default: 
//		free(buffer); 
//		return 0; 
//	}
//
//	// Create one OpenGL texture
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//
//	// "Bind" the newly created texture : all future texture functions will modify this texture
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glPixelStorei(GL_UNPACK_ALIGNMENT,1);	
//
//	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16; 
//	unsigned int offset = 0;
//
//	/* load the mipmaps */ 
//	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) 
//	{ 
//		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize; 
//		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,  
//			0, size, buffer + offset); 
//
//		offset += size; 
//		width  /= 2; 
//		height /= 2; 
//
//		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
//		if(width < 1) width = 1;
//		if(height < 1) height = 1;
//
//	} 
//
//	free(buffer); 
//
//	return textureID;
//}
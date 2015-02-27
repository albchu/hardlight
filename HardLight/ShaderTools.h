//taken from http://www.opengl-tutorial.org/
#ifndef SHADERTOOLS_H
#define SHADERTOOLS_H

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

void errorReport(const char*);

// returns texture id used by OpenGL
GLuint load_tga_texture(const char * imagepath);

//GLuint load_dds_texture(const char * imagepath);

#endif

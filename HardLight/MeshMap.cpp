#include "MeshMap.h"
#include "tempOBJ\objloader.hpp"
#include "objParser.h"
#include "ParsedFile.h"
#include <windows.h>

MeshMap::MeshMap()
{
	
	loadAllOBJs("../data/Models/");

}

MeshData* MeshMap::getEntityMesh(string ent)
{
	return &meshes[ent]; 
}

void MeshMap::setEntityMesh(string ent, MeshData m_data)
{
	meshes[ent] = m_data;
}

void MeshMap::deleteEntityMesh(string ent)
{
	meshes.erase(ent);
}

// searches directory for .objs and fills list of parsed objs
void MeshMap::loadAllOBJs(const char* directory) {

	MeshData mesh;
	objParser parser;
	char searchPath[200];
	wchar_t* wbuff;
	char* cbuff;

	sprintf_s(searchPath, "%s*.obj", directory);
	WIN32_FIND_DATA fd;

	int size = MultiByteToWideChar(CP_UTF8, 0, searchPath, -1, NULL, 0);
	wbuff = new wchar_t[size];
	MultiByteToWideChar(CP_UTF8, 0, searchPath, -1, wbuff, size);

	HANDLE handle = ::FindFirstFile(wbuff, &fd);
	cout << "MeshMap importing the following objects by their filename as keys: " << endl;
	if(handle != INVALID_HANDLE_VALUE) { 
		do { 

			if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {

				size = WideCharToMultiByte(CP_UTF8, 0, fd.cFileName, -1, NULL, 0,  NULL, NULL);
				cbuff = new char[size];
				WideCharToMultiByte(CP_UTF8, 0, fd.cFileName, -1, &cbuff[0], size, NULL, NULL);
				

				std::string dirString = std::string(directory);
				std::string filename = std::string(cbuff);

				mesh = parser.loadObj(ParsedFile((dirString + filename).c_str()));
				mesh.order_arrays();
				setEntityMesh( filename, mesh);

				cout << filename << endl;
			}
		}while(::FindNextFile(handle, &fd));
		::FindClose(handle); 
		cout << "MeshMap has completed importing" << endl;
	} 
}
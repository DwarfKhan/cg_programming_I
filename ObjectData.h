#pragma once
#include <string>
#include <fstream> 
#include <iostream>


namespace ObjLoader {

	struct ObjData {
		float *vertices = nullptr;
		float *normals = nullptr;
		float *uvs = nullptr;
		unsigned int *faces = nullptr;
		 unsigned int numVertices = 0;
		 unsigned int numNormals = 0;
		 unsigned int numUvs = 0;
		 unsigned int numFaces = 0;
	};


	//TODO: cleanup this data
	int Load(const char* fileName, ObjData &data);

}

#pragma once

//fstream & string allow std::ifstream, std::getline
#include <fstream>
#include <string>

namespace ObjLoader {
	struct ObjData {
		unsigned int vertexBufferID = 0, textureBufferID = 0, normalBufferID = 0;
		unsigned int *faces = nullptr;
		float *vertices = nullptr, *normals = nullptr,
			*uvs = nullptr;
		unsigned int numVertices = 0, numNormals = 0, 
			numUvs = 0, numFaces = 0;
	};

	//TODO: Make function later to clean up model data!
	int Load(const char *filePath, ObjData &data);
};

#include "ObjectData.h"


	using namespace ObjLoader;

	static int RecursiveLoad(const char* filePath, ObjData &data) {


		std::ifstream file(filePath);
		std::string nextLine;
		while (std::getline(file, nextLine)) {
			std::stringstream ss(nextLine);
			if (nextLine.length() > 2) {

				if (nextLine[0] == 'v') {

					if (nextLine[1] == 32) { //verts
						if (data.vertices == nullptr) {
							++data.numVertices;
						}
						else {
							for (int i = 0; i < 3; i++) {
								ss >> *data.vertices++;
							}
						}
					}

					if (nextLine[1] == 't') { //uvs
						if (data.uvs == 0) {
							++data.numUvs;
						}
					}

					if (nextLine[1] == 'n') { //normals
						if (data.normals == nullptr) {
							++data.numNormals;
						}
					}
				}
				else if (nextLine[0] == 'f') { // faces
					if (data.faces == nullptr) {
						++data.numFaces;
					}
				}
			}
		}
		if (data.faces == nullptr) {
			data.faces = (unsigned int*)malloc(data.numFaces * 3);
			data.vertices = (float*)malloc(data.numVertices * 3);
			data.normals = (float*)malloc(data.numNormals * 3);
			data.uvs = (float*)malloc(data.numUvs * 3);

			return RecursiveLoad(filePath, data);
		}
	}



	int ObjLoader::Load(const char* filePath, ObjData &data) {

		return RecursiveLoad(filePath, data);
	}

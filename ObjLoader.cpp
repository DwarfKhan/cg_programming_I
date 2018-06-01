#include "ObjLoader.h"

#include <string>       // std::string
#include <iostream>     // std::cout

#include <stdio.h>	//for sscanf...

#define SizeOfFloat3 sizeof(float) * 3
#define SizeOfFloat2 sizeof(float) * 2

static int RecursiveLoad(const char *filePath, ObjLoader::ObjData &data) {
	std::ifstream file(filePath);
	std::string nextLine;

	//Temporary values we will use to increment...
	auto vertices = data.vertices;
	auto normals = data.normals;
	auto uvs = data.uvs;
	auto faces = data.faces;

	while (std::getline(file, nextLine)) {
		if (nextLine.length() > 2) {
			switch (nextLine[0])
			{
				//Reading vertices...
			case 'v':
				switch (nextLine[1])
				{
				case 32:	//Reading vertices...
					if (data.vertices == nullptr) {
						++data.numVertices;
						continue;
					}

					sscanf(nextLine.c_str(), "%*c %f %f %f",
						&vertices[0], &vertices[1], &vertices[2]);
					vertices += 3;

					break;
				case 't':	//Reading uvs...
					if (data.uvs == nullptr) {
						++data.numUvs;
						continue;
					}

					sscanf(nextLine.c_str(), "%*2c %f %f", &uvs[0], &uvs[1]);
					uvs += 2;

					break;
				case 'n':	//Reading normals...
					if (data.normals == nullptr) {
						++data.numNormals;
						continue;
					}

					sscanf(nextLine.c_str(), "%*2c %f %f %f",
						&normals[0], &normals[1], &normals[2]);
					normals += 3;

					break;
				}
				break;
			case 'f':	//Reading faces...
				if (nextLine[1] == 32 && data.faces == nullptr) {
					++data.numFaces;
					continue;
				}

				sscanf(nextLine.c_str(), "%*c %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
					&faces[0], &faces[1], &faces[2], &faces[3], &faces[4], &faces[5],
					&faces[6], &faces[7], &faces[8], &faces[9], &faces[10], &faces[11]);
				faces += 12;

				break;
			}
		}
	}

	//Ohhhh, if faces == nullptr, then we did not set the faces!
	//	We just counted first! So let's run it again!
	if (data.faces == nullptr) {
		data.vertices = (float*)malloc(data.numVertices * SizeOfFloat3);
		data.normals = (float*)malloc(data.numNormals * SizeOfFloat3);
		data.uvs = (float*)malloc(data.numUvs * SizeOfFloat2);
		data.faces = (unsigned int*)malloc(data.numFaces * sizeof(unsigned int) * 12);

		return RecursiveLoad(filePath, data);
	}

	//Now that we have our face data, let's use it to recreate our vertex, normal, and texture buffers!
	data.numVertices = data.numFaces * 2 * 3;	//2 triangles, 3 vertices per triangle
	vertices = (float*)malloc(SizeOfFloat3 * data.numVertices);
	for (size_t i = 0, j = 0, index = 0; i < data.numFaces; i++, j += 12) {
		//vertices...
		size_t vertIndex = data.faces[j] - 1;	//0
		vertices[index++] = data.vertices[vertIndex * 3];
		vertices[index++] = data.vertices[vertIndex * 3 + 1];
		vertices[index++] = data.vertices[vertIndex * 3 + 2];

		vertIndex = data.faces[j + 3] - 1;		//1
		vertices[index++] = data.vertices[vertIndex * 3];
		vertices[index++] = data.vertices[vertIndex * 3 + 1];
		vertices[index++] = data.vertices[vertIndex * 3 + 2];

		vertices[index++] = data.vertices[(data.faces[j + 6] - 1) * 3];
		vertices[index++] = data.vertices[(data.faces[j + 6] - 1) * 3 + 1];
		vertices[index++] = data.vertices[(data.faces[j + 6] - 1) * 3 + 2];

		//
		vertices[index++] = data.vertices[(data.faces[j] - 1) * 3];
		vertices[index++] = data.vertices[(data.faces[j] - 1) * 3 + 1];
		vertices[index++] = data.vertices[(data.faces[j] - 1) * 3 + 2];

		vertices[index++] = data.vertices[(data.faces[j + 6] - 1) * 3];
		vertices[index++] = data.vertices[(data.faces[j + 6] - 1) * 3 + 1];
		vertices[index++] = data.vertices[(data.faces[j + 6] - 1) * 3 + 2];

		vertices[index++] = data.vertices[(data.faces[j + 9] - 1) * 3];
		vertices[index++] = data.vertices[(data.faces[j + 9] - 1) * 3 + 1];
		vertices[index++] = data.vertices[(data.faces[j + 9] - 1) * 3 + 2];

		/*
		//vertices...
		vertices[index++] = data.vertices[data.faces[j] - 1];
		vertices[index++] = data.vertices[data.faces[j + 3] - 1];
		vertices[index++] = data.vertices[data.faces[j + 6] - 1];

		vertices[index++] = data.vertices[data.faces[j] - 1];
		vertices[index++] = data.vertices[data.faces[j + 6] - 1];
		vertices[index++] = data.vertices[data.faces[j + 9] - 1];*/

		//texture coords...
		//TODO: Implement later...

		//normals...
		//TODO: Implement later...
	}

	free(data.vertices);
	data.vertices = vertices;

	for (int i = 0; i < data.numVertices * 3; i += 3) {
		printf("v%d %f, %f, %f\n",i/3 , vertices[i], vertices[i + 1], vertices[i + 2]);
	}

	return 0;
}

//TODO: Take in file name instead of hardcoding it in function...
int ObjLoader::Load(const char *filePath, ObjData &data) {
	return RecursiveLoad(filePath, data);
}
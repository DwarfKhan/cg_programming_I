#pragma once

#include "Init.h"
#include "ObjLoader.h"

void BeginRendering();

void RenderVertex(GLuint vertexBuffer, glm::mat4 model, GLuint programID /*shader program id*/);
void RenderCube(GLuint vertexBuffer, glm::mat4 model, GLuint programID);
void RenderQuad(GLuint vertexBuffer, glm::mat4 model, GLuint programID);
void RenderTriangle(GLuint vertexBuffer, glm::mat4 model, GLuint programID);
void RenderObj(ObjLoader::ObjData data, glm::mat4 model, GLuint programID);
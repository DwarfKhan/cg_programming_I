#pragma once

#include "Init.h"

void BeginRendering();

void RenderVertex(GLuint vertexBuffer, glm::mat4 model, GLuint programID /*shader program id*/);
void RenderQuad(GLuint vertexBuffer, glm::mat4 model, GLuint programID);
void RenderCube(GLuint vertexBuffer, glm::mat4 model, GLuint programID);
void RenderTriangle(GLuint vertexBuffer, glm::mat4 model, GLuint programID);
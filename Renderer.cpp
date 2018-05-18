#include "Renderer.h"

namespace {
	double lastTime = glfwGetTime();
	float deltaTime = lastTime;

	float angle = 0.0f;

	auto objPos = glm::vec3(0, 0, 0);

	glm::mat4 TransformObject() {
		//Keyboard input handled here...
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			objPos.x += (deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			objPos.x -= (deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_UP)) {
			objPos.y += (deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			objPos.y -= (deltaTime);
		}

		if (glfwGetKey(window, GLFW_KEY_Q)) {
			angle += deltaTime * 60.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_E)) {
			angle -= deltaTime * 60.0f;
		}

		//Matrix math here...
		glm::mat4 model;								//Starts out as identity matrix...
		

		model = glm::rotate(model, angle, vec3(1, 1, 0));

		//model = glm::translate(model, objPos);			//Moves quad...

		return model;
	}
}

void BeginRendering()
{
	GLuint vertexArrayID = 0;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	//Create and compile glsl program from shaders...
	GLuint programID = LoadShaders("BasicVertexShader.vertexshader", "BasicFragmentShader.fragmentshader");

	GLuint triangleID = LoadTriangle();
	//GLuint quadID = LoadQuad();
	GLuint cubeID = LoadCube();

	ObjLoader::ObjData data;
	ObjLoader::Load("cube.obj", data);

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//RenderTriangle(triangleID);
		//RenderQuad(quadID, TransformQuad(), programID);
		RenderCube(cubeID, TransformObject(), programID);

		//Update();
		//Render();
		glfwSwapBuffers(window);
		glfwPollEvents();

		//Set delta time...
		deltaTime = glfwGetTime() - lastTime;

		//Set last time...
		lastTime = glfwGetTime();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}

void RenderVertex(GLuint vertexBuffer, glm::mat4 model, GLuint programID /*shader program id*/) {
	glUseProgram(programID);

	GLuint uniformModel = glGetUniformLocation(programID, "model");
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glVertexAttribPointer(
		0,			//attribute layout
		3,			//Elements in array
		GL_FLOAT,	//Each element is of type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array buffer offset...
	);
}

void RenderCube(GLuint vertexBuffer, glm::mat4 model, GLuint programID) {
	RenderVertex(vertexBuffer, model, programID);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);
}

void RenderQuad(GLuint vertexBuffer, glm::mat4 model, GLuint programID) {
	RenderVertex(vertexBuffer, model, programID);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
}

void RenderTriangle(GLuint vertexBuffer, glm::mat4 model, GLuint programID) {
	RenderVertex(vertexBuffer, model, programID);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}
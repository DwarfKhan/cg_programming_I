#include "GameManager.h"
#include "Matrix.h"
//GLFWwindow* window = NULL;



int main(){
	if(InitWindowFailed() | InitGlewFailed()){
		return EXIT_WITH_ERROR;
	}

	Matrix matrix;

	BeginRendering();


	return EXIT_WITH_SUCCESS;
}
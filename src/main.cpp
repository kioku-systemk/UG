//
//  UG entry point
//

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "TestNKGUI.h"

void init()
{

}


void reshape(GLFWwindow* win, int width, int height)
{
	GLfloat h = (GLfloat)height / (GLfloat)width;
	GLfloat xmax, znear, zfar;

	znear = 5.0f;
	zfar = 1000.0f;
	xmax = znear * 0.5f;

	glViewport(0, 0, (GLint)width, (GLint)height);
}

void draw()
{
	glClearColor(0.1, 0.2, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}


static void error_callback(int e, const char *d)
{
	printf("Error %d: %s\n", e, d);
}

int main()
{
	GLFWwindow* window;
	int width, height;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	//glfwWindowHint(GLFW_DEPTH_BITS, 16);

	window = glfwCreateWindow(1280, 720, "UG", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		fprintf(stdout, "GLEW OK : Glew Ver. %s\n", glewGetString(GLEW_VERSION));
	}
	else {
		fprintf(stderr, "Failed to initialize GLEW = %s\n", glewGetErrorString(err));
	}

	// Set callback functions
	glfwSetFramebufferSizeCallback(window, reshape);
	//glfwSetKeyCallback(window, key);

	glfwSwapInterval(1);

	glfwGetFramebufferSize(window, &width, &height);
	reshape(window, width, height);

	// Parse command-line options
	init();

	TestNKGUI gui(window);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// Main Draw
		draw();

		gui.Draw();
		
		// Swap buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW
	glfwTerminate();

	return 0;
}


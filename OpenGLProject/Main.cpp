#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

const unsigned int width = 1200;
const unsigned int height = 800;

// Coordinates of a triangle

/*Vertices coordinates
GLfloat vertices[] = {
	//				COORDINATES							COLORS
	-0.5f,  -0.5f * float(sqrt(3)) / 3,		0.0f, 0.8f, 0.3f, 0.02f,	// Lower left corner
	 0.5f,  -0.5f * float(sqrt(3)) / 3,		0.0f, 0.8f, 0.3f, 0.02f,	// Lower right corner
	 0.0f,   0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.32f,	// Upper center corner
	-0.25f,  0.5f * float(sqrt(3)) / 6,		0.0f, 0.9f, 0.45f, 0.17f,	// Inner left
	 0.25f,  0.5f * float(sqrt(3)) / 6,		0.0f, 0.9f, 0.45f, 0.17f,	// Inner right
	 0.0f,  -0.5f * float(sqrt(3)) / 3,		0.0f, 0.8f, 0.3f, 0.02f		// Inner down
};*/


/* Coordinates of a square
// Vertices coordinates
GLfloat vertices[] = {
	//				COORDINATES							COLORS
	-0.5f,  -0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// Lower left corner
	-0.5f,	 0.5f,	0.0f,	0.0f, 1.0f, 0.02f,	0.0f, 1.0f, // Upper left corner
	 0.5f,   0.5f,	0.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f,	0.0f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f, // Lower right corner
};*/

/*GLfloat vertices[] = {
	//	COORDINATES				COLORS				TexCoord
	-0.5f,  0.0f,	0.5f,	0.83f, 0.7f, 0.44f,	0.0f, 0.0f,	// Lower left corner
	-0.5f,	0.0f,	-0.5f,	0.83f, 0.7f, 0.44f,	5.0f, 0.0f, // Upper left corner
	 0.5f,  0.0f,	-0.5f,	0.83f, 0.7f, 0.44f,	0.0f, 0.0f, // Upper right corner
	 0.5f,  0.0f,	0.5f,	0.83f, 0.7f, 0.44f,	5.0f, 0.0f, // Lower right corner
	 0.0f,  0.8f,	0.0f,	0.92, 0.86f, 0.76f, 2.5f, 5.0f
};*/

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};


/* Indices for triangle
GLuint indices[] = {
	0, 3, 5, // Lower left triangle
	3, 2, 4, //Lower right triangle
	5, 4, 1 // Upper triangle
};*/

/* Indices for square
GLuint indices[] = {
	0, 2, 1,	// Upper triangle
	0, 3, 2		// Lower triangle
};*/

/*GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};*/

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] = {
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f,
};

GLuint lightIndices[] = {
	0,1,2,
	0,2,3,
	0,4,7,
	0,7,3,
	3,7,6,
	3,6,2,
	2,6,5,
	2,5,1,
	1,5,4,
	1,4,0,
	4,5,6,
	4,6,7
};

int main() {
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// so that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	

	// Create a new GLFWwindow object of 800 by 800 pixels, naming it "OpenGLProject"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLProject", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the whole window is used
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));


	// If not Image than 6 instead of 8
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightColor.x, lightColor.y, lightColor.z);

	// Gets ID of uniform called "scale"
	// GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture

	Texture popCat("pyramid_texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);


	// float rotation = 0.0f;
	double prevTime = glfwGetTime(); //

	glEnable(GL_DEPTH_TEST);


	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		// Specifiy the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60) {
			rotation += 0.05f;
			prevTime = crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));*/

		double crntTime = glfwGetTime();
		double deltaTime = crntTime - prevTime;
		prevTime = crntTime;

		camera.Inputs(window, deltaTime);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");


		// glUniform1f(uniID, 0.5f);


		popCat.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		// Draw primitives, number of indices, datatype of indices, index of indices
		// If the triangle should be drawn use 9 instead of 6
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();

	// Delete Window before exiting
	glfwDestroyWindow(window);
	// Terminate whole GLFW process
	glfwTerminate();
	return 0;
}
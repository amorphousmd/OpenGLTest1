#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() 
{
	glfwInit();

	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	//Give hints of version, we only care about the modern functions


	//Create a window 
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGLTest1", NULL, NULL); 
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Set window = current context --- Context = object that holds the whole of OpenGL (vastly simplfied)
	glfwMakeContextCurrent(window); 

	//Tell GLAD to load the needed configuration for OpenGL
	gladLoadGL(); 
	
	//Viewport = area we want OpenGL to render --- x,y coor 0 0 bottom left 800 800 top right
	glViewport(0, 0, 800, 800); 

	// State what kind of shader you want, there are 3 types of shaders in common use 
	// pixel, vertex and geometry, here we use the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); 
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Change the source code in VertexShader with VertexShaderSource
	glCompileShader(vertexShader); //Compile the shader right now or the machine can't understand

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); //Delete the shaders as they are already in the program

	GLfloat vertices[] = //Every 3 floats = 1 coordinate --- 3 lines = left corner, right corner, top corner
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // 3 coordinates of equilateral triangle
	};

	// If you run the program now nothing is going to happen because we haven't told openGL to do anythign with the shader

	GLuint VAO, VBO; // = Vertex array object, Vertex buffer object

	//Create buffer object
	glGenVertexArrays(1, &VAO); // VAO must be created before VBO
	glGenBuffers(1, &VBO); // 1 3d object, point it to the reference VBO

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind VBO to targer GL_ARRAY_BUFFEr

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // enable the vertex

	// Unbind VAO and VBO 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//Specify color of background
	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//Tell OpenGL to execute the command we've prepared for --- after this step we have the back buffer with 
	// the color we want and the front buffer with the default color
	//glClear(GL_COLOR_BUFFER_BIT); 
	//glfwSwapBuffers(window);



	while(!glfwWindowShouldClose(window)) //Keep windows on until press close or another function tells the Windows to close	
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window); 
	glfwTerminate(); 
	return 0;
}
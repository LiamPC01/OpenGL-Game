#include "Header.h"


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
"}\n\0";

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.75f, 0.2f, 1.0f);"
"}\n\0";

int main()
{
	// glfw Initialize and configure
	glfwInit();
	// Set OpenGL version to 3 if user does not have correct version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfw create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLGame", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// GLAD load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Check if compilation wass successful
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success) 
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "VERTEX SHADER COMPILATION FAILED\n" << infoLog << std::endl;
	}

	// Fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check if compilation wass successful
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "FRAGMENT SHADER COMPILATION FAILED\n" << infoLog << std::endl;
	}

	//Fragment shader 2
	unsigned int fragmentShader2;
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	// Shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for shader linking error
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "SHADER LINKING FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Shader program 2
	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	// check for shader linking error

	// VBO and VAO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind VAO first then bind and set vertex buffers then config vertex attributes
	glBindVertexArray(VAO);
	// copy our vertices array a buffer for opengl to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	// set the vertex attributes to pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// VBO and VAO 2
	unsigned int VBO2, VAO2;
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	// bind VAO first then bind and set vertex buffers then config vertex attributes
	glBindVertexArray(VAO2);
	// copy our vertices array a buffer for opengl to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	// set the vertex attributes to pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	
	/*
	// EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//draw triangle 2
		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// delete resources after use
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}
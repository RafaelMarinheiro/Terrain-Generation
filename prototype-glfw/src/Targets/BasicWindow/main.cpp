#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Core/Core.hpp>
#include <Core/Math.hpp>
#include <Core/FileSystem.hpp>
#include <Core/Graphics.hpp>

using namespace amaze;

int main()
{
	// -------------------------------- INIT ------------------------------- //


	core::SystemManager::instance().initSystem("Window",
											new core::WindowSystem());
	
	core::Window * window = new core::Window("HUE", 800, 600);

	// ----------------------------- RESOURCES ----------------------------- //

	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	float vertices[] = {
		 0.0f,  0.5f, // Vertex 1 (X, Y)
		 0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	gl::Shader shader;

	shader.loadFromFile(gl::Shader::VERTEX_SHADER, core::Resources::pathForResource("Shaders/Basic/basic.vsh"));
	shader.loadFromFile(gl::Shader::FRAGMENT_SHADER, core::Resources::pathForResource("Shaders/Basic/basic.fsh"));
	shader.createAndLinkProgram();
	shader.addAttribute("position");
	shader.use();

	glEnableVertexAttribArray(shader["position"]);
	glVertexAttribPointer(shader["position"], 2, GL_FLOAT, GL_FALSE, 0, 0);

	// ---------------------------- RENDERING ------------------------------ //

	while(!window->shouldClose())
	{
		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Draw a triangle from the 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap buffers and poll window events
		window->swapBuffers();
		glfwPollEvents();
	}

	// ---------------------------- CLEARING ------------------------------ //

	// Delete allocated resources
	shader.unUse();
	shader.deleteProgram();
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	// ---------------------------- TERMINATE ----------------------------- //

	core::SystemManager::instance().destroySystem("Window");

	return 0;
}

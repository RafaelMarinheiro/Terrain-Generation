#include <stdio.h>

#include <Core/Core.hpp>
#include <Core/Math.hpp>
#include <Core/FileSystem.hpp>
#include <Core/Graphics.hpp>
#include <Core/Input/InputController.hpp>
#include <Core/Input/MouseCameraController.hpp>
#include <Core/Input/SunController.hpp>

#include <Core/Render/BasicRenderer.hpp>

#include <Atmosphere/AtmosphereNode.hpp>

#include <Terrain/builders/all.hpp>
#include <Terrain/HeightMapNode.hpp>

#include <Ocean/OceanNode.hpp>

#include <TreeGeom/builders/FractalTreeBuilder.hpp>
#include <TreeGeom/TreeNode.hpp>

#include <vector>
#include <string>
#include <iostream>

using namespace amaze;

void printMatrix(const glm::mat4 & mat){
	for(int i = 0; i < 4; i++){
		std::cerr << "|";
		for(int j = 0; j < 4; j++){
			std::cerr << " " << mat[i][j];
		}
		std::cerr << " |" << std::endl;
	}
	std::cerr << std::endl;
}

void printVector(const glm::vec4 & mat){
	// for(int i = 0; i < 4; i++){
		std::cerr << "(";
		for(int j = 0; j < 4; j++){
			std::cerr << " " << mat[j];
		}
		std::cerr << " )" << std::endl;
	// } 
}

void printVector(const glm::vec3 & mat){
	// for(int i = 0; i < 4; i++){
		std::cerr << "(";
		for(int j = 0; j < 3; j++){
			std::cerr << " " << mat[j];
		}
		std::cerr << " )" << std::endl;
	// } 
}

bool gorender = true;

std::vector<input::InputController *> input_controllers;

void handleKeypress(GLFWwindow * window, int key, int code, int action, int mods){
	if(action == GLFW_PRESS){
		for(int i = 0; i < input_controllers.size(); i++){
			input_controllers[i]->handleKeyPress(key);
		}
		// gorender = false;
	} else if(action == GLFW_RELEASE){
		for(int i = 0; i < input_controllers.size(); i++){
			input_controllers[i]->handleKeyRelease(key);
		}
		// gorender = true;
	}
}

float lastX = 0;
float lastY = 0;

void handleMouseMove(GLFWwindow * window, double mouseX, double mouseY){
	for(int i = 0; i < input_controllers.size(); i++){
		input_controllers[i]->handleMouseMove((mouseX-lastX)/800.0, (mouseY-lastY)/800.0);
	}
	lastX = mouseX;
	lastY = mouseY;
}

int main()
{
	// -------------------------------- INIT ------------------------------- //


	core::SystemManager::instance().initSystem("Window",
											new core::WindowSystem());
	
	core::Window * window = new core::Window("HUE", 800, 600);

	render::BasicRenderer renderer;
	renderer.init();
	render::Viewer viewer;

	MouseCameraController cameraController;
	cameraController.camera = &(viewer.camera);

	SunController sunController;

	input_controllers.push_back(&cameraController);
	input_controllers.push_back(&sunController);

	glm::mat4 identity;

	// ----------------------------- GEOMETRY ------------------------------ //
	HeightMapBuilder * builder = new DiamondSquareHeightMapBuilder(0.2);
	HeightMap * heightMap = builder->buildHeightMap(100.0, 100.0, 513, 513);
	HeightMapNode heightMapNode;

	heightMapNode.init(heightMap, 10.0);

	OceanNode oceanNode;
	oceanNode.init(3.0);

	AtmosphereNode atmosphereNode;
	atmosphereNode.init();

	// renderer.geometryNodes.push_back(&heightMapNode);

	TreeBuilder * tbuilder = new FractalTreeBuilder();
	Tree * tree = tbuilder->generateTree(6, 20, 
			16.7, -33.3, 0.85, 0.85, 2, 0, 0);

	TreeNode treeNode;
	treeNode.init(tree);

	renderer.geometryNodes.push_back(&treeNode);

	renderer.lightNodes.push_back(&atmosphereNode);
	// renderer.lightNodes.push_back(&oceanNode);
	// renderer.postProcessingNodes.push_back(&oceanNode);
	// ----------------------------- RESOURCES ----------------------------- //


	// ----------------------------- SHADER ----------------------------- //


	// ---------------------------- RENDERING ------------------------------ //


	// glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	// glDisable(GL_CULL_FACE);
	
	// Specify the function which should execute when a key is pressed or released
	glfwSetKeyCallback(window->getWindow(), handleKeypress);
	// Specify the function which should execute when the mouse is moved
	glfwSetCursorPosCallback(window->getWindow(), handleMouseMove);

	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	double previous = glfwGetTime();
	double lag = 0.0;
	double fps = 1.0/60;
	while(!window->shouldClose())
	{
				// Clear the screen to black

		double current = glfwGetTime();
		double elapsed = current-previous;
		lag += elapsed;
		previous = current;
		glfwPollEvents();

		printf("FPS: %lf\n", 1/elapsed);
		while(lag >= fps){
			for(int i = 0; i < input_controllers.size(); i++){
				input_controllers[i]->update();
			}
			lag -= fps;
		}

		// viewer.camera.lookAt(glm::vec3(0.0, 0.0, 0.0));

		glm::vec3 sunDirection = sunController.getSunDirection();

		atmosphereNode.sunPosition = sunDirection;

		renderer.render(viewer);
		window->swapBuffers();
	}

	// ---------------------------- CLEARING ------------------------------ //


	// ---------------------------- TERMINATE ----------------------------- //

	core::SystemManager::instance().destroySystem("Window");

	return 0;
}

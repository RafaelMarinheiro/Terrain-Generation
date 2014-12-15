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

	heightMapNode.init(heightMap, 26.0);

	OceanNode oceanNode;
	oceanNode.init(10);

	AtmosphereNode atmosphereNode;
	atmosphereNode.init();


	renderer.geometryNodes.push_back(&heightMapNode);

	renderer.skyNodes.push_back(&atmosphereNode);

	renderer.lightNodes.push_back(&atmosphereNode);
	renderer.lightNodes.push_back(&oceanNode);


	TreeBuilder * tbuilder = new FractalTreeBuilder();
	Tree * tree1 = tbuilder->generateTree(7, 0.3, 
			.27, -0.59, 0.9, 0.8, 0.03, 0, 0);

	TreeNode treeNode1;
	treeNode1.init(tree1, &heightMapNode);


	Tree * tree2 = tbuilder->generateTree(7, 0.3, 
			.0, -0.39, 0.9, 0.8, 0.03, 0, 0);

	TreeNode treeNode2;
	treeNode2.init(tree2, &heightMapNode);


	Tree * tree3 = tbuilder->generateTree(7, 0.3, 
			.2, -0.3, 0.9, 0.8, 0.03, 0, 0);

	TreeNode treeNode3;
	treeNode3.init(tree3, &heightMapNode);

	for(int i = 5; i < 100; i+= 5){
		for(int j = 5; j < 100; j+= 5){
			float height = heightMapNode.heightMap->getHeightAt(i*5,j*5);
			printf("height %f \n", height);
			if(height < 0.6 && height > 0.4 ){
				render::TransformationNode * traslateNode = new render::TransformationNode();
				traslateNode->transformation = glm::translate(glm::mat4(1.0f), glm::vec3(i+0.0f, 0.0f, j+0.0f));
				traslateNode->child = &treeNode3;
				renderer.geometryNodes.push_back(traslateNode);
			}
		}
	}

	// renderer.geometryNodes.push_back(&treeNode);

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
	
	viewer.time = 0.0;
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

		//printf("FPS: %lf\n", 1/elapsed);
		while(lag >= fps){
			for(int i = 0; i < input_controllers.size(); i++){
				input_controllers[i]->update();
			}
			lag -= fps;
			viewer.time += fps;
		}

		glm::vec3 sunDirection = sunController.getSunDirection();

		viewer.sunPosition = sunDirection;

		renderer.render(viewer);
		window->swapBuffers();
	}

	// ---------------------------- CLEARING ------------------------------ //


	// ---------------------------- TERMINATE ----------------------------- //

	core::SystemManager::instance().destroySystem("Window");

	return 0;
}

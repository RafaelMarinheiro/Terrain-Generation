/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-20 05:04:26
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-23 15:15:42
*/

#include <Terrain/HeightMapNode.hpp>
#include <Core/GL/OpenGL.hpp>
#include <Core/FileSystem.hpp>

#include <iostream>

namespace amaze{
	void HeightMapNode::init(HeightMap * _heightMap, float _height){
		this->heightMap = _heightMap;
		this->height = _height;

		std::vector<float> vertices;
		std::vector<int> indices;

		{
			int nx = heightMap->getResolutionX();
			int ny = heightMap->getResolutionY();

			float dx = heightMap->getSizeX()/(nx-1);
			float dy = heightMap->getSizeY()/(ny-1);

			for(int i = 0; i < nx; i++){
				for(int j = 0; j < ny; j++){
					vertices.push_back(i*dx);
					vertices.push_back(j*dy);
					if(i < nx - 1 && j < ny - 1){
						indices.push_back(j + i*nx);
						indices.push_back(j + 1 + i*nx);
						indices.push_back(j + 1 + (i+1)*nx);

						indices.push_back(j + i*nx);
						indices.push_back(j + 1 + (i+1)*nx);
						indices.push_back(j + (i+1)*nx);
					}
				}
			}

			nindices = indices.size();
		}

		//Init buffers and textures
		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);

			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(int), &indices[0], GL_STATIC_DRAW);

			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, heightMap->getResolutionX(), heightMap->getResolutionY(), 0, GL_RED, GL_FLOAT, heightMap->getHeightData());
		}


		//Init shader
		{	
			std::vector<std::string> files;
			files.push_back(core::Resources::pathForResource("Shaders/Common.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Terrain/Helper.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Terrain/Material.glsl"));

			materialShader.loadFromFiles(files);

			materialShader.addUniform("modelMatrix");
			materialShader.addUniform("viewMatrix");
			materialShader.addUniform("projectionMatrix");
			
			materialShader.addUniform("terrain_heightMap");
			materialShader.addUniform("terrain_size");
			materialShader.addUniform("terrain_height");

			materialShader.addAttribute("position");

			glBindVertexArray(vao);
			materialShader.use();
			glEnableVertexAttribArray(materialShader["position"]);
			glVertexAttribPointer(materialShader["position"], 2, GL_FLOAT, GL_FALSE, 0, 0);

			glUniform1f(materialShader("terrain_size"), heightMap->getSizeX());
			glUniform1f(materialShader("terrain_height"), height);

			materialShader.unUse();
			glBindVertexArray(0);
		}
	}

	void HeightMapNode::destroy(){
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
		glDeleteVertexArrays(1, &vao);
		glDeleteTextures(1, &tex);
		materialShader = gl::Shader();
		heightMap = NULL;
	}

	void HeightMapNode::render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix){
		if(renderPass == render::DEFERRED_MATERIAL_PASS){
			glBindVertexArray(vao);

			materialShader.use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex);
			glUniform1i(materialShader("terrain_heightMap"), 0);
			glUniformMatrix4fv(materialShader("modelMatrix"), 1, GL_FALSE, glm::value_ptr(worldMatrix));
			glUniformMatrix4fv(materialShader("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.viewMatrix()));
			glUniformMatrix4fv(materialShader("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.projectionMatrix()));
			glDrawElements(GL_TRIANGLES, nindices, GL_UNSIGNED_INT, 0);

			materialShader.unUse();

			glBindVertexArray(0);
		}
	}
}
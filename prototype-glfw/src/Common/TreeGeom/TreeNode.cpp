

#include <stdio.h>

#include <TreeGeom/TreeNode.hpp>
#include <Core/GL/OpenGL.hpp>
#include <Core/FileSystem.hpp>

#include <math.h>
#include <iostream>
# define PI           3.1415926535897932384
namespace amaze{


	void TreeNode::init(Tree * tree){
		this-> tree = tree;

		std::vector<float> vertices;
		std::vector<float> normals;
		std::vector<int> indices;

		glm::vec3 * branchNodes = tree->branchNodes;
		float radius = tree->radius;
		float twigging = 0.7*(1.0-pow(2,-1*(float)tree->MAXDEPTH));

		{
			//make trunk
			glm::vec3 curr = branchNodes[0];
			glm::vec3 next = branchNodes[1];
			glm::vec3 axis1 = glm::normalize(next - curr);
			glm::vec3 axis2 = glm::normalize(glm::vec3(0,float(-1)*axis1.z,axis1.y));
			glm::vec3 axis3 = glm::cross(axis1,axis2);
			//generate vertices
			int subdivisions = 20;
			for(int i=0;i<=subdivisions;i++){
				float angle = 2*PI*((float)i/(float) subdivisions);
				//bottom
				glm::vec3 norm = float(cos(angle))*axis2 + float(sin(angle))*axis3;
				glm::vec3 point1 = (float(cos(angle))*axis2 + float(sin(angle))*axis3)*radius + curr;
				vertices.push_back(point1.x);
				vertices.push_back(point1.y);
				vertices.push_back(point1.z);
				vertices.push_back(norm.x);
				vertices.push_back(norm.y);
				vertices.push_back(norm.z);

				//top
				glm::vec3 point2 = (float(cos(angle))*axis2 + float(sin(angle))*axis3)*radius + next;
				vertices.push_back(point2.x);
				vertices.push_back(point2.y);
				vertices.push_back(point2.z);
				vertices.push_back(norm.x);
				vertices.push_back(norm.y);
				vertices.push_back(norm.z);
			}
			//generate triangles
			// 0 2 1, 1 2 3, 2 4 3, 3 4 5
			for(int i= 0; i< subdivisions;i++){
				int k = 2*i;
				indices.push_back(k);
				indices.push_back(k+2);
				indices.push_back(k+1);
				
				indices.push_back(k+1);
				indices.push_back(k+2);
				indices.push_back(k+3);
			}



			//rest of the branches
			for(int branch=1;branch < tree->numNodes/2;branch++){

				int leftI = 2*branch;
				int rightI = leftI+1;


				curr = branchNodes[branch];

				//for the left
				next = branchNodes[leftI];
				axis1 = glm::normalize(next - curr);
				axis2 = glm::normalize(glm::vec3(0,float(-1)*axis1.z,axis1.y));
				axis3 = glm::cross(axis1,axis2);
				int start = vertices.size()/6;
				for(int i=0;i<=subdivisions;i++){
					float angle = 2*PI*((float)i/(float) subdivisions);
					//bottom
					glm::vec3 norm = float(cos(angle))*axis2 + float(sin(angle))*axis3;

					glm::vec3 point1 = (float(cos(angle))*axis2 + float(sin(angle))*axis3 )
										*radius*(float)pow(twigging,floor(log2(branch)))+ curr;
					vertices.push_back(point1.x);
					vertices.push_back(point1.y);
					vertices.push_back(point1.z);
					vertices.push_back(norm.x);
					vertices.push_back(norm.y);
					vertices.push_back(norm.z);
					//top
					glm::vec3 point2 = (float(cos(angle))*axis2 + float(sin(angle))*axis3)*radius*(float)pow(twigging,floor(log2(branch)) + 1) + next;

					vertices.push_back(point2.x);
					vertices.push_back(point2.y);
					vertices.push_back(point2.z);
					vertices.push_back(norm.x);
					vertices.push_back(norm.y);
					vertices.push_back(norm.z);
				}

				for(int i= 0; i< subdivisions;i++){
					int k = 2*i + start;
					indices.push_back(k);
					indices.push_back(k+2);
					indices.push_back(k+1);
					
					indices.push_back(k+1);
					indices.push_back(k+2);
					indices.push_back(k+3);
				}



				//for the right
				next = branchNodes[rightI];

				axis1 = glm::normalize(next - curr);
				axis2 = glm::vec3(0,float(-1)*axis1.z,axis1.y);
				axis3 = glm::cross(axis1,axis2);
				start = vertices.size()/6;
				for(int i=0;i<=subdivisions;i++){
					float angle = 2*PI*((float)i/(float) subdivisions);
					//bottom
					glm::vec3 norm = float(cos(angle))*axis2 + float(sin(angle))*axis3;
					glm::vec3 point1 = (float(cos(angle))*axis2 + float(sin(angle))*axis3 )
										*radius*(float)pow(twigging,floor(log2(branch)))+ curr;
					vertices.push_back(point1.x);
					vertices.push_back(point1.y);
					vertices.push_back(point1.z);
					vertices.push_back(norm.x);
					vertices.push_back(norm.y);
					vertices.push_back(norm.z);
					//top
					glm::vec3 point2 = (float(cos(angle))*axis2 + float(sin(angle))*axis3)*radius*(float)pow(twigging,floor(log2(branch)) + 1) + next;
					vertices.push_back(point2.x);
					vertices.push_back(point2.y);
					vertices.push_back(point2.z);
					vertices.push_back(norm.x);
					vertices.push_back(norm.y);
					vertices.push_back(norm.z);
				}

				for(int i= 0; i< subdivisions;i++){
					int k = 2*i + start;
					indices.push_back(k);
					indices.push_back(k+2);
					indices.push_back(k+1);
					
					indices.push_back(k+1);
					indices.push_back(k+2);
					indices.push_back(k+3);
				}
				nindices = indices.size();
			}


		}

		{
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);

			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(int), &indices[0], GL_STATIC_DRAW);

			// glActiveTexture(GL_TEXTURE0);
			// glGenTextures(1, &tex);
			// glBindTexture(GL_TEXTURE_2D, tex);

			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, heightMap->getResolutionX(), heightMap->getResolutionY(), 0, GL_RED, GL_FLOAT, heightMap->getHeightData());
		}

		{	
			std::vector<std::string> files;
			files.push_back(core::Resources::pathForResource("Shaders/Common.glsl"));
			files.push_back(core::Resources::pathForResource("Shaders/Tree/Tree.glsl"));
			// files.push_back(core::Resources::pathForResource("Shaders/Terrain/Material.glsl"));

			materialShader.loadFromFiles(files);

			materialShader.addUniform("modelMatrix");
			materialShader.addUniform("viewMatrix");
			materialShader.addUniform("projectionMatrix");
			

			materialShader.addAttribute("position");
			materialShader.addAttribute("normal");
			glBindVertexArray(vao);
			materialShader.use();
			glEnableVertexAttribArray(materialShader["position"]);
			glVertexAttribPointer(materialShader["position"], 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
			glVertexAttribPointer(materialShader["normal"], 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *) (3*sizeof(float)));

			materialShader.unUse();
			glBindVertexArray(0);
		}
	}

	void TreeNode::render(const render::Viewer & viewer, render::RenderPass renderPass, const glm::mat4x4 & worldMatrix){
		if(renderPass == render::DEFERRED_MATERIAL_PASS){
			glBindVertexArray(vao);

			materialShader.use();
			glUniformMatrix4fv(materialShader("modelMatrix"), 1, GL_FALSE, glm::value_ptr(worldMatrix));
			glUniformMatrix4fv(materialShader("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.viewMatrix()));
			glUniformMatrix4fv(materialShader("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(viewer.camera.projectionMatrix()));
			glDrawElements(GL_TRIANGLES, nindices, GL_UNSIGNED_INT, 0);

			materialShader.unUse();

			glBindVertexArray(0);
		}
	}

	void TreeNode::destroy(){
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
		glDeleteVertexArrays(1, &vao);
		glDeleteTextures(1, &tex);
		materialShader = gl::Shader();
		tree = NULL;
	}
}
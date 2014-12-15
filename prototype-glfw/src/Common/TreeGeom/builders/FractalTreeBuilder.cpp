



#include <TreeGeom/builders/FractalTreeBuilder.hpp>
#include <math.h>

namespace amaze{

	void FractalTreeBuilder::recursiveBranch(Tree * tree, int index, int depth){
		if(depth+1 > tree->MAXDEPTH){
			return;
		}
		int leftI = index*2;
		int rightI = left + 1;

		glm::vec3 curr = tree->branchNodes[index];
		glm::vec3 parent = tree->branchNodes[index/2];
		glm::vec3 axis = curr - parent;

		float u = axis.x;
		float w = axis.y;
		float v = axis.z;
		float L = glm::length(axis);

		float denom = math::sqrt(u*u + v*v);

		float cosTheta = math::cos(tree->theta);
		float sinTheta = math::sin(tree->theta);

		float cosPhi = math::cos(tree->phi);
		float sinPhi = math::sin(tree->phi);

		float x1 = curr.x + tree->R1*(u*cosTheta - (L*v*sinTheta/denom));
		float z1 = curr.z + tree->R1*(v*cosTheta - (L*u*sinTheta/denom));
		float y1 = curr.y + tree->R1*w*cosTheta;

		float x2 = curr.x + tree->R2*(u*cosPhi - (L*v*sinPhi/denom));
		float z2 = curr.z + tree->R2*(v*cosPhi - (L*u*sinPhi/denom));
		float y1 = curr.y + tree->R2*w*cosPhi;


		glm::vec3 left = glm::vec3(x1,y1,z1);
		glm::vec3 right = glm::vec3(x2,y2,z2);

		tree->branchNodes[leftI] = left;
		recursiveBranch(tree,leftI,depth+1);
		tree->branchNodes[rightI] = right;
		recursiveBranch(tree,rightI,depth+1);


	}

}




#include <TreeGeom/TreeBuilder.hpp>
#include <math.h>

namespace amaze{
	TreeBuilder::TreeBuilder(){}
	TreeBuilder::~TreeBuilder(){}


	Tree * TreeBuilder::generateTree(unsigned int maxDepth, float _trunkLength, 
			float _theta, float _phi, float r1, float r2, float _radius, float x, float y){
		Tree * tree = new Tree(maxDepth, _trunkLength, _theta, _phi, _r1, _r2, _radius);
		makeBranches(tree,x,y);
		return tree;
	}


	void TreeBuilder::makeBranches(Tree * tree, float x, float y){
		tree->branchNodes[0] = glm::vec3(x,0,y);
		tree->branchNodes[1] = glm::vec3(0,tree->trunkLength,0) + tree->branchNodes[0];

		glm::vec3 left = glm::vec3(cos(tree->theta),sin(tree->theta),0)*tree->R1 + tree->branchNodes[1];
		glm::vec3 right = glm::vec3(cos(tree->phi),sin(tree->phi),0)*tree->R2 + tree->branchNodes[1];

		if(tree->MAXDEPTH <= 1){
			return;
		}
		tree->branchNodes[2] = left;
		tree->branchNodes[3] = right;

		recursiveBranch(tree,2,2);
		recursiveBranch(tree,3,2);

	}
}
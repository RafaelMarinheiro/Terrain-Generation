



#include <TreeGeom/Tree.hpp>
#include <math.h>
#include <stdio.h>

namespace amaze{

	Tree::Tree(unsigned int maxDepth, float _trunkLength, float _theta, float _phi, float r1, float r2, float _radius){
		MAXDEPTH = maxDepth;
		trunkLength = _trunkLength;
		theta = _theta;
		phi = _phi;
		R1 = r1;
		R2 = r2;
		radius = _radius;
		numNodes = (int) (pow(2.0,(float)MAXDEPTH));

		branchNodes = new glm::vec3[numNodes];
		

	}
	Tree::~Tree(){
		delete[] branchNodes;
	}
}
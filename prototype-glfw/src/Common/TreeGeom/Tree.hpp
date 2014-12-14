

#include <Core/Math/Vector.hpp>


#ifndef TREE_HPP
#define TREE_HPP

namespace amaze{

	class Tree{
		friend class TreeBuilder;

	public: 
		Tree(unsigned int maxDepth, float _trunkLength, float _theta, float _phi, float r1, float r2, float _radius);
		~Tree();

		glm::vec3 * getTreeData();

	private:
		unsigned int MAXDEPTH;
		float trunkLength, theta, phi, R1, R2, radius;
		glm::vec3 * branchNodes;
	};
}

#endif
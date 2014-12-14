



#ifndef TREE_BUILDER_HPP
#define TREE_BUILDER_HPP

#include <TreeGeom/Tree.hpp>


namespace amaze{

	class TreeBuilder{
	public:
		TreeBuilder();
		~TreeBuilder();

		Tree * generateTree(unsigned int maxDepth, float _trunkLength, 
			float _theta, float _phi, float r1, float r2, float _radius, float x, float y);
	protected:
		virtual void recursiveBranch(Tree * tree, int index, int depth) = 0;
	
		void makeBranches(Tree * tree, float x, float y);
	};
}

#endif
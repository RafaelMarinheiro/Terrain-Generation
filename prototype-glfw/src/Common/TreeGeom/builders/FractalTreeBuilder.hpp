


#ifndef FRACTAL_TREE_BUILDER_HPP
#define FRACTAL_TREE_BUILDER_HPP

#include <TreeGeom/TreeBuilder.hpp>

namespace amaze{


	class FractalTreeBuilder : public TreeBuilder{
	public:
		FractalTreeBuilder(){}
	protected:
		virtual void recursiveBranch(Tree * tree, int index, int depth);

	};
}

#endif
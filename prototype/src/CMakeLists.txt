# /* 
# * @Author: Rafael Marinheiro
# * @Date:   2014-10-18 22:50:16
# * @Last Modified by:   Rafael Marinheiro
# * @Last Modified time: 2014-10-18 23:40:59
# */


include_directories("Common")

file(GLOB_RECURSE Maze_SRC
	"Common/Maze/*.hpp"
	"Common/Maze/*.cpp"
)

file(GLOB_RECURSE Terrain_SRC
	"Common/Terrain/*.hpp"
	"Common/Terrain/*.cpp"
)

if (BUILD_MAZE)
	add_subdirectory(MazeViewer)
	add_subdirectory(TerrainViewer)
endif()
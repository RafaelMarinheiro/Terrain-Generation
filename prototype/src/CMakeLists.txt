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

if (BUILD_MAZE)
	add_subdirectory(MazeViewer)
endif()
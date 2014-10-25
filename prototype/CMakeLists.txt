# /* 
# * @Author: Rafael Marinheiro
# * @Date:   2014-10-18 22:50:16
# * @Last Modified by:   Rafael Marinheiro
# * @Last Modified time: 2014-10-18 23:40:59
# */


cmake_minimum_required (VERSION 2.8.11)
project (MazePrototype)


# General Configuration: find all the required libraries.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#===================================================================
# compile options
#===================================================================

option(USE_DEBUG "Turn on the debug mode" OFF)
option(BUILD_MAZE "Build Project" ON)


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Recurse into the "src" subdirectory. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.

add_subdirectory(src)
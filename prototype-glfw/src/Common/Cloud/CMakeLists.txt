file(GLOB_RECURSE FILES_COMMON_CLOUD_SRC
		"${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(COMMON_CLOUD_SRC ${FILES_COMMON_CLOUD_SRC} PARENT_SCOPE)
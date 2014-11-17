# Look for OpenGL.
find_package(OpenGL REQUIRED)

# Look for GLFW.
find_package(GLFW REQUIRED)

# Look for GLEW.
find_package(GLEW REQUIRED)

add_executable(BasicWindow
				main.cpp
				${COMMON_CORE_SRC})

add_dependencies(BasicWindow Copy_Code_Resources)

target_include_directories(BasicWindow
							PRIVATE ${GLFW_INCLUDE_DIR}
							PRIVATE ${GLEW_INCLUDE_DIR})

target_link_libraries(BasicWindow
						${GLFW_LIBRARIES}
						${GLEW_LIBRARIES}
						${OPENGL_LIBRARY})


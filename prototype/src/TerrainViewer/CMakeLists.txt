# /* 
# * @Author: Rafael Marinheiro
# * @Date:   2014-10-18 23:25:26
# * @Last Modified by:   Rafael Marinheiro
# * @Last Modified time: 2014-10-18 23:40:17
# */

# Handle dependencies
# Depends on
# - QT4
# - QGLViewer
# - OpenGL

	FIND_PACKAGE(Qt4 COMPONENTS QtCore QtXml QtOpenGL QtGui REQUIRED)
	find_package(OpenGL REQUIRED)
	find_package(QGLViewer REQUIRED)

# QT specifics
	set(QT_USE_QTXML 1)
	set(QT_USE_QTOPENGL 1)
	set(CMAKE_AUTOMOC ON)


	include(${QT_USE_FILE})

# File sources
# PGBase_SRC is a list that contain
# every .h or .cpp file in the directory

	file(GLOB TerrainViewer_SRC
		"*.hpp"
		"*.cpp"
	)

# Create the target PGBaseViewer

	add_executable(TerrainViewer
					# "main.cpp"
					${TerrainViewer_SRC}
					${Terrain_SRC})

# Specify the include directories

	target_include_directories(TerrainViewer
	    PUBLIC ${QGLViewer_INCLUDE_DIR})

# Specify the libraries to link
	target_link_libraries(TerrainViewer
		${QT_LIBRARIES}
		${OPENGL_LIBRARIES}
		${QGLViewer_LIBRARY}
		)
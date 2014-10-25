/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-18 23:25:26
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-18 23:40:17
*/

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#ifdef _WIN32
		#include <windows.h>
	#endif

	#include <GL/gl.h>
	#include <GL/glu.h>
#endif
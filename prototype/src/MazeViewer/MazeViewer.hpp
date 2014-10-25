/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-18 22:50:47
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 04:40:38
*/

#ifndef MAZE_VIEWER_H
#define MAZE_VIEWER_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QApplication>

#include <Maze/Maze.hpp>

namespace amaze{
	class MazeViewer : public QGLWidget{
	Q_OBJECT

	public:
		explicit MazeViewer(amaze::Maze * maze, QWidget *parent = 0);
	    ~MazeViewer();

	protected:
		//This method handles window resizing
		void resizeGL(int w, int h);

		//This method handles OpenGL initialization
		void initializeGL();

		//This method handle gl painting
		//It will be called after updateGL() is called
		void paintGL();
		void keyPressEvent(QKeyEvent *event);

	private:
		bool m_fullscreen;
		amaze::Maze * m_maze;
	};
}

#endif // MAZE_VIEWER_H
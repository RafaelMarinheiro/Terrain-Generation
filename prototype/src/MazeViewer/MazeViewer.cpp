/* 
* @Author: Rafael Marinheiro
* @Date:   2014-10-18 22:50:16
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-10-25 05:28:27
*/

#include "MazeViewer.hpp"

#include <pg_gl.h>

namespace amaze{
	MazeViewer::MazeViewer(amaze::Maze * maze, QWidget *parent) :
		QGLWidget(parent), m_fullscreen(false), m_maze(maze){
		this->setWindowTitle("MazeViewer");
	}

	MazeViewer::~MazeViewer(){

	}

	void MazeViewer::resizeGL(int w, int h)
	{
		if(h == 0){
			h = 1;
		}

		glViewport(0, 0, w, h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// gluPerspective(45.0f,(GLfloat)w/(GLfloat)h, 0.1f, 100.0f);
		glOrtho(0, 1, 0, 1, -1.0, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void MazeViewer::initializeGL(){
		glShadeModel(GL_SMOOTH);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}

	void MazeViewer::paintGL(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		unsigned int size_x = m_maze->getSizeX();
		unsigned int size_y = m_maze->getSizeY();

		Maze::MazeNode nodei;

		float grid_x = 1.0/size_x;
		float grid_y = 1.0/size_y;

		glTranslatef(grid_x/2, grid_y/2, 0.0);

		for(int y = 0; y < size_y; y++){
			for(int x = 0; x < size_x; x++){
				Maze::MazeNode node;
				node.x = x;
				node.y = y;

				Maze::MazeNodeData data = m_maze->getDataAt(node);

				if(!data.up){
					glColor3d(1.0, 0.0,0.0);
					glBegin(GL_QUADS);
						glVertex3f(-grid_x/2, grid_y/2, 0);
						glVertex3f(-grid_x/2, 0.9*grid_y/2, 0);
						glVertex3f(grid_x/2, 0.9*grid_y/2, 0);
						glVertex3f(grid_x/2, grid_y/2, 0);
					glEnd();
				}

				if(!data.down){
					glColor3d(0.0, 1.0,0.0);
					glBegin(GL_QUADS);
						glVertex3f(-grid_x/2, -grid_y/2, 0);
						glVertex3f(grid_x/2, -grid_y/2, 0);
						glVertex3f(grid_x/2, -0.9*grid_y/2, 0);
						glVertex3f(-grid_x/2, -0.9*grid_y/2, 0);
					glEnd();
				}

				if(!data.right){
					glColor3d(0.0, 0.0, 1.0);
					glBegin(GL_QUADS);
						glVertex3f(grid_x/2, grid_y/2, 0);
						glVertex3f(0.9*grid_x/2, grid_y/2, 0);
						glVertex3f(0.9*grid_x/2, -grid_y/2, 0);
						glVertex3f(grid_x/2, -grid_y/2, 0);
					glEnd();
				}

				if(!data.left){
					glColor3d(0.0, 1.0, 1.0);
					glBegin(GL_QUADS);
						glVertex3f(-0.9*grid_x/2, grid_y/2, 0);
						glVertex3f(-grid_x/2, grid_y/2, 0);
						glVertex3f(-grid_x/2, -grid_y/2, 0);
						glVertex3f(-0.9*grid_x/2, -grid_y/2, 0);
					glEnd();
				}


				glBegin(GL_POINTS);				// Drawing Using Triangles
					glVertex3f( 0.0f, 0.0f, 0.0f);		// Top
				glEnd();	
				glTranslatef(grid_x, 0.0, 0.0);
			}
			glTranslatef(-1.0, grid_y, 0.0);
		}

		// glTranslatef(-1.5f, 0.0f, -6.0f);	// Move Left 1.5 Units And Into The Screen 6.0

		// glBegin(GL_TRIANGLES);				// Drawing Using Triangles
		// 	glVertex3f( 0.0f, 0.0f, 0.0f);		// Top
		// 	glVertex3f(	1.0f, 0.0f, 0.0f);		// Bottom Left
		// 	glVertex3f( 0.0f, 1.0f, 0.0f);		// Bottom Right
		// glEnd();							// Finished Drawing The Triangle

		// glTranslatef(3.0f,0.0f,0.0f);		// Move Right 3 Units

		// glBegin(GL_QUADS);					// Draw A Quad
		// 	glVertex3f(-1.0f, 1.0f, 0.0f);		// Top Left
		// 	glVertex3f( 1.0f, 1.0f, 0.0f);		// Top Right
		// 	glVertex3f( 1.0f,-1.0f, 0.0f);		// Bottom Right
		// 	glVertex3f(-1.0f,-1.0f, 0.0f);		// Bottom Left
		// glEnd();							// Finished Drawing The Quad
	}

	void MazeViewer::keyPressEvent(QKeyEvent *event){
		switch(event->key()){
			case Qt::Key_F2:{
				m_fullscreen = !m_fullscreen;
				if(m_fullscreen){
					showFullScreen();
				} else{
					showNormal();
				}
				updateGL();
				break;
			}
			case Qt::Key_Escape:{
				qApp->exit();
				break;
			}
		}
	}
}

/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 05:14:14
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-07 06:30:05
*/

#include "TerrainViewer.hpp"
#include <algorithm>
// #include <pg_gl.h>

TerrainViewer::TerrainViewer(amaze::HeightMap * heightMap){
	_heightMap = heightMap;
}

TerrainViewer::~TerrainViewer(){
	delete _heightMap;
}

void TerrainViewer::init(){
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	// glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	this->camera()->setZNearCoefficient(0.00001);
	this->camera()->setZClippingCoefficient(1000.0);
	// setSceneCenter( qglviewer::Vec(25,25,0) );
}

void colorForHeight(double height, double maxi, double mini){
	double h = (height-mini)/(maxi-mini);

	if(h > 0.8){
		glColor3f(0.22, 0.19, 0.2);
	} else if(h > 0.6){
		glColor3f(0.77, 0.57, 0.44);
	} else if(h > 0.4){
		glColor3f(0.48, 0.56, 0.32);
	} else if(h > 0.3){
		h = (h-0.3)/0.1;
		glColor3f((1-h)*0.61 + h*0.48,
				  (1-h)*0.65 + h*0.56,
				  (1-h)*0.46 + h*0.32);
	} else{
		glColor3f(0.19, 0.27, 0.41);
	}
}

double trueHeight(double height, double maxi, double mini){
	if(height < mini*0.7 + maxi*0.3){
		return mini*0.7 + maxi*0.3 - 0.1;
	} else{
		return height;
	}
}

void TerrainViewer::draw(){

	int nx = _heightMap->getResolutionX();
	int ny = _heightMap->getResolutionY();
	double dx = _heightMap->getSizeX()/nx;
	double dy = _heightMap->getSizeY()/ny;

	double ddx = _heightMap->getSizeX()/2;
	double ddy = _heightMap->getSizeY()/2;

	double maxi = -1000000;
	double mini = 10000000;
	for(int x = 0; x < nx; x++){
		for(int y = 0; y < ny; y++){
			double h = _heightMap->getHeightAt(x, y);
			maxi = std::max(maxi, h);
			mini = std::min(mini, h);
		}
	}


	for(int x = 0; x < nx-1; x++){
		for(int y = 0; y < ny-1; y++){
			glBegin(GL_QUADS);
				double a, b, c, d;
				a = _heightMap->getHeightAt(x, y);
				b = _heightMap->getHeightAt(x, y+1);
				c = _heightMap->getHeightAt(x+1, y+1);
				d = _heightMap->getHeightAt(x+1, y);

				a = trueHeight(a, maxi, mini);
				b = trueHeight(b, maxi, mini);
				c = trueHeight(c, maxi, mini);
				d = trueHeight(d, maxi, mini);

				colorForHeight(a, maxi, mini);
				glVertex3f(dx*x-ddx, dy*y-ddy, a);

				colorForHeight(b, maxi, mini);
				glVertex3f(dx*x-ddx, dy*(y+1)-ddy, b);

				colorForHeight(c, maxi, mini);
				glVertex3f(dx*(x+1)-ddx, dy*(y+1)-ddy, c);

				colorForHeight(d, maxi, mini);
				glVertex3f(dx*(x+1)-ddx, dy*y-ddy, d);
			glEnd();
		}
	}
}
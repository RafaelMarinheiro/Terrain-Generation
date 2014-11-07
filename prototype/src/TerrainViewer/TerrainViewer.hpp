/* 
* @Author: Rafael Marinheiro
* @Date:   2014-11-07 05:13:34
* @Last Modified by:   Rafael Marinheiro
* @Last Modified time: 2014-11-07 05:17:14
*/

#ifndef TERRAIN_VIEWER_HPP
#define TERRAIN_VIEWER_HPP

#include <QGLViewer/qglviewer.h>
#include <Terrain/HeightMap.hpp>

class TerrainViewer : public QGLViewer{

public:
	TerrainViewer(amaze::HeightMap * heightMap);
	~TerrainViewer();
protected :
	virtual void draw();
	virtual void init();
	// virtual QString helpString() const;

private:
	amaze::HeightMap * _heightMap;
};

#endif // TERRAIN_VIEWER_HPP

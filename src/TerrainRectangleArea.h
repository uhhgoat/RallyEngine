#pragma once
#include "Terrain.h"
class TRAIterator;
class TerrainRectangleArea
{
public:
	TerrainRectangleArea() {};
	TerrainRectangleArea(Terrain* terrain, Collidable* col);

	CellIndex min;
	CellIndex max;
	TRAIterator begin();
	TRAIterator end();
};
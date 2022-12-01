#pragma once
#include "Terrain.h"
class TerrainAttorney
{
public:
	class Tools
	{
		friend class TerrainRectangleArea;
	private:
		static CellIndex GetCellInd(Terrain* t, Vect Pos) { return t->GetCellInd(Pos); };
	};
	class Collision
	{
		friend class CollisionTestTerrainCommand;
	private:
		static Cell GetCell(Terrain* t, CellIndex ind) { return t->GetCell(ind); };
	};
};
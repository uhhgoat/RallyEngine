#include "TerrainRectangleArea.h"
#include "TRAIterator.h"
#include "TerrainAttorney.h"

TerrainRectangleArea::TerrainRectangleArea(Terrain* terrain, Collidable* col)
{
	Vect pos = col->GetDefaultBSphere().GetCenter();
	float radius = col->GetDefaultBSphere().GetRadius();

	Vect Min = Vect(pos.X() - radius, 0, pos.Z() - radius);
	Vect Max = Vect(pos.X() + radius, 0, pos.Z() + radius);
	//ShowCellRange(Vect(pos.X() - radius, 0, pos.Z() - radius), Vect(pos.X() + radius, 0, pos.Z() + radius));

	//min = terrain->GetCellInd(Min);
	//max = terrain->GetCellInd(Max);

	min = TerrainAttorney::Tools::GetCellInd(terrain, Min);
	max = TerrainAttorney::Tools::GetCellInd(terrain, Max);
	
}

TRAIterator TerrainRectangleArea::begin()
{
	return TRAIterator(min, this);
}

TRAIterator TerrainRectangleArea::end()
{
	return TRAIterator(max, this);
}

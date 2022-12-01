#include "CollisionTestTerrainCommand.h"
#include "CollisionVolume.h"
#include "RallyMathTools.h"
#include "Collidable.h"
#include "RallyColors.h"
#include "TerrainRectangleArea.h"
#include "TRAIterator.h"
#include "TerrainAttorney.h"

CollisionTestTerrainCommand::CollisionTestTerrainCommand(CollidableGroup* g)
	: pG(g)
{ }

CollisionTestTerrainCommand::~CollisionTestTerrainCommand()
{
	
}

void CollisionTestTerrainCommand::execute()
{
	Terrain* terrain = SceneManager::GetCurrentScene()->GetTerrain();
	const CollidableGroup::StorageList& Collection = pG->GetColliderCollection();

	for (auto it1 = Collection.begin(); it1 != Collection.end(); it1++)
	{
		Collidable* col = (*it1);
		TerrainRectangleArea CandidateCells = TerrainRectangleArea(terrain, col);

		for (TRAIterator itCell = CandidateCells.begin(); !(itCell == CandidateCells.end()); itCell.next())
		{
			if (!RallyMathTools::Intersect(CollisionVolumeAABB(TerrainAttorney::Collision::GetCell(terrain, itCell.current).Min, TerrainAttorney::Collision::GetCell(terrain, itCell.current).Max), col->GetDefaultBSphere()))
			{
				continue;
			}
			else if(RallyMathTools::Intersect(CollisionVolumeAABB(TerrainAttorney::Collision::GetCell(terrain, itCell.current).Min, TerrainAttorney::Collision::GetCell(terrain, itCell.current).Max), col->GetCollisionVolume()))
			{
				(*it1)->CollisionTerrain();
				break;
			}
		}

	}
}
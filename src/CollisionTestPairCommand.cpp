#include "CollisionTestPairCommand.h"
#include "CollisionVolume.h"
#include "RallyMathTools.h"
#include "Collidable.h"
#include "RallyColors.h"
#include "Visualizer.h"
CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd)
	: pG1(g1), pG2(g2), pDispatch(pd)
{ }

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete pDispatch;
}

void CollisionTestPairCommand::execute()
{
	//TEST IF GROUP AABBs INTERSECT
	if (!RallyMathTools::Intersect(pG1->GetGroupAABB(), pG2->GetGroupAABB()))
	{
		//Visualizer::ShowCollisionVolume(pG1->GetGroupAABB(), RALLY_COLORS::BLUE);
		//Visualizer::ShowCollisionVolume(pG2->GetGroupAABB(), RALLY_COLORS::BLUE);
		return;
	}
	//Visualizer::ShowCollisionVolume(pG1->GetGroupAABB(), RALLY_COLORS::RED);
	//Visualizer::ShowCollisionVolume(pG2->GetGroupAABB(), RALLY_COLORS::RED);

	const CollidableGroup::StorageList& Collection1 = pG1->GetColliderCollection();
	const CollidableGroup::StorageList& Collection2 = pG2->GetColliderCollection();

	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{
		//TEST IF BSPHERE INTERSECTS GROUP
		const CollisionVolumeBSphere& BS1 = (*it1)->GetDefaultBSphere();
		if (!RallyMathTools::Intersect(BS1, pG2->GetGroupAABB()))
		{
			//Visualizer::ShowCollisionVolume(BS1, RALLY_COLORS::BLUE);
			continue;
		}
		//Visualizer::ShowCollisionVolume(BS1, RALLY_COLORS::RED);
		const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();
		for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
		{
			//TEST IF BSPHERE INSTERSECTS BSPHERE
			const CollisionVolumeBSphere& BS2 = (*it2)->GetDefaultBSphere();
			if (!RallyMathTools::Intersect(BS1, BS2))
			{
				//Visualizer::ShowCollisionVolume(BS2, RALLY_COLORS::BLUE);
				continue;
			}
			//Visualizer::ShowCollisionVolume(BS2, RALLY_COLORS::RED);
			const CollisionVolume& cv2 = (*it2)->GetCollisionVolume();
			//bool test_result = true;  

			if (RallyMathTools::Intersect(cv1, cv2))
			{
				pDispatch->ProcessCallbacks(*it1, *it2);

				//Visualizer::ShowCollisionVolume(cv1, RALLY_COLORS::RED);
				//Visualizer::ShowCollisionVolume(cv2, RALLY_COLORS::RED);
			}
		}
	}
}

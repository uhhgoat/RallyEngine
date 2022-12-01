#include "CollisionTestSelfCommand.h"
#include "CollisionVolume.h"
#include "RallyMathTools.h"
#include "Collidable.h"
#include "RallyColors.h"
#include "Visualizer.h"
CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd)
	: pG(g), pDispatch(pd)
{ }

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete pDispatch;
}

void CollisionTestSelfCommand::execute()
{
	const CollidableGroup::StorageList& Collection = pG->GetColliderCollection();

	for (auto it1 = Collection.begin(); it1 != Collection.end(); it1++)
	{
		const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();
		const CollisionVolumeBSphere& BS1 = (*it1)->GetDefaultBSphere();
		for (auto it2 = std::next(it1); it2 != Collection.end(); it2++)
		{
			//TEST IF BSPHERE INSTERSECTS BSPHERE
			const CollisionVolumeBSphere& BS2 = (*it2)->GetDefaultBSphere();
			if (!RallyMathTools::Intersect(BS1, BS2))
			{
				continue;
			}
			//Visualizer::ShowCollisionVolume(BS1, RALLY_COLORS::RED);
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
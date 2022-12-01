#include "CollisionManager.h"
#include <assert.h>


void CollisionManager::SetGroupForTypeID(TypeID ind)
{
	if (ColGroupCollection[ind] == nullptr)
		ColGroupCollection[ind] = new CollidableGroup();

}


CollidableGroup* CollisionManager::GetColGroup(TypeID id)
{
	return ColGroupCollection[id];
}


void CollisionManager::ProcessCollisions()
{
	for (CollidableGroup* colGroup : ColGroupCollection)
	{
		if(colGroup != nullptr)
			colGroup->UpdateGroupAABB();
	}

	for (CollisionTestCommands::iterator it = colTestCommands.begin(); it != colTestCommands.end(); it++)
	{
		(*it)->execute();
	}
}

CollisionManager::~CollisionManager()
{
	for (auto&& child : colTestCommands) {
		delete child;
	}
	for (auto&& child : ColGroupCollection) {
		delete child;
	}
}
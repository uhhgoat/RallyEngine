#include "CollidableGroup.h"
#include "CollidableAttorney.h"
#include "GroupAABBAttorney.h"
CollidableGroup::CollidableGroup()
{
	groupAABB = new CollisionVolumeAABB();
}
CollidableGroup::~CollidableGroup()
{
	delete groupAABB;
}

void CollidableGroup::Register(Collidable* col)
{
	CollidableGroup::StorageListRef ref = storageList.insert(storageList.end(), col);
	CollidableAttorney::Registration::setStorageRef(col, ref);
}
void CollidableGroup::Deregister(const StorageListRef ref)
{
	storageList.erase(ref);
}
const CollidableGroup::StorageList& CollidableGroup::GetColliderCollection()
{
	return storageList;
}

void CollidableGroup::UpdateGroupAABB()
{
	GroupAABBAttorney::ResetGroupData(groupAABB);
	for (Collidable* col : storageList)
	{
		if (col != nullptr)
		{
			GroupAABBAttorney::ComputeGroupData(groupAABB, col->GetDefaultBSphere());
		}
	}
}

const CollisionVolumeAABB& CollidableGroup::GetGroupAABB()
{
	return *groupAABB;
}

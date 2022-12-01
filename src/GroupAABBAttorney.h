#pragma once
#include "CollisionVolumeAABB.h"
class CollisionVolumeBSphere;

class GroupAABBAttorney
{
private:
	friend class CollidableGroup;
	static void ComputeGroupData(CollisionVolumeAABB* aabb, const CollisionVolumeBSphere& sphere) { aabb->ComputeGroupData(sphere); };
	static void ResetGroupData(CollisionVolumeAABB* aabb) { aabb->ResetGroupData(); };
};
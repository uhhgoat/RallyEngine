#pragma once
#include "AzulCore.h"
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolume
{
public:
	virtual ~CollisionVolume() = default;
	virtual void ComputeData(Model* mod, Matrix& mat, float scale) = 0;

	virtual bool Intersect(const CollisionVolume& other) = 0;

	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;

	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;
	virtual void DebugView(const Vect& col) const = 0;
};
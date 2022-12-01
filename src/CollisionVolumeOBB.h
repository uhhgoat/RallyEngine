#pragma once
#include "CollisionVolumeBoundingBoxBase.h"
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB : public CollisionVolumeBoundingBoxBase
{
private:

public:
	void ComputeData(Model* mod, Matrix& mat, float scale) override;
	
	bool Intersect(const CollisionVolume& other) override;

	bool IntersectAccept(const CollisionVolume& other) const override;
	bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	bool IntersectVisit(const CollisionVolumeOBB& other) const override;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	void DebugView(const Vect& col) const override;
};
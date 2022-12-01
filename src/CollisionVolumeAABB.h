#pragma once
#include "CollisionVolumeBoundingBoxBase.h"
class CollisionVolumeBSphere;
class CollisionVolumeOBB;
class CollisionVolumeAABB : public CollisionVolumeBoundingBoxBase
{
private:
	friend class GroupAABBAttorney;

	Vect Min;
	Vect Max;

	void ComputeGroupData(const CollisionVolumeBSphere& sphere);
	void ResetGroupData();

public:
	CollisionVolumeAABB() = default;
	CollisionVolumeAABB(Vect min, Vect max);
	void ComputeData(Model* mod, Matrix& mat, float scale) override;
	const Vect& GetMin() const;
	const Vect& GetMax() const;
	bool Intersect(const CollisionVolume& other) override;

	

	bool IntersectAccept(const CollisionVolume& other) const override;
	bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	bool IntersectVisit(const CollisionVolumeOBB& other) const override;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	void DebugView(const Vect& col) const override;
};
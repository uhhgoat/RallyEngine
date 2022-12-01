#pragma once
#include "CollisionVolume.h"
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolumeBSphere : public CollisionVolume
{
private:
	Vect Center;
	float Radius;

public:
	void ComputeData(Model* mod, Matrix& mat, float scale) override;
	const Vect& GetCenter() const;
	float GetRadius() const;

	bool Intersect(const CollisionVolume& other) override;


	bool IntersectAccept(const CollisionVolume& other) const override;
	bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	void DebugView(const Vect& col) const override;
};
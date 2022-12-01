#include "CollisionVolumeOBB.h"
#include "CollisionVolumeBSphere.h"
#include "RallyMathTools.h"
#include "Visualizer.h"
void CollisionVolumeOBB::ComputeData(Model* mod, Matrix& mat, float scale)
{
	AZUL_UNUSED_FLOAT(scale);
	WorldTrans = mat;
	LocMin = mod->getMinAABB();
	LocMax = mod->getMaxAABB();

	HalfDiag = 0.5f * (LocMax - LocMin);

	Center = (LocMin + HalfDiag) * WorldTrans;

	ScaleSquared = (Vect(1, 0, 0, 0) * mat).magSqr();

}
bool CollisionVolumeOBB::Intersect(const CollisionVolume& other)
{
	AZUL_UNUSED(&other);
	return true;
}
void CollisionVolumeOBB::DebugView(const Vect& col) const
{
	Visualizer::ShowOBB(*this, col);
}

bool CollisionVolumeOBB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return RallyMathTools::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return RallyMathTools::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return RallyMathTools::Intersect(*this, other);
}

#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "RallyMathTools.h"
#include "Visualizer.h"
void CollisionVolumeBSphere::ComputeData(Model* mod, Matrix& mat, float scale)
{
	Radius = mod->getRadius() * scale;
	Center = mod->getCenter() * mat;

}
const Vect& CollisionVolumeBSphere::GetCenter() const
{
	return Center;
}
float CollisionVolumeBSphere::GetRadius() const
{
	return Radius;
}
bool CollisionVolumeBSphere::Intersect(const CollisionVolume& other)
{
	AZUL_UNUSED(&other);
	return true;
}

void CollisionVolumeBSphere::DebugView(const Vect& col) const
{
	Visualizer::ShowBSphere(*this, col);
}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return RallyMathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return RallyMathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return RallyMathTools::Intersect(other, *this);
}

#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "RallyMathTools.h"
#include "Visualizer.h"
CollisionVolumeAABB::CollisionVolumeAABB(Vect min, Vect max)
{
	Min = min;
	Max = max;
	Vect scale = max - min;
	Vect v = 0.5f * (max + min);
	WorldTrans = Matrix(SCALE, scale) * Matrix(TRANS, v);

	LocMin = min * WorldTrans.getInv();
	LocMax = max * WorldTrans.getInv();

	HalfDiag = 0.5f * (LocMax - LocMin);

	Center = (LocMin + HalfDiag) * WorldTrans;

	ScaleSquared = (Vect(1, 0, 0, 0) * WorldTrans).magSqr();
}
void CollisionVolumeAABB::ComputeData(Model* mod, Matrix& mat, float scale)
{
	AZUL_UNUSED_FLOAT(scale);
	Vect* arr = mod->getVectList();
	int n = mod->getVectNum();

	Vect vert = arr[0] * mat;

	float minX = vert.X();
	float minY = vert.Y();
	float minZ = vert.Z();

	float maxX = vert.X();
	float maxY = vert.Y();
	float maxZ = vert.Z();

	for (int i = 0; i < n; i++)
	{
		vert = arr[i] * mat;
		if (vert.X() < minX)
			minX = vert.X();
		if (vert.Y() < minY)
			minY = vert.Y();
		if (vert.Z() < minZ)
			minZ = vert.Z();
		if (vert.X() > maxX)
			maxX = vert.X();
		if (vert.Y() > maxY)
			maxY = vert.Y();
		if (vert.Z() > maxZ)
			maxZ = vert.Z();
	}
	Min = Vect(minX, minY, minZ);
	Max = Vect(maxX, maxY, maxZ);

	WorldTrans = mat;
	LocMin = mod->getMinAABB();
	LocMax = mod->getMaxAABB();

	HalfDiag = 0.5f * (LocMax - LocMin);

	Center = (LocMin + HalfDiag) * WorldTrans;

	ScaleSquared = (Vect(1, 0, 0, 0) * WorldTrans).magSqr();

}
void CollisionVolumeAABB::ComputeGroupData(const CollisionVolumeBSphere& sphere)
{
	Vect sC = sphere.GetCenter();
	float r = sphere.GetRadius();

	Min.X() = (Min.X() == 0 || sC.X() - r < Min.X()) ? sC.X() - r : Min.X();
	Min.Y() = (Min.Y() == 0 || sC.Y() - r < Min.Y()) ? sC.Y() - r : Min.Y();
	Min.Z() = (Min.Z() == 0 || sC.Z() - r < Min.Z()) ? sC.Z() - r : Min.Z();

	Max.X() = (Max.X() == 0 || sC.X() + r > Max.X()) ? sC.X() + r : Max.X();
	Max.Y() = (Max.Y() == 0 || sC.Y() + r > Max.Y()) ? sC.Y() + r : Max.Y();
	Max.Z() = (Max.Z() == 0 || sC.Z() + r > Max.Z()) ? sC.Z() + r : Max.Z();
}
void CollisionVolumeAABB::ResetGroupData()
{
	Min = Vect(0, 0, 0);
	Max = Vect(0, 0, 0);
}
const Vect& CollisionVolumeAABB::GetMin() const
{
	return Min;
}
const Vect& CollisionVolumeAABB::GetMax() const
{
	return Max;
}
bool CollisionVolumeAABB::Intersect(const CollisionVolume& other)
{
	AZUL_UNUSED(&other);
	return true;
}
void CollisionVolumeAABB::DebugView(const Vect& col) const
{
	Visualizer::ShowAABB(*this, col);
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return RallyMathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return RallyMathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return RallyMathTools::Intersect(*this, other);
}

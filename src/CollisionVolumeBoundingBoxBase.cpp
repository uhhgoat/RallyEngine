#include "CollisionVolumeBoundingBoxBase.h"
#include "CollisionVolumeBSphere.h"
#include "RallyMathTools.h"
#include "Visualizer.h"
const Vect& CollisionVolumeBoundingBoxBase::GetMin() const
{
	return LocMin;
}
const Vect& CollisionVolumeBoundingBoxBase::GetMax() const
{
	return LocMax;
}
const Matrix& CollisionVolumeBoundingBoxBase::GetWorld() const
{
	return WorldTrans;
}
const Vect& CollisionVolumeBoundingBoxBase::GetHalfDiag() const
{
	return HalfDiag;
}
const Vect& CollisionVolumeBoundingBoxBase::GetCenter() const
{
	return Center;
}
const float CollisionVolumeBoundingBoxBase::GetScaleSquared() const
{
	return ScaleSquared;
}

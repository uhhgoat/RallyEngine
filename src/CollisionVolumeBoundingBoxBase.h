#pragma once
#include "CollisionVolume.h"
class CollisionVolumeBoundingBoxBase : public CollisionVolume
{
protected:
	Vect LocMin;
	Vect LocMax;
	Matrix WorldTrans;

	Vect HalfDiag;
	Vect Center;
	float ScaleSquared = 0;

public:
	//void ComputeData(Model* mod, Matrix& mat, float scale) override;
	virtual const Vect& GetMin() const;
	virtual const Vect& GetMax() const;
	virtual const Matrix& GetWorld() const;
	virtual const Vect& GetHalfDiag() const;
	virtual const Vect& GetCenter() const;
	virtual const float GetScaleSquared() const;
};
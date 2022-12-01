#include "RallyMathTools.h"

bool RallyMathTools::Intersect(const CollisionVolume& A, const CollisionVolume& B)
{
	return A.IntersectAccept(B);
}

bool RallyMathTools::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B)
{
	Vect AC = A.GetCenter();
	Vect BC = B.GetCenter();
	float distSQ = (BC - AC).magSqr();
	float RadSQ = (A.GetRadius() + B.GetRadius()) * (A.GetRadius() + B.GetRadius());

	return distSQ <= RadSQ;
}

bool RallyMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B)
{
	float axx = A.GetMax().X();
	float axy = A.GetMax().Y();
	float axz = A.GetMax().Z();

	float amx = A.GetMin().X();
	float amy = A.GetMin().Y();
	float amz = A.GetMin().Z();

	float bxx = B.GetMax().X();
	float bxy = B.GetMax().Y();
	float bxz = B.GetMax().Z();

	float bmx = B.GetMin().X();
	float bmy = B.GetMin().Y();
	float bmz = B.GetMin().Z();

	return (!IntersectOverlap(amx, axx, bmx, bxx) || !IntersectOverlap(amy, axy, bmy, bxy) || !IntersectOverlap(amz, axz, bmz, bxz)) ? false : true;
}

bool RallyMathTools::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B)
{
	Vect V01 = A.GetWorld().get(ROW_0);
	Vect V02 = A.GetWorld().get(ROW_1);
	Vect V03 = A.GetWorld().get(ROW_2);
	Vect V04 = B.GetWorld().get(ROW_0);
	Vect V05 = B.GetWorld().get(ROW_1);
	Vect V06 = B.GetWorld().get(ROW_2);
	Vect V07 = V01.cross(V04);
	Vect V08 = V01.cross(V05);
	Vect V09 = V01.cross(V06);
	Vect V10 = V02.cross(V04);
	Vect V11 = V02.cross(V05);
	Vect V12 = V02.cross(V06);
	Vect V13 = V03.cross(V04);
	Vect V14 = V03.cross(V05);
	Vect V15 = V03.cross(V06);
	return
		OBBOverlapOnV(A, B, V01) &&
		OBBOverlapOnV(A, B, V02) &&
		OBBOverlapOnV(A, B, V03) &&
		OBBOverlapOnV(A, B, V04) &&
		OBBOverlapOnV(A, B, V05) &&
		OBBOverlapOnV(A, B, V06) &&
		OBBOverlapOnV(A, B, V07) &&
		OBBOverlapOnV(A, B, V08) &&
		OBBOverlapOnV(A, B, V09) &&
		OBBOverlapOnV(A, B, V10) &&
		OBBOverlapOnV(A, B, V11) &&
		OBBOverlapOnV(A, B, V12) &&
		OBBOverlapOnV(A, B, V13) &&
		OBBOverlapOnV(A, B, V14) &&
		OBBOverlapOnV(A, B, V15);
}



bool RallyMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeBSphere& B)
{
	float x = ClampToInterval(B.GetCenter().X(), A.GetMin().X(), A.GetMax().X());
	float y = ClampToInterval(B.GetCenter().Y(), A.GetMin().Y(), A.GetMax().Y());
	float z = ClampToInterval(B.GetCenter().Z(), A.GetMin().Z(), A.GetMax().Z());
	Vect V = Vect(x, y, z);

	return PointInSphere(V, B);
}

bool RallyMathTools::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeBSphere& B)
{
	Matrix inverse = A.GetWorld().getInv();
	Vect Cp = B.GetCenter() * inverse;
	Vect Q = ClampToBox(Cp, A.GetMin(), A.GetMax());
	Vect Qp = Q * A.GetWorld();
	return PointInSphere(Qp, B);
}

bool RallyMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeOBB& B)
{
	Vect V01 = A.GetWorld().get(ROW_0);
	Vect V02 = A.GetWorld().get(ROW_1);
	Vect V03 = A.GetWorld().get(ROW_2);
	Vect V04 = B.GetWorld().get(ROW_0);
	Vect V05 = B.GetWorld().get(ROW_1);
	Vect V06 = B.GetWorld().get(ROW_2);
	Vect V07 = V01.cross(V04);
	Vect V08 = V01.cross(V05);
	Vect V09 = V01.cross(V06);
	Vect V10 = V02.cross(V04);
	Vect V11 = V02.cross(V05);
	Vect V12 = V02.cross(V06);
	Vect V13 = V03.cross(V04);
	Vect V14 = V03.cross(V05);
	Vect V15 = V03.cross(V06);
	return
		OBBOverlapOnV(A, B, V01) &&
		OBBOverlapOnV(A, B, V02) &&
		OBBOverlapOnV(A, B, V03) &&
		OBBOverlapOnV(A, B, V04) &&
		OBBOverlapOnV(A, B, V05) &&
		OBBOverlapOnV(A, B, V06) &&
		OBBOverlapOnV(A, B, V07) &&
		OBBOverlapOnV(A, B, V08) &&
		OBBOverlapOnV(A, B, V09) &&
		OBBOverlapOnV(A, B, V10) &&
		OBBOverlapOnV(A, B, V11) &&
		OBBOverlapOnV(A, B, V12) &&
		OBBOverlapOnV(A, B, V13) &&
		OBBOverlapOnV(A, B, V14) &&
		OBBOverlapOnV(A, B, V15);
}


//OTHER TOOLS

bool RallyMathTools::IntersectOverlap(float a, float b, float c, float d)
{
	return (b < c || d < a) ? false : true;
}

bool RallyMathTools::PointInInterval(float p, float a, float b)
{
	return (p < a || p > b) ? false : true;
}

float RallyMathTools::ClampToInterval(float p, float a, float b)
{
	if (p < a)
		return a;
	else if (p > b)
		return b;
	else return p;
}

bool RallyMathTools::PointInSphere(Vect V, const CollisionVolumeBSphere& B)
{
	Vect BC = B.GetCenter();
	float distSQ = (BC - V).magSqr();
	float RadSQ = (B.GetRadius()) * (B.GetRadius());

	return distSQ <= RadSQ;
}

Vect RallyMathTools::ClampToBox(Vect V, Vect Min, Vect Max)
{
	float x = ClampToInterval(V.X(), Min.X(), Max.X());
	float y = ClampToInterval(V.Y(), Min.Y(), Max.Y());
	float z = ClampToInterval(V.Z(), Min.Z(), Max.Z());
	return Vect(x, y, z);
}

bool RallyMathTools::PointInAABB(Vect V, Vect Min, Vect Max)
{
	return ( PointInInterval(V.X(), Min.X(), Max.X()) && PointInInterval(V.Y(), Min.Y(), Max.Y()) && PointInInterval(V.Z(), Min.Z(), Max.Z()) );
}

bool RallyMathTools::PointInOBB(Vect V, const CollisionVolumeBoundingBoxBase& A)
{
	Matrix inverse = A.GetWorld().getInv();
	return PointInAABB(V*inverse, A.GetMin(), A.GetMax());
}

Vect RallyMathTools::Projection_w_V(Vect V, Vect W)
{
	return (V.dot(W) / W.dot(W)) * W;
}

float RallyMathTools::Projection_w_V_Length(Vect V, Vect W)
{
	return (abs(V.dot(W)) / W.mag());
}

float RallyMathTools::MaxOBBProjOnV(Vect V, const CollisionVolumeBoundingBoxBase& A)
{
	float a = A.GetHalfDiag().X();
	float b = A.GetHalfDiag().Y();
	float c = A.GetHalfDiag().Z();
	Vect Vp = V * A.GetWorld().getInv();

	return (A.GetScaleSquared()) * ((abs(Vp.X() * a) + abs(Vp.Y() * b) + abs(Vp.Z() * c)) / V.mag() );
}

bool RallyMathTools::OBBOverlapOnV(const CollisionVolumeBoundingBoxBase& A, const CollisionVolumeBoundingBoxBase& B, Vect V)
{
	if (V.magSqr() <= FLT_EPSILON)
		return true;

	Vect d = B.GetCenter() - A.GetCenter();
	float D = Projection_w_V_Length(d, V);
	float P1 = MaxOBBProjOnV(V, A);
	float P2 = MaxOBBProjOnV(V, B);
	return D <= P1 + P2;
}
/*
Matrix RallyMathTools::GetRotationBetween(Vect _a, Vect _b)
{
	Matrix G = Matrix(RotOrientType::ROT_ORIENT, _b, _a);
	return G;
}
*/
Matrix RallyMathTools::GetRotationTo(Vect _a)
{

	Matrix G = Matrix(RotOrientType::ROT_ORIENT, Vect(1, 0, 0), _a);
	Matrix H = Matrix(RotOrientType::ROT_ORIENT, Vect(0, 0, 1), _a);

	return Matrix(ROT_Y, -MATH_PI2) * G * H;

}

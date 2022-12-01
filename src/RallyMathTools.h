#pragma once
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
class RallyMathTools
{
public:
	/*!
	\brief Called testing intersection between two collision volumes
	*/

	static bool Intersect(const CollisionVolume& A, const CollisionVolume& B);

	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B);
	static bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B);
	static bool Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B);

	static bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeBSphere& B);
	static bool Intersect(const CollisionVolumeOBB& A, const CollisionVolumeBSphere& B);
	static bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeOBB& B);



	//OTHER TOOLS
	//2D--------------------------------------------------------------
	/*!
	\brief Called to see if two intervals overlap
	*/
	static bool IntersectOverlap(float a, float b, float c, float d);
	/*!
	\brief Called to see if a point is in an interval
	*/
	static bool PointInInterval(float p, float a, float b);
	/*!
	\brief Called to clamp a point to an interval
	*/
	static float ClampToInterval(float p, float a, float b);

	//3D--------------------------------------------------------------
	/*!
	\brief Called to see if point inside sphere
	*/
	static bool PointInSphere(Vect V, const CollisionVolumeBSphere& B);
	/*!
	\brief Called to clamp point to AABB
	*/
	static Vect ClampToBox(Vect V, Vect Min, Vect Max);
	/*!
	\brief Called to see if point inside AABB
	*/
	static bool PointInAABB(Vect V, Vect Min, Vect Max);
	/*!
	\brief Called to see if point inside OBB
	*/
	static bool PointInOBB(Vect V, const CollisionVolumeBoundingBoxBase& A);
	/*!
	\brief Called to cast projection of V on W
	*/
	static Vect Projection_w_V(Vect V, Vect W);
	/*!
	\brief Called to get the length of the projection of V on W
	*/
	static float Projection_w_V_Length(Vect V, Vect W);
	/*!
	\brief Called to get length of maximum OBB projection on V
	*/
	static float MaxOBBProjOnV(Vect V, const CollisionVolumeBoundingBoxBase& A);
	/*!
	\brief Called to see if the projections of two OBBs overlap on V
	*/
	static bool OBBOverlapOnV(const CollisionVolumeBoundingBoxBase& A, const CollisionVolumeBoundingBoxBase& B, Vect V);

	//static Matrix GetRotationBetween(Vect _a, Vect _b);

	/*!
	\brief Called to get rotation matrix to align to _a
	*/
	static Matrix GetRotationTo(Vect _a);
};
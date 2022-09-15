//SurrealMathTools

#include "SurrealMathTools.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

bool SurrealMathTools::Intersect(const CollisionVolume& A, const CollisionVolume& B)
{
	return A.IntersectAccept(B);
}

bool SurrealMathTools::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B)
{
	float centerDistance = (B.GetCenter() - A.GetCenter()).magSqr();

	float totalRadii = A.GetRadius() + B.GetRadius();
	totalRadii *= totalRadii;

	if (totalRadii < centerDistance)
		return false;
	else
		return true;
}

bool SurrealMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B)
{
	return Overlap(A.GetMin().X(), A.GetMax().X(), B.GetMin().X(), B.GetMax().X())
		&& Overlap(A.GetMin().Y(), A.GetMax().Y(), B.GetMin().Y(), B.GetMax().Y())
		&& Overlap(A.GetMin().Z(), A.GetMax().Z(), B.GetMin().Z(), B.GetMax().Z());
}

bool SurrealMathTools::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B)
{
	Vect axis[15]; 
	CreateAxisArray(A, B, axis);

	for (int i = 0; i < 15; i++)
	{
		if (IsVectNonZero(axis[i]))
		{
			if (!Overlap(A, B, axis[i]))
				return false;
		}
	}

	return true; 
}

bool SurrealMathTools::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeAABB& B)
{
	return Overlap(ClampPoint(A.GetCenter(), B.GetMin(), B.GetMax()), A.GetCenter(), A.GetRadius());
}

bool SurrealMathTools::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeOBB& B)
{
	Vect Q = WorldToLocal(B.GetWorld(), A.GetCenter()); 
	Q = ClampPoint(Q, B.GetMin(), B.GetMax());
	Q = LocalToWorld(B.GetWorld(), Q);
	return Overlap(Q, A.GetCenter(), A.GetRadius());
}

bool SurrealMathTools::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeOBB& B)
{
	Vect axis[15]; 
	CreateAxisArray(B, A, axis);

	for (int i = 0; i < 15; i++)
	{
		if (IsVectNonZero(axis[i]))
		{
			if (!Overlap(B, A, axis[i]))
				return false;
		}
	}

	return true;
}

//Check if [a, b] overlaps [c, d]
bool SurrealMathTools::Overlap(const float a, const float b, const float c, const float d)
{
	return !((b < c) || (d < a));
}

//Check if point in radius
bool SurrealMathTools::Overlap(const Vect& point, const Vect& center, const float radius)
{
	if ((point - center).mag() <= radius)
		return true;
	else
		return false;
}

bool SurrealMathTools::Overlap(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B, const Vect& v)
{
	float D = fabsf(((B.GetCenter() - A.GetCenter()).dot(v)) / v.mag());
	float Pa = ProjectAlongV(A, v);
	float Pb = ProjectAlongV(B, v);

	return D <= (Pa + Pb);
}

bool SurrealMathTools::Overlap(const CollisionVolumeOBB& A, const CollisionVolumeAABB& B, const Vect& v)
{
	float D = fabsf(((B.GetCenter() - A.GetCenter()).dot(v)) / v.mag()); 
	float Pa = ProjectAlongV(A, v);
	float Pb = ProjectAlongV(B, v);

	return D <= (Pa + Pb);
}

Vect SurrealMathTools::ClampPoint(const Vect& point, const Vect& minPoint, const Vect& maxPoint)
{
	return Vect(ClampValue(point.X(), minPoint.X(), maxPoint.X()),
				ClampValue(point.Y(), minPoint.Y(), maxPoint.Y()),
				ClampValue(point.Z(), minPoint.Z(), maxPoint.Z()));
}

float SurrealMathTools::ClampValue(const float value, const float min, const float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

Vect SurrealMathTools::WorldToLocal(const Matrix& world, const Vect& point)
{
	return point * world.getInv(); 
}

Vect SurrealMathTools::LocalToWorld(const Matrix& world, const Vect& point)
{
	return point * world;
}

float SurrealMathTools::ProjectAlongV(const CollisionVolumeOBB& A, const Vect& v)
{
	Vect pureV = WorldToLocal(A.GetWorld(), v);

	Vect HalfDiag = A.GetHalfDiagonal(); 
	float ProjMax = fabsf(pureV.X() * HalfDiag.X()) + fabsf(pureV.Y() * HalfDiag.Y()) + fabsf(pureV.Z() * HalfDiag.Z());
	ProjMax = ProjMax / v.mag();

	return A.GetScaleSquared() * ProjMax;
}

float SurrealMathTools::ProjectAlongV(const CollisionVolumeAABB& A, const Vect& v)
{
	Vect pureV =  WorldToLocal(A.GetWorld(), v);

	Vect HalfDiag = A.GetHalfDiagonal();
	float ProjMax = fabsf(pureV.X() * HalfDiag.X()) + fabsf(pureV.Y() * HalfDiag.Y()) + fabsf(pureV.Z() * HalfDiag.Z());
	ProjMax = ProjMax / v.mag();

	return A.GetScaleSquared() * ProjMax;
	
}

void SurrealMathTools::CreateAxisArray(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B, Vect* axis)
{
	axis[0] = A.GetWorld().get(ROW_0);
	axis[1] = A.GetWorld().get(ROW_1);
	axis[2] = A.GetWorld().get(ROW_2);
	axis[3] = B.GetWorld().get(ROW_0);
	axis[4] = B.GetWorld().get(ROW_1);
	axis[5] = B.GetWorld().get(ROW_2);
	axis[6] = axis[0].cross(axis[3]); 
	axis[7] = axis[0].cross(axis[4]);
	axis[8] = axis[0].cross(axis[5]); 
	axis[9] = axis[1].cross(axis[3]); 
	axis[10] = axis[1].cross(axis[4]); 
	axis[11] = axis[1].cross(axis[5]);
	axis[12] = axis[2].cross(axis[3]);
	axis[13] = axis[2].cross(axis[4]);
	axis[14] = axis[2].cross(axis[5]);
}

void SurrealMathTools::CreateAxisArray(const CollisionVolumeOBB& A, const CollisionVolumeAABB& B, Vect* axis)
{
	axis[0] = A.GetWorld().get(ROW_0);
	axis[1] = A.GetWorld().get(ROW_1);
	axis[2] = A.GetWorld().get(ROW_2);
	axis[3] = B.GetWorld().get(ROW_0);
	axis[4] = B.GetWorld().get(ROW_1);
	axis[5] = B.GetWorld().get(ROW_2);
	axis[6] = axis[0].cross(axis[3]);
	axis[7] = axis[0].cross(axis[4]);
	axis[8] = axis[0].cross(axis[5]);
	axis[9] = axis[1].cross(axis[3]);
	axis[10] = axis[1].cross(axis[4]);
	axis[11] = axis[1].cross(axis[5]);
	axis[12] = axis[2].cross(axis[3]);
	axis[13] = axis[2].cross(axis[4]);
	axis[14] = axis[2].cross(axis[5]);
}

bool SurrealMathTools::IsVectNonZero(const Vect& v)
{
	if (v.magSqr() > FLT_EPSILON)
		return true;
	else
		return false;
}
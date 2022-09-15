#ifndef _SurrealMathTools
#define _SurrealMathTools

class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class Vect; 
class Matrix;

namespace SurrealMathTools
{
	bool Intersect(const CollisionVolume& A, const CollisionVolume& B);
	bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B); 
	bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeAABB& B);
	bool Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B);
	bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeAABB& B);
	bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeOBB& B);
	bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeOBB& B);

	bool Overlap(const float a, const float b, const float c, const float d);
	bool Overlap(const Vect& point, const Vect& center, const float radius);
	bool Overlap(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B, const Vect& v);
	bool Overlap(const CollisionVolumeOBB& A, const CollisionVolumeAABB& B, const Vect& v);

	Vect ClampPoint(const Vect& point, const Vect& minPoint, const Vect& maxPoint);
	float ClampValue(const float value, const float min, const float max); 

	Vect WorldToLocal(const Matrix& world, const Vect& point); 
	Vect LocalToWorld(const Matrix& world, const Vect& point);

	float ProjectAlongV(const CollisionVolumeOBB& A, const Vect& v);
	float ProjectAlongV(const CollisionVolumeAABB& A, const Vect& v);

	void CreateAxisArray(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B, Vect* axis);
	void CreateAxisArray(const CollisionVolumeOBB& A, const CollisionVolumeAABB& B, Vect* axis);

	bool IsVectNonZero(const Vect& v);

}

#endif _SurrealMathTools
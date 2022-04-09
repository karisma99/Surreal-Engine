#ifndef _CollisionVolume
#define _CollisionVolume

#include "Matrix.h"
#include "Model.h"

class CollisionVolumeBSphere;

class CollisionVolume
{
public:
	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume& c) = delete;
	CollisionVolume& operator = (const CollisionVolume& t) = delete;
	virtual ~CollisionVolume() = default;

	virtual void ComputeData(Model* mod, const Matrix& mat) { mod; mat; };
	virtual bool Intersect(const CollisionVolume& other) = 0;
	virtual bool Intersect(const CollisionVolumeBSphere& other) = 0;


};

#endif _CollisionVolume
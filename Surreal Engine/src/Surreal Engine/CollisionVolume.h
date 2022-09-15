#ifndef _CollisionVolume
#define _CollisionVolume

#include "Matrix.h"
#include "Surreal Graphics/Model.h"

class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolume
{
public:
	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume& c) = delete;
	CollisionVolume& operator = (const CollisionVolume& t) = delete;
	virtual ~CollisionVolume() = default;

	virtual void ComputeData(Model* mod, const Matrix& mat) { mod; mat; };
	virtual void DebugView(const Vect& col) const = 0;

	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0; 
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;
	


};

#endif _CollisionVolume
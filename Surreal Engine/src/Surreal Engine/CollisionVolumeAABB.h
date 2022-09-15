#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "Matrix.h"
#include "Surreal Graphics/Model.h"
#include "Vect.h"
#include "CollisionVolume.h"
#include "CollidableGroup.h"

class VisualizerCommand;
class CollisionVolumeBSphere;
class CollisionVolumeOBB;

class CollisionVolumeAABB : public CollisionVolume, public Align16
{
public:
	CollisionVolumeAABB();
	CollisionVolumeAABB(const CollisionVolumeAABB& c) = delete;
	CollisionVolumeAABB& operator = (const CollisionVolumeAABB& t) = delete;
	~CollisionVolumeAABB();

	virtual void ComputeData(Model* mod, const Matrix& mat);
	virtual void DebugView(const Vect& col) const;
	virtual bool IntersectAccept(const CollisionVolume& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	Vect GetMin() const;
	Vect GetMax() const; 
	Vect GetCenter() const;
	Matrix GetWorld() const; 
	Vect GetHalfDiagonal() const;
	float GetScaleSquared() const;
	VisualizerCommand* GetCommand(Matrix m, Vect c) const;
	void ComputeData(const CollisionVolumeBSphere& pBSphere);
	void ComputeData(CollidableGroup::CollidableCollection& CollideCol);
	void ComputeData(const Vect& _min, const Vect& _max);


private:
	Matrix World; 
	Vect CornerMax; 
	Vect CornerMin;
	Vect WorldCenter; 
	VisualizerCommand* pCommand;

};

#endif _CollisionVolumeAABB
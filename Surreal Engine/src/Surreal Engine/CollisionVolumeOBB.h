#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "Matrix.h"
#include "Surreal Graphics/Model.h"
#include "Vect.h"
#include "CollisionVolume.h"

class VisualizerCommand;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;

class CollisionVolumeOBB : public CollisionVolume, public Align16
{
public:
	CollisionVolumeOBB();
	CollisionVolumeOBB(Model* pMod);
	CollisionVolumeOBB(const CollisionVolumeOBB& c) = delete;
	CollisionVolumeOBB& operator = (const CollisionVolumeOBB& t) = delete;
	~CollisionVolumeOBB();

	virtual void ComputeData(Model* mod, const Matrix& mat);
	virtual void DebugView(const Vect& col) const;
	virtual bool IntersectAccept(const CollisionVolume& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;

	Vect GetMin() const;
	Vect GetMax() const;
	Vect GetHalfDiagonal() const; 
	Vect GetCenter() const; 
	float GetScaleSquared() const;
	Matrix GetWorld() const;
	VisualizerCommand* GetCommand(Matrix m, Vect c) const;


private:
	Matrix World;
	Vect CornerMax;
	Vect CornerMin;
	Vect WorldCenter;
	Vect HalfDiag;
	VisualizerCommand* pCommand;
	float ScaleFactor;

};

#endif _CollisionVolumeOBB
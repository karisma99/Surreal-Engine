#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "Matrix.h"
#include "Surreal Graphics/Model.h"
#include "Vect.h"
#include "CollisionVolume.h"

class VisualizerCommand;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolumeBSphere : public CollisionVolume, public Align16
{
public:
	CollisionVolumeBSphere();
	CollisionVolumeBSphere(const CollisionVolumeBSphere& c) = delete;
	CollisionVolumeBSphere& operator = (const CollisionVolumeBSphere& t) = delete;
	~CollisionVolumeBSphere();

	virtual void ComputeData(Model* mod, const Matrix& mat);
	virtual void DebugView(const Vect& col) const; 
	virtual bool IntersectAccept(const CollisionVolume& other) const override; 
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override; 
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override; 
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	Vect GetCenter() const; 
	float GetRadius() const; 
	VisualizerCommand* GetCommand(Matrix m, Vect c) const;


private:
	Vect center; 
	float radius; 
	Matrix matrix; 
	VisualizerCommand* pCommand;

};

#endif _CollisionVolumeBSphere
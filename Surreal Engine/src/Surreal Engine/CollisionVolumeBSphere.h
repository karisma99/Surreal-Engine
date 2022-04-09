#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "Matrix.h"
#include "Model.h"
#include "Vect.h"
#include "CollisionVolume.h"

class VisualizerCommand;

class CollisionVolumeBSphere : public CollisionVolume, public Align16
{
public:
	CollisionVolumeBSphere();
	CollisionVolumeBSphere(const CollisionVolumeBSphere& c) = delete;
	CollisionVolumeBSphere& operator = (const CollisionVolumeBSphere& t) = delete;
	~CollisionVolumeBSphere();

	virtual void ComputeData(Model* mod, const Matrix& mat);
	virtual bool Intersect(const CollisionVolume& other);
	virtual bool Intersect(const CollisionVolumeBSphere& other);

	Vect GetCenter() const; 
	float GetRadius() const; 
	VisualizerCommand* GetCommand(Matrix m, Vect c) const;


private:
	Vect center; 
	float radius; 
	Matrix matrix; 
	VisualizerCommand* pCommand;

};

#endif _CollisionVolume
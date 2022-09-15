//CollisionVolumeBSphere

#include "CollisionVolumeBSphere.h"
#include "Visualizer.h"
#include "VisualizerCommand.h"
#include "VisualizerCommandFactory.h"
#include "SurrealMathTools.h"

CollisionVolumeBSphere::CollisionVolumeBSphere()
{
	this->pCommand = VisualizerCommandFactory::CreateCommand(matrix, center, Collidable::VolumeType::BSPHERE);
	this->radius = 0.0f; 
	this->center = Vect(0, 0, 0);
}

CollisionVolumeBSphere::~CollisionVolumeBSphere()
{
	VisualizerCommandFactory::RecycleCommand(pCommand);
}

void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat)
{
	this->center = mod->GetCenter() * mat; 
	this->radius = mod->GetRadius() * mat.get(MatrixRowType::ROW_0).mag();
	this->matrix = mat;
}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return SurrealMathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return SurrealMathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return SurrealMathTools::Intersect(*this, other);
}

void CollisionVolumeBSphere::DebugView(const Vect& col) const
{
	Visualizer::ShowSphere(*this, col);
}

Vect CollisionVolumeBSphere::GetCenter() const
{
	return this->center; 
}

float CollisionVolumeBSphere::GetRadius() const
{
	return this->radius;
}

VisualizerCommand* CollisionVolumeBSphere::GetCommand(Matrix m, Vect c) const
{
	this->pCommand->Update(m, c, Collidable::VolumeType::BSPHERE);
	return this->pCommand;
}
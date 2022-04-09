//CollisionVolumeBSphere

#include "CollisionVolumeBSphere.h"
#include "VisualizerCommand.h"
#include "VisualizerCommandFactory.h"

CollisionVolumeBSphere::CollisionVolumeBSphere()
{
	this->pCommand = VisualizerCommandFactory::CreateCommand(matrix, center);
	this->radius = 0.0f; 
	this->center = Vect(0, 0, 0);
}

CollisionVolumeBSphere::~CollisionVolumeBSphere()
{
	VisualizerCommandFactory::RecycleCommand(pCommand);
}

void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat)
{
	this->center = mod->getCenter() * mat; 
	this->radius = mod->getRadius() * mat.get(MatrixRowType::ROW_0).mag();
	this->matrix = mat;
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolume& other)
{
	other;
	return false;
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolumeBSphere& other)
{
	Vect temp(this->GetCenter() - other.GetCenter());
	return (temp.mag() < (this->GetRadius() + other.GetRadius()));
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
	this->pCommand->Update(m, c);
	return this->pCommand;
}
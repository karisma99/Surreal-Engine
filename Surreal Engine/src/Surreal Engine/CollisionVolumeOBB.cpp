//CollisionVolumeOBB

#include "CollisionVolumeOBB.h"
#include "Visualizer.h"
#include "VisualizerCommand.h"
#include "VisualizerCommandFactory.h"
#include "SurrealMathTools.h"
#include "Collidable.h"

CollisionVolumeOBB::CollisionVolumeOBB()
{
	this->World = Matrix(IDENTITY);
	this->CornerMax = Vect(0, 0, 0);
	this->CornerMin = Vect(0, 0, 0);
	this->WorldCenter = Vect(0, 0, 0);
	this->pCommand = VisualizerCommandFactory::CreateCommand(World, CornerMax, Collidable::VolumeType::OBB);
	this->ScaleFactor = 0.0f;
}

CollisionVolumeOBB::CollisionVolumeOBB(Model* pMod)
{
	this->World = Matrix(IDENTITY);
	CornerMin = pMod->GetMinAABB();
	CornerMax = pMod->GetMaxAABB();
	HalfDiag = 0.5f * (CornerMax - CornerMin);
	this->WorldCenter = Vect(0, 0, 0);
	this->pCommand = VisualizerCommandFactory::CreateCommand(World, CornerMax, Collidable::VolumeType::OBB);
	this->ScaleFactor = 0.0f;
}

CollisionVolumeOBB::~CollisionVolumeOBB()
{
	VisualizerCommandFactory::RecycleCommand(pCommand);
}

void CollisionVolumeOBB::ComputeData(Model* mod, const Matrix& mat)
{
	mod;
	World = mat; 
	WorldCenter = (CornerMin + HalfDiag) * World;
	ScaleFactor = World.get(ROW_0).dot(World.get(ROW_0));
}

bool CollisionVolumeOBB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return SurrealMathTools::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return SurrealMathTools::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return SurrealMathTools::Intersect(*this, other);
}

void CollisionVolumeOBB::DebugView(const Vect& col) const
{
	Visualizer::ShowBox(*this, col);
}

Vect CollisionVolumeOBB::GetMin() const
{
	return this->CornerMin;
}

Vect CollisionVolumeOBB::GetMax() const
{
	return this->CornerMax;
}

Vect CollisionVolumeOBB::GetHalfDiagonal() const
{
	return HalfDiag;
}

Vect CollisionVolumeOBB::GetCenter() const
{
	return WorldCenter;
}

float CollisionVolumeOBB::GetScaleSquared() const
{
	return ScaleFactor;
}

Matrix CollisionVolumeOBB::GetWorld() const
{
	return this->World;
}

VisualizerCommand* CollisionVolumeOBB::GetCommand(Matrix m, Vect c) const
{
	this->pCommand->Update(m, c, Collidable::VolumeType::OBB);
	return this->pCommand;
}
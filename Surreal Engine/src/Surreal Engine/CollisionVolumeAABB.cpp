//CollisionVolumeAABB

#include "CollisionVolumeAABB.h"
#include "Visualizer.h"
#include "VisualizerCommand.h"
#include "VisualizerCommandFactory.h"
#include "SurrealMathTools.h"
#include "Collidable.h"

CollisionVolumeAABB::CollisionVolumeAABB()
{
	this->World = Matrix(IDENTITY);
	this->CornerMax = Vect(0, 0, 0);
	this->CornerMin = Vect(0, 0, 0);
	this->pCommand = VisualizerCommandFactory::CreateCommand(World, Vect(0, 0, 0), Collidable::VolumeType::AABB);
}

CollisionVolumeAABB::~CollisionVolumeAABB()
{
	VisualizerCommandFactory::RecycleCommand(pCommand);
}

void CollisionVolumeAABB::ComputeData(Model* mod, const Matrix& mat)
{
	StandardVertex* pVert = mod->GetVertexArray(); 
	Vect currVect = pVert[0].Pos * mat;
	int numVect = mod->GetVertexNum();

	Vect v = currVect;
	float minX = currVect.X();
	float maxX = currVect.X();

	float minY = currVect.Y();
	float maxY = currVect.Y();

	float minZ = currVect.Z();
	float maxZ = currVect.Z();

	float x, y, z; 

	for (int i = 0; i < numVect; i++)
	{
		currVect = pVert[0].Pos * mat;
		x = currVect.X();
		y = currVect.Y();
		z = currVect.Z();

		if (x < minX)
			minX = x;
		else if (x > maxX)
			maxX = x; 

		if (y < minY)
			minY = y;
		else if (y > maxY)
			maxY = y;

		if (z < minZ)
			minZ = z;
		else if (z > maxZ)
			maxZ = z; 
	}

	CornerMin = Vect(minX, minY, minZ); 
	CornerMax = Vect(maxX, maxY, maxZ); 

	WorldCenter = (0.5f * (CornerMin + CornerMax));
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return SurrealMathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return SurrealMathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return SurrealMathTools::Intersect(*this, other);
}

void CollisionVolumeAABB::DebugView(const Vect& col) const
{
	Visualizer::ShowBox(*this, col);
}

Vect CollisionVolumeAABB::GetMin() const
{
	return this->CornerMin;
}

Vect CollisionVolumeAABB::GetMax() const
{
	return this->CornerMax;
}

Vect CollisionVolumeAABB::GetCenter() const
{
	return WorldCenter;
}

Matrix CollisionVolumeAABB::GetWorld() const
{
	return this->World;
}

Vect CollisionVolumeAABB::GetHalfDiagonal() const
{
	return 0.5f * (CornerMax - CornerMin);
}

float CollisionVolumeAABB::GetScaleSquared() const
{
	return World.get(ROW_0).dot(World.get(ROW_0));
}

VisualizerCommand* CollisionVolumeAABB::GetCommand(Matrix m, Vect c) const
{
	this->pCommand->Update(m, c, Collidable::VolumeType::AABB);
	return this->pCommand;
}

void CollisionVolumeAABB::ComputeData(const CollisionVolumeBSphere& pBSphere)
{
	const Vect center = pBSphere.GetCenter();
	float r = pBSphere.GetRadius();
	const Vect diff = Vect(r, r, r);

	CornerMin.set(center - diff);
	CornerMax.set(center + diff);
}

void CollisionVolumeAABB::ComputeData(CollidableGroup::CollidableCollection& CollideCol)
{
	if (CollideCol.size() > 0)
	{
		ComputeData((*CollideCol.begin())->GetDefaultVolume());
		Vect min = CornerMin;
		Vect max = CornerMax;

		float minX = min.X();
		float maxX = max.X();

		float minY = min.Y();
		float maxY = max.Y();

		float minZ = min.Z();
		float maxZ = max.Z();

		for (Collidable* it : CollideCol)
		{
			ComputeData(it->GetDefaultVolume());
			min = CornerMin;
			max = CornerMax;

			if (min.X() < minX)
				minX = min.X();
			else if (max.X() > maxX)
				maxX = max.X();

			if (min.Y() < minY)
				minY = min.Y();
			else if (max.Y() > maxY)
				maxY = max.Y();

			if (min.Z() < minZ)
				minZ = min.Z();
			else if (max.Z() > maxZ)
				maxZ = max.Z();
		}

		CornerMin.set(minX, minY, minZ);
		CornerMax.set(maxX, maxY, maxZ);
	}
}

void CollisionVolumeAABB::ComputeData(const Vect& min, const Vect& max)
{
	CornerMin = min;
	CornerMax = max;

	World = Matrix(IDENTITY);
	WorldCenter = min + (0.5f * (max - min));
}
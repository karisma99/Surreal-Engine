//SurrealMathTools

#include "SurrealMathTools.h"
#include "CollisionVolumeBSphere.h"
#include "AzulCore.h"

bool SurrealMathTools::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B)
{
	float centerDistance = (B.GetCenter() - A.GetCenter()).magSqr();

	float totalRadii = A.GetRadius() + B.GetRadius();
	totalRadii *= totalRadii;

	if (totalRadii < centerDistance)
		return false;
	else
		return true;
}
//TerrainRectangleArea

#include "TerrainRectangleArea.h"
#include "TerrainObject.h"
#include "SceneManager.h"

TerrainRectangleArea::TerrainRectangleArea(const int _minX, const int _maxX, const int _minZ, const int _maxZ)
{
	minX = _minX; 
	maxX = _maxX; 
	minZ = _minZ; 
	maxZ = _maxZ;

	currX = minX; 
	currZ = minZ; 

	pTerrain = SceneManager::GetCurrentScene()->GetTerrain();
	_begin = pTerrain->GetCellAtIndex(minX, minZ);
	_end = pTerrain->GetCellAtIndex(maxX, maxZ);
}

CollisionVolumeAABB* TerrainRectangleArea::begin()
{
	return this->_begin;
}

CollisionVolumeAABB* TerrainRectangleArea::next()
{
	if (++currX > maxX)
	{
		if (++currZ > maxZ)
		{
			return nullptr;
		}

		currX = minX;
	}

	return pTerrain->GetCellAtIndex(currX, currZ);
}

int TerrainRectangleArea::GetMinI()
{
	return minX;
}

int TerrainRectangleArea::GetMaxI()
{
	return maxX;
}

int TerrainRectangleArea::GetMinJ()
{
	return minZ;
}

int TerrainRectangleArea::GetMaxJ()
{
	return maxZ;
}

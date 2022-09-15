#ifndef _TerrainRectangleArea
#define _TerrainRectangleArea

class TerrainObject;
class CollisionVolumeAABB;

class TerrainRectangleArea
{
public:
	TerrainRectangleArea() = delete;
	TerrainRectangleArea(const int minX, const int maxX, const int minZ, const int maxZ);
	TerrainRectangleArea(const TerrainRectangleArea& c) = delete;
	TerrainRectangleArea& operator = (const TerrainRectangleArea& t) = delete;
	~TerrainRectangleArea() = default;

	CollisionVolumeAABB* begin();
	CollisionVolumeAABB* next();
	int GetMinI();
	int GetMaxI();
	int GetMinJ();
	int GetMaxJ();

private:
	TerrainObject* pTerrain;
	CollisionVolumeAABB* _begin;
	CollisionVolumeAABB* _end;

	int minX; 
	int maxX; 
	int minZ; 
	int maxZ; 

	int currX; 
	int currZ;

};

#endif _TerrainRectangleArea
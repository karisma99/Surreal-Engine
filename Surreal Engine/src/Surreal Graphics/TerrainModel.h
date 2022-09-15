#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <d3d11.h>

// forward declaration
class Model;
class CollisionVolumeAABB;
class Collidable;

class TerrainModel : public Align16
{
public:
	TerrainModel() = delete;
	TerrainModel(LPCWSTR heightmapFile, float vertexNum, float cellSize, float maxheight, float ytrans, int RepeatU, int RepeatV);
	TerrainModel(const TerrainModel&) = delete;
	TerrainModel(TerrainModel&&) = delete;
	TerrainModel& operator=(const TerrainModel&) = delete;
	TerrainModel& operator=(TerrainModel&&) = delete;
	~TerrainModel();

	void Render(ID3D11DeviceContext* context);
	Model* GetModel();
	CollisionVolumeAABB* GetAABBArray();
	Vect* GetNormals();
	CollisionVolumeAABB* GetCellAtPosition(const Vect& pos);
	CollisionVolumeAABB* GetCellAtIndices(int xIndex, int zIndex);
	void GetTriAtPosition(const Vect& pos);
	Vect GetTerrainNormalAtPosition(const Vect& pos);
	Vect GetCellCenterAtPosition(const Vect& pos);

	void Intersect(Collidable* col);

private:
	Model* pModTerrain;
	Vect* pNormals;

	Vect cellOrigin;
	float cellSize;
	int cellsPerSide;
	int cellNum;
	CollisionVolumeAABB* cellAABBs;

	int GetVertexIndex(int sideLength, int i, int j);
	int GetTexelIndex(size_t pixelWidth, int sideLength, int i, int j);
};

#endif _TerrainModel
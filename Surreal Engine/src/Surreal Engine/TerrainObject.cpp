//TerrainObject

#include "TerrainObject.h"
#include "TextureManager.h"
#include <codecvt>
#include "Collidable.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "Visualizer.h"
#include "Matrix.h"
#include "Colors.h"
#include "TerrainRectangleArea.h"


TerrainObject::TerrainObject()
{
	pGObj_TexFlat = nullptr; 
	pGObj_ColorFlat = nullptr; 
	pAABB = nullptr;
	normalsArray = nullptr;
	pModel = nullptr;
}

TerrainObject::TerrainObject(const std::string& heightmapFile, const std::string& textureKey, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	std::wstring ExpectedPath = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(heightmapFile);
	LPCWSTR myPath = ExpectedPath.c_str();
	float cellSize = 10.0f;
	pModel = new TerrainModel(myPath, len, cellSize, maxheight, -ytrans, RepeatU, RepeatV);

	pGObj_TexFlat = new GraphicsObject_TextureFlat(pModel->GetModel(), TextureManager::Get(textureKey));
	//pGObj_TexFlat->SetWorld(Matrix(TRANS, 0, ytrans, 0));
	pGObj_TexFlat->SetWorld(Matrix(IDENTITY));

	pGObj_ColorFlat = new GraphicsObject_ColorFlat(pModel->GetModel(), Color::Blue);
	pGObj_ColorFlat->SetWorld(Matrix(IDENTITY));

	pAABB = pModel->GetAABBArray();
	normalsArray = pModel->GetNormals();
}

TerrainObject::~TerrainObject()
{
	delete pGObj_TexFlat;
	delete pGObj_ColorFlat;
	delete pModel;
}

void TerrainObject::Draw()
{
	pGObj_TexFlat->Render();
}

CollisionVolumeAABB* TerrainObject::GetCellAtIndex(int i, int j)
{
	return pModel->GetCellAtIndices(i, j);
}

void TerrainObject::Intersect(Collidable* col)
{
	pModel->Intersect(col);
}

Vect TerrainObject::GetTerrainNormalAtPosition(const Vect& pos)
{
	return pModel->GetTerrainNormalAtPosition(pos);

}

Vect TerrainObject::GetCellCenterAtPosition(const Vect& pos)
{
	return pModel->GetCellCenterAtPosition(pos);

}

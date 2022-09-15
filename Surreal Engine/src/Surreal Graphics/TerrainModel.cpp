#include "TerrainModel.h"
#include "Model.h"
#include "DirectXTex.h"
#include <assert.h>
#include "Surreal Engine/CollisionVolumeAABB.h"
#include "Colors.h"
#include "Surreal Engine/Collidable.h"
#include "Surreal Engine/CollisionVolumeBSphere.h"
#include <cmath>
#include "Surreal Engine/Visualizer.h"

TerrainModel::TerrainModel(LPCWSTR heightmapFile, float len, float _cellSize, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	size_t side = hgtmap->height;	// the image should be square
	size_t pixel_width = 4;			// 4 bytes RGBA per pixel

	cellSize = _cellSize;

	int vertNum = (int)(len * len);
	StandardVertex* verts = new StandardVertex[vertNum];
	pNormals = new Vect[vertNum];

	int triNum = (int)((len - 1) * (len - 1) * 2);
	TriangleByIndex* tris = new TriangleByIndex[triNum];

	float urep = RepeatU / (len - 1);
	float vrep = RepeatV / (len - 1);

	float scale = (len / side);
	float yScale = (255 / maxheight);

	// setting up vertices
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			int texelIndex = GetTexelIndex(pixel_width, side, (int)(i / scale), (int)(j / scale));
			float x = (i - len / 2) * _cellSize;
			float y = hgtmap->pixels[texelIndex] / yScale + ytrans;
			float z = (j - len / 2) * _cellSize;
			verts[GetVertexIndex((int)len, i, j)].set(x, y, z, urep * i, vrep * j);
		}
	}

	cellOrigin = verts[GetVertexIndex((int)len, 0, 0)].Pos;

	// computing normals
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			// check to make sure we skip edge vertices
			if (i != 0 && i != len - 1 && j != 0 && j != len - 1)
			{
				// center
				StandardVertex* center = &verts[GetVertexIndex((int)len, i, j)];
				// left
				StandardVertex* left = &verts[GetVertexIndex((int)len, i - 1, j)];
				// right
				StandardVertex* right = &verts[GetVertexIndex((int)len, i + 1, j)];
				// up
				StandardVertex* up = &verts[GetVertexIndex((int)len, i, j + 1)];
				// down
				StandardVertex* down = &verts[GetVertexIndex((int)len, i, j - 1)];
				// down diagonal
				StandardVertex* downDiag = &verts[GetVertexIndex((int)len, i - 1, j - 1)];
				// up diagonal
				StandardVertex* upDiag = &verts[GetVertexIndex((int)len, i + 1, j + 1)];

				// left side face
				Vect edge1 = left->Pos - center->Pos;
				Vect helperEdge = up->Pos - center->Pos;
				edge1 = edge1.cross(helperEdge).getNorm();
				// right side face
				Vect edge2 = right->Pos - center->Pos;
				helperEdge = down->Pos - center->Pos;
				edge2 = edge2.cross(helperEdge).getNorm();
				// bottom left corner face
				Vect edge3 = left->Pos - center->Pos;
				helperEdge = downDiag->Pos - center->Pos;
				edge3 = edge3.cross(helperEdge).getNorm();
				// bottom right corner face
				Vect edge4 = down->Pos - center->Pos;
				helperEdge = downDiag->Pos - center->Pos;
				edge4 = edge4.cross(helperEdge).getNorm();
				// top left corner face
				Vect edge5 = up->Pos - center->Pos;
				helperEdge = upDiag->Pos - center->Pos;
				edge5 = edge5.cross(helperEdge).getNorm();
				// top right corner face
				Vect edge6 = right->Pos - center->Pos;
				helperEdge = upDiag->Pos - center->Pos;
				edge6 = edge6.cross(helperEdge).getNorm();

				helperEdge = Vect((edge1.X() + edge2.X() + edge3.X() + edge4.X() + edge5.X() + edge6.X()) / 6,
					(edge1.Y() + edge2.Y() + edge3.Y() + edge4.Y() + edge5.Y() + edge6.Y()) / 6,
					(edge1.Z() + edge2.Z() + edge3.Z() + edge4.Z() + edge5.Z() + edge6.Z()) / 6);

				verts[GetVertexIndex((int)len, i, j)].normal = helperEdge;
				pNormals[GetVertexIndex((int)len, i, j)] = helperEdge;

			}
			else
			{
				verts[GetVertexIndex((int)len, i, j)].normal = Vect(0, 0, 0);
				pNormals[GetVertexIndex((int)len, i, j)] = Vect(0, 0, 0);
			}
				
		}
	}

	cellsPerSide = (int)(len - 1);
	cellNum = (int)((len - 1) * (len - 1));
	cellAABBs = new CollisionVolumeAABB[cellNum];
	int AABBcounter = 0;

	// setting up triangles and aabb array
	int triangleIndex = 0;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1; j++)
		{
			// indices for tri / aabb corners
			int corner0 = i + (int)(len * j) + 1;
			int corner1 = i + (int)len + (int)(len * j);
			int corner2 = i + (int)(len * j);
			int corner3 = i + (int)len + (int)(len * j) + 1;

			// setting tris
			tris[triangleIndex++].set(corner0, corner1, corner2);
			tris[triangleIndex++].set(corner0, corner3, corner1);

			// finding min and max for aabb
			Vect min = verts[corner0].Pos;
			Vect max = verts[corner0].Pos;

			// corner 1
			if (verts[corner1].Pos.X() < min.X()) // x
				min.X() = verts[corner1].Pos.X();
			if (verts[corner1].Pos.X() > max.X())
				max.X() = verts[corner1].Pos.X();
			if (verts[corner1].Pos.Y() < min.Y()) // y
				min.Y() = verts[corner1].Pos.Y();
			if (verts[corner1].Pos.Y() > max.Y())
				max.Y() = verts[corner1].Pos.Y();
			if (verts[corner1].Pos.Z() < min.Z()) // z
				min.Z() = verts[corner1].Pos.Z();
			if (verts[corner1].Pos.Z() > max.Z())
				max.Z() = verts[corner1].Pos.Z();
			// corner 2
			if (verts[corner2].Pos.X() < min.X()) // x
				min.X() = verts[corner2].Pos.X();
			if (verts[corner2].Pos.X() > max.X())
				max.X() = verts[corner2].Pos.X();
			if (verts[corner2].Pos.Y() < min.Y()) // y
				min.Y() = verts[corner2].Pos.Y();
			if (verts[corner2].Pos.Y() > max.Y())
				max.Y() = verts[corner2].Pos.Y();
			if (verts[corner2].Pos.Z() < min.Z()) // z
				min.Z() = verts[corner2].Pos.Z();
			if (verts[corner2].Pos.Z() > max.Z())
				max.Z() = verts[corner2].Pos.Z();
			// corner 3
			if (verts[corner3].Pos.X() < min.X()) // x
				min.X() = verts[corner3].Pos.X();
			if (verts[corner3].Pos.X() > max.X())
				max.X() = verts[corner3].Pos.X();
			if (verts[corner3].Pos.Y() < min.Y()) // y
				min.Y() = verts[corner3].Pos.Y();
			if (verts[corner3].Pos.Y() > max.Y())
				max.Y() = verts[corner3].Pos.Y();
			if (verts[corner3].Pos.Z() < min.Z()) // z
				min.Z() = verts[corner3].Pos.Z();
			if (verts[corner3].Pos.Z() > max.Z())
				max.Z() = verts[corner3].Pos.Z();

			cellAABBs[AABBcounter].ComputeData(min, max);
			AABBcounter++;
		}
	}

	pModTerrain = new Model(verts, vertNum, tris, triNum);
	delete[] verts;
	delete[] tris;
}

int TerrainModel::GetVertexIndex(int sideLength, int i, int j)
{
	return j * sideLength + i;
}

int TerrainModel::GetTexelIndex(size_t pixelWidth, int sideLength, int i, int j)
{
	return pixelWidth * (j * sideLength + i);
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}

void TerrainModel::Intersect(Collidable* col)
{
	Vect radius = Vect(col->GetDefaultVolume().GetRadius(), col->GetDefaultVolume().GetRadius(), col->GetDefaultVolume().GetRadius());
	Vect min = col->GetDefaultVolume().GetCenter() + -radius;
	Vect max = col->GetDefaultVolume().GetCenter() + radius;

	int minX = (int)std::floor((min.X() - cellOrigin.X()) / cellSize);
	int minZ = (int)std::floor((min.Z() - cellOrigin.Z()) / cellSize);

	// correct x in case outside of terrain boundaries
	if (minX < 0)
		minX = 0;
	else if (minX > cellsPerSide - 1)
		minX = cellsPerSide - 1;
	// correct z in case outside of terrain boundaries
	if (minZ < 0)
		minZ = 0;
	else if (minZ > cellsPerSide - 1)
		minZ = cellsPerSide - 1;

	int maxX = (int)std::ceil((max.X() - cellOrigin.X()) / cellSize);
	int maxZ = (int)std::ceil((max.Z() - cellOrigin.Z()) / cellSize);

	// correct x in case outside of terrain boundaries
	if (maxX < 0)
		maxX = 0;
	else if (maxX > cellsPerSide - 1)
		maxX = cellsPerSide - 1;
	// correct z in case outside of terrain boundaries
	if (maxZ < 0)
		maxZ = 0;
	else if (maxZ > cellsPerSide - 1)
		maxZ = cellsPerSide - 1;

	for (int i = minX; i < maxX; i++)
	{
		for (int j = minZ; j < maxZ; j++)
		{
			CollisionVolumeAABB* cell = GetCellAtIndices(i, j);
			if (cell->IntersectAccept(col->GetDefaultVolume()))
			{
				if (cell->IntersectAccept(col->GetCollisionVolume()))
				{
					//Callback
					col->CollisionTerrain();
					cell->DebugView(Colors::Red);
					Visualizer::ShowCollisionVolume(col->GetCollisionVolume(), Colors::Red);
				}
				else
				{
					cell->DebugView(Colors::Blue);
					Visualizer::ShowCollisionVolume(col->GetCollisionVolume(), Colors::Blue);
				}
			}
			else
			{
				cell->DebugView(Colors::Yellow);
				Visualizer::ShowSphere(col->GetDefaultVolume(), Colors::Yellow);
			}
				
		}
	}
}

Model* TerrainModel::GetModel()
{
	return pModTerrain;
}

CollisionVolumeAABB* TerrainModel::GetCellAtIndices(int xIndex, int zIndex)
{
	return &cellAABBs[xIndex * cellsPerSide + zIndex];
}

CollisionVolumeAABB* TerrainModel::GetCellAtPosition(const Vect& pos)
{
	int x = (int)((pos.X() - cellOrigin.X()) / cellSize);
	int z = (int)((pos.Z() - cellOrigin.Z()) / cellSize);

	if (x < 0)
		x = 0;
	else if (x > cellsPerSide - 1)
		x = cellsPerSide - 1;
	if (z < 0)
		z = 0;
	else if (z > cellsPerSide - 1)
		z = cellsPerSide - 1;

	return GetCellAtIndices(x, z);
}

void TerrainModel::GetTriAtPosition(const Vect& pos)
{
	int x = (int)((pos.X() - cellOrigin.X()) / cellSize);
	int z = (int)((pos.Z() - cellOrigin.Z()) / cellSize);

	if (x < 0)
		x = 0;
	else if (x > cellsPerSide - 1)
		x = cellsPerSide - 1;
	if (z < 0)
		z = 0;
	else if (z > cellsPerSide - 1)
		z = cellsPerSide - 1;

	int verticesPerSide = cellsPerSide + 1;

	StandardVertex* topRightCorner = &pModTerrain->GetVertexArray()[z + (verticesPerSide * x) + 1];
	StandardVertex* bottomLeftCorner = &pModTerrain->GetVertexArray()[z + verticesPerSide + (verticesPerSide * x)];
	StandardVertex* bottomRightCorner = &pModTerrain->GetVertexArray()[z + (verticesPerSide * x)];
	StandardVertex* topLeftCorner = &pModTerrain->GetVertexArray()[z + verticesPerSide + (verticesPerSide * x) + 1];

	Vect divider = pos - bottomLeftCorner->Pos;
	StandardVertex* pointA, * pointB, * pointC;

	if (-divider.Z() < divider.X())
	{
		pointA = bottomLeftCorner;
		pointB = topLeftCorner;
		pointC = topRightCorner;
	}
	else 
	{
		pointA = bottomLeftCorner;
		pointB = bottomRightCorner;
		pointC = topRightCorner;
	}

	//  --- barycentric calculations ---

	Vect pointAFlat(pointA->Pos.X(), 0, pointA->Pos.Z());
	Vect pointBFlat(pointB->Pos.X(), 0, pointB->Pos.Z());
	Vect pointCFlat(pointC->Pos.X(), 0, pointC->Pos.Z());
	Vect posFlat(pos.X(), 0, pos.Z());

	Vect v0 = pointBFlat - pointAFlat;
	Vect v1 = pointC->Pos - pointBFlat;
	Vect v2 = posFlat - pointAFlat;

	float a = v0.dot(v0);
	float b = v1.dot(v0);
	float c = v1.dot(v1);
	float d = v2.dot(v0);
	float e = v2.dot(v1);

	float beta = (d * c - b * e) / (a * c - b * b);
	float gamma = (a * e - d * b) / (a * c - b * b);

	float yVal = pointA->Pos.Y() + beta * (pointB->Pos.Y() - pointA->Pos.Y()) + gamma * (pointC->Pos.Y() - pointB->Pos.Y());
	
	Vect point(pos.X(), yVal, pos.Z());

	Vect normal = pointA->normal + beta * (pointB->normal - pointA->normal) + gamma * (pointC->normal - pointB->normal);
}

CollisionVolumeAABB* TerrainModel::GetAABBArray()
{
	return this->cellAABBs;
}

Vect* TerrainModel::GetNormals()
{
	return this->pNormals;
}

Vect TerrainModel::GetTerrainNormalAtPosition(const Vect& pos)
{
	int i = (int)((pos.X() - cellOrigin.X()) / cellSize);
	int j = (int)((pos.Z() - cellOrigin.Z()) / cellSize);

	return this->pNormals[i * cellsPerSide + j];
}

Vect TerrainModel::GetCellCenterAtPosition(const Vect& pos)
{
	return GetCellAtPosition(pos)->GetCenter();
}



TerrainModel::~TerrainModel()
{
	delete pModTerrain;
	delete[] cellAABBs;
	delete[] pNormals;
}
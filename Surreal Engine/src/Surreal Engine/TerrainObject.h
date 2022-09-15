#ifndef _TerrainObject
#define _TerrainObject

#include "Drawable.h"

class Vect; 
class TerrainModel; 
class GraphicsObject_TextureFlat;
class GraphicsObject_ColorFlat;
class CollisionVolumeAABB; 
class CollisionVolumeBSphere; 
class Collidable;
class TerrainRectangleArea;

class TerrainObject : public Drawable
{
public:
	TerrainObject();
	TerrainObject(const std::string& heightmapFile, const std::string& textureKey, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);
	TerrainObject(const TerrainObject& c) = delete;
	TerrainObject& operator = (const TerrainObject& t) = delete;
	~TerrainObject();

	virtual void Draw();

	void Intersect(Collidable* col);

	Vect GetTerrainNormalAtPosition(const Vect& pos);
	Vect GetCellCenterAtPosition(const Vect& pos);
	CollisionVolumeAABB* GetCellAtIndex(int i, int j);

	//TerrainRectangleArea GetCollisionArea(const CollisionVolumeBSphere& bsphere);


private:
	GraphicsObject_TextureFlat* pGObj_TexFlat; 
	GraphicsObject_ColorFlat* pGObj_ColorFlat; 

	TerrainModel* pModel;
	CollisionVolumeAABB* pAABB; 
	Vect* normalsArray;


};

#endif _TerrainObject
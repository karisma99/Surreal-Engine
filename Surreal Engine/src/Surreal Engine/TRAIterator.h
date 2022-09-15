#ifndef _TRAIterator
#define _TRAIterator

#include "Vect.h"

class TerrainRectangleArea;
class CollisionVolumeAABB;

class TRAIterator
{
public:
	TRAIterator() = default;
	TRAIterator(int i, int j, TerrainRectangleArea* p);
	TRAIterator(const TRAIterator& c);
	TRAIterator& operator = (const TRAIterator& t);
	~TRAIterator() = default;

	bool operator != (const TRAIterator&);
	TRAIterator& operator++ ();
	TRAIterator operator+(int x);

	CollisionVolumeAABB* GetCellAABB();

	void ShowCell(const Vect& color);

private:
	TerrainRectangleArea* pRect;

	int i;
	int j;

};

#endif _TRAIterator
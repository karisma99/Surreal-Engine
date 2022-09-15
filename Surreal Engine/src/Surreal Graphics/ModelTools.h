#ifndef _ModelTools
#define _ModelTools

#include "Vect.h"

struct StandardVertex;
struct TriangleByIndex;

class ModelTools
{

public:
	static void Create2dUnitBox(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri);
	static void CreateUnitBox(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri);
	static void CreateUnitBoxRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri);
	static void CreateUnitBoxSixFaceTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri);
	static void CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri);
	static void CreateUnitPyramidRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri);
	static void CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri);
};



#endif _ModelTools
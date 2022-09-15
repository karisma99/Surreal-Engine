#include "Skybox.h"
#include "Model.h"

Skybox::Skybox(float size)
{
	int nverts = 24;
	StandardVertex* pVerts = new StandardVertex[nverts];
	int ntri = 12;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	// Setting up faces
		// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(size, size, size, 0.5f, 0.333f, 0, 0, 0);
	pVerts[vind + 1].set(-size, size, size, 0.75f, 0.333f, 0, 0, 0);
	pVerts[vind + 2].set(-size, -size, size, 0.75f, 0.667f, 0, 0, 0);
	pVerts[vind + 3].set(size, -size, size, 0.5f, 0.65f, 0, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(size, size, -size, 0.25f, 0.333f, 0, 0, 0);
	pVerts[vind + 1].set(-size, size, -size, 0.0f, 0.333f, 0, 0, 0);
	pVerts[vind + 2].set(-size, -size, -size, 0, 0.66f, 0, 0, 0);
	pVerts[vind + 3].set(size, -size, -size, 0.25f, 0.66f, 0, 0, 0);
	pTriList[tind].set(vind + 0, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind + 0, vind + 2, vind + 3);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(size, size, -size, 0.25f, 0.333f, 0, 0, 0);
	pVerts[vind + 1].set(size, size, size, 0.5f, 0.333f, 0, 0, 0);
	pVerts[vind + 2].set(size, -size, size, 0.5f, 0.65f, 0, 0, 0);
	pVerts[vind + 3].set(size, -size, -size, 0.25f, 0.66f, 0, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-size, size, size, 0.75f, 0.335f, 0, 0, 0);
	pVerts[vind + 1].set(-size, size, -size, 1.0f, 0.335f, 0, 0, 0);
	pVerts[vind + 2].set(-size, -size, -size, 1.0f, 0.665f, 0, 0, 0);
	pVerts[vind + 3].set(-size, -size, size, 0.75f, 0.665f, 0, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(size, size, -size, 0.5f, 0.0, 0, 0, 0);
	pVerts[vind + 1].set(-size, size, -size, 0.75f, 0.0, 0, 0, 0);
	pVerts[vind + 2].set(-size, size, size, 0.75f, 0.333f, 0, 0, 0);
	pVerts[vind + 3].set(size, size, size, 0.5f, 0.333f, 0, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(size, -size, size, 0.5f, 0.6667f, 0, 0, 0);
	pVerts[vind + 1].set(-size, -size, size, 0.72f, 0.666f, 0, 0, 0);
	pVerts[vind + 2].set(-size, -size, -size, 0.72f, 0.99f, 0, 0, 0);
	pVerts[vind + 3].set(size, -size, -size, 0.5f, 0.99f, 0, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	pModel = new Model(pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;
}

Skybox::~Skybox()
{
	delete pModel;
}

void Skybox::Render(ID3D11DeviceContext* context)
{
	pModel->SetToContext(context);
	pModel->Render(context);
}

Model* Skybox::GetModel()
{
	return pModel;
}
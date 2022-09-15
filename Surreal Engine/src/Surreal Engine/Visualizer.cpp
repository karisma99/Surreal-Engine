//Visualizer

#include "Visualizer.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "VisualizerCommand.h"
#include "Colors.h"
#include "VisualizerCommandFactory.h"
#include "SceneManager.h"

Visualizer* Visualizer::ptrInstance = nullptr;
Vect Visualizer::DEFAULT_COLOR = Color::Black;

Visualizer::Visualizer()
{
	WFUnitSphere = new GraphicsObject_ColorFlat(ModelManager::Get("Sphere"), DEFAULT_COLOR);
	WFUnitBox= new GraphicsObject_ColorFlat(ModelManager::Get("UnitBox"), DEFAULT_COLOR);

}

void Visualizer::privDelete()
{
	VisualizerCommandFactory::Delete();

	delete WFUnitSphere;
	WFUnitSphere = nullptr;

	delete WFUnitBox;
	WFUnitBox = nullptr;

	delete ptrInstance;
	ptrInstance = nullptr;
}

void Visualizer::privShowSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	Vect size = S.GetRadius() * Vect(1, 1, 1);
	Vect pos = S.GetCenter(); 
	Matrix world = Matrix(SCALE, size) * Matrix(TRANS, pos);
	VisualCommandList.insert(VisualCommandList.end(), S.GetCommand(world, col));
}

void Visualizer::privShowBox(const CollisionVolumeAABB& B, const Vect& col)
{
	Matrix world = Matrix(SCALE, B.GetMax() - B.GetMin())  * Matrix(TRANS, 0.5f * (B.GetMax() + B.GetMin()));

	VisualCommandList.insert(VisualCommandList.end(), B.GetCommand(world, col));
}

void Visualizer::privShowBox(const CollisionVolumeOBB& B, const Vect& col)
{
	Matrix world = Matrix(SCALE, B.GetMax() - B.GetMin()) * Matrix(TRANS, 0.5f * (B.GetMax() + B.GetMin()));
	world *= B.GetWorld();
	VisualCommandList.insert(VisualCommandList.end(), B.GetCommand(world, col));
}

void Visualizer::privShowCollisionVolume(const CollisionVolume& c, const Vect& col)
{
	c.DebugView(col);
}

void Visualizer::privRenderSphere(Matrix& S, const Vect& col)
{
	WFUnitSphere->SetWorld(S);
	WFUnitSphere->SetColor(col);
	WFUnitSphere->RenderWireframe();
}

void Visualizer::privRenderBox(Matrix& B, const Vect& col)
{
	WFUnitBox->SetWorld(B);
	WFUnitBox->SetColor(col);
	WFUnitBox->RenderWireframe();
}

void Visualizer::privVisualizeAll()
{
	for (auto& it : VisualCommandList)
	{
		it->Execute();
	}

	VisualCommandList.clear();
}


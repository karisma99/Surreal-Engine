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
	WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ConstantColor"), DEFAULT_COLOR);
}

void Visualizer::privDelete()
{
	VisualizerCommandFactory::Delete();

	delete WFUnitSphere;
	WFUnitSphere = nullptr;

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

void Visualizer::privRenderSphere(Matrix& S, const Vect& col)
{
	WFUnitSphere->SetWorld(S);
	WFUnitSphere->SetColor(col);
	WFUnitSphere->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

void Visualizer::privVisualizeAll()
{
	for (auto& it : VisualCommandList)
	{
		it->Execute();
	}

	VisualCommandList.clear();
}


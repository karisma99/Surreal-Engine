// Visualizer

#ifndef _Visualizer
#define _Visualizer

#include <list>
#include "Vect.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "CollisionVolumeBSphere.h"

class VisualizerCommand; 

class Visualizer
{
private:

	friend class VisualizerAttorney;

	static Visualizer* ptrInstance;

	Visualizer();
	Visualizer(const Visualizer& c) = delete;
	Visualizer& operator = (const Visualizer& t) = delete;
	~Visualizer() = default;

	static Visualizer& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new Visualizer;
		return *ptrInstance;
	};

	using VisualizerCommandCol = std::list<VisualizerCommand*>;
	VisualizerCommandCol VisualCommandList; 

public:
	static void ShowSphere(const CollisionVolumeBSphere& S, const Vect& V = DEFAULT_COLOR) { Instance().privShowSphere(S, V); };

private:

	void privDelete(); 
	static void Delete() { Instance().privDelete(); };

	void privVisualizeAll(); 
	static void VisualizeAll() { Instance().privVisualizeAll(); };

	void privRenderSphere(Matrix& S, const Vect& col);
	static void RenderSphere(Matrix& S, const Vect& col) { Instance().privRenderSphere(S, col); };

	void privShowSphere(const CollisionVolumeBSphere& S, const Vect& V); 

	static Vect DEFAULT_COLOR; 
	GraphicsObject_WireframeConstantColor* WFUnitSphere; 

};

#endif _Visualizer
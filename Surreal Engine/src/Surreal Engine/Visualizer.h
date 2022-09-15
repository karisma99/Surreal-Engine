// Visualizer

#ifndef _Visualizer
#define _Visualizer

#include <list>
#include "Vect.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

class VisualizerCommand; 
class GraphicsObject_ColorFlat;

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
	static void ShowBox(const CollisionVolumeAABB& B, const Vect& V = DEFAULT_COLOR) { Instance().privShowBox(B, V); };
	static void ShowBox(const CollisionVolumeOBB& B, const Vect& V = DEFAULT_COLOR) { Instance().privShowBox(B, V); };
	static void ShowCollisionVolume(const CollisionVolume& c, const Vect& col = DEFAULT_COLOR) { Instance().privShowCollisionVolume(c, col); };

private:

	void privDelete(); 
	static void Delete() { Instance().privDelete(); };

	void privVisualizeAll(); 
	static void VisualizeAll() { Instance().privVisualizeAll(); };

	void privRenderSphere(Matrix& S, const Vect& col);
	static void RenderSphere(Matrix& S, const Vect& col) { Instance().privRenderSphere(S, col); };

	void privRenderBox(Matrix& B, const Vect& col);
	static void RenderBox(Matrix& B, const Vect& col) { Instance().privRenderBox(B, col); };

	void privShowSphere(const CollisionVolumeBSphere& S, const Vect& V); 
	void privShowBox(const CollisionVolumeAABB& B, const Vect& V);
	void privShowBox(const CollisionVolumeOBB& B, const Vect& V);
	void privShowCollisionVolume(const CollisionVolume& S, const Vect& V); 

	static Vect DEFAULT_COLOR; 
	GraphicsObject_ColorFlat* WFUnitSphere;
	GraphicsObject_ColorFlat* WFUnitBox;

};

#endif _Visualizer
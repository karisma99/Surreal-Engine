#ifndef _VisualizerAttorney
#define _VisualizerAttorney

#include "Visualizer.h"

class VisualizerAttorney
{
public:
	class GameLoop
	{
		friend class Surreal;

	private:
		static void Delete() { Visualizer::Delete(); }
		static void VisualizeAll() { Visualizer::VisualizeAll(); }
	};

public:
	class Callback
	{
		friend class VisualizerCommand;

	private:
		static void RenderSphere(Matrix m, Vect c) { Visualizer::RenderSphere(m, c); }
		static void RenderBox(Matrix m, Vect c) { Visualizer::RenderBox(m, c); }
	};
};

#endif _VisualizerAttorney
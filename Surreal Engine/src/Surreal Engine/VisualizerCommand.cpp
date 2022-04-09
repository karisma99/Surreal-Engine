//VisualizerCommand

#include "VisualizerCommand.h"
#include "VisualizerAttorney.h"


VisualizerCommand::VisualizerCommand(Matrix m, Vect c)
{
	matrix = m; 
	color = c;
}

void VisualizerCommand::Execute()
{
	VisualizerAttorney::Callback::RenderSphere(matrix, color);
}

void VisualizerCommand::Update(Matrix m, Vect c)
{
	matrix = m; 
	color = c;
}
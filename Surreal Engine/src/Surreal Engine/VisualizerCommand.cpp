//VisualizerCommand

#include "VisualizerCommand.h"
#include "VisualizerAttorney.h"


VisualizerCommand::VisualizerCommand(Matrix m, Vect c, Collidable::VolumeType vol)
{
	matrix = m; 
	color = c;
	type = vol;
}

void VisualizerCommand::Execute()
{
	if(type == Collidable::VolumeType::BSPHERE)
		VisualizerAttorney::Callback::RenderSphere(matrix, color);
	else if (type == Collidable::VolumeType::AABB || type == Collidable::VolumeType::OBB)
		VisualizerAttorney::Callback::RenderBox(matrix, color);
}

void VisualizerCommand::Update(Matrix m, Vect c, Collidable::VolumeType vol)
{
	matrix = m; 
	color = c;
	type = vol;
}
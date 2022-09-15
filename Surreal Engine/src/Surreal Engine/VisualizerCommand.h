#ifndef _VisualizerCommand
#define _VisualizerCommand

#include "VisualizerCommandBase.h"
#include "Matrix.h"
#include "Vect.h"
#include "Collidable.h"

class VisualizerCommand : public VisualizerCommandBase
{
public:
	VisualizerCommand() = default;
	VisualizerCommand(Matrix m, Vect c, Collidable::VolumeType vol);
	VisualizerCommand(const VisualizerCommand& c) = delete;
	VisualizerCommand& operator = (const VisualizerCommand& t) = delete;
	virtual ~VisualizerCommand() = default;

	virtual void Execute();

	void Update(Matrix m, Vect c, Collidable::VolumeType vol);

private:

	Matrix matrix; 
	Vect color;
	Collidable::VolumeType type;

};

#endif _VisualizerCommand
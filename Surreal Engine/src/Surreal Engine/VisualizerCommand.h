#ifndef _VisualizerCommand
#define _VisualizerCommand

#include "VisualizerCommandBase.h"
#include "Matrix.h"
#include "Vect.h"

class VisualizerCommand : public VisualizerCommandBase
{
public:
	VisualizerCommand() = default;
	VisualizerCommand(Matrix m, Vect c);
	VisualizerCommand(const VisualizerCommand& c) = delete;
	VisualizerCommand& operator = (const VisualizerCommand& t) = delete;
	~VisualizerCommand() = default;

	virtual void Execute();

	void Update(Matrix m, Vect c);

private:

	Matrix matrix; 
	Vect color;

};

#endif _VisualizerCommand
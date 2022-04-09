#ifndef _VisualizerCommandBase
#define _VisualizerCommandBase

class VisualizerCommandBase
{
public:
	VisualizerCommandBase() = default;
	VisualizerCommandBase(const VisualizerCommandBase& c) = delete;
	VisualizerCommandBase& operator = (const VisualizerCommandBase& t) = delete;
	virtual ~VisualizerCommandBase() = default;

	virtual void Execute() { };
private:

};

#endif _VisualizerCommandBase

#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand

#include "CommandBase.h"
#include "Drawable.h"

class DrawableManager;

class DrawDeregistrationCommand : public CommandBase
{
public:
	DrawDeregistrationCommand() = default;
	DrawDeregistrationCommand(Drawable* up);
	DrawDeregistrationCommand(const DrawDeregistrationCommand& c) = delete;
	DrawDeregistrationCommand& operator = (const DrawDeregistrationCommand& t) = delete;
	~DrawDeregistrationCommand() = default;

	virtual void Execute();

private:

	Drawable* pDraw;

};

#endif _DrawDeregistrationCommand
#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand

#include "CommandBase.h"
#include "Drawable.h"

class DrawableManager;

class DrawRegistrationCommand : public CommandBase
{
public:
	DrawRegistrationCommand() = default;
	DrawRegistrationCommand(Drawable* up);
	DrawRegistrationCommand(const DrawRegistrationCommand& c) = delete;
	DrawRegistrationCommand& operator = (const DrawRegistrationCommand& t) = delete;
	~DrawRegistrationCommand() = default;

	virtual void Execute();

private:

	Drawable* pDraw;

};

#endif _DrawRegistrationCommand
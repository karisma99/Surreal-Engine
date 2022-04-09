//DrawRegistrationCommand

#include "DrawRegistrationCommand.h"
#include "DrawableAttorney.h"


DrawRegistrationCommand::DrawRegistrationCommand(Drawable* up)
{
	pDraw = up;
}

void DrawRegistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneRegistration(pDraw);
}
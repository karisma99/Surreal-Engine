//DrawDeregistrationCommand

#include "DrawDeregistrationCommand.h"
#include "DrawableAttorney.h"


DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* up)
{
	pDraw = up;
}

void DrawDeregistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneDeregistration(pDraw);
}
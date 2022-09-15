#include "Surreal Engine/Surreal.h"
#include "Surreal Graphics/WindowController.h"

void Surreal::GameInitialize()
{
	// Game Window Device setup
	WindowController::SetWindowName("Surreal Engine");
	WindowController::SetWindowWidthHeight(800, 600);

}
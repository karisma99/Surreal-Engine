#include "Surreal Graphics/WindowController.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// start the game
	try
	{
		WindowController::RunProgram(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
		WindowController::Delete();
	}
	catch (std::string exception)
	{
		Trace::out("%s", exception.c_str());
		return EXIT_FAILURE;
	}

	return 0;
}
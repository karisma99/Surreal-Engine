#include "WindowController.h"
#include <WindowsX.h>
#include "Surreal Engine/SurrealAttorney.h"
#include <assert.h>
#include "../DX Application/Resource.h"
#include "GPUController.h"

WindowController* WindowController::instance = nullptr;

WindowController::WindowController()
    : g_hInst(nullptr),
    cmdShow(0),
    g_hWnd(nullptr),
    windowWidth(800),
    windowHeight(600) // default dimensions
{
}

WindowController::~WindowController()
{
}

int WindowController::NonstaticRunProgram(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Window initialization
    HRESULT hr = InitWindow(hInstance, nCmdShow);
    assert(SUCCEEDED(hr));  // We'll be doing a lot of this...

    // Initialize the engine
    SurrealAttorney::GameLoop::Initialize(g_hWnd);

    // Main message loop and application calls
    // This is how MS/Windows deal with various input/widgets/UI/Menu stuff
    MSG msg = { 0 };
    bool ReadyToExit = false;
    while (!ReadyToExit)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            ReadyToExit = ReadyToExit || (msg.message == WM_QUIT);
        }
        SurrealAttorney::GameLoop::Update();
        SurrealAttorney::GameLoop::Draw();
    }

    // Shutting down the engine
    SurrealAttorney::GameLoop::UnloadContent();
    SurrealAttorney::GameLoop::Delete();

    //Shutting down graphics
    GPUController::Delete();

    return (int)msg.wParam;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT WindowController::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDC_TUTORIAL1); 
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "MainlWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // save these so we can use them to set different window dimension later
    g_hInst = hInstance;
    cmdShow = nCmdShow;

    // set up window with our preset dimensions
    RECT rc = { 0, 0, windowWidth, windowHeight };

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    g_hWnd = CreateWindow("MainlWindowClass", "Main Window",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
        nullptr);
    if (!g_hWnd)
        return E_FAIL;

    ShowWindow(g_hWnd, nCmdShow);

    return S_OK;
}

void WindowController::PrivSetWindowWidthHeight(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
    SetWindowPos(g_hWnd, HWND_TOP, 0, 0, w, h, SWP_NOMOVE);
}

void WindowController::PrivSetWindowName(const char* name)
{
    SetWindowText(g_hWnd, name);
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
        // Early exit using ESC key: very useful during development
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            PostQuitMessage(0);
            return 0;
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
        SetCapture(WindowController::Instance().g_hWnd);
        //Window::Instance().g_dxapp->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;

    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
        ReleaseCapture();
        //Window::Instance().g_dxapp->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;

    case WM_MOUSEMOVE:
        //Window::Instance().g_dxapp->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;

    case WM_MOUSEWHEEL:
        //Window::Instance().g_dxapp->OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

bool WindowController::PrivIsKeyPressed(const SURREAL_KEY k)
{
    SHORT key_state = GetAsyncKeyState(k);
    return key_state & 0x08000;
}
#include "Window.h"

Window* window;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//0 is success
	//-1 is to set running to false
	LRESULT result = 0;
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			window->SetRunning(false);
			break;
		}
		case WM_DESTROY:
		{
			window->SetRunning(false);
			break;
		}
		case WM_SIZE:
		{
			window->m_renderer->CreateBuffers(hwnd);
			break;
		}
		default:
		{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
}

Window::Window()
{
	window = this;
	m_running = true;
	m_renderer = new Renderer();
	m_renderer->Initialise();
	Initialise();
}

Window::~Window() { m_running = false; }

bool Window::IsRunning() { return m_running; }

void Window::SetRunning(bool isRunning) { m_running = isRunning; }

void Window::Initialise()
{
	//Create Window Class
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = L"Game Window";
	windowClass.lpfnWndProc = window_callback;

	//Register Class
	RegisterClass(&windowClass);

	//Create Window
	m_window = CreateWindow(windowClass.lpszClassName, L"Arcade Game", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,
		CW_USEDEFAULT, 1280, 720, 0, 0, 0, 0);

	//Creating a Context
	m_context = GetDC(m_window);
}

HWND Window::GetWindow() { return m_window; }
HDC Window::GetWindowContext() { return m_context; }
